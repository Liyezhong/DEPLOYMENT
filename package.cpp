#include <QProcess>
#include <unistd.h>
#include <QDebug>
#include "package.h"

Package::Package(QString &name, QString &path, QString &installDir, QObject *parent)
    : QObject(parent),
      isInstall(false),
      isRemove(false),
      name(name),
      path(path),
      installDir(installDir)
{
     process = new QProcess();
}

void Package::install()
{
    connect(process, &QProcess::readyReadStandardOutput, [&]() {
            while (process->canReadLine()) {
                QString s(process->readLine());
                emit updateText(s);
            }
    });
    connect(process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
               [=](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "exitCode: " << exitCode << " QProcess::ExitStatus: " << exitStatus;
        emit this->finished();
    });

    process->start(this->path);
}

void Package::remove()
{
    QString cmd = "rm -rf " + path;
    QProcess::execute(cmd);
    ::sync();
    qDebug() << __FUNCTION__ << __LINE__;
}

void Package::execute()
{

}

void Package::setEnable()
{
    ::unlink(this->installDir.toStdString().c_str());
    ::symlink(path.toStdString().c_str(), installDir.toStdString().c_str());
    ::sync();
}

Package::~Package()
{
    delete process;
}
