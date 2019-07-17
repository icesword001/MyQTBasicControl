#include "QNoBorderWidget.h"
#include <QDebug>

#ifdef Q_OS_WIN
#include <windowsx.h>
#include <Windows.h>
#pragma comment (lib,"user32.lib")
#endif // Q_OS_WIN

#include <QGraphicsDropShadowEffect>

QNoBorderWidget::QNoBorderWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint/* |Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint*/);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_StyledBackground);

#ifdef Q_OS_WIN
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
//    const MARGINS shadow = { 5, 5, 5, 5 };
//    DwmExtendFrameIntoClientArea(hwnd, &shadow);
#endif // Q_OS_WIN

    m_titleHeight = 0;
    m_nframeWidth = 4;
    m_Widget = nullptr;
    m_bFrameEnable = true;
    m_nShadowWidth = 15;
    m_centerWidget = nullptr;
    m_shadowColor = Qt::darkGray;
    m_bDbClick = true;
    m_nMinWidth = 800;
    m_nMinHeight = 30;

    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(m_nShadowWidth, m_nShadowWidth, m_nShadowWidth, m_nShadowWidth);
    m_layout->setSpacing(0);
}

bool QNoBorderWidget::isChildContorl(int xPos, int yPos)
{
    if(m_Widget && m_Widget->childAt(xPos - m_nShadowWidth, yPos - m_nShadowWidth))
    {
        return true;
    }
    return false;
}

bool QNoBorderWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Q_OS_WIN
    MSG* msg = (MSG*)message;
    switch (msg->message) {
    case WM_NCHITTEST://边框可变
    {
        const int nFrameShadow = m_nShadowWidth; //边框阴影
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();

        if(m_bFrameEnable && !::IsZoomed(msg->hwnd))
        {
            if(!isChildContorl(xPos, yPos))
            {
                if (xPos > nFrameShadow && xPos < m_nframeWidth + nFrameShadow)
                    *result = HTLEFT;
                if (xPos > (this->width() - m_nframeWidth - nFrameShadow) && xPos < (this->width() - nFrameShadow))
                    *result = HTRIGHT;
                if (yPos > nFrameShadow && yPos < m_nframeWidth + nFrameShadow)
                    *result = HTTOP;
                if (yPos > (this->height() - m_nframeWidth - nFrameShadow) && yPos < (this->height() - nFrameShadow))
                    *result = HTBOTTOM;
                if (xPos > nFrameShadow && xPos < m_nframeWidth + nFrameShadow && yPos > nFrameShadow && yPos < m_nframeWidth + nFrameShadow)
                    *result = HTTOPLEFT;
                if (xPos > (this->width() - m_nframeWidth - nFrameShadow) && xPos < (this->width() - nFrameShadow) && yPos > nFrameShadow && yPos < m_nframeWidth + nFrameShadow)
                    *result = HTTOPRIGHT;
                if (xPos > nFrameShadow && xPos < m_nframeWidth + nFrameShadow && yPos >(this->height() - m_nframeWidth - nFrameShadow) && yPos < (this->height() - nFrameShadow))
                    *result = HTBOTTOMLEFT;
                if (xPos > (this->width() - m_nframeWidth - nFrameShadow) && xPos < (this->width() - nFrameShadow) && yPos >(this->height() - m_nframeWidth - nFrameShadow) && yPos < (this->height() - nFrameShadow))
                    *result = HTBOTTOMRIGHT;
            }
            else
            {
                return QWidget::nativeEvent(eventType, message, result);
            }
        }

        if (*result == HTLEFT || *result == HTRIGHT || *result == HTTOP
            || *result == HTBOTTOM || *result == HTTOPLEFT || *result == HTTOPRIGHT
            || *result == HTBOTTOMLEFT || *result == HTBOTTOMRIGHT)
        {
            return true;
        }
        else
        {
            if(m_Widget)
            {
                m_titleHeight = m_Widget->height();
                                int nS = 0;
                if(!::IsZoomed(msg->hwnd))
                {
                    nS = m_nShadowWidth;
                }
                QRect captionRect(nS + m_nframeWidth, nS + m_nframeWidth, this->width() - 2*nS - 2* m_nframeWidth, m_Widget->height() - m_nframeWidth);
                if (captionRect.contains(xPos, yPos) )
                {
                    if(!isChildContorl(xPos, yPos))
                    {
                        *result = HTCAPTION;
                        return true;
                    }
                    else
                        return QWidget::nativeEvent(eventType, message, result);
                }
            }
            else
            {
                return QWidget::nativeEvent(eventType, message, result);
            }
        }

    }
        break;
    case WM_NCCALCSIZE:
        return true;

    case WM_GETMINMAXINFO://防止多屏时最大化时窗口不完整
    {
        if (::IsZoomed(msg->hwnd)) {
            // 最大化时会超出屏幕，所以填充边框间距
            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);            
            m_layout->setContentsMargins(0, 0, 0, 0);
        }
        else {
            this->setContentsMargins(0, 0, 0, 0);
            m_layout->setContentsMargins(m_nShadowWidth, m_nShadowWidth, m_nShadowWidth, m_nShadowWidth);
            MINMAXINFO* pMMI = (MINMAXINFO*)msg->lParam;
            pMMI->ptMinTrackSize.x = m_nMinWidth + 2 * m_nShadowWidth;
            pMMI->ptMinTrackSize.y = m_nMinHeight + 2 * m_nShadowWidth;
            msg->lParam = (LPARAM)pMMI;
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        return true;
    }
    case WM_NCLBUTTONDBLCLK:
    {
        if(!m_bDbClick)
        {
            return true;
        }
        emit sigDoubleClick();
        break;
    }
    }
