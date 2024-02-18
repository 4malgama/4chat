#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class AvatarWidget;

class MessageWidget : public QWidget
{
    Q_OBJECT
    
    AvatarWidget* avatar;
    QLabel* author;
    QLabel* text;
    
    QHBoxLayout* hLayout;   // main
    QVBoxLayout* vLayout;   // author & text
    
    void initUi(const QPixmap& image, const QString& name, const QString& message);
    
public:
    explicit MessageWidget(QWidget *parent = nullptr);
    MessageWidget(const QPixmap& image, const QString& name, const QString& message, QWidget* parent = nullptr);
    
    void setAvatar(const QPixmap& image);
    void setAuthor(const QString& name);
    void setText(const QString& message);
    
    const QPixmap& getAvatar() const;
    QString getAuthor() const;
    QString getText() const;

private:
    void paintEvent(QPaintEvent*) override;
};

#endif // MESSAGEWIDGET_H
