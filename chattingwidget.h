#ifndef CHATTINGWIDGET_H
#define CHATTINGWIDGET_H

#include <QWidget>

namespace Ui {
class ChattingWidget;
}

class ChattingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChattingWidget(QWidget *parent = nullptr);
    ~ChattingWidget();

private:
    Ui::ChattingWidget *ui;
};

#endif // CHATTINGWIDGET_H
