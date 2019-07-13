#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QBubbleWidget.h>
#include <QHBoxLayout>

class testWidget : public QBubbleWidget
{
    Q_OBJECT
public:
    explicit testWidget(QWidget *parent = nullptr);


private:
    QHBoxLayout* m_layout;
signals:

public slots:
};

#endif // TESTWIDGET_H
