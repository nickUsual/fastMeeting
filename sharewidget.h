#ifndef SHAREWIDGET_H
#define SHAREWIDGET_H

#include <QWidget>
#include <QLabel>
#include<QResizeEvent>
namespace Ui {
class ShareWidget;
}

class ShareWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShareWidget(QWidget *parent = nullptr);
    ~ShareWidget();
    QLabel * getLabel();

   void resizeEvent(QResizeEvent* size) override;

private:
    int currentW ; // 用以记录当前窗体宽度
    int currentH ;// 用以记录当前窗体高度
    Ui::ShareWidget *ui;
    //展示共享桌面的图片
    QLabel * shareLabel;
};

#endif // SHAREWIDGET_H
