#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QProcess>

class Package : public QObject
{
    Q_OBJECT
public:
    explicit Package(QString &name, QString &path, QString &installDir, QObject *parent = nullptr);
    ~Package();
public:
    void install();
    void remove();
    void setEnable();

signals:
    void updateProgress(int value);
    void updateText(QString &text);
    void finished(void);

private:
    void execute();

public:
    bool isInstall;
    bool isRemove;
    QString name;
    QString path;
    QString installDir;
    QProcess *process;
};

#endif // PACKAGE_H
