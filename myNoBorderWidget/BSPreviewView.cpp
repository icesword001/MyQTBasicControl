#include "BSPreviewView.h"
#include <QGraphicsItem>

BSGraphicsRectItem::BSGraphicsRectItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
}

QVariant BSGraphicsRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionHasChanged && scene()) {
        qDebug() << "scene rect is :" << this->rect();
        return QGraphicsRectItem::itemChange(change, value);
        // value is the new position.
        QPointF ptTL = this->rect().topLeft();
        QPointF ptBR = this->rect().bottomRight();

        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        QPointF rectLTPos = QPointF(newPos.x() + rect.x(), newPos.y() + rect.y());
        QPointF rectBRPos = QPointF(newPos.x() + rect.x() + this->rect().width(), newPos.y() + rect.y() + this->rect().height());
        qDebug() << "scene rect is :" << rect << newPos << this->rect() << rectLTPos << rectBRPos;
        QRectF rectS = QRectF(0, 0, rect.width(), rect.height());
        QPointF newTL = QPointF(newPos.x() + rect.x(), newPos.y() + rect.y());
        QPointF newBR = QPointF(newTL.x() + this->rect().width(), newTL.y() + this->rect().height());
        if(rect.contains(ptTL) && rect.contains(ptBR))
        {
            this->setRect(newTL.x(), newTL.y(),  this->rect().width(), this->rect().height());
            return newPos;
        }
        else
        {
            if(rect.contains(ptTL))
            {
                if(newBR.x() >= rect.bottomRight().x())
                {
                    newBR.setX(rect.bottomRight().x());
                    newTL.setX(rect.bottomRight().x() - this->rect().width());
                }

                if(newBR.y() >= rect.bottomRight().y())
                {
                    newBR.setY(rect.bottomRight().y());
                    newTL.setY(rect.bottomRight().y() - this->rect().height());
                }
            }
            else
            {
                if(newTL.x() < rect.topLeft().x())
                {
                    newTL.setX(rect.topLeft().x());
                }

                if(newTL.y() < rect.topLeft().y())
                {
                    newTL.setY(rect.topLeft().y());
                }
            }
            this->setRect(newTL.x(), newTL.y(),  this->rect().width(), this->rect().height());
            //this->setRect(newPos.x(), newPos.y(), this->rect().width(), this->rect().height());
            return newPos;
        }

//        if (!rectS.contains(newPos)) {
//            // Keep the item inside the scene rect.
//            newPos.setX(qMin(rectS.right(), qMax(newPos.x(), rectS.left())));
//            newPos.setY(qMin(rectS.bottom(), qMax(newPos.y(), rectS.top())));
//        }
//        else
//        {

//        }
        qDebug() << "scene rect is 22222222:" << rect << newPos;
        return newPos;
        //return QGraphicsRectItem::itemChange(change, newPos);;
    }
    return QGraphicsRectItem::itemChange(change, value);
}

void BSGraphicsRectItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsRectItem::dragMoveEvent(event);
}

BSPreviewView::BSPreviewView(QWidget *parent) : QStyleSheetWidget(parent)
{
    m_view = new QGraphicsView(this);
    m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_scene = new QGraphicsScene(this);
    m_view->setScene(m_scene);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->hide();

    this->setStyleSheet("background-color:white;");
}

void BSPreviewView::setBackgroundImage(const QImage& image)
{
    m_image = image;
    if(!m_image.isNull())
    {
        centeredViewport(width(), height());
        m_view->setGeometry(m_imageRect);
        m_scene->setSceneRect(m_imageRect);
        QGraphicsPixmapItem* itemImage = new QGraphicsPixmapItem;
        QPixmap pixmap = QPixmap::fromImage(m_image);
        pixmap = pixmap.scaled(m_imageRect.width(), m_imageRect.height());
        itemImage->setPixmap(pixmap);
        itemImage->setPos(m_imageRect.x(), m_imageRect.y());
        m_scene->addItem(itemImage);
        drawControlRect();
        m_view->show();
    }

}

void BSPreviewView::drawControlRect()
{
    if(!m_image.isNull())
    {
        m_itemRect = new BSGraphicsRectItem;
        m_itemRect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemSendsGeometryChanges);
        m_itemRect->setRect(m_rectRc);
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
        pen.setStyle(Qt::SolidLine);
        m_itemRect->setPen(pen);
        m_scene->addItem(m_itemRect);
    }
}

QRect BSPreviewView::centeredViewport(int width, int height)
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
    //m_rectRc = QRect(m_imageRect.x() + 2, m_imageRect.y() + 2, m_imageRect.width() - 4 , m_imageRect.height() - 4);
    m_rectRc = QRect(m_imageRect.x(), m_imageRect.y(), 100 , 100);

    return m_imageRect;
}
