#include "ClickableWidget.h"
#include <QMouseEvent>

ClickableWidget::ClickableWidget(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("ClickableWidget { border: 1px solid #2980b9; border-radius: 10px; background-color: #3498db; }");
}

void ClickableWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}


// #include "ClickableWidget.h"

// ClickableWidget::ClickableWidget(QWidget *parent) : QWidget(parent) {
//     setCursor(Qt::PointingHandCursor);  // Set a cursor to indicate it's clickable
// }

// void ClickableWidget::mousePressEvent(QMouseEvent *event) {
//     if (event->button() == Qt::LeftButton) {
//         emit clicked();  // Emit clicked signal on mouse press
//     }
// }
