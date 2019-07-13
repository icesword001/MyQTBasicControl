#include "BSPreviewWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>
#include <QPainterPath>
#include <QDebug>

BSPreviewWidget::BSPreviewWidget(QWidget *parent) : QStyleSheetWidget(parent)
{
    m_rectRc = QRect(0, 0, 0, 0);

    m_bPressed = false;
//    m_timer = new QTimer(this);
//    m_timer->setInterval(1);
//    connect(m_timer, &QTimer::timeout, this, [&]
//    {
//        if(m_bPressed)
//        {
//            this->repaint();
//        }
//    });
//    m_timer->start();
}


void BSPreviewWidget::setBackgroundImage(const QImage& image)
{
    m_image = image;
    centeredViewport(width(), height());
    repaint();
}

void BSPreviewWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿
    painter.fillRect(event->rect(), palette().window());    //填充默认背景
    painter.setViewport(m_imageRect);   //计算图片显示范围

    if(m_image.isNull())
    {
        return QStyleSheetWidget::paintEvent(event);
    }
    else
    {
        painter.drawPixmap(QRect(0, 0, width(), height()), QPixmap::fromImage(m_image));
        QPainterPath path;
        path.addRect(m_rectRc);
        qDebug() << "move rect.....:" << m_rectRc;
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.setViewTransformEnabled(false);
        painter.drawPath(path);
    }

}

void BSPreviewWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();
    if(m_imageRect.contains(pt) && m_rectRc.contains(pt))
    {
        m_bPressed = true;
        m_ptPressed = pt;
    }
    QWidget::mousePressEvent(event);
}

void BSPreviewWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPressed = false;
    repaint();
    QWidget::mouseReleaseEvent(event);
}

void BSPreviewWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPressed)
    {
        QPoint pt = event->pos();
        int nX = m_rectRc.x() - m_ptPressed.x() + pt.x();
        int nY = m_rectRc.y() - m_ptPressed.y() + pt.y();
        int nW = m_rectRc.width();
        int nH = m_rectRc.height();
        if(m_imageRect.contains(QPoint(nX, nY)) && m_imageRect.contains(QPoint(nX + nW - 1, nY + nH - 1)))
        {
            m_rectRc = QRect(nX, nY, nW, nH);
            m_ptPressed = pt;
            //m_lstPt.append(pt);
            qDebug() << "move .....:" << pt << m_ptPressed;
            repaint();
        }

        qDebug() << "move new rect.....:" << nX << nY << nW << nH << m_imageRect << pt;
        return;
    }
    QWidget::mouseMoveEvent(event);
}

QRect BSPreviewWidget::centeredViewport(int width, int height)
{
    double ratio = double(m_image.width())/double(m_image.height());
    int heightFromWidth = static_cast<int> (width / ratio);
    int widthFromHeight = static_cast<int> (height * ratio);

    if (heightFromWidth <= height)
    {
        m_imageRect = QRect(0,(height - heightFromWidth) / 2, width, heightFromWidth);
    }
    else
    {
        m_imageRect = QRect((width - widthFromHeight) / 2, 0, widthFromHeight, height);
    }
    m_rectRc = QRect(m_imageRect.x() + 2, m_imageRect.y() + 2, 100 , 100);

    return m_imageRect;
}
