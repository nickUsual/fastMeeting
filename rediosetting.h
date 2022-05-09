#ifndef REDIOSETTING_H
#define REDIOSETTING_H

#include <QWidget>

namespace Ui {
class RedioSetting;
}

class RedioSetting : public QWidget
{
    Q_OBJECT

public:
    explicit RedioSetting(QWidget *parent = nullptr);
    ~RedioSetting();

private slots:
    void on_pushButton_clicked();
signals:
    void redioSettingClose();

private:
    Ui::RedioSetting *ui;
};

#endif // REDIOSETTING_H
