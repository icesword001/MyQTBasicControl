#ifndef QCUSTOMWIDGET_H
#define QCUSTOMWIDGET_H

#include <QWidget>
#include "QNoBorderWidget.h"
#include <QVBoxLayout>
#include "QTitleWidget.h"
#include <QPushButton>
#include <QBubbleWidget.h>
#include <testWidget.h>
#include <BSPreviewWidget.h>
#include "BSPreviewView.h"

/*
 * 带标题栏的无边框窗体
 *
*/

class QCustomWidget : public QNoBorderWidget
{
    Q_OBJECT
public:
    explicit QCustomWidget(QWidget *parent = nullptr);

protected:
//    void paintEvent(QPaintEvent* event);
    virtual bool eventFilter(QObject* object, QEvent* event);
    virtual void changeEvent(QEvent *event);

private:
    QVBoxLayout*    m_vLayout;

    QPushButton*    m_btnTest;
    QTitleWidget*   m_titleWidget;

    QBubbleWidget*  m_bubbleWidget;
    BSPreviewWidget*    m_previewWidget;



signals:

public slots:
    void        sltTitleBtnClicked(QTitleWidget::ButtonStatus status);

    void        sltTest();
};

#endif // QCUSTOMWIDGET_H
