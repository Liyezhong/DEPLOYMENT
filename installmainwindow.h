#ifndef INSTALLMAINWINDOW_H
#define INSTALLMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QButtonGroup>
#include "package.h"
#include <QVector>


namespace Ui {
class InstallMainWindow;
}

enum {
    MASTER,
    PTS,
    SERVICE,
    SETTINGS,
};

class InstallMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InstallMainWindow(QWidget *parent = 0);
    ~InstallMainWindow();

private:
    void masterHandle();
    void ptsHandle();
    void serviceHandle();
    void settingsHandle();

private:
    void newAvailablePackageItem(QListWidget *listWidget, size_t id, Package *package);
    void newExistPackageItem(QListWidget *listWidget, size_t id, Package *package);


private:
    //----------------------------------
    QVector<Package *> *findInstallPackage(QString pattern);

private slots:
    void on_InstallTabWidget_currentChanged(int index);

    void on_InstallTabWidget_tabBarClicked(int index);

private:
    Ui::InstallMainWindow *ui;
    QButtonGroup enableRadioGroup;
    QVector<Package *> *masterPackages;
    QVector<Package *> *ptsPackages;
    QVector<Package *> *servicePackages;
};

#endif // INSTALLMAINWINDOW_H
