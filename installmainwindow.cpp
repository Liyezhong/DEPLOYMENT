#include "installmainwindow.h"
#include "ui_installmainwindow.h"
#include "installformitem.h"
#include "existpackageform.h"

#include <QDebug>
#include <QFile>
#include <QDir>

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

QVector<Package *> * InstallMainWindow::findInstallPackage(QString pattern)
{
    QVector<Package *> *vector = new QVector<Package *>();

    //




    //

    return vector;
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
    InstallFormItem *item = new InstallFormItem(id, package, this);
    auto listWidgetItem = new QListWidgetItem();
    listWidget->addItem(listWidgetItem);
    listWidget->setItemWidget(listWidgetItem, item);
    listWidgetItem->setSizeHint(item->size());
}

void InstallMainWindow::masterHandle()
{
    int i = 0;
    masterPackages = this->findInstallPackage("MSW_*.sh");
#if 0
    for (auto package: *ptsPackages) {
        i++
#else
    Package *package = nullptr;
    for (i = 0; i < 10; i++) {
#endif
        newAvailablePackageItem(ui->AvaliableListWidget, i, package);
        newExistPackageItem(ui->ExistListWidget, i, package);
    }
}

void InstallMainWindow::ptsHandle()
{
    int i = 0;
    ptsPackages = this->findInstallPackage("PTS_*.sh");
#if 0
    for (auto package: *ptsPackages) {
        i++
#else
    Package *package = nullptr;
    for (i = 0; i < 10; i++) {
#endif
        newAvailablePackageItem(ui->AvaliableListWidget, i, package);
        newExistPackageItem(ui->ExistListWidget, i, package);
    }
}

void InstallMainWindow::serviceHandle()
{
    int i = 0;
    servicePackages = this->findInstallPackage("SVC_*.sh");
    for (auto package: *servicePackages) {
        i++;
        newAvailablePackageItem(ui->AvaliableListWidget, i, package);
        newExistPackageItem(ui->ExistListWidget, i, package);
    }
}

void InstallMainWindow::settingsHandle()
{
    qDebug() << __FUNCTION__ << __LINE__;
}
