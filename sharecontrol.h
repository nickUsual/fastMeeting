#ifndef SHARECONTROL_H
#define SHARECONTROL_H

#include <QWidget>
#include "ExternVariable.h"
namespace Ui {
class ShareControl;
}

class ShareControl : public QWidget
{
    Q_OBJECT

public:
    explicit ShareControl(QWidget *parent = nullptr);
    ~ShareControl();

private:
    Ui::ShareControl *ui;
    QList<UserId> useridList;
    UserId temp;
};

#endif // SHARECONTROL_H
