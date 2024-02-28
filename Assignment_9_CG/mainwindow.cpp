#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>

QImage img(500,500, QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   dda(250, 0, 250, 499);
   dda(0, 250, 499, 250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(int x1, int y1, int x2, int y2)
{

    float x,y,dx,dy,xinc,yinc,len;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(dx)>abs(dy)){
        len = abs(dx);
    }
    else len = abs(dy);
    x = x1;
    y = y1;
    int i=0;
    xinc = dx/len;
    yinc = dy/len;
    while(i<len){
        x = x + xinc;
        y = y + yinc;
        i++;
        img.setPixel(x,y,qRgb(255,255,255));
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_DRAW_clicked()
{
    int x1, x2, y1, y2;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    dda(x1+250,y1+250,x2+250,y2+250);
}

void MainWindow::on_Translate_clicked()
{
    int x1, x2, y1, y2, tx, ty;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    tx = ui -> textEdit_5 -> toPlainText().toInt();
    ty = ui -> textEdit_6 -> toPlainText().toInt();
    dda(x1+tx+250, y1+ty+250, x2+tx+250, y2+ty+250);
}

void MainWindow::on_Scale_clicked()
{
    int x1, x2, y1, y2, tx, ty;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    tx = ui -> textEdit_5 -> toPlainText().toInt();
    ty = ui -> textEdit_6 -> toPlainText().toInt();

    dda((x1*tx)+250, (y1*ty)+250, (x2*tx)+250, (y2*ty)+250);
}

void MainWindow::on_Rotate_clicked()
{
    int x1, x2, y1, y2, r,m,n;
    x1 = ui -> textEdit -> toPlainText().toInt();
    y1 = ui -> textEdit_2 -> toPlainText().toInt();
    x2 = ui -> textEdit_3 -> toPlainText().toInt();
    y2 = ui -> textEdit_4 -> toPlainText().toInt();
    r = ui -> textEdit_7 -> toPlainText().toInt();
    m=x1;

    float ro=r*M_PI/180;
    x1=x1*cos(ro)+y1*sin(ro);
    y1=y1*cos(ro)-m*sin(ro);
    n=x2;
    x2=x2*cos(ro)+y2*sin(ro);
    y2=y2*cos(ro)-n*sin(ro);


    dda((x1)+250, (y1)+250, (x2)+250, (y2)+250);
}

void MainWindow::on_Clear_clicked()
{
    //Clear
    for(int i=0; i<500;i++){
        for(int j=0; j<500;j++){
            img.setPixel(i, j, qRgb(0, 0, 0));
        }
    }
    dda(250, 0, 250, 499);
    dda(0, 250, 499, 250);
    ui->label->setPixmap(QPixmap :: fromImage(img));
}
