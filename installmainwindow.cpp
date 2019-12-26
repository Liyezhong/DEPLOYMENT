#include "installmainwindow.h"
#include "ui_installmainwindow.h"
#include "installformitem.h"
#include "existpackageform.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>

InstallMainWindow::InstallMainWindow(QWidget *parent) :
    QMainWindow(parent),
    masterPackages(nullptr),
    masterInstallPackages(nullptr),
    ptsPackages(nullptr),
    ptsInstallPackages(nullptr),
    servicePackages(nullptr),
    serviceInstallPackages(nullptr),
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
        if (masterPackages)
        masterPackages->clear();
        if (masterInstallPackages)
        masterInstallPackages->clear();
        ui->AvaliableListWidget->clear();
        ui->ExistListWidget->clear();
        masterHandle();
        break;
    case PTS:
        if (ptsPackages)
        ptsPackages->clear();
        if (ptsInstallPackages)
        ptsInstallPackages->clear();
        ui->ptsAvaliableListWidget->clear();
        ui->ptsExistListWidget->clear();
        ptsHandle();
        break;
    case SERVICE:
        if (servicePackages)
        servicePackages->clear();
        if (serviceInstallPackages)
        serviceInstallPackages->clear();
        ui->serviceAvaliableListWidget->clear();
        ui->serviceExistListWidget->clear();
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

QVector<Package *> * InstallMainWindow::findPackage(QString script)
{
    QVector<Package *> *vector = new QVector<Package *>();

    //
    QProcess findPackageProcess;
    QStringList parameter;
    parameter << script;
    findPackageProcess.start("bash", parameter);

    if (!findPackageProcess.waitForFinished())
        return vector;
    QString result(findPackageProcess.readAll());
    // MSW_dev_01.101.280=/home/root/MSW_dev_01.101.280=0
    // MSW_dev_01.101.287=/home/root/MSW_dev_01.101.287.sh
    qDebug() << "result: " << result;

    if (!result.isEmpty()) {
        foreach (const QString &str, result.split('\n')) {
            auto item = str.split('=');
            qDebug() << "item: " << item;
            qDebug() << "item's size: " << item.size();
            if (item.size() < 2)
                break;
            QString installDir;
            int totalTime;
            if (script.contains("master")) {
                installDir = "/home/root/skyline_arm";
                totalTime = 150; // 150 seconds
            } else if (script.contains("pts")) {
                installDir = "/home/root/prototest";
                totalTime = 30;
            } else if (script.contains("service")) {
                installDir = "/home/root/service";
                totalTime = 30;
            }

            auto package = new Package(item.at(0), item.at(1), installDir, totalTime);
            if (item.size() == 2) {
                package->isEnable = false;
            } else {
                bool isEnabledFlag = (bool)QString(item.at(2)).toInt();
                if (isEnabledFlag)
                    package->isEnable = true;
                else
                    package->isEnable = false;
            }
            vector->push_back(package);
            connect(package, SIGNAL(updateExistList(Package*)), this, SLOT(updateExistList(Package*)));
        }
    }

    return vector;
}

