#ifndef INSTALLMAINWINDOW_H
#define INSTALLMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QButtonGroup>


namespace Ui {
class InstallMainWindow;
}

enum {
    MASTER,
    PTS,
    SERVICE,
    SETTINGS,
};

struct Package {
public:
    Package(QString &name, QString &path, QString &installDir);
public:
    bool install();
    void remove();
    void setEnable();

    bool isInstall;
    bool isRemove;
    QString name;
    QString path;
    QString installDir;
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
    void findInstallPackage(QString pattern);

private slots:
    void on_InstallTabWidget_currentChanged(int index);

    void on_InstallTabWidget_tabBarClicked(int index);

private:
    Ui::InstallMainWindow *ui;
    QButtonGroup enableRadioGroup;
};

#endif // INSTALLMAINWINDOW_H
