#include "modifyingsystemconfig_uil.h"
#include "ui_modifyingsystemconfig_uil.h"
#include <QDebug>
ModifyingSystemConfig_Uil::ModifyingSystemConfig_Uil(QWidget *parent, SystemFileStructure *systemconfig) :
    QDialog(parent),
    ui(new Ui::ModifyingSystemConfig_Uil)
{
    ui->setupUi(this);
    setWindowTitle(systemconfig->sName);
    m_pSystemconfig = systemconfig;
    UiInit();
    QString sWidgetBoxStyle=QString("QWidget#widget{font-size:14px;color:rgb(255,255,255);border: 0px solid ;"
                                    "background-color: qlineargradient(spread:pad,x1:1, x2:0, y1:0, y2:0,"
                                    "stop: 0 rgba(120,120,120,255),stop: 1 rgba(39,39,39,255));}");
    ui->widget->setStyleSheet(sWidgetBoxStyle);
}

ModifyingSystemConfig_Uil::~ModifyingSystemConfig_Uil()
{
    delete ui;
}

void ModifyingSystemConfig_Uil::soltSave()
{
    GetWidgeItem();
    emit sigSave();
    this->close();
}

void ModifyingSystemConfig_Uil::soltClose()
{
    this->close();
}

void ModifyingSystemConfig_Uil::UiInit()
{
    QString sWidgetBoxStyle=QString("QWidget{background-color:transparent;font-size:14px;color:rgb(255,255,255);border: 0px}");
    if(m_pSystemconfig != nullptr)
    {
        QGridLayout* pGLayout = new QGridLayout();
        for (int var = 0; var < sizeof(m_pSystemconfig->item)/sizeof(ModItems); ++var)
        {
            if(!m_pSystemconfig->item[var].sLabel.isEmpty())
            {
                WidgetType widgettype;
                QLabel * label =new QLabel(ui->widget);
                label->setText(m_pSystemconfig->item[var].sLabel);
                label->setStyleSheet(sWidgetBoxStyle);
                pGLayout->addWidget(label,var,0);
                widgettype.sType = m_pSystemconfig->item[var].sType;
                if(m_pSystemconfig->item[var].sType == "combox")
                {
                    QString sComboBoxStyle=QString("QComboBox{background-color:transparent;color:rgb(186,187,188);width: 25px;height: 25px;"
                                                   "border: 1px solid rgb(144,144,146);font-size:14px;}");

                    QString sComboBoxStyle2=QString("QComboBox{background-color:transparent;color:rgb(186,187,188);width: 25px;height: 25px;"
                                                   "border: 1px solid rgb(144,144,146);font-size:14px;}"
                                                    "QComboBox::drop-down {width: 15px;border-left-width: 0px;}"
                                                    "QComboBox::down-arrow {background-color:rgb(144,144,146);;}"
                                                    "QComboBox::down-arrow:on {background-color:rgb(144,144,146);;}");
                    QComboBox * pcomboBox  = new QComboBox(ui->widget);
                    pcomboBox->setStyleSheet(sComboBoxStyle);
                    QStringList slist = m_pSystemconfig->item[var].sParameter.split(",");
                    for (int var = 0; var < slist.size(); var++) {
                        pcomboBox->addItem(slist[var],var);
                    }
                    pcomboBox->setCurrentIndex(m_pSystemconfig->item[var].nValue.toInt());
                    pGLayout->addWidget(pcomboBox,var,1);
                    widgettype.pWidget = (void *)pcomboBox;
                }else if (m_pSystemconfig->item[var].sType == "lineedit")
                {
                    QString sWidgetBoxStyle=QString("QWidget{height: 25px;background-color:transparent;font-size:14px;color:rgb(255,255,255);border: 1px solid rgb(144,144,146);}");
                    QLineEdit * plineEdit = new QLineEdit(ui->widget);
                    plineEdit->setStyleSheet(sWidgetBoxStyle);
                    plineEdit->setText(m_pSystemconfig->item[var].nValue);
                    pGLayout->addWidget(plineEdit,var,1);
                    widgettype.pWidget = (void *)plineEdit;
                }else if (m_pSystemconfig->item[var].sType == "checkbox")
                {
                    QString sCheckBoxStyle=QString("QCheckBox{background-color:transparent;font-width:bold;border: 0px solid rgb(144,144,146);width: 20px;height: 20px;}"
                                                   "QCheckBox::indicator{width: 20px;height: 20px;color:rgb(144,144,146)}"
                                                   "QCheckBox{font-size: 14px;;}"
                                                   "QCheckBox::indicator:checked { border: 1px solid rgb(144,144,146);image: url(:/new/prefix1/icon/checked.png);}"
                                                   "QCheckBox::indicator:unchecked {border: 1px solid rgb(144,144,146);}");

                    QCheckBox* pcheckBox = new QCheckBox(ui->widget);
                    pcheckBox->setMinimumSize(26,26);
                    pcheckBox->setStyleSheet(sCheckBoxStyle);
                    if(m_pSystemconfig->item[var].nValue == 0){
                        pcheckBox->setCheckState(Qt::Unchecked);
                    }else if (m_pSystemconfig->item[var].nValue == 1) {
                        pcheckBox->setCheckState(Qt::Checked);
                    }
                    pGLayout->addWidget(pcheckBox,var,1);
                    widgettype.pWidget = (void *)pcheckBox;
                }else if (m_pSystemconfig->item[var].sType == "label")
                {
                    QLabel * plabel =new QLabel(ui->widget);
                    plabel->setStyleSheet(sWidgetBoxStyle);
                    plabel->setText(m_pSystemconfig->item[var].nValue);
                    pGLayout->addWidget(plabel,var,1);
                    widgettype.pWidget = (void *)plabel;
                }
                m_mWidgetType[m_pSystemconfig->item[var].sLabel] = widgettype;
            }
        }
        QHBoxLayout* pHLayout = new QHBoxLayout();
        QPushButton * pButton1 = new QPushButton("保存",ui->widget);
        connect(pButton1,SIGNAL(clicked()),this,SLOT(soltSave()));
        QPushButton * pButton2 = new QPushButton("取消",ui->widget);
        connect(pButton2,SIGNAL(clicked()),this,SLOT(soltClose()));
        pButton1->setMinimumHeight(30);
        pButton2->setMinimumHeight(30);
        pHLayout->addWidget(pButton1);
        pHLayout->addWidget(pButton2);

        QVBoxLayout * pVLayout = new QVBoxLayout();
        pVLayout->addLayout(pGLayout);
        pVLayout->addLayout(pHLayout);

        ui->widget->setLayout(pVLayout);
    }

}

