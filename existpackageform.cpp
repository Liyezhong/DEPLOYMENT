#include "existpackageform.h"
#include "ui_existpackageform.h"
#include <QDebug>
#include <unistd.h>
#include <QMessageBox>


ExistPackageForm::ExistPackageForm(QListWidget *listWidget, QListWidgetItem *listWidgetItem, QButtonGroup *buttonGroup, Package *package, QWidget *parent) :
    listWidget(listWidget),
    listWidgetItem(listWidgetItem),
    buttonGroup(buttonGroup),
    package(package),
    QWidget(parent),
    ui(new Ui::ExistPackageForm)
{
    ui->setupUi(this);
    buttonGroup->addButton(ui->enableRadioButton);

    if (package == nullptr)
        return;
    qDebug() << "ui->name: " << ui->name->text();
    qDebug() << "package->name: " << package->name;
    ui->name->setText(package->name);

//    char linkPath[512] = {0};
//    int ret = ::readlink(package->installDir.toStdString().c_str(), linkPath, 512);
//    if (ret < 0)
//        return;
//    if (!strcmp(linkPath, package->path.toStdString().c_str()))
     if (package->isEnable)
        ui->enableRadioButton->setChecked(true);
}

ExistPackageForm::~ExistPackageForm()
{
    delete ui;
}

void ExistPackageForm::on_removeButton_clicked()
{
    buttonGroup->removeButton(ui->enableRadioButton);
    listWidget->removeItemWidget(listWidgetItem);
    if (package) {
        this->package->remove();
        delete package;
    }

    delete listWidgetItem;

    this->deleteLater();
}

void ExistPackageForm::on_enableRadioButton_toggled(bool checked)
{
    if (checked == false)
        return;
    if (package)
        this->package->setEnable();
    qDebug() << __FUNCTION__ << __LINE__;
}

void ExistPackageForm::on_exportButton_clicked()
{
    //1. check usb exist.
    QProcess usb;
    QStringList parameter;
    parameter << "-c"
              << "mount | grep /run/media/sd | awk '{print $3}' | tail -1";
    usb.start("bash", parameter);
    usb.waitForFinished();
    QString udisk_path = usb.readAll();

    if (udisk_path == "") {
        QMessageBox::warning(this,
              "Deployment", "Please plug U disk into the usb port of the SKYLINE instrument.",  QMessageBox::Ok);
        return;
    }

    //2. check usb exist.
    QProcess exportProcess;
    parameter.clear();
    QString exportPackageName = package->name+ ".Logfiles.tar.bz2";
    QString cp = "cd " + package->path + ";"
                 + "tar jcf " + exportPackageName + " Logfiles;"
                 + "cp -rf " + exportPackageName + " " + udisk_path + "/;"
                 + "rm -rf " + exportPackageName + ";";
    parameter << "-c"
              << cp
              << "sync && sync";
    QString text = ui->exportButton->text();
    ui->exportButton->setText("exporting");
    QMessageBox::information(nullptr,
              "Deployment", "Exporting, please wait a few time.",  QMessageBox::Ok);
    exportProcess.start("bash", parameter);

    exportProcess.waitForFinished(-1);
    ui->exportButton->setText(text);
    QMessageBox::information(this,
              "Deployment", "Successfully exported",  QMessageBox::Ok);
}
