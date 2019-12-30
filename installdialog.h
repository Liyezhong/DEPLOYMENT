#ifndef INSTALLDIALOG_H
#define INSTALLDIALOG_H

#include <QDialog>
#include "package.h"

namespace Ui {
class installDialog;
}

class installDialog : public QDialog
{
    Q_OBJECT

public:
    explicit installDialog(Package *package = nullptr, QWidget *parent = 0);
    ~installDialog();

public slots:
    void updateProgress(int value);
    void updateText(QString text);
    void _finished();

protected:
    void closeEvent(QCloseEvent *ev);

private:
    Ui::installDialog *ui;
    Package *package;
    QThread *thread;

    int totalTime;
    QTimer progressTimer;
};

#endif // INSTALLDIALOG_H
