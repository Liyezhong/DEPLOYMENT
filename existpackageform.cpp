#include "existpackageform.h"
#include "ui_existpackageform.h"
#include <QDebug>
#include <unistd.h>


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
    char linkPath[512] = {0};
    int ret = ::readlink(package->installDir.toStdString().c_str(), linkPath, 512);
    if (ret < 0)
        return;
    if (!strcmp(linkPath, package->path.toStdString().c_str()))
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
    if (package)
        this->package->remove();
    delete package;

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
