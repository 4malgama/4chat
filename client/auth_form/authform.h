#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>

namespace Ui {
    class AuthForm;
}

class AuthForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();
    
    void setBlock(bool block);
    
signals:
    void event_close();
    
private slots:
    void on_pushButton_clicked();
    
private:
    Ui::AuthForm *ui;
    void closeEvent(QCloseEvent*);
};

#endif // AUTHFORM_H
