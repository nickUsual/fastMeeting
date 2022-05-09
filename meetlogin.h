#ifndef MEETLOGIN_H
#define MEETLOGIN_H

#include <QWidget>

namespace Ui {
class meetlogin;
}

class meetlogin : public QWidget
{
    Q_OBJECT

public:
    explicit meetlogin(QWidget *parent = nullptr);
    ~meetlogin();

private slots:
    void on_visiableButton_clicked();

    void on_enterAdmin_clicked();

private:
    Ui::meetlogin *ui;
    bool passwd_Visiable;
    QWidget *mywidget;
};

#endif // MEETLOGIN_H
