#include "mainwindow.h"
#include<cmath>
#include "ui_mainwindow.h"

QImage img(500, 500, QImage ::Format_RGB888 );

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0; i<500;i++){
        for(int j=0; j<500;j++){
            img.setPixel(i, j, qRgb(0, 0, 0));

        }
    }
    ui->label->setPixmap(QPixmap :: fromImage(img));
}
    
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDAline(int x1, int y1, int x2, int y2){
    float dx = (x2 - x1);
    float dy = (y2 - y1);
    float step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    dx = dx / step;
    dy = dy / step;

    float x = x1, y = y1;
    int i = 1;

    while (i <= step)
    {
        img.setPixel(x, y, qRgb(255,255,0));
        x += dx;
        y += dy;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::koch(int x1, int y1, int x2, int y2, int iter){

    int x3, y3, x4, y4, x, y;
    float angle = 60*M_PI/180;

    x3 = (2*x1 + x2)/3;
    y3 = (2*y1 + y2)/3;

    x4 = (2*x2 + x1)/3;
    y4 = (2*y2 + y1)/3;

    x = x3 + (x4 - x3)*cos(angle) + (y4-y3)*sin(angle);
    y = y3 - (x4 - x3)*sin(angle) + (y4-y3)*cos(angle);


    if(iter > 1){
        koch(x1, y1, x3, y3, iter - 1);
        koch(x3, y3, x, y, iter - 1);
        koch(x, y, x4, y4, iter -1);
        koch(x4, y4, x2, y2, iter - 1);
    }
    else{

        DDAline(x1, y1, x3, y3);
        DDAline(x3, y3, x, y);
        DDAline(x, y, x4, y4);
        DDAline(x4, y4, x2, y2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Clear
    for(int i=0; i<500;i++){
        for(int j=0; j<500;j++){
            img.setPixel(i, j, qRgb(0, 0, 0));
        }
    }
    ui->label->setPixmap(QPixmap :: fromImage(img));
}


void MainWindow::on_pushButton_2_clicked()
{
    // x1=100
    //x2=250
    //y=150
    int x1, y1, x2, y2, iter;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
//    y2 = ui->textEdit_4->toPlainText().toInt();
    y2 = y1;
    iter = ui->textEdit_5->toPlainText().toInt();

    koch(x1, y1, x2, y2, iter);

    // For 3rd size of triangle
//    int x3 = ((x1+x2)-sqrt(3)*(y1-y2))/2;
//    int y3 = ((y1+y2)-sqrt(3)*(x1-x2))/2;
//    koch(x3,y3, x1, y1, iter);
//    koch(x2,y2, x3, y3, iter);
}
