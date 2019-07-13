#include "QTitleWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QDebug>

QTitleWidget::QTitleWidget(QWidget* parent, Buttons state)
{
    if(!parent)
    {
        Q_ASSERT_X(0, "error", "parent is nullptr in TitleWidget");
    }
    m_parentWidget = parent;
    m_btnMin = nullptr;
    m_btnMax = nullptr;
    m_btnRestore = nullptr;
    m_btnClose = nullptr;
    m_nHeight = 32;
    m_buttonState = state;

    this->setFixedHeight(m_nHeight);

    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setContentsMargins(0, 0, 2, 0);
    m_hLayout->setSpacing(0);
    m_hLayout->addStretch(1);

    this->setStyleSheet(QString("QWidget{background-color:gray;}"));
    //注册事件
//    m_parentWidget->installEventFilter(this);

    initButton(m_buttonState);

}

void QTitleWidget::initButton(Buttons state)
{
    Q_ASSERT(!(m_btnMin || m_btnMax || m_btnRestore || m_btnClose));
    if(state == BtnAll || state == BtnMinMax || state == BtnMinOnly)
    {
        // 最小化按钮
        m_btnMin = new QPushButton("min", this);
        m_btnMin->setObjectName("min");
        m_btnMin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_btnMin->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
        m_btnMin->setFixedWidth(80);
        connect(m_btnMin, &QPushButton::clicked, [&]() {
            emit sigBtnClicked(ButtonMin);
        });
        m_hLayout->addWidget(m_btnMin, 0, Qt::AlignVCenter);
    }

    if(state == BtnAll || state == BtnMinMax || state == BtnMaxOnly)
    {
        // 最大化按钮
        m_btnMax = new QPushButton("max", this);
        m_btnMax->setObjectName("max");
        m_btnMax->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_btnMax->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
        m_btnMax->setFixedWidth(80);
        connect(m_btnMax, &QPushButton::clicked, [&](bool) {
            emit sigBtnClicked(ButtonMax);
        });
        m_hLayout->addWidget(m_btnMax);

        // 还原按钮
        m_btnRestore = new QPushButton("restore", this);
        m_btnRestore->setObjectName("restore");
        m_btnRestore->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_btnRestore->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
        m_btnRestore->setFixedWidth(80);
        m_btnRestore->hide();
        connect(m_btnRestore, &QPushButton::clicked, [&]() {
            emit sigBtnClicked(ButtonRestore);
        });
        m_hLayout->addWidget(m_btnRestore);
    }

    if(state == BtnAll || state == BtnCloseOnly )
    {
        // 关闭按钮
        m_btnClose = new QPushButton("close", this);
        m_btnClose->setObjectName("close");
        m_btnClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_btnClose->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
        m_btnClose->setFixedWidth(80);
        connect(m_btnClose, &QPushButton::clicked, [&]() {
            emit sigBtnClicked(ButtonClose);
        });
        m_hLayout->addWidget(m_btnClose);
    }

}

bool QTitleWidget::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::WindowStateChange)
    {
        Qt::WindowStates states = m_parentWidget->windowState();
        updateMaxState(states);

        return true;
    }
//    qDebug() << "event is " << event->type() << object;

    return QWidget::eventFilter(object, event);
}

void QTitleWidget::setHeight(int nHeigth)
{
    if(nHeigth > 0)
    {
        m_nHeight = nHeigth;
        this->setFixedHeight(m_nHeight);
    }
}

bool QTitleWidget::isCaption(int x, int y)
{
    if(this->rect().contains(x, y))
    {
        if(!this->childAt(x, y))
        {
            return true;
        }
    }
    return false;
}

void QTitleWidget::updateMaxState(Qt::WindowStates states)
{
    if (m_buttonState == BtnAll || m_buttonState == BtnMinMax || m_buttonState == BtnMaxOnly)
    {
        if (states & Qt::WindowMaximized)
        {
            m_btnMax->hide();
            m_btnRestore->show();
        }
        else
        {

            m_btnRestore->hide();
            m_btnMax->show();
        }
    }
}
