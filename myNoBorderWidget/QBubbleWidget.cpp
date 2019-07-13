#include "QBubbleWidget.h"
#include <QPainter>
#include <QPolygon>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

QBubbleWidget::QBubbleWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("QBubbleWidget");
    m_nArrowStartX = 15;
    m_borderShadow = SHADOW_WIDTH;
    m_arrowDirection = QBubbleWidget::ArrowTop;
    m_nArrowHeight = ARROW_HEIGHT;
    m_nArrowWidth = ARROW_WIDTH;
    m_borderRadius = BORDER_RADIUS;

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 设置阴影边框;
    m_shadowEffect = new QGraphicsDropShadowEffect(this);
    m_shadowEffect->setOffset(0, 0);
    m_shadowEffect->setColor(Qt::gray);
    m_shadowEffect->setBlurRadius(m_borderShadow);
    this->setGraphicsEffect(m_shadowEffect);
}

void QBubbleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));                //白色


    QPainterPath painterPath;
    //绘制箭头
    QPolygon arrowPolygon;
    switch (m_arrowDirection) {
    case ArrowTop:
    {
        arrowPolygon.append(QPoint(m_nArrowStartX, m_nArrowHeight));
        arrowPolygon.append(QPoint(m_nArrowStartX + m_nArrowWidth / 2, 0));
        arrowPolygon.append(QPoint(m_nArrowStartX + m_nArrowWidth, m_nArrowHeight));

        painterPath.addRoundedRect(QRect(0, m_nArrowHeight,
                                         width(), height() - m_nArrowHeight),
                                         m_borderRadius, m_borderRadius);
    }
        break;
    case ArrowBottom:
    {
        arrowPolygon.append(QPoint(m_nArrowStartX, this->height() - m_nArrowHeight));
        arrowPolygon.append(QPoint(m_nArrowStartX + m_nArrowWidth / 2, this->height()));
        arrowPolygon.append(QPoint(m_nArrowStartX + m_nArrowWidth, this->height() - m_nArrowHeight));

        painterPath.addRoundedRect(QRect(0, 0,
                                         width(), height() - m_nArrowHeight),
                                         m_borderRadius, m_borderRadius);
    }
        break;
    case ArrowLeft:
    {
        arrowPolygon.append(QPoint(m_nArrowHeight, m_nArrowStartX));
        arrowPolygon.append(QPoint(0, m_nArrowStartX + m_nArrowWidth / 2));
        arrowPolygon.append(QPoint(m_nArrowHeight, m_nArrowStartX + m_nArrowWidth));

        painterPath.addRoundedRect(QRect(m_nArrowHeight, 0,
                                         width() - m_nArrowHeight, height()),
                                         m_borderRadius, m_borderRadius);
    }
        break;
    case ArrowRight:
    {
        arrowPolygon.append(QPoint(this->width() - m_nArrowHeight, m_nArrowStartX));
        arrowPolygon.append(QPoint(this->width(), m_nArrowStartX + m_nArrowWidth / 2));
        arrowPolygon.append(QPoint(this->width() - m_nArrowHeight, m_nArrowStartX + m_nArrowWidth));

        painterPath.addRoundedRect(QRect(0, 0,
                                         width() - m_nArrowHeight, height()),
                                         m_borderRadius, m_borderRadius);
    }
        break;
    }

    painterPath.addPolygon(arrowPolygon);
    painter.drawPath(painterPath);

}

//设置箭头方向，不设置时默认向上
void QBubbleWidget::setArrowDirection(ArrowDirection direction)
{
    m_arrowDirection = direction;
    this->repaint();
}

//设置三角箭头大小
void QBubbleWidget::setArrowSize(int width, int height)
{
    if(width > 1 && height > 0)
    {
        m_nArrowHeight = height;
        m_nArrowWidth = width;
    }
}

//设置起始位置
void QBubbleWidget::setArrowPosition(int startPos)
{
    if(startPos > 0)
    {
        switch (m_arrowDirection) {
        case ArrowTop:
        case ArrowBottom:
            if(startPos < this->width())
            {
                m_nArrowStartX = startPos;
            }
            break;
        case ArrowRight:
        case ArrowLeft:
            if(startPos < this->height())
            {
                m_nArrowStartX = startPos;
            }
            break;
        }
    }
}

//设置边框圆角大小
void QBubbleWidget::setBorderRadius(int width)
{
    m_borderRadius = width;
}

void QBubbleWidget::setBorderShadow(int width)
{
    m_borderShadow = width;
    m_shadowEffect->setBlurRadius(m_borderShadow);
    this->setGraphicsEffect(m_shadowEffect);
}

void QBubbleWidget::setShadowColor(QString color)
{
    m_shadowEffect->setColor(QColor(color));
    this->setGraphicsEffect(m_shadowEffect);
}

void QBubbleWidget::setCenterWidget(QWidget* widget)
{
    if(widget)
    {
        auto layout = new QHBoxLayout(this);
        switch (m_arrowDirection) {
        case ArrowTop:
            layout->setContentsMargins(0, m_nArrowHeight, 0, 0);
            break;
        case ArrowBottom:
            layout->setContentsMargins(0, 0, 0, m_nArrowHeight);
            break;
        case ArrowLeft:
            layout->setContentsMargins(m_nArrowHeight, 0, 0, 0);
            break;
        case ArrowRight:
            layout->setContentsMargins(0, 0, m_nArrowHeight, 0);
            break;
        }
        layout->setSpacing(0);
        layout->addWidget(widget);
    }
}