#endif // Q_OS_WIN
    return QWidget::nativeEvent(eventType, message, result);
}

void QNoBorderWidget::setFrameWidth(int nWidth)
{
    m_nframeWidth = nWidth;
    this->update();
}

void QNoBorderWidget::setFrameEnable(bool bEnable)
{
    m_bFrameEnable = bEnable;
#ifdef Q_OS_WIN
    HWND hwnd = (HWND)this->winId();
    DWORD exStyle = ::GetWindowLong(hwnd, GWL_STYLE);
    if(m_bFrameEnable)
    {
        ::SetWindowLong(hwnd, GWL_STYLE, exStyle | WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX);
    }
    else
    {
        ::SetWindowLong(hwnd, GWL_STYLE, exStyle | WS_POPUP);
    }
#endif
}

void QNoBorderWidget::setTitleWidget(QWidget* widget)
{
    if(widget)
    {
        m_Widget = widget;
    }
}

void QNoBorderWidget::setShadowWidth(int nWidth, QColor color)
{
    m_nShadowWidth = nWidth;
    m_shadowColor = color;
    m_layout->setContentsMargins(m_nShadowWidth, m_nShadowWidth, m_nShadowWidth, m_nShadowWidth);
    if(m_centerWidget && m_nShadowWidth > 0)
    {
        QGraphicsDropShadowEffect *m_shadowEffect = new QGraphicsDropShadowEffect(m_centerWidget);
        m_shadowEffect->setOffset(0, 0);
        m_shadowEffect->setColor(m_shadowColor);
        m_shadowEffect->setBlurRadius(m_nShadowWidth);
        m_centerWidget->setGraphicsEffect(m_shadowEffect);
    }
}

void QNoBorderWidget::setCenterWidget(QWidget* widget)
{
    if(!widget)
    {
        return;
    }

    if(m_centerWidget)
    {
        m_layout->removeWidget(m_centerWidget);
    }
    m_layout->addWidget(widget);
    m_centerWidget = widget;
    setShadowWidth(m_nShadowWidth, m_shadowColor);
}

void QNoBorderWidget::setEnableDbClickTitle(bool bEnable)
{
    m_bDbClick = bEnable;
}

void QNoBorderWidget::setToolWindowStyle(bool bToolStyle)
{
#ifdef Q_OS_WIN
    HWND hwnd = (HWND)this->winId();
    DWORD exStyle = ::GetWindowLong(hwnd, GWL_STYLE);
    if(!bToolStyle)
    {
        ::SetWindowLong(hwnd, GWL_STYLE, exStyle & ~WS_EX_TOOLWINDOW);
    }
    else
    {
        ::SetWindowLong(hwnd, GWL_STYLE, exStyle | WS_EX_TOOLWINDOW);
    }
#endif
}
