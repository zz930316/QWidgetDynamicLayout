#include "systemconfigurationinterface_uil.h"
#include "ui_systemconfigurationinterface_uil.h"
#include <QDebug>

SystemConfigurationInterface_uil::SystemConfigurationInterface_uil(QWidget *parent, SystemFileStructure *systemconfig) :
    QWidget(parent),
    ui(new Ui::SystemConfigurationInterface_uil)
{
    ui->setupUi(this);
    m_pSystemconfig = systemconfig;
    m_pModifyingSystemConfig_Uil = new ModifyingSystemConfig_Uil(nullptr,systemconfig);
    connect(m_pModifyingSystemConfig_Uil,SIGNAL(sigSave() ),this,SLOT(soltSaveSystemconfig() ));
    UiInit();
//    QString sWidgetBoxStyle=QString("QWidget#widget_3{"
//                                     "font-size:14px;color:rgb(255,255,255);border: 0px solid ;"
//                                     "background-color:rgb(138,151,161);border-radius:1px;}");

    QString sWidgetBoxStyle=QString("QWidget#widget_3{font-size:14px;color:rgb(255,255,255);border: 0px solid ;"
                                    "background-color: qlineargradient(spread:pad,x1:0, x2:0, y1:0, y2:1,"
                                    "stop: 0 rgba(120,120,120,255),stop: 1 rgba(39,39,39,255));}");

    ui->widget_3->setStyleSheet(sWidgetBoxStyle);
}

SystemConfigurationInterface_uil::~SystemConfigurationInterface_uil()
{
    delete ui;
}

void SystemConfigurationInterface_uil::UiInit()
{

    QString sWidgetBoxStyle=QString("QWidget{font-size:14px;color:rgb(255,255,255);border: 0px ;}");
    QGridLayout* pGLayout = new QGridLayout();
    QVBoxLayout* pVLayout = new QVBoxLayout();//水平布局
    QLabel * label =new QLabel(ui->widget);
    label->setText(m_pSystemconfig->sName);
    label->setStyleSheet(sWidgetBoxStyle);
    pVLayout->addWidget(label);
    pVLayout->addSpacerItem(new QSpacerItem(0,10));
    for (int var = 0; var < sizeof(m_pSystemconfig->item)/sizeof(ModItems); ++var)
    {
        if(!m_pSystemconfig->item[var].sLabel.isEmpty() && m_pSystemconfig->item[var].sSign == "Yes")
        {
            WidgetType widgettype;
            QLabel * label =new QLabel(ui->widget);
            label->setText(m_pSystemconfig->item[var].sLabel);
            QLabel * label2 =new QLabel(ui->widget);
            label->setStyleSheet(sWidgetBoxStyle);
            label2->setStyleSheet(sWidgetBoxStyle);
            widgettype.sType = m_pSystemconfig->item[var].sType;
            widgettype.pWidget = (void *)label2;
            if(m_pSystemconfig->item[var].sType == "combox")
            {
                QStringList slist = m_pSystemconfig->item[var].sParameter.split(",");
                int n = m_pSystemconfig->item[var].nValue.toInt();
                QString s = slist[m_pSystemconfig->item[var].nValue.toInt()];
                label2->setText(slist[m_pSystemconfig->item[var].nValue.toInt()]);
            }else if (m_pSystemconfig->item[var].sType == "lineedit")
            {
                label2->setText(m_pSystemconfig->item[var].nValue);
            }else if (m_pSystemconfig->item[var].sType == "checkbox")
            {
                QStringList slist = m_pSystemconfig->item[var].sParameter.split(",");
                int n = m_pSystemconfig->item[var].nValue.toInt();
                QString s = slist[m_pSystemconfig->item[var].nValue.toInt()];
                label2->setText(slist[m_pSystemconfig->item[var].nValue.toInt()]);
            }else if (m_pSystemconfig->item[var].sType == "label")
            {
                label2->setText(m_pSystemconfig->item[var].nValue);
            }
            pGLayout->addWidget(label,var,0);
            pGLayout->addWidget(label2,var,1);
            m_mWidgetType[m_pSystemconfig->item[var].sLabel] = widgettype;
        }
    }
    pVLayout->addLayout(pGLayout);
    ui->widget->setLayout(pVLayout);

    QString folderpath = QString("%1/icon/%2.png").arg(QApplication::applicationDirPath()).arg(m_pSystemconfig->text.sIcon);
    SetPixmap(folderpath);
//    if(m_pSystemconfig->text.sIcon == "par_other"){
//        SetPixmap(":/new/prefix1/icon/par_other.png");
//    }else if (m_pSystemconfig->text.sIcon == "par_scan") {
//        SetPixmap(":/new/prefix1/icon/par_scan.png");
//    }else if (m_pSystemconfig->text.sIcon == "par_video") {
//        SetPixmap(":/new/prefix1/icon/par_video.png");
//    }else if (m_pSystemconfig->text.sIcon == "") {

//    }

}

