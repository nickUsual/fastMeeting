#ifndef RECVCONTROLWIDGET_H
#define RECVCONTROLWIDGET_H

#include <QWidget>
#include "ExternVariable.h"
#include <QMessageBox>
namespace Ui {
class RecvControlWidget;
}

class RecvControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecvControlWidget(QWidget *parent=nullptr,UserId id=0);
    ~RecvControlWidget();

private slots:
    void on_agreeControl_clicked();

    void on_disagreeControl_clicked();

private:
    Ui::RecvControlWidget *ui;
    UserId otherId;
};

#endif // RECVCONTROLWIDGET_H
