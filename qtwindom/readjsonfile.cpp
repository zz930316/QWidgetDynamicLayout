#include "readjsonfile.h"
#pragma execution_character_set("utf-8")
#include <QTextCodec>
#include <QDebug>

ReadJsonFile::ReadJsonFile()
{

}

bool ReadJsonFile::load(QString sPath, SystemFileStructure *sysdata)
{
    QFile sysfile(sPath);
    if(!sysfile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray allData = sysfile.readAll();
    sysfile.close();
    QString msg = QString::fromLocal8Bit(allData.data());

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(msg.toStdString().data(), &jsonError);
    int s = jsonError.error;
    if (jsonError.error != QJsonParseError::NoError){
        return false;
    }
    if (doucment.isArray())
    {
        int arr = doucment.array().size();
        for (int var = 0; var < arr; var++)
        {
            QJsonObject object = doucment.array().at(var).toObject();
            int a =object.size();

            QJsonDocument document;
            document.setObject(object);
            QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
            QString simpjson_str(simpbyte_array);

            QString str = "模块信息";
            if (object.contains(str)) {
                QJsonValue value = object.value("模块信息");
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("图例")) {
                        QJsonValue value = obj.value("图例");
                        if (value.isString()) {
                            sysdata->text.sIcon = value.toString();
                        }
                    }
                    if (obj.contains("坐标"))
                    {
                        QJsonValue value = obj.value("坐标");
                        if (value.isArray()) {
                            QJsonArray array = value.toArray();
                            for (int i = 0; i < array.size(); ++i) {
                                QJsonValue value = array.at(i);
                                if (value.isDouble()) {
                                    sysdata->text.vnPoint.push_back(value.toDouble());
                                }
                            }
                        }
                    }
                }
            }else
            {
                sysdata->item[var].sLabel = GetString(object,"名称");
                sysdata->item[var].sCode = GetString(object,"代号");
                sysdata->item[var].sParameter = GetString(object,"范围");
                sysdata->item[var].sType = GetString(object,"显示");
                sysdata->item[var].nValue = GetString(object,"值");
                sysdata->item[var].sSign = GetString(object,"标记");
            }
        }
    }
    return true;
}

bool ReadJsonFile::SaveSystemconfig(QString sPath, SystemFileStructure *sysdata)
{
    QJsonArray jsonArray; //保存数组数据的JSONArray对象
    QJsonObject jObject;
    QJsonObject jObject2;
    jObject2["图例"] = QJsonValue(sysdata->text.sIcon);
    QJsonArray jArray;
    for (int var = 0; var < sysdata->text.vnPoint.size(); ++var) {
        jArray.insert(var,sysdata->text.vnPoint[var]);
    }
    jObject2["坐标"] = QJsonValue(jArray);
    jObject["模块信息"] = jObject2;
    jsonArray.append(jObject);
    for (int var = 0; var < sizeof(sysdata->item)/sizeof(ModItems); ++var)
    {
        if(!sysdata->item[var].sLabel.isEmpty()) {
            QJsonObject jObject2;
            jObject2["名称"] = QJsonValue(sysdata->item[var].sLabel);
            jObject2["代号"] = QJsonValue(sysdata->item[var].sCode);
            jObject2["范围"] = QJsonValue(sysdata->item[var].sParameter);
            jObject2["显示"] = QJsonValue(sysdata->item[var].sType);
            if(sysdata->item[var].sType.contains("lineedit"))
            {
                jObject2["值"] = QJsonValue(sysdata->item[var].nValue);
            }else{
                jObject2["值"] = QJsonValue(sysdata->item[var].nValue.toInt());
            }
            if(!sysdata->item[var].sSign.isEmpty())
            {
                jObject2["标记"] = QJsonValue(sysdata->item[var].sSign);
            }
            jsonArray.append(jObject2);
        }
    }


    QJsonDocument jsonDoc(jsonArray);
    QByteArray byteArray=jsonDoc.toJson();
    QString text = QString(byteArray);

    QFile file(sPath);
    //坑：记得记录不用QIODevice::Text文件格式就是unix
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream.setCodec("GBK");
        stream << text;
        file.close();
    }


//    QJsonDocument jsonDoc(jsonArray);
//    QByteArray byteArray=jsonDoc.toJson();
////    QString msg = QString::fromLocal8Bit(byteArray.data());

//    QTextCodec* coder = QTextCodec::codecForName ("GB18030");
//    QString string = coder->toUnicode(byteArray);
//    QFile file(sPath);
//    file.open(QIODevice::ReadWrite|QIODevice::Text);
//    file.write(string.toStdString().data());
    return true;
}

QString ReadJsonFile::GetString(QJsonObject object, QString str)
{
    QString svalue = "";
    if (object.contains(str))
    {
        QJsonValue value = object.value(str);
        if (value.isString())
        {
            svalue = value.toString();
        }else if (value.isDouble() ) {
            svalue = QString::number(value.toDouble()) ;
        }
    }
    return svalue;
}

int ReadJsonFile::GetInt(QJsonObject object, QString str)
{
    int nValue = 0;
    if (object.contains(str))
    {
        QJsonValue value = object.value(str);
        if (value.isString())
        {
            nValue = value.toInt();
        }
    }
    return nValue;
}
