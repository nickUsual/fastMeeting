#include "syssetting.h"
#include "ui_syssetting.h"
#include "ExternVariable.h"
#include <QSettings>
#include <QDebug>
SysSetting::SysSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysSetting)
{
    ui->setupUi(this);
    QString fileName = QCoreApplication::applicationDirPath();

     set= new QSettings(fileName+"/startSetting.ini", QSettings::IniFormat);
     ui->camCheckBox->setChecked(set->value("camera/enable").toBool());
     ui->redioCheckBox->setChecked(set->value("microphone/enable").toBool());
     ui->micCheckBox->setChecked(set->value("redio/enable").toBool());
     ui->speakCheckBox->setChecked(set->value("speaker/enable").toBool());
    connect(ui->camCheckBox, &QCheckBox::stateChanged, this, [=](int enable)
    {
        set->setValue("camera/enable",bool(enable));
        set->sync();
    });
    connect(ui->redioCheckBox, &QCheckBox::stateChanged, this, [=](int enable)
    {
        set->setValue("microphone/enable",bool(enable));
        set->sync();
    });
    connect(ui->micCheckBox, &QCheckBox::stateChanged, this, [=](int enable)
    {
        set->setValue("redio/enable",bool(enable));
        set->sync();
    });
    connect(ui->speakCheckBox, &QCheckBox::stateChanged, this, [=](int enable)
    {
        set->setValue("speaker/enable",bool(enable));
        set->sync();
    });
}

SysSetting::~SysSetting()
{
    delete ui;
}

void SysSetting::on_camCheckBox_stateChanged(int arg1)
{

}

void SysSetting::on_pushButton_clicked()
{
    if(ui->camCheckBox->isChecked() == true){

        qDebug() << "测试-------"<< set->value("camera/enable").toBool();
       set->setValue("camera/enable",true);
       set->sync();
    }else{
        qDebug() << "打开了";
       set->setValue("camera/enable",false);
    }


    if(ui->redioCheckBox->isChecked()== true){
       set->setValue("microphone/enable",true);
    }else{
       set->setValue("microphone/enable",false);
    }


    if(ui->micCheckBox->isChecked() == true){
       set->setValue("redio/enable",true);
    }else{
       set->setValue("redio/enable",false);
    }


    if(ui->speakCheckBox->isChecked() == true){
       set->setValue("speaker/enable",true);
    }else{
       set->setValue("speaker/enable",false);
    }
    emit sysClose();

}
