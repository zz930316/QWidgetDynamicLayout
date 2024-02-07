#ifndef MODIFYINGSYSTEMCONFIG_UIL_H
#define MODIFYINGSYSTEMCONFIG_UIL_H

#include <QDialog>
#include <parameterclass.h>
namespace Ui {
class ModifyingSystemConfig_Uil;
}

class ModifyingSystemConfig_Uil : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyingSystemConfig_Uil(QWidget *parent = nullptr,SystemFileStructure* systemconfig = nullptr);
    ~ModifyingSystemConfig_Uil();

signals:
    void sigSave();
private slots:
    void soltSave();
    void soltClose();

private:

    void UiInit();
    void GetWidgeItem();
private:
    QMap<QString,WidgetType> m_mWidgetType;
    Ui::ModifyingSystemConfig_Uil *ui;
    SystemFileStructure* m_pSystemconfig ;
};

#endif // MODIFYINGSYSTEMCONFIG_UIL_H
