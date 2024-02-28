#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
QImage img(750, 750, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

      ,
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    float x1, x2, x3, x4;
    float y1, y2, y3, y4;

    x1 = ui->textEdit->toPlainText().toFloat();
    x2 = ui->textEdit_3->toPlainText().toFloat();
    x3 = ui->textEdit_5->toPlainText().toFloat();
    x4 = ui->textEdit_7->toPlainText().toFloat();

    y1 = ui->textEdit_2->toPlainText().toFloat();
    y2 = ui->textEdit_4->toPlainText().toFloat();
    y3 = ui->textEdit_6->toPlainText().toFloat();
    y4 = ui->textEdit_8->toPlainText().toFloat();

    //     100,350     250,350
    //     100,500     250,500

    dda_line(x1, y1, x2, y2);
    dda_line(x2, y2, x3, y3);
    dda_line(x3, y3, x4, y4);
    dda_line(x1, y1, x4, y4);

    dda_line((x1 + x2) / 2, y1, x2, (y2 + y3) / 2);
    dda_line(x2, (y2 + y3) / 2, (x3 + x4) / 2, y4);
    dda_line((x3 + x4) / 2, y4, x1, (y1 + y4) / 2);
    dda_line(x1, (y1 + y4) / 2, (x1 + x2) / 2, y1);

    circle((x1 + x2) / 2, (y2 + y3) / 2, 75 / sqrt(2));
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1, x2, x3;
    float y1, y2, y3;

    x1 = ui->textEdit_9->toPlainText().toFloat();
    x2 = ui->textEdit_11->toPlainText().toFloat();
    x3 = ui->textEdit_13->toPlainText().toFloat();

    y1 = ui->textEdit_10->toPlainText().toFloat();
    y2 = ui->textEdit_12->toPlainText().toFloat();
    y3 = ui->textEdit_14->toPlainText().toFloat();

    //             225,120
    //      150,250      300,250

    dda_line(x1, y1, x2, y2);
    dda_line(x2, y2, x3, y3);
    dda_line(x3, y3, x1, y1);
    // radius is a/2sqrt(3)  center (x+y+z/3)
    circle((x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3, 25 * sqrt(3));
    circle((x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3, 50 * sqrt(3));
}

void MainWindow::dda_line(float x1, float y1, float x2, float y2)
{
    float dx, dy, step, x, y;
    float xinc, yinc;
    int i = 1;
    dx = x2 - x1;
    dy = y2 - y1;
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    xinc = dx / step;
    yinc = dy / step;
    x = x1;
    y = y1;

    //    while(i<=step)
    //    {
    //        img.setPixel(x,y,qRgb(255,255,360));
    //        x+=xinc;
    //        y+=yinc;
    //        i++;
    //    }
    for (i = 1; i <= step; i++)
    {
        img.setPixel(x, y, qRgb(255, 255, 360));
        x += xinc;
        y += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->show();
}

void MainWindow::circle(float x, float y, float r)
{
    float x1 = 0, y1 = r;
    int p = 3 - 2 * r;
    do
    {
        img.setPixel(x + x1, y + y1, qRgb(255, 255, 360));
        img.setPixel(x - x1, y + y1, qRgb(255, 255, 360));
        img.setPixel(x + x1, y - y1, qRgb(255, 255, 360));
        img.setPixel(x - x1, y - y1, qRgb(255, 255, 360));

        img.setPixel(x + y1, y + x1, qRgb(255, 255, 360));
        img.setPixel(x - y1, y + x1, qRgb(255, 255, 360));
        img.setPixel(x + y1, y - x1, qRgb(255, 255, 360));
        img.setPixel(x - y1, y - x1, qRgb(255, 255, 360));

        if (p < 0)
            p = p + 4 * x1 + 6;
        else
        {
            p = p + 4 * (x1 - y1) + 10;
            y1--;
        }
        x1++;

    } while (x1 <= y1);

    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->show();
}
