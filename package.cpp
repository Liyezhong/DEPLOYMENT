#include <QProcess>
#include <unistd.h>
#include <QDebug>
#include "package.h"
#include <QThread>
#include <QMessageBox>
#include <QApplication>

Package::Package(QString name, QString path, QString installDir, int totalTime, QObject *parent)
    : QObject(parent),
      isInstall(false),
      isRemove(false),
      name(name),
      path(path),
      installDir(installDir),
      process(nullptr),
      totalTime(totalTime),
      progressValue(0)
{
}

void Package::_updateProgress()
{
    emit updateProgress(progressValue++);
}

void Package::install()
{
    process = new QProcess();
    connect(process, &QProcess::started, [&]() {
        progressTimer = new QTimer();
        connect(progressTimer, SIGNAL(timeout()), this, SLOT(_updateProgress()));
        progressTimer->start(totalTime * 1000 / 100);
    });
    connect(process, &QProcess::readyReadStandardOutput, [&]() {
        qDebug() << "process->bytesAvailable(): " << process->bytesAvailable();
            while (process->canReadLine() > 0) {
                QString s(process->readLine());
                qDebug() << "process's read: " << s;
                emit updateText(s);
            }
    });
    connect(process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
               [=](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "exitCode: " << exitCode << " QProcess::ExitStatus: " << exitStatus;
        while (++progressValue <= 100) {
            emit updateProgress(progressValue);
            QThread::msleep(30);
        }
        progressValue = 0;
        progressTimer->stop();
        delete progressTimer;
        emit this->finished();
        emit this->updateExistList(this);
    });

    qDebug() << "installScript: " << installScript << "path: " << this->path;
    process->start("bash", QStringList() << this->installScript << this->path);
//    qDebug() << process->readAll();
}

void Package::remove()
{
    QString cmd = "rm -rf " + path;
    if (isEnable == true) {
        cmd += " " + installDir;
    }
    QProcess::execute(cmd);
    ::sync();
    qDebug() << __FUNCTION__ << __LINE__;
}

void Package::execute()
{

}

void Package::setEnable()
{
//    ::unlink(this->installDir.toStdString().c_str());
//    ::symlink(path.toStdString().c_str(), installDir.toStdString().c_str());
//    ::sync();
//    QString cmd = "unlink  " + installDir + "; ln -fs " + path + " " + installDir;

    QProcess::execute("rm", QStringList() << "-f" << installDir);
    QProcess::execute("ln", QStringList() << "-fs"
                      << path
                      << installDir);
    ::sync();
    qDebug() << __FUNCTION__ << __LINE__ << "installDir: " << installDir;
}

Package::~Package()
{
    if (process) {
        process->kill();
        delete process;
    }
}
