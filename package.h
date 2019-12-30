#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QProcess>
#include <QTimer>

class Package : public QObject
{
    Q_OBJECT
public:
    explicit Package(QString name, QString path, QString installDir, int totalTime, QObject *parent = nullptr);
    ~Package();
public slots:
    void install();
private slots:
    void _updateProgress();
public:
    void remove();
    void setEnable();

signals:
    void updateProgress(int value);
    void updateText(QString text);
    void finished(void);
    void updateExistList(Package *);

private:
    void execute();

public:
    bool isInstall;
    bool isRemove;
    bool isEnable;
    QString name;
    QString path;
    QString installDir;
    QProcess *process;

    QTimer *progressTimer;
    int totalTime;
    int progressValue;
    QString installScript;
};

#endif // PACKAGE_H
