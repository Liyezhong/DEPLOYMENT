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
    SLAVE,
    SETTINGS,
};

enum {
  MACHINE_TYPE_NULL,
  MACHINE_TYPE_PLATINUM,
  MACHINE_TYPE_GOLD,
};

enum {
    ALPHA_NULL,
    ALPHA_1,
    ALPHA_2,
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
    void slaveHandle();


private:
    void newAvailablePackageItem(QListWidget *listWidget, size_t id, Package *package);
    void newExistPackageItem(QListWidget *listWidget, size_t id, Package *package);

public slots:
    void updateExistList(Package *package);

private:
    //----------------------------------
    QVector<Package *> *findPackage(QString script);

private slots:
    void on_InstallTabWidget_currentChanged(int index);

    void on_save_pushButton_clicked();

    void on_reboot_pushButton_clicked();

    void on_machineTypeComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::InstallMainWindow *ui;
    QButtonGroup enableRadioGroup;
    QVector<Package *> *masterPackages;
    QVector<Package *> *ptsPackages;
    QVector<Package *> *servicePackages;
    QVector<Package *> *slavePackages;

    QVector<Package *> *masterInstallPackages;
    QVector<Package *> *ptsInstallPackages;
    QVector<Package *> *serviceInstallPackages;
    QVector<Package *> *slaveInstallPackages;

    QString ip;
    QString mac;
    QString gateway;
    QString netmask;

    int machine_type;
    int alpha_type;
};

#endif // INSTALLMAINWINDOW_H
