#include "message_widget.h"
#include "avatar_widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>


void MessageWidget::initUi(const QPixmap& image, const QString& name, const QString& message)
{
    hLayout = new QHBoxLayout(this);
    hLayout->setSpacing(6);
    hLayout->setContentsMargins(4, 4, 0, 4);
    vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0, 0, 0, 0);
    
    avatar = new AvatarWidget(image, this);
    
    avatar->setMaximumSize(40, 40);
    avatar->setMinimumSize(40, 40);
    
    author = new QLabel(this);
    author->setFont(QFont("Roboto", 10));
    author->setText("<b>" + name + "</b>");
    author->setTextFormat(Qt::RichText);
    
    text = new QLabel(this);
    text->setFont(QFont("Roboto", 10));
    text->setText(message);
    //text->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    text->setTextFormat(Qt::RichText);
    
    vLayout->addWidget(author);
    vLayout->addWidget(text);
    
    hLayout->addWidget(avatar);
    hLayout->addItem(vLayout);
    
    setMinimumHeight(sizeHint().height());
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

MessageWidget::MessageWidget(QWidget *parent)
    : QWidget{parent}
{
    initUi(QPixmap(), "Anonymous", QString());
}

MessageWidget::MessageWidget(const QPixmap& image, const QString& name, const QString& message, QWidget* parent)
    : QWidget(parent)
{
    initUi(image, name, message);
}

void MessageWidget::setAvatar(const QPixmap& image)
{
    avatar->setImage(image);
}

void MessageWidget::setAuthor(const QString& name)
{
    author->setText(name);
}

void MessageWidget::setText(const QString& message)
{
    text->setText(message);
}

const QPixmap& MessageWidget::getAvatar() const
{
    return avatar->getImage();
}

QString MessageWidget::getAuthor() const
{
    return author->text();
}

QString MessageWidget::getText() const
{
    return text->text();
}

void MessageWidget::paintEvent(QPaintEvent* e)
{
    QPen pen;
    pen.setWidth(0);
    pen.setColor(Qt::transparent);
    
    QBrush brush(QColor(255, 255, 255, 20));
    
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    p.setPen(pen);
    p.setBrush(brush);
    p.drawRoundedRect(0, 0, width(), height(), 10, 10);
}
