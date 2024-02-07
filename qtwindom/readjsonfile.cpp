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

            QString str = "ģ����Ϣ";
            if (object.contains(str)) {
                QJsonValue value = object.value("ģ����Ϣ");
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("ͼ��")) {
                        QJsonValue value = obj.value("ͼ��");
                        if (value.isString()) {
                            sysdata->text.sIcon = value.toString();
                        }
                    }
                    if (obj.contains("����"))
                    {
                        QJsonValue value = obj.value("����");
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
                sysdata->item[var].sLabel = GetString(object,"����");
                sysdata->item[var].sCode = GetString(object,"����");
                sysdata->item[var].sParameter = GetString(object,"��Χ");
                sysdata->item[var].sType = GetString(object,"��ʾ");
                sysdata->item[var].nValue = GetString(object,"ֵ");
                sysdata->item[var].sSign = GetString(object,"���");
            }
        }
    }
    return true;
}

bool ReadJsonFile::SaveSystemconfig(QString sPath, SystemFileStructure *sysdata)
{
    QJsonArray jsonArray; //�����������ݵ�JSONArray����
    QJsonObject jObject;
    QJsonObject jObject2;
    jObject2["ͼ��"] = QJsonValue(sysdata->text.sIcon);
    QJsonArray jArray;
    for (int var = 0; var < sysdata->text.vnPoint.size(); ++var) {
        jArray.insert(var,sysdata->text.vnPoint[var]);
    }
    jObject2["����"] = QJsonValue(jArray);
    jObject["ģ����Ϣ"] = jObject2;
    jsonArray.append(jObject);
    for (int var = 0; var < sizeof(sysdata->item)/sizeof(ModItems); ++var)
    {
        if(!sysdata->item[var].sLabel.isEmpty()) {
            QJsonObject jObject2;
            jObject2["����"] = QJsonValue(sysdata->item[var].sLabel);
            jObject2["����"] = QJsonValue(sysdata->item[var].sCode);
            jObject2["��Χ"] = QJsonValue(sysdata->item[var].sParameter);
            jObject2["��ʾ"] = QJsonValue(sysdata->item[var].sType);
            if(sysdata->item[var].sType.contains("lineedit"))
            {
                jObject2["ֵ"] = QJsonValue(sysdata->item[var].nValue);
            }else{
                jObject2["ֵ"] = QJsonValue(sysdata->item[var].nValue.toInt());
            }
            if(!sysdata->item[var].sSign.isEmpty())
            {
                jObject2["���"] = QJsonValue(sysdata->item[var].sSign);
            }
            jsonArray.append(jObject2);
        }
    }


    QJsonDocument jsonDoc(jsonArray);
    QByteArray byteArray=jsonDoc.toJson();
    QString text = QString(byteArray);

    QFile file(sPath);
    //�ӣ��ǵü�¼����QIODevice::Text�ļ���ʽ����unix
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
