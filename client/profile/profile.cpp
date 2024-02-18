#include "profile.h"
#include "ui_profile.h"
#include "classes.h"
#include "client.h"

#include <QFile>

#include <QDebug>

namespace profile
{
    Profile* w = nullptr;
    
    void close()
    {
        w = nullptr;
    }
    
    void show(const AccountData* accData)
    {
        if (w == nullptr)
        {
            w = new Profile();
            QObject::connect(w, &Profile::event_close, close);
            w->init(accData);
        }
        else
        {
            w->activateWindow();
        }
    }
}

namespace client { Client* get(); }

namespace
{
    const int MAX_RANK_SCORE = 100000;
    const int START_NEXT_SCORE = 100;
    const int STEP_NEXT_SCORE = 300;
    
    int clamp(int min, int max, int value)
    {
        return (value < min ? min : (value > max ? max : value));
    }
    
    int nextDeltaScore(int rank)
    {
        return clamp(0, MAX_RANK_SCORE, START_NEXT_SCORE + STEP_NEXT_SCORE * rank);
    }
    
    int nextScore(int rank)
    {
        int d = 0;
        for (int i = 0; i <= rank; i++)
            d += nextDeltaScore(i);
        return d;
    }
}

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);

    ui->iconMoney->setPixmap(QPixmap(":/icons/resources/icons/money.png").scaled(20, 20, Qt::KeepAspectRatio));
    ui->iconGold->setPixmap(QPixmap(":/icons/resources/icons/gold.png").scaled(24, 24, Qt::KeepAspectRatio));
    
    show();
}

Profile::~Profile()
{
    delete ui;
}

void Profile::init(const AccountData* accData)
{
    ui->avatar->setPixmap(client::get()->avatar());
    ui->fieldMoney->setText(QString::number(accData->money));
    ui->fieldGold->setText(QString::number(accData->gold));
    
    ui->progress->setMaximum(nextScore(accData->rank));
    ui->progress->setMinimum(nextScore(accData->rank - 1));
    ui->progress->setValue(accData->score);
    ui->progress->setFormat("%v/" + QString::number(ui->progress->maximum()));
    
    ui->rankImage->setPixmap(QPixmap("cache/images/ranks/" + QString::number(accData->rank) + ".png", "PNG").scaled(ui->rankImage->size()));
    
    ui->displayName->setText(accData->displayName);
}

void Profile::closeEvent(QCloseEvent*)
{
    emit event_close();
    delete this;
}

void Profile::on_btnSave_clicked()
{
    close();
}

