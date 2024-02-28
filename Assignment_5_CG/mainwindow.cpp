#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
#include<iostream>

using namespace std;

QImage img(750,750,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //Clipping window
//     100,350     250,350
//     100,500     250,500
    dda_line(100,350,250,350);
    dda_line(100,350,100,500);
    dda_line(250,500,250,350);
    dda_line(100,500,250,500);

}



void MainWindow::dda_line(float x1,float y1,float x2,float y2)
{
    float dx,dy,step,x,y;
    float xinc,yinc;
    int i=1;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>abs(dy))
        step=abs(dx);
    else
        step=abs(dy);

    xinc=dx/step;
    yinc=dy/step;
    x=x1;
    y=y1;
    while(i<=step)
    {
        img.setPixel(x,y,qRgb(255,255,360));
        x+=xinc;
        y+=yinc;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->show();
}



void MainWindow::on_pushButton_2_clicked()
{
    float x1,x2;
    float y1,y2;
    x1=ui->textEdit->toPlainText().toDouble();
    x2=ui->textEdit_3->toPlainText().toDouble();

    y1=ui->textEdit_2->toPlainText().toDouble();
    y2=ui->textEdit_4->toPlainText().toDouble();
    //     100,350     250,350
    //     100,500     250,500

    cohenSutherlandClip(x1,y1,x2,y2);
}



// Defining region codes as TBRL
const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000

// Defining x_max, y_max and x_min, y_min for clipping rectangle
const int x_max = 250;
const int y_max = 500;
const int x_min = 100;
const int y_min = 350;


int computeCode(double x, double y)
{
    // initialized as being inside
    int code = INSIDE;

    if (x < x_min) // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min) // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;

    return code;
}

void MainWindow:: cohenSutherlandClip(double x1, double y1, double x2, double y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
// If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2) {
// If both endpoints are outside rectangle, in same region
            break;
        }
        else {
// Some segment of line lies within the rectangle
            int code_out;
            double x, y;

// At least one endpoint is outside the rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

// Find intersection point using formulas
            // y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

// Now intersection point x, y is found we replace point outside rectangle
// by intersection point
            if (code_out == code1) {
                x1 = x  ;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept) {
// display clipped line
        dda_line(x1,y1,x2,y2);
    }
    else
//display entire line
        dda_line(x1,y1,x2,y2);

}

