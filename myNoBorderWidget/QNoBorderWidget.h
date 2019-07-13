#ifndef QNOBORDERWIDGET_H
#define QNOBORDERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

/*
 * 去除系统自带边框，实现边框可变且无闪烁（windows平台， 依赖User32.lib），支持边框阴影，支持圆角
 *
 *
 *
*/

class QNoBorderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QNoBorderWidget(QWidget *parent = nullptr);
    virtual void    setFrameWidth(int nWidth);                              //设置边框宽度
    virtual void    setFrameEnable(bool bEnable);                           //是否可通过边框改变大小
    void            setTitleWidget(QWidget* widget);                        //设置圆角时， CenterWidget 与TitleWidget圆角需要保持一样
    void            setShadowWidth(int nWidth, QColor color);               //设置阴影宽度
    void            setCenterWidget(QWidget* widget);
    void            setEnableDbClickTitle(bool bEnable);                    //是否可以双击标题栏
    void            setToolWindowStyle(bool bToolStyle);                    //是否显示在任务栏

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    bool isChildContorl(int xPos, int yPos);                                    //检测是否在边框上

protected:
    int     m_titleHeight;              //标题栏高度
    int     m_nframeWidth;              //边框宽度
    QWidget*    m_Widget;               //标题栏
    QWidget*    m_centerWidget;         //阴影层
    bool    m_bFrameEnable;             //边框是否可变
    int     m_nShadowWidth;             //阴影宽度
    QColor  m_shadowColor;
    bool    m_bDbClick;
    int     m_nMinWidth;                //可调整的最小范围
    int     m_nMinHeight;

    QHBoxLayout*    m_layout;           //

signals:
    void    sigDoubleClick();

public slots:
};

#endif // QNOBORDERWIDGET_H
