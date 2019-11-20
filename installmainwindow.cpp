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

    ui->ip_1_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->ip_2_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->ip_3_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->ip_4_lineEdit->setValidator(new QIntValidator(1, 254));

    ui->gateway_1_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->gateway_2_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->gateway_3_lineEdit->setValidator(new QIntValidator(1, 254));
    ui->gateway_4_lineEdit->setValidator(new QIntValidator(1, 254));

    QRegExp rx("[a-fA-F0-9]{2}");
    ui->mac_1_lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->mac_2_lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->mac_3_lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->mac_4_lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->mac_5_lineEdit->setValidator(new QRegExpValidator(rx, this));
    ui->mac_6_lineEdit->setValidator(new QRegExpValidator(rx, this));


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
    /**
     * /usr/bin/eGTouchD
ifconfig eth0 hw ether be:1e:9c:ae:ec:59 10.10.235.242 netmask 255.255.255.0 up
route add default gw 10.10.235.2

ip link add dev can1 type vcan
ip link set can1 txqueuelen 10000
ip link set can1 up

ip link set can0 type can bitrate 1000000 loopback off
ip link set can0 txqueuelen 10000
ip link set can0 up

while true; do
# 1. ssh restart
    netstat -antp | grep 22 | grep LISTEN || systemctl start dropbear.socket

# 2. keyboard input key manage
    kbd=`ls /dev/input/by-id/*-kbd 2>/dev/null`
    if [ $? -eq 0 ]; then
        pidof key || key $kbd
    else
        pkill -9 key
    fi

# 3. system log
#	logfilecount=$(ls /home/root/log/dmesg.* && )

    sleep 10
done


     */
    qDebug() << __FUNCTION__ << __LINE__;
    QStringList parameter;
    parameter << "/home/arthur/1.sh";
    QProcess::execute("bash", parameter);
}

void InstallMainWindow::on_save_pushButton_clicked()
{
    //
    qDebug() << __FUNCTION__ << __LINE__;
}

void InstallMainWindow::on_reboot_pushButton_clicked()
{
    //
    qDebug() << __FUNCTION__ << __LINE__;
}
