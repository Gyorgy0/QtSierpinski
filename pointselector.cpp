#include "pointselector.h"
#include "qpainter.h"

PointSelector::PointSelector(QWidget *parent)
    : QWidget{parent}
{}

void PointSelector::setC(QPoint newC)
{
    C = newC;
}

void PointSelector::setB(QPoint newB)
{
    B = newB;
}

void PointSelector::setA(QPoint newA)
{
    A = newA;
}
void PointSelector::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
void PointSelector::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QPen pen;
    pen.setWidth(15);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(A);
    painter.drawPoint(B);
    painter.drawPoint(C);
}
