#include "testWidget.h"
#include <QPushButton>

testWidget::testWidget(QWidget *parent) : QBubbleWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    m_layout->addWidget(new QPushButton("3ee"));
}
