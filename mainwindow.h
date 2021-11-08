#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QStandardItemModel>

#include <color.h>
#include <quantizationmethod.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage image;
    QStandardItemModel *m;
    QuantizationMethod *methods[4];

    void updateColors(QList<Color> colors);

private slots:
    void on_addImageButton_clicked();
    void on_pathLineEdit_textChanged(const QString &arg1);
    void on_colorNumSpinBox_valueChanged(int arg1);
    void on_methodComboBox_currentIndexChanged(int index);
};
#endif // MAINWINDOW_H
