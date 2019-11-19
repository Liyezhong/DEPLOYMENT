#include "installformitem.h"
#include "ui_installformitem.h"
#include "package.h"
#include "installdialog.h"

InstallFormItem::InstallFormItem(size_t _id, Package *package, QWidget *parent) :
    id(_id),
    package(package),
    QWidget(parent),
    ui(new Ui::InstallFormItem)
{
    ui->setupUi(this);
    ui->id->setText(QString().setNum(id));
}

InstallFormItem::~InstallFormItem()
{
    delete ui;
}

void InstallFormItem::on_installButton_clicked()
{
    installDialog dialog(package, this);
    dialog.exec();
}
