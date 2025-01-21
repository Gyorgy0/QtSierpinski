#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint A = QPoint(230, 10);
    QPoint B = QPoint(10, 460);
    QPoint C = QPoint(460, 460);
    QColor DrawColor = Qt::red;
    QColor BackgroundColor = Qt::white;
    QPixmap ExportImage;

public slots:
    void QtDataExport();
    void QtDataImport();
    void ImageExport();
    void SetLinecolor();
    void SetBackgroundColor();
    void InputTriangle();

private slots:
    void DrawButton_click();
    void DrawTriangles(QPoint A, QPoint B, QPoint C, QPainter *painter, int iteration);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
