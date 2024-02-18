#ifndef CREATEFORM_H
#define CREATEFORM_H

#include <QWidget>

namespace Ui {
    class CreateForm;
}

class CreateForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CreateForm(QWidget *parent = nullptr);
    ~CreateForm();
    
signals:
    void event_close();
    
private slots:
    void on_btnCreate_clicked();
    
    void on_leName_textChanged(const QString &arg1);
    
    void on_sliderMinRank_valueChanged(int value);
    
    void on_sliderMaxRank_valueChanged(int value);
    
private:
    Ui::CreateForm *ui;
    void closeEvent(QCloseEvent*) override;
    void checkFields();
};

#endif // CREATEFORM_H
