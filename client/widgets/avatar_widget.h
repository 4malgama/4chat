#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QLabel>


class AvatarWidget : public QWidget
{
    Q_OBJECT
    
    qreal roundRadius;
    QPixmap pixmap;
    
public:
    explicit AvatarWidget(QWidget *parent = nullptr);
    AvatarWidget(const QPixmap& image, QWidget* parent = nullptr);
    
    const qreal& getRadius() const;
    const QPixmap& getImage() const;
    void setRadius(qreal radius);
    void setImage(const QPixmap& image);
    
private:
    void paintEvent(QPaintEvent*) override;
};

#endif // AVATARWIDGET_H
