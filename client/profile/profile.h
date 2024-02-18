#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
    class Profile;
}

class AccountData;

class Profile : public QWidget
{
    Q_OBJECT
    
public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();
    
    void init(const AccountData* accData);
    
signals:
    void event_close();
    
private slots:
    void on_btnSave_clicked();
    
private:
    Ui::Profile *ui;
    void closeEvent(QCloseEvent*);
};

#endif // PROFILE_H
