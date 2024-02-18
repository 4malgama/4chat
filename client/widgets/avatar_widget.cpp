#include "avatar_widget.h"
#include <QPainter>
#include <QPainterPath>


AvatarWidget::AvatarWidget(QWidget *parent)
    : QWidget(parent)
{
    roundRadius = 50;
    pixmap = QPixmap("cache/images/default_avatar.png");
}

AvatarWidget::AvatarWidget(const QPixmap& image, QWidget* parent)
    : QWidget(parent)
{
    if (image.isNull())
        pixmap = QPixmap("cache/images/default_avatar.png");
    else
        pixmap = image;
    roundRadius = 50;
}

const qreal& AvatarWidget::getRadius() const
{
    return roundRadius;
}

const QPixmap& AvatarWidget::getImage() const
{
    return pixmap;
}

void AvatarWidget::setRadius(qreal radius)
{
    roundRadius = radius;
}

void AvatarWidget::setImage(const QPixmap& image)
{
    pixmap = image;
}

void AvatarWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addRoundedRect(0, 0, width(), height(), roundRadius, roundRadius);
    p.setClipPath(path);
    if (!pixmap.isNull())
        p.drawPixmap(0, 0, pixmap.scaled(width(), height(), Qt::KeepAspectRatioByExpanding));
}

