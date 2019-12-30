#include "installdialog.h"
#include "ui_installdialog.h"
#include <QThread>
#include <QCloseEvent>
#include <QMessageBox>


installDialog::installDialog(Package *package, QWidget *parent) :
    package(package),
    QDialog(parent),
    ui(new Ui::installDialog)
{
    ui->setupUi(this);

    // textbrowser background and text color.
//    QPalette pal;
//    pal = ui->textBrowser->palette();
//    pal.setColor(QPalette::Base, QColor(0,0,0));
//    ui->textBrowser->setPalette(pal);
//    ui->textBrowser->setStyleSheet("color:white;");

//    ui->textBrowser->append("10000\n1000\n2000\n3000\n");
//    ui->textBrowser->append("10000\n1000\n2000\n3000\n");

    //
    updateProgress(0);

    ui->title->setText(package->name + " is installing...");

    if (package == nullptr)
        return;

    thread = new QThread();
    package->moveToThread(thread);

    connect(thread, SIGNAL(started()), package, SLOT(install()));

    thread->start();
    connect(package, SIGNAL(updateProgress(int)), this, SLOT(updateProgress(int)));
    connect(package, SIGNAL(updateText(QString)), this, SLOT(updateText(QString)));
    connect(package, SIGNAL(finished()), this, SLOT(_finished()));

}

void installDialog::_finished()
{
//    QMessageBox::information(this, "Information", "Installation successful!");
    this->accept();
}

void installDialog::updateProgress(int value)
{
    ui->progressBar->setValue(value);
}

void installDialog::updateText(QString text)
{
//    ui->textBrowser->append(text + "\n");
}

installDialog::~installDialog()
{
    if (package) {
        thread->terminate();
        thread->wait();
        delete thread;
//        delete package;
    }
    delete ui;
}

void installDialog::closeEvent(QCloseEvent *ev)
{
    ev->accept();
}

