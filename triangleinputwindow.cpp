#include "triangleinputwindow.h"
#include "ui_triangleinputwindow.h"

TriangleInputWindow::TriangleInputWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TriangleInputWindow)
{
    ui->setupUi(this);
    // Haromszog pontjainak megadasa
    connect(ui->widget, SIGNAL(clicked()), SLOT(SetCustomPoints()));
}

TriangleInputWindow::~TriangleInputWindow()
{
    delete ui;
}

void TriangleInputWindow::SetCustomPoints()
{
    QPoint mousepos = mapFromGlobal(QCursor::pos());
    if (pointcounter == 0) {
        CustomA = mousepos;
        pointcounter++;
    } else if (pointcounter == 1) {
        CustomB = mousepos;
        pointcounter++;
    } else if (pointcounter == 2) {
        CustomC = mousepos;
        pointcounter = 0;
    }
    ui->widget->setA(CustomA);
    ui->widget->setB(CustomB);
    ui->widget->setC(CustomC);
    ui->widget->hide();
    ui->widget->show();
}
