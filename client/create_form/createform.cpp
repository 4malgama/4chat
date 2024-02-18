#include "createform.h"
#include "ui_createform.h"

#include <QDebug>

namespace client
{
    void createRoom(const QString& name, int maxCount, int minRank, int maxRank, bool vip, int cost);
}

namespace createform
{
    CreateForm* w = nullptr;
    
    void close()
    {
        w = nullptr;
    }
    
    void show()
    {
        if (w == nullptr)
        {
            w = new CreateForm();
            QObject::connect(w, &CreateForm::event_close, close);
        }
        else
        {
            w->activateWindow();
        }
    }
}

CreateForm::CreateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateForm)
{
    ui->setupUi(this);
    
    int minRank = ui->sliderMinRank->value();
    int maxRank = ui->sliderMaxRank->value();
    
    ui->lblMinR->setText("Мин. ранг (" + QString::number(minRank) + "):");
    ui->lblMaxR->setText("Макс. ранг (" + QString::number(maxRank) + "):");
    
    show();
}

CreateForm::~CreateForm()
{
    delete ui;
}

void CreateForm::closeEvent(QCloseEvent*)
{
    emit event_close();
    delete this;
}

void CreateForm::checkFields()
{
    QString name = ui->leName->text();
    bool bad = (name.contains(QRegExp("[ \\[\\]!@#\\$%\\^&\\*\\(\\)-+:;'\"/\\?><\\.,]")) || (name.length() < 3));
    ui->btnCreate->setDisabled(bad);
}

void CreateForm::on_btnCreate_clicked()
{
    client::createRoom(
        ui->leName->text(),
        ui->sbMaxCount->value(),
        ui->sliderMinRank->value(),
        ui->sliderMaxRank->value(),
        ui->groupBox_2->isChecked(),
        ui->sbCost->value()
    );
    close();
}


void CreateForm::on_leName_textChanged(const QString &arg)
{
    checkFields();
}


void CreateForm::on_sliderMinRank_valueChanged(int value)
{
    if (value > ui->sliderMaxRank->value())
        ui->sliderMaxRank->setValue(value);
    
    int minRank = ui->sliderMinRank->value();
    int maxRank = ui->sliderMaxRank->value();
    
    ui->lblMinR->setText("Мин. ранг (" + QString::number(minRank) + "):");
    ui->lblMaxR->setText("Макс. ранг (" + QString::number(maxRank) + "):");
}


void CreateForm::on_sliderMaxRank_valueChanged(int value)
{
    if (value < ui->sliderMinRank->value())
        ui->sliderMinRank->setValue(value);
    
    int minRank = ui->sliderMinRank->value();
    int maxRank = ui->sliderMaxRank->value();
    
    ui->lblMinR->setText("Мин. ранг (" + QString::number(minRank) + "):");
    ui->lblMaxR->setText("Макс. ранг (" + QString::number(maxRank) + "):");
}

