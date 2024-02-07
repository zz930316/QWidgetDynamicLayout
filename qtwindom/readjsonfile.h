#ifndef READJSONFILE_H
#define READJSONFILE_H
//#pragma execution_character_set("utf-8")
#include <QString>
#include <vector>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QJsonValue>
#include <parameterclass.h>
using namespace std;


class ReadJsonFile
{
public:
    ReadJsonFile();

    bool load(QString sPath,SystemFileStructure* sysdata);
    bool SaveSystemconfig(QString sPath,SystemFileStructure* sysdata);

private:
    QString GetString(QJsonObject object,QString str);
    int GetInt(QJsonObject object,QString str);
};

#endif // READJSONFILE_H
