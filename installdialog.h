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
    void updateText(QString &text);

private:
    Ui::installDialog *ui;
    Package *package;
    QThread *thread;
};

#endif // INSTALLDIALOG_H
