#include "installmainwindow.h"
#include "ui_installmainwindow.h"
#include "installformitem.h"
#include "existpackageform.h"
#include <QProcess>

#include <QDebug>
#include <QProcess>
#include <unistd.h>

InstallMainWindow::InstallMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstallMainWindow)
{
    ui->setupUi(this);

//    this->setWindowOpacity(1);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->InstallTabWidget->setCurrentIndex(0);
    enableRadioGroup.setExclusive(true);
}

InstallMainWindow::~InstallMainWindow()
{
    delete ui;
}

void InstallMainWindow::on_InstallTabWidget_currentChanged(int index)
{
    qDebug() << "change: " << index;

    switch(index) {
    case MASTER:
        masterHandle();
        break;
    case PTS:
        ptsHandle();
        break;
    case SERVICE:
        serviceHandle();
        break;
    case SETTINGS:
        settingsHandle();
        break;
    }
}

void InstallMainWindow::on_InstallTabWidget_tabBarClicked(int index)
{

}

void InstallMainWindow::findInstallPackage(QString pattern)
{

}

void InstallMainWindow::newExistPackageItem(QListWidget *listWidget, size_t id, Package *package)
{
    auto listWidgetItem = new QListWidgetItem();
    ExistPackageForm *item = new ExistPackageForm(listWidget, listWidgetItem, &enableRadioGroup, package, this);
    listWidget->addItem(listWidgetItem);
    listWidget->setItemWidget(listWidgetItem, item);
    listWidgetItem->setSizeHint(item->size());
}

void InstallMainWindow::newAvailablePackageItem(QListWidget *listWidget, size_t id, Package *package)
{
    InstallFormItem *item = new InstallFormItem(id, package);
    auto listWidgetItem = new QListWidgetItem();
    listWidget->addItem(listWidgetItem);
    listWidget->setItemWidget(listWidgetItem, item);
    listWidgetItem->setSizeHint(item->size());
}

void InstallMainWindow::masterHandle()
{
    Package *package = nullptr;
    for (int i = 0; i < 15; i++) {
        newAvailablePackageItem(ui->AvaliableListWidget, i, package);
        newExistPackageItem(ui->ExistListWidget, i, package);
    }
}

void InstallMainWindow::ptsHandle()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void InstallMainWindow::serviceHandle()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void InstallMainWindow::settingsHandle()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

Package::Package(QString &name, QString &path, QString &installDir)
    : isRemove(false),
      isInstall(false),
      name(name),
      path(path),
      installDir(installDir)
{
}

void Package::remove()
{
    QString cmd = "rm -rf " +path;
    QProcess::execute(cmd);
    ::sync();
    qDebug() << __FUNCTION__ << __LINE__;
}

void Package::setEnable()
{
    ::unlink(this->installDir.toStdString().c_str());
    ::symlink(path.toStdString().c_str(), installDir.toStdString().c_str());
////    int readlink(const char *p a t h n a m e, char * b u f, int b u f s i z e) ;
//    readlink();
    ::sync();
}