void InstallMainWindow::newExistPackageItem(QListWidget *listWidget, size_t id, Package *package)
{
    auto listWidgetItem = new QListWidgetItem();
    ExistPackageForm *item = new ExistPackageForm(listWidget, listWidgetItem, &enableRadioGroup, package);
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

void InstallMainWindow::updateExistList(Package *package)
{
    if (package->name.contains("MSW"))
       on_InstallTabWidget_currentChanged(MASTER);
    else if (package->name.contains("PTS"))
       on_InstallTabWidget_currentChanged(PTS);
    else if (package->name.contains("SVC"))
       on_InstallTabWidget_currentChanged(SERVICE);
}

void InstallMainWindow::masterHandle()
{
    int i = 0;
    masterPackages = this->findPackage("/usr/leica/bin/find_master.sh");
#if 1
    for (auto package: *masterPackages) {
#else
    Package *package = nullptr;
    for (i = 0; i < 10; i++) {
#endif
        newExistPackageItem(ui->ExistListWidget, i++, package);
    }

    masterInstallPackages = this->findPackage("/usr/leica/bin/find_master_install.sh");
    i = 0;
    for (auto package: *masterInstallPackages)
        newAvailablePackageItem(ui->AvaliableListWidget, i++, package);
}

void InstallMainWindow::ptsHandle()
{
    int i = 0;
    ptsPackages = this->findPackage("/usr/leica/bin/find_pts.sh");
#if 1
    for (auto package: *ptsPackages) {
#else
    Package *package = nullptr;
    for (i = 0; i < 10; i++) {
#endif
        newExistPackageItem(ui->ptsExistListWidget, i++, package);
    }

    ptsInstallPackages = this->findPackage("/usr/leica/bin/find_pts_install.sh");
    i = 0;
    for (auto package: *ptsInstallPackages)
        newAvailablePackageItem(ui->ptsAvaliableListWidget, i++, package);
}

void InstallMainWindow::serviceHandle()
{
    int i = 0;
    servicePackages = this->findPackage("/usr/leica/bin/find_service.sh");
#if 1
    for (auto package: *servicePackages) {
#else
    Package *package = nullptr;
    for (i = 0; i < 10; i++) {
#endif
        newExistPackageItem(ui->serviceExistListWidget, i++, package);
    }

    serviceInstallPackages = this->findPackage("/usr/leica/bin/find_service_install.sh");
    i = 0;
    for (auto package: *serviceInstallPackages)
        newAvailablePackageItem(ui->serviceAvaliableListWidget, i++, package);
}

void InstallMainWindow::settingsHandle()
{
    qDebug() << __FUNCTION__ << __LINE__;
    {
        QProcess ip_mac;
        QStringList parameter;
        parameter << "/usr/leica/bin/ip_mac_read.sh";
        ip_mac.start("bash", parameter);

        if (!ip_mac.waitForFinished())
            return;
        QString result(ip_mac.readAll());
        qDebug() << "result: " << result;

        if (!result.isEmpty()) {
            foreach (const QString &str, result.split('\n')) {
                auto item = str.split('=');
                if (item.at(0) == "ip") {
                    ip = item.at(1);
                    qDebug() << " ip: " << item.at(1);
                } else if (item.at(0) == "mac") {
                    mac = item.at(1);
                    qDebug() << " mac: " << item.at(1);
                } else if (item.at(0) == "gateway") {
                    gateway = item.at(1);
                    qDebug() << " gateway: " << item.at(1);
                } else if (item.at(0) == "netmask") {
                    netmask = item.at(1);
                    qDebug() << " netmask: " << item.at(1);
                }
            }

            // run ip_mac_read.sh
            auto ipList = ip.split('.');
            ui->ip_1_lineEdit->setText(ipList.at(0));
            ui->ip_2_lineEdit->setText(ipList.at(1));
            ui->ip_3_lineEdit->setText(ipList.at(2));
            ui->ip_4_lineEdit->setText(ipList.at(3));

            auto gatewayList = gateway.split('.');
            ui->gateway_1_lineEdit->setText(gatewayList.at(0));
            ui->gateway_2_lineEdit->setText(gatewayList.at(1));
            ui->gateway_3_lineEdit->setText(gatewayList.at(2));
            ui->gateway_4_lineEdit->setText(gatewayList.at(3));

            auto macList = mac.split(':');
            ui->mac_1_lineEdit->setText(macList.at(0));
            ui->mac_2_lineEdit->setText(macList.at(1));
            ui->mac_3_lineEdit->setText(macList.at(2));
            ui->mac_4_lineEdit->setText(macList.at(3));
            ui->mac_5_lineEdit->setText(macList.at(4));
            ui->mac_6_lineEdit->setText(macList.at(5));
        }
    }

    // Platinum / Gold, Alpha
    {
        QProcess machineTypeProcess;
        QStringList parameter;
        parameter << "/usr/leica/bin/update_machine_type.sh"
                  << "r";
        machineTypeProcess.start("bash", parameter);

        if (!machineTypeProcess.waitForFinished())
            return;
        QString result(machineTypeProcess.readAll());
        qDebug() << "machineTypeProcess: " << result;


        if (result == "") {
            ui->machineTypeComboBox->setCurrentIndex(0);
            ui->alphaTypeComboBox->setCurrentIndex(0);
        } else {
            foreach (const QString &str, result.split('\n')) {
                auto item = str.split('=');
                if (item.at(0) == "MACHINE_TYPE") {
                    if (item.at(1) == "Platinum")
                        ui->machineTypeComboBox->setCurrentIndex(1);
                    else
                        ui->machineTypeComboBox->setCurrentIndex(2);
                    qDebug() << " MACHINE_TYPE: " << item.at(1);
                } else if (item.at(0) == "ALPHA_TYPE") {
                    if (item.at(1) == "Alpha1")
                        ui->alphaTypeComboBox->setCurrentIndex(1);
                    else
                        ui->alphaTypeComboBox->setCurrentIndex(2);
                    qDebug() << " ALPHA_TYPE: " << item.at(1);
                }
            }
        }

        machine_type = ui->machineTypeComboBox->currentIndex();
        alpha_type = ui->alphaTypeComboBox->currentIndex();
    }
}

void InstallMainWindow::on_save_pushButton_clicked()
{
    //
    if (ui->ip_1_lineEdit->text().isEmpty()
            || ui->ip_2_lineEdit->text().isEmpty()
            || ui->ip_3_lineEdit->text().isEmpty()
            || ui->ip_4_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Warnning", "Please note that the ip address must be specified");
        return;
    }
    if (ui->gateway_1_lineEdit->text().isEmpty()
            || ui->gateway_2_lineEdit->text().isEmpty()
            || ui->gateway_3_lineEdit->text().isEmpty()
            || ui->gateway_4_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Warnning", "Please note that the gateway ip address must be specified");
        return;
    }
    if (ui->mac_1_lineEdit->text().isEmpty()
            || ui->mac_2_lineEdit->text().isEmpty()
            || ui->mac_3_lineEdit->text().isEmpty()
            || ui->mac_4_lineEdit->text().isEmpty()
            || ui->mac_5_lineEdit->text().isEmpty()
            || ui->mac_6_lineEdit->text().isEmpty()
            ) {
        QMessageBox::warning(this, "Warnning", "Please note that the hardware address must be specified");
        return;
    }
    if (ui->machineTypeComboBox->currentIndex() == MACHINE_TYPE_NULL) {
        QMessageBox::warning(this, "Warnning", "Please note that the machine type must be specified");
        return;
    }
    if (ui->alphaTypeComboBox->currentIndex() == ALPHA_NULL) {
        QMessageBox::warning(this, "Warnning", "Please note that the alpha type must be specified");
        return;
    }
    qDebug() << __FUNCTION__ << __LINE__;
    QString ip_new = ui->ip_1_lineEdit->text()
            + "." + ui->ip_2_lineEdit->text()
            + "." + ui->ip_3_lineEdit->text()
            + "." + ui->ip_4_lineEdit->text();
    bool is_modify = false;
    if (ip != ip_new) {
        is_modify = true;
        ip = ip_new;
    }
    QString mac_new = ui->mac_1_lineEdit->text()
            + ":" + ui->mac_2_lineEdit->text()
            + ":" + ui->mac_3_lineEdit->text()
            + ":" + ui->mac_4_lineEdit->text()
            + ":" + ui->mac_5_lineEdit->text()
            + ":" + ui->mac_6_lineEdit->text();
    if (mac != mac_new) {
        is_modify = true;
        mac = mac_new;
    }
    QString gateway_new = ui->gateway_1_lineEdit->text()
            + "." + ui->gateway_2_lineEdit->text()
            + "." + ui->gateway_3_lineEdit->text()
            + "." + ui->gateway_4_lineEdit->text();
    if (gateway != gateway_new) {
        is_modify = true;
        gateway = gateway_new;
    }

    if (machine_type != ui->machineTypeComboBox->currentIndex()) {
        is_modify = true;
        machine_type = ui->machineTypeComboBox->currentIndex();
    }

    if (alpha_type != ui->alphaTypeComboBox->currentIndex()) {
        is_modify = true;
        alpha_type = ui->alphaTypeComboBox->currentIndex();
    }

    if (is_modify == true) {

        // ip mac gateway
        QStringList parameter;
        parameter << "/usr/leica/bin/ip_mac_write.sh"
                  << ip
                  << mac
                  << gateway;
        QProcess::execute("bash", parameter);
    }
    {
        // machine type
        QStringList parameter;
        parameter << "/usr/leica/bin/update_machine_type.sh"
                  << "w";
        switch (machine_type) {
        case MACHINE_TYPE_PLATINUM:
            parameter << "Platinum";
            break;
        case MACHINE_TYPE_GOLD:
            parameter << "Gold";
            break;
        }
        switch (alpha_type) {
        case ALPHA_1:
            parameter << "Alpha1";
            break;
        case ALPHA_2:
            parameter << "Alpha2";
            break;
        }

        QProcess::execute("bash", parameter);
    }
}

void InstallMainWindow::on_reboot_pushButton_clicked()
{
    //
    qDebug() << __FUNCTION__ << __LINE__;
    QProcess::execute("reboot");
}

void InstallMainWindow::on_machineTypeComboBox_currentIndexChanged(int index)
{
    qDebug() << "machine_type: " << index;
}
