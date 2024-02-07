#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>
#include <systemconfigurationinterface_uil.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DataInit();
    UiInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::soltSaveSystemconfig(QString str)
{
    QString folderpath = QString("%1/info").arg(QApplication::applicationDirPath());
    for (int var = 0; var < m_vsysdata.size(); ++var)
    {
        if (m_vsysdata[var]->sName == str)
        {
            folderpath = QString("%1/%2.json").arg(folderpath).arg(m_vsysdata[var]->sName);
            m_CJson.SaveSystemconfig(folderpath,m_vsysdata[var]);
        }
    }
}

void MainWindow::UiInit()
{
    QGridLayout* pGLayout = new QGridLayout();
    for (int var = 0; var < m_vsysdata.size(); ++var) {
        SystemConfigurationInterface_uil* widget = new SystemConfigurationInterface_uil(this,m_vsysdata[var]);

        connect(widget,SIGNAL(sigSaveSystemconfig(QString)),this,SLOT(soltSaveSystemconfig(QString) ));

//        qDebug()<<m_vsysdata[var]->sName<<m_vsysdata[var]->text.vnPoint[0]
//               << m_vsysdata[var]->text.vnPoint[1];
        pGLayout->addWidget(widget,m_vsysdata[var]->text.vnPoint[0],
                m_vsysdata[var]->text.vnPoint[1]);

    }
    ui->centralWidget->setLayout(pGLayout);
}

void MainWindow::DataInit()
{
    FilesCount();
    LoadJson(m_fileInfoList);
}

void MainWindow::ConnectInit()
{

}

void MainWindow::FilesCount()
{
    QString folderpath = QString("%1/info/").arg(QApplication::applicationDirPath());
    QDir *dir = new QDir(folderpath);
    QStringList filter;
    m_fileInfoList = dir->entryInfoList(filter);
    return ;
}

void MainWindow::LoadJson(QFileInfoList &fileInfoList)
{
    for (int var = 2; var < fileInfoList.count(); ++var) {
        QString sPath = fileInfoList.at(var).absoluteFilePath();
        int nbegin = sPath.lastIndexOf("/")+1;
        int nend = sPath.lastIndexOf(".");
        int nnamelength = nend - nbegin;
        QString sName = sPath.mid(nbegin,nnamelength);
        SystemFileStructure* sysdata = new SystemFileStructure();
        sysdata->sName = sName;
        m_CJson.load(sPath,sysdata);
        m_vsysdata.push_back(sysdata);
    }
}