void ModifyingSystemConfig_Uil::GetWidgeItem()
{
    QMap<QString,WidgetType>::Iterator iter = m_mWidgetType.begin();
    for (iter; iter != m_mWidgetType.end(); iter++) {
        QString str = iter.key();
        WidgetType widgettype = iter.value();
        for (int var = 0; var < sizeof(m_pSystemconfig->item)/sizeof(ModItems); ++var)
        {
            QString sLabel = m_pSystemconfig->item[var].sLabel;
            QString ss = widgettype.sType;
            if(widgettype.sType == "combox" && str== sLabel)
            {
                QComboBox * pcomboBox = (QComboBox*)widgettype.pWidget;
                m_pSystemconfig->item[var].nValue = pcomboBox->currentData().toString();
                qDebug()<<str<<pcomboBox->currentData().toString();
            }else if (widgettype.sType == "lineedit" && str == sLabel)
            {
                QLineEdit * plineEdit = (QLineEdit*)widgettype.pWidget;
                m_pSystemconfig->item[var].nValue = plineEdit->text() ;
            }else if (widgettype.sType == "checkbox" && str == sLabel)
            {
                QCheckBox* pcheckBox = (QCheckBox*)widgettype.pWidget;
                if(pcheckBox->checkState() == Qt::Unchecked){
                    m_pSystemconfig->item[var].nValue = "0";
                }else if (pcheckBox->checkState() == Qt::Checked) {
                    m_pSystemconfig->item[var].nValue == "1";
                }
            }else if (widgettype.sType == "label" && str == sLabel)
            {
                QLabel * plabel = (QLabel*)widgettype.pWidget;
                m_pSystemconfig->item[var].nValue = plabel->text() ;
            }
        }
    }
}
