#ifndef BSPREVIEWWIDGET_H
#define BSPREVIEWWIDGET_H

#include <QWidget>
#include "QStyleSheetWidget.h"
#include <QTimer>
/*
 * 预览控制区
 *
 */

class BSPreviewWidget : public QStyleSheetWidget
{
    Q_OBJECT
public:
    explicit BSPreviewWidget(QWidget *parent = nullptr);

    void    setBackgroundImage(const QImage& image);     //设置背景图

protected:
    void    paintEvent(QPaintEvent* event);
    void    mousePressEvent(QMouseEvent *event);
    void    mouseReleaseEvent(QMouseEvent *event);
    void    mouseMoveEvent(QMouseEvent *event);

    //计算图片显示位置（保证图片不变形）
    QRect   centeredViewport(int width, int height);


private:
    QImage          m_image;
    int             m_nTopBorderWidth;      //图片显示距离上边距离；
    int             m_nLeftBorderWidth;

    QRect           m_rectRc;               //控制矩形显示区域
    QRect           m_imageRect;            //图片显示位置
    bool            m_bPressed;
    bool            m_bMove;
    QPoint          m_ptPressed;
    QList<QPoint>      m_lstPt;
    QTimer*         m_timer;

signals:

public slots:
};

#endif // BSPREVIEWWIDGET_H
