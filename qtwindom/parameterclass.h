#ifndef PARAMETERCLASS_H
#define PARAMETERCLASS_H
#include <QString>
#include <vector>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QJsonValue>
#include <parameterclass.h>
#include <QVBoxLayout>
#include <QMap>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QListView>
using namespace std;



struct ModItems
{
    QString sLabel;
    QString sCode;
    QString sParameter;
    QString sType;
    QString nValue;
    QString sSign;
    ModItems() {
        sLabel = "";
        sCode = "";
        sParameter = "";
        sType = "";
        nValue = "";
        sSign = "";
    }
};

struct ModText
{
    QString sIcon;
    vector<int> vnPoint;
    ModText() {
        sIcon = "";
    }
};

struct SystemFileStructure
{
    QString sName;
    ModText text;
    ModItems item[10];
    SystemFileStructure() {
        sName = "";
    }

};

struct WidgetType
{
    QString sType;
    void * pWidget;
    WidgetType() {
       sType = "";
       pWidget = nullptr;
    }
};


#endif // PARAMETERCLASS_H
