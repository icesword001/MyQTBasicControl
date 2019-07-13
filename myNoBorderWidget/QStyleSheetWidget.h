#ifndef QSTYLESHEETWIDGET_H
#define QSTYLESHEETWIDGET_H

#include <QWidget>

/*
 * 自绘widget的基类，使之能够独立使用stylesheet，不受父类stylesheet影响
 *
*/

class QStyleSheetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QStyleSheetWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // QSTYLESHEETWIDGET_H
