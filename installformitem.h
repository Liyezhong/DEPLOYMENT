#ifndef INSTALLFORMITEM_H
#define INSTALLFORMITEM_H

#include <QWidget>

#include "installmainwindow.h"

namespace Ui {
class InstallFormItem;
}

class InstallFormItem : public QWidget
{
    Q_OBJECT

public:
    explicit InstallFormItem(size_t _id, Package *package, QWidget *parent = 0);
    ~InstallFormItem();

private:
    Ui::InstallFormItem *ui;
    size_t id;
    Package *package;
};

#endif // INSTALLFORMITEM_H
