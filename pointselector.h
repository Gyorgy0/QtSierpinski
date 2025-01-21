#ifndef POINTSELECTOR_H
#define POINTSELECTOR_H

#include <QWidget>

class PointSelector : public QWidget
{
    Q_OBJECT
public:
    explicit PointSelector(QWidget *parent = nullptr);
    QPoint A;
    QPoint B;
    QPoint C;

    void setA(QPoint newA);

    void setB(QPoint newB);

    void setC(QPoint newC);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // POINTSELECTOR_H
