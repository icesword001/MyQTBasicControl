#ifndef BSPREVIEWVIEW_H
#define BSPREVIEWVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include "QStyleSheetWidget.h"
#include <QGraphicsRectItem>
#include <QDebug>

class BSGraphicsRectItem : public QGraphicsRectItem
{
public:
    explicit BSGraphicsRectItem(QGraphicsItem *parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
};

class BSPreviewView : public QStyleSheetWidget
{
    Q_OBJECT
public:
    explicit BSPreviewView(QWidget *parent = nullptr);

    void    setBackgroundImage(const QImage& image);     //设置背景图


protected:
    //计算图片显示位置（保证图片不变形）
    QRect   centeredViewport(int width, int height);
    void    drawControlRect();

private:
    QGraphicsView*      m_view;
    QGraphicsScene*     m_scene;

    QImage          m_image;
    int             m_nTopBorderWidth;      //图片显示距离上边距离；
    int             m_nLeftBorderWidth;

    QRect           m_rectRc;               //控制矩形显示区域
    QRect           m_imageRect;            //图片显示位置
    bool            m_bPressed;
    bool            m_bMove;
    QPoint          m_ptPressed;

    BSGraphicsRectItem* m_itemRect;         //控制框大小


signals:

public slots:
};

#endif // BSPREVIEWVIEW_H
