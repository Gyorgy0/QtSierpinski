#ifndef TRIANGLEINPUTWINDOW_H
#define TRIANGLEINPUTWINDOW_H

#include <QDialog>

namespace Ui {
class TriangleInputWindow;
}

class TriangleInputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TriangleInputWindow(QWidget *parent = nullptr);
    ~TriangleInputWindow();

    QPoint CustomA;
    QPoint CustomB;
    QPoint CustomC;
    int pointcounter = 0;

public slots:
    void SetCustomPoints();

private:
    Ui::TriangleInputWindow *ui;
};

#endif // TRIANGLEINPUTWINDOW_H
