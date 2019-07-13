#ifndef QBUBBLEWIDGET_H
#define QBUBBLEWIDGET_H

#include <QWidget>

/*
 * 带三角箭头气泡的无边框窗体，可做为基类，也可以做为parent直接添加其它内容
 * 支持4个方向，带4边阴影
 * 做为基类使用时，需要根据三角箭头方向和大小设置新的布局边缘距离，参考setCenterWidget接口
*/

//默认值
#define SHADOW_WIDTH 10                 // 窗口阴影宽度;
#define ARROW_WIDTH 15                  // 三角的宽度;
#define ARROW_HEIGHT 10                 // 三角的高度;
#define BORDER_RADIUS 5                 // 窗口边角的弧度;

class QGraphicsDropShadowEffect;
class QBubbleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QBubbleWidget(QWidget *parent = nullptr);

    //三角箭头方向
    enum ArrowDirection{
        ArrowTop = 0,
        ArrowRight,
        ArrowBottom,
        ArrowLeft
    };

    //设置箭头方向，不设置时默认向上
    void    setArrowDirection(ArrowDirection direction);
    //设置三角箭头大小
    void    setArrowSize(int width, int height);
    //设置起始位置
    void    setArrowPosition(int startPos);

    //设置边框圆角大小
    void    setBorderRadius(int width);

    //设置边框阴影大小
    void    setBorderShadow(int width);
    //设置阴影颜色
    void    setShadowColor(QString color);

    //增加内部widget
    void    setCenterWidget(QWidget* widget);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_nArrowStartX;                 //三角到边缘的距离，箭头在上下时，到左边的距离；箭头在左右时，距离到top的距离
    int m_nArrowWidth;                  //三角箭头的宽度（底边宽）
    int m_nArrowHeight;                 //三角箭头的高度（底边到对角高度）
    ArrowDirection m_arrowDirection;    //方向

    QString m_borderColor;
    int     m_borderWidth;
    int     m_borderRadius;

    int     m_borderShadow;
    QGraphicsDropShadowEffect* m_shadowEffect;

signals:

public slots:
};

#endif // QBUBBLEWIDGET_H
