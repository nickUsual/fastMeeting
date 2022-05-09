#ifndef MEETINGINFOR_H
#define MEETINGINFOR_H

#include <QWidget>

namespace Ui {
class MeetingInfor;
}

class MeetingInfor : public QWidget
{
    Q_OBJECT

public:
    explicit MeetingInfor(QWidget *parent = nullptr);
    ~MeetingInfor();

private slots:
    void on_pushButton_clicked();
signals:
    void meetinginforClose();
private:
    Ui::MeetingInfor *ui;
};

#endif // MEETINGINFOR_H
