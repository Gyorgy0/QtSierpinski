#include "mainwindow.h"
#include <QBuffer>
#include <QColorDialog>
#include <QFileDialog>
#include <QSettings>
#include "./ui_mainwindow.h"
#include "triangleinputwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Kirajzoltatas
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(DrawButton_click()));
    // Menubar funkcioi
    connect(ui->actionAdatok_export_l_sa, SIGNAL(triggered()), SLOT(QtDataExport()));
    connect(ui->actionAdatok_import_l_sa, SIGNAL(triggered()), SLOT(QtDataImport()));
    connect(ui->actionK_p_ment_se, SIGNAL(triggered()), SLOT(ImageExport()));
    connect(ui->actionH_romsz_g_sz_ne, SIGNAL(triggered()), SLOT(SetLinecolor()));
    connect(ui->actionH_tt_r_sz_ne, SIGNAL(triggered()), SLOT(SetBackgroundColor()));
    connect(ui->actionH_romsz_g_megad_sa, SIGNAL(triggered()), SLOT(InputTriangle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::QtDataExport()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Adatok mentése..."),
                                                    QString(),
                                                    tr("Konfigurációs fájlok (*.qtdata)"));
    if (!fileName.isEmpty()) {
        QSettings *data = new QSettings(fileName, QSettings::IniFormat);
        // Adatok mentese
        data->setValue("A", A);
        data->setValue("B", B);
        data->setValue("C", C);
        data->setValue("DrawColor", DrawColor);
        data->setValue("BackgroundColor", BackgroundColor);
        data->setValue("IterationLvl", ui->spinBox->value());
        data->sync();
    }
}
void MainWindow::QtDataImport()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Adatok beolvasása.."),
                                                    QString(),
                                                    tr("Konfigurációs fájlok (*.qtdata)"));
    if (!fileName.isEmpty()) {
        QSettings *data = new QSettings(fileName, QSettings::IniFormat);
        // Adatok beolvasasa
        A = data->value("A").value<QPoint>();
        B = data->value("B").value<QPoint>();
        C = data->value("C").value<QPoint>();
        DrawColor = data->value("DrawColor").value<QColor>();
        BackgroundColor = data->value("BackgroundColor").value<QColor>();
        ui->spinBox->setValue(data->value("IterationLvl").toInt());
    }
}
void MainWindow::ImageExport()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Kép mentése"),
                                                    QString(),
                                                    tr("Képek (*.png)"));
    if (!fileName.isEmpty()) {
        ExportImage.save(fileName);
    }
}

void MainWindow::SetLinecolor()
{
    QColorDialog colorselector(this);
    colorselector.setWindowTitle("Háromszög színének kiválasztása...");
    colorselector.show();
    if (colorselector.exec() == QDialog::DialogCode::Accepted) {
        DrawColor = colorselector.selectedColor();
    }
}

void MainWindow::SetBackgroundColor()
{
    QColorDialog colorselector(this);
    colorselector.setWindowTitle("Háttérszín kiválasztása...");
    colorselector.show();
    if (colorselector.exec() == QDialog::DialogCode::Accepted) {
        BackgroundColor = colorselector.selectedColor();
    }
}

void MainWindow::InputTriangle()
{
    TriangleInputWindow inputwindow(this);
    inputwindow.show();
    if (inputwindow.exec() == QDialog::DialogCode::Accepted) {
        A = inputwindow.CustomA;
        B = inputwindow.CustomB;
        C = inputwindow.CustomC;
    } else {
        A = QPoint(230, 10);
        B = QPoint(10, 460);
        C = QPoint(460, 460);
    }
}

void MainWindow::DrawTriangles(QPoint A, QPoint B, QPoint C, QPainter *painter, int iteration)
{
    painter->drawLine(A, B);
    painter->drawLine(B, C);
    painter->drawLine(C, A);
    if (iteration > 0) {
        DrawTriangles(A, (A + B) / 2, (A + C) / 2, painter, iteration - 1);
        DrawTriangles(B, (A + B) / 2, (B + C) / 2, painter, iteration - 1);
        DrawTriangles(C, (C + B) / 2, (A + C) / 2, painter, iteration - 1);
    }
}

int GetTriangleWidth(QPoint A, QPoint B, QPoint C)
{
    int triangleminwidth = A.x();
    triangleminwidth = std::min(triangleminwidth, B.x());
    triangleminwidth = std::min(triangleminwidth, C.x());
    int trianglemaxwidth = A.x();
    trianglemaxwidth = std::max(trianglemaxwidth, B.x());
    trianglemaxwidth = std::max(trianglemaxwidth, C.x());
    return trianglemaxwidth - triangleminwidth;
}
int GetTriangleHeight(QPoint A, QPoint B, QPoint C)
{
    int triangleminheight = A.y();
    triangleminheight = std::min(triangleminheight, B.y());
    triangleminheight = std::min(triangleminheight, C.y());
    int trianglemaxheight = A.y();
    trianglemaxheight = std::max(trianglemaxheight, B.y());
    trianglemaxheight = std::max(trianglemaxheight, C.y());
    return trianglemaxheight - triangleminheight;
}
void MainWindow::DrawButton_click()
{
    int width = 0;
    int height = 0;
    int mintrianglesize = 5;
    int trianglewidth = GetTriangleWidth(A, B, C);
    int triangleheight = GetTriangleHeight(A, B, C);
    if (trianglewidth / pow(2, ui->spinBox->value()) >= mintrianglesize * (500 / trianglewidth)
        || triangleheight / pow(2, ui->spinBox->value())
               >= mintrianglesize * (500 / triangleheight)) {
        width = 500;
        height = 500;
    } else {
        width = (500 / trianglewidth) * mintrianglesize * pow(2, ui->spinBox->value());
        height = (500 / triangleheight) * mintrianglesize * pow(2, ui->spinBox->value());
    }
    QPixmap image(width, height);
    QPainter painter(&image);
    QPen pen;
    QGraphicsScene *scene = new QGraphicsScene();
    scene->clear();
    pen.setWidth(1);
    image.fill(BackgroundColor);
    pen.setColor(DrawColor);
    painter.setPen(pen);
    DrawTriangles(QPoint(A.x() * (width / 500), A.y() * (height / 500)),
                  QPoint(B.x() * (width / 500), B.y() * (height / 500)),
                  QPoint(C.x() * (width / 500), C.y() * (height / 500)),
                  &painter,
                  ui->spinBox->value());
    scene->addPixmap(image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    image.swap(ExportImage);
}
