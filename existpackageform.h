#ifndef EXISTPACKAGEFORM_H
#define EXISTPACKAGEFORM_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QListWidget>
#include "installmainwindow.h"

namespace Ui {
class ExistPackageForm;
}

class ExistPackageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ExistPackageForm(QListWidget *listWidget,
        QListWidgetItem *listWidgetItem, QButtonGroup *buttonGroup, Package * package, QWidget *parent = 0);
    ~ExistPackageForm();

public:


private slots:
    void on_removeButton_clicked();

    void on_enableRadioButton_toggled(bool checked);

private:
    Ui::ExistPackageForm *ui;
    QButtonGroup *buttonGroup;
    QListWidget *listWidget;
    QListWidgetItem *listWidgetItem;
    Package * package;
};

#endif // EXISTPACKAGEFORM_H
