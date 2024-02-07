#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>
#include <readjsonfile.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void soltSaveSystemconfig(QString str);
private:
    void UiInit();
    void DataInit();
    void ConnectInit();
    void FilesCount();
    void LoadJson(QFileInfoList &fileInfoList);



private:
    Ui::MainWindow *ui;
    QFileInfoList m_fileInfoList;
    vector<SystemFileStructure*> m_vsysdata;
    ReadJsonFile m_CJson;
};

#endif // MAINWINDOW_H
