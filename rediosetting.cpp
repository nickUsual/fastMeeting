#include "rediosetting.h"
#include "ui_rediosetting.h"
#include "ExternVariable.h"

RedioSetting::RedioSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RedioSetting)
{
    ui->setupUi(this);
    ui->microlSlider->setRange(0,100);
    ui->microlSlider->setSingleStep(1);
    ui->microlSlider->setValue(kern->get_input_volume() * 100);
    ui->redionSlider->setRange(0,100);
    ui->redionSlider->setSingleStep(1);
    ui->redionSlider->setValue(kern->get_output_volume() * 100);
    for(auto i :kern->get_input_list()){
         ui->micoComBox->addItem(i);
    }
    ui->micoComBox->setCurrentIndex(kern->get_input());
    for(auto i:kern->get_output_list()){
        ui->redioComboBox->addItem(i);
    }
    ui->redioComboBox->setCurrentIndex(kern->get_outout());
    connect(ui->micoComBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=](int idx)
    {
        kern->set_input(ui->micoComBox->currentIndex());
        ui->microlSlider->setValue(kern->get_input_volume() * 100);
    });
    connect(ui->redioComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=](int idx)
    {
        kern->set_output(ui->redioComboBox->currentIndex());
        ui->redionSlider->setValue(kern->get_output_volume() * 100);
    });
    connect(ui->microlSlider, &QSlider::sliderMoved, this, [=](int pos){
        kern->set_input_volume(pos /double(100));
    });
    connect(ui->redionSlider, &QSlider::sliderMoved, this, [=](int pos){
        kern->set_output_volume(pos /double(100));
    });
}

RedioSetting::~RedioSetting()
{
    delete ui;
}

void RedioSetting::on_pushButton_clicked()
{
    //
    emit redioSettingClose();
}
