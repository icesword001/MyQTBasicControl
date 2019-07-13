#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include <QWidget>
#include "QStyleSheetWidget.h"

/*
 * 自定义widget标题栏
 *
 */

class QPushButton;
class QHBoxLayout;

class QTitleWidget : public QStyleSheetWidget
{
    Q_OBJECT
public:
    enum ButtonStatus {
        ButtonMin = 0,
        ButtonMax,
        ButtonRestore,
        ButtonClose
    };

    enum Buttons{
        BtnAll = 0,         //所有按钮都显示
        BtnCloseOnly,       //只显示关闭按钮
        BtnMinMax,          //只显示最大化和最小化
        BtnMinOnly,         //只显示最小化按钮
        BtnMaxOnly,         //只显示最大化按钮
    };

    //父类不能为nullptr
    explicit QTitleWidget(QWidget* parent, Buttons state = BtnAll);
    //设置标题栏高度
    void    setHeight(int nHeigth);
    //判断是否在标题栏上
    bool    isCaption(int x, int y);
    //更新最大化和还原按钮
    void    updateMaxState(Qt::WindowStates states);


protected:
    void    initButton(Buttons state);
    virtual bool eventFilter(QObject* object, QEvent* event);

private:
    QWidget*        m_parentWidget;
    QHBoxLayout*    m_hLayout;
    QPushButton*    m_btnMin;
    QPushButton*    m_btnMax;
    QPushButton*    m_btnRestore;
    QPushButton*    m_btnClose;

    int             m_nHeight;
    Buttons         m_buttonState;

signals:
    void            sigBtnClicked(QTitleWidget::ButtonStatus);
};

#endif // QTITLEWIDGET_H
