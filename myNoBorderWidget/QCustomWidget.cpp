#include "QCustomWidget.h"
#include <QDebug>
#include <QtWidgets/QtWidgets>

QCustomWidget::QCustomWidget(QWidget *parent) : QNoBorderWidget(parent)
{
    QWidget* widget = new QWidget(this);
    widget->setObjectName("QCustomWidget_widget");
    this->setObjectName("QCustomWidget_this");
    this->setFrameEnable(true);

    m_vLayout = new QVBoxLayout(widget);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setSpacing(0);

    m_titleWidget = new QTitleWidget(widget, QTitleWidget::BtnAll);
    connect(m_titleWidget, SIGNAL(sigBtnClicked(QTitleWidget::ButtonStatus)), this, SLOT(sltTitleBtnClicked(QTitleWidget::ButtonStatus)));
    m_vLayout->insertWidget(0, m_titleWidget, 0, Qt::AlignTop);

    m_btnTest = new QPushButton(widget);
    m_btnTest->setObjectName("btnTest");
    m_btnTest->setFixedSize(100, 32);
    connect(m_btnTest, &QPushButton::clicked, this, &QCustomWidget::sltTest);
    m_vLayout->addWidget(m_btnTest);

    m_bubbleWidget = new QBubbleWidget(widget);
    m_bubbleWidget->setFixedSize(100, 200);
    m_vLayout->addWidget(m_bubbleWidget, 0, Qt::AlignHCenter);

    m_previewWidget = new BSPreviewWidget(widget);
    m_previewWidget->setObjectName("m_previewWidget");
    m_previewWidget->setFixedSize(800, 300);
    m_vLayout->addSpacing(10);
    m_vLayout->addWidget(m_previewWidget, 0, Qt::AlignHCenter);

    m_vLayout->addStretch(1);
    this->setTitleWidget(m_titleWidget);


//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    m_shadowEffect->setColor(Qt::green);
//    m_previewWidget->setGraphicsEffect(m_shadowEffect);

//    m_vLayout->setMargin(16);

    widget->setStyleSheet("QWidget#QCustomWidget_widget{background-color:blue;border-radius:10px;}");

//    QGraphicsDropShadowEffect *m_shadowEffect = new QGraphicsDropShadowEffect(widget);
//    m_shadowEffect->setOffset(0, 0);
//    m_shadowEffect->setColor(Qt::red);
//    m_shadowEffect->setBlurRadius(10);
//    widget->setGraphicsEffect(m_shadowEffect);

//    m_previewWidget->installEventFilter(this);
//    this->installEventFilter(m_previewWidget);

    m_titleWidget->installEventFilter(this);

    this->setCenterWidget(widget);
    this->setEnableDbClickTitle(true);

}

bool QCustomWidget::eventFilter(QObject *object, QEvent *event)
{
    return QNoBorderWidget::eventFilter(object, event);
}

void QCustomWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)
    {
        Qt::WindowStates states = this->windowState();
        if(m_titleWidget)
        {
            m_titleWidget->updateMaxState(states);
        }
    }
    return QNoBorderWidget::changeEvent(event);
}


void QCustomWidget::sltTitleBtnClicked(QTitleWidget::ButtonStatus status)
{
    switch (status) {
    case QTitleWidget::ButtonMin:
        this->showMinimized();
        break;

    case QTitleWidget::ButtonMax:
        this->showMaximized();
        break;

    case QTitleWidget::ButtonRestore:
        this->showNormal();
        break;

    case QTitleWidget::ButtonClose:
        this->close();
        break;

    default:
        break;
    }

}

void QCustomWidget::sltTest()
{
    qDebug() << "button click............." << QString::fromLocal8Bit("客户看看是否速度飞快是开的飞快");
    qDebug() << m_bubbleWidget->size();

    m_bubbleWidget->setArrowSize(30, 30);
    m_bubbleWidget->setArrowPosition(30);
    m_bubbleWidget->setBorderRadius(30);
    m_bubbleWidget->setBorderShadow(30);
    m_bubbleWidget->setArrowDirection(QBubbleWidget::ArrowLeft);
    m_bubbleWidget->setShadowColor("red");

    QLabel* label = new QLabel("tewteet");
    m_bubbleWidget->setCenterWidget(label);

    QImage image;
    if(image.load(QString::fromLocal8Bit("E:/work/首页_展示图/1.png")))
    {
        m_previewWidget->setBackgroundImage(image);
    }
}
