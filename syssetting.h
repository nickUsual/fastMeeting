#ifndef SYSSETTING_H
#define SYSSETTING_H

#include <QWidget>
#include<qsettings.h>
namespace Ui {
class SysSetting;
}

class SysSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SysSetting(QWidget *parent = nullptr);
    ~SysSetting();

private slots:

    void on_camCheckBox_stateChanged(int arg1);

    void on_pushButton_clicked();
signals:
    void sysClose();

private:
    QSettings *set;
    Ui::SysSetting *ui;
};

#endif // SYSSETTING_H
