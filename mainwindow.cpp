#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <quantizationmethod.h>
#include <uniformquantizationmethod.h>
#include <mediancutmethod.h>
#include <octreequantizationmethod.h>
#include <kmeansmethod.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      image()
{
    ui->setupUi(this);

    methods[0] = new UniformQuantizationMethod();
    methods[1] = new MedianCutMethod();
    methods[2] = new KMeansMethod();
    methods[3] = new OctreeQuantizationMethod();

    methods[ui->methodComboBox->currentIndex()]->setColorNum(ui->colorNumSpinBox->value());

    m = new QStandardItemModel();
    ui->colorPaletteListView->setModel(m);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColors(QList<Color> colors)
{
    m->clear();

    for (Color color : colors) {
       QPixmap pixmap(400, 400);
       pixmap.fill(QColor(color.getColor()));
       m->appendRow(new QStandardItem(QIcon(pixmap), QString::number(color.getPercentage() * 100) + "%"));
    }
}

void MainWindow::on_addImageButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this,
        tr("选择要颜色分析的图片"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!image.load(imagePath))
    {
        return;
    }

    ui->pathLineEdit->setText(imagePath); 
    ui->imageDisplayLabel->setScaledContents( true );
    ui->imageDisplayLabel->setPixmap(QPixmap(imagePath).scaled(800, 500, Qt::KeepAspectRatio));

    methods[ui->methodComboBox->currentIndex()]->setImage(Image(QImage(imagePath).scaled(100,100,Qt::KeepAspectRatioByExpanding)));
    methods[ui->methodComboBox->currentIndex()]->generateColors();
    updateColors(methods[ui->methodComboBox->currentIndex()]->getColors());
}

void MainWindow::on_pathLineEdit_textChanged(const QString &imagePath)
{
    if (!image.load(imagePath))
    {
        return;
    }

    ui->imageDisplayLabel->setScaledContents( true );
    ui->imageDisplayLabel->setPixmap(QPixmap(imagePath).scaled(800, 500, Qt::KeepAspectRatio));

    methods[ui->methodComboBox->currentIndex()]->setImage(Image(QImage(imagePath).scaled(100,100,Qt::KeepAspectRatioByExpanding)));
    methods[ui->methodComboBox->currentIndex()]->generateColors();
    updateColors(methods[ui->methodComboBox->currentIndex()]->getColors());
}


void MainWindow::on_colorNumSpinBox_valueChanged(int arg1)
{
    methods[ui->methodComboBox->currentIndex()]->setColorNum(arg1);
    methods[ui->methodComboBox->currentIndex()]->generateColors();
    updateColors(methods[ui->methodComboBox->currentIndex()]->getColors());
}


void MainWindow::on_methodComboBox_currentIndexChanged(int index)
{
    if (!ui->pathLineEdit->text().isEmpty())
    {
        methods[ui->methodComboBox->currentIndex()]->setImage(Image(QImage(ui->pathLineEdit->text()).scaled(100,100,Qt::KeepAspectRatioByExpanding)));
        methods[ui->methodComboBox->currentIndex()]->setColorNum(ui->colorNumSpinBox->value());
        methods[ui->methodComboBox->currentIndex()]->generateColors();
        updateColors(methods[ui->methodComboBox->currentIndex()]->getColors());
    }
}