void SystemConfigurationInterface_uil::SetPixmap(QString str)
{
    QPixmap *pixmap = new QPixmap(str);
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
}

void SystemConfigurationInterface_uil::UpdateUi()
{
    QMap<QString,WidgetType>::Iterator iter = m_mWidgetType.begin();
    for (iter; iter != m_mWidgetType.end(); iter++) {
        QString str = iter.key();
        WidgetType widgettype = iter.value();
        for (int var = 0; var < sizeof(m_pSystemconfig->item)/sizeof(ModItems); ++var)
        {
            QString sLabel = m_pSystemconfig->item[var].sLabel;
            QString ss = widgettype.sType;
            QLabel * plabel = (QLabel*)widgettype.pWidget;
            if(widgettype.sType == "combox" && str== sLabel)
            {
                QStringList slist = m_pSystemconfig->item[var].sParameter.split(",");
                plabel->setText(slist[m_pSystemconfig->item[var].nValue.toInt()]);
            }else if (widgettype.sType == "lineedit" && str == sLabel)
            {
                plabel->setText(m_pSystemconfig->item[var].nValue);
            }else if (widgettype.sType == "checkbox" && str == sLabel)
            {
                QStringList slist = m_pSystemconfig->item[var].sParameter.split(",");
                plabel->setText(slist[m_pSystemconfig->item[var].nValue.toInt()]);
            }else if (widgettype.sType == "label" && str == sLabel)
            {
                plabel->setText(m_pSystemconfig->item[var].nValue);
            }
        }
    }
}

void SystemConfigurationInterface_uil::enterEvent(QEvent *event)
{
    QString sWidgetBoxStyle=QString("QWidget#widget_3{font-size:14px;color:rgb(255,255,255);border: 2px solid rgb(0,148,255);"
                                    "background-color: qlineargradient(spread:pad,x1:0, x2:0, y1:0, y2:1,"
                                    "stop: 0 rgba(120,120,120,255),stop: 1 rgba(39,39,39,255));}");
    ui->widget_3->setStyleSheet(sWidgetBoxStyle);
}

void SystemConfigurationInterface_uil::leaveEvent(QEvent *event)
{
    QString sWidgetBoxStyle=QString("QWidget#widget_3{font-size:14px;color:rgb(255,255,255);border: 0px solid;"
                                    "background-color: qlineargradient(spread:pad,x1:0, x2:0, y1:0, y2:1,"
                                    "stop: 0 rgba(120,120,120,255),stop: 1 rgba(39,39,39,255));}");
    ui->widget_3->setStyleSheet(sWidgetBoxStyle);
}

void SystemConfigurationInterface_uil::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button()){
        QString sWidgetBoxStyle=QString("QWidget#widget_3{"
                                         "font-size:14px;color:rgb(255,255,255);border: 0px solid ;"
                                         "background-color:rgb(76,255,0);border-radius:1px;}");
        ui->widget_3->setStyleSheet(sWidgetBoxStyle);
    }
}

void SystemConfigurationInterface_uil::soltSaveSystemconfig()
{
    UpdateUi();
    emit sigSaveSystemconfig(m_pSystemconfig->sName);
}

void SystemConfigurationInterface_uil::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pModifyingSystemConfig_Uil->exec();
}

void SystemConfigurationInterface_uil::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
