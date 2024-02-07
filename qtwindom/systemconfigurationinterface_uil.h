#ifndef SYSTEMCONFIGURATIONINTERFACE_UIL_H
#define SYSTEMCONFIGURATIONINTERFACE_UIL_H

#include <QWidget>
#include <parameterclass.h>
#include "modifyingsystemconfig_uil.h"

namespace Ui {
class SystemConfigurationInterface_uil;
}

class SystemConfigurationInterface_uil : public QWidget
{
    Q_OBJECT

public:
    explicit SystemConfigurationInterface_uil(QWidget *parent = nullptr,SystemFileStructure* systemconfig = nullptr);
    ~SystemConfigurationInterface_uil();



signals:
    void sigSaveSystemconfig(QString );
private slots:
    void soltSaveSystemconfig();

private:

    void UiInit();
//    void DataInit();
//    void ConnectInit();
    void SetPixmap(QString str);

    void UpdateUi();
protected:
    void enterEvent(QEvent *event);         //进入窗口
    void leaveEvent(QEvent *event);         //移出窗口
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *event);

private:
    Ui::SystemConfigurationInterface_uil *ui;
    SystemFileStructure* m_pSystemconfig;
    QMap<QString,ModItems > m_mItem;
    ModifyingSystemConfig_Uil * m_pModifyingSystemConfig_Uil;
    QMap<QString,WidgetType> m_mWidgetType;
};

#endif // SYSTEMCONFIGURATIONINTERFACE_UIL_H
