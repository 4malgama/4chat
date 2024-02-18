#include "authform.h"
#include "ui_authform.h"


namespace client
{
    void login(const QString& login, const QString& password);
}

namespace authform
{
    AuthForm* w = nullptr;
    
    void close()
    {
        w = nullptr;
    }
    
    void show()
    {
        if (w == nullptr)
        {
            w = new AuthForm();
            QObject::connect(w, &AuthForm::event_close, close);
        }
        else
        {
            w->activateWindow();
        }
    }
    
    void hide()
    {
        if (w != nullptr)
        {
            w->close();
        }
    }
    
    void block()
    {
        w->setBlock(true);
    }
    
    void unblock()
    {
        w->setBlock(false);
    }
}

AuthForm::AuthForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    show();
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::setBlock(bool block)
{
    ui->leLogin->setDisabled(block);
    ui->lePassword->setDisabled(block);
    ui->pushButton->setDisabled(block);
    ui->cbRemember->setDisabled(block);
}

void AuthForm::closeEvent(QCloseEvent*)
{
    emit event_close();
    delete this;
}

void AuthForm::on_pushButton_clicked()
{
    QString login = ui->leLogin->text();
    QString password = ui->lePassword->text();
    
    if (login.isEmpty() || password.isEmpty())
        return;
    
    if (login.contains(';') || password.contains(';'))
        return;
    
    if (login.length() < 4 || password.length() < 4)
        return;
    
    client::login(login, password);
}

