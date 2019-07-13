#include "QStyleSheetWidget.h"
#include <QStyleOption>
#include <QPainter>

QStyleSheetWidget::QStyleSheetWidget(QWidget *parent) : QWidget(parent)
{

}

void QStyleSheetWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
