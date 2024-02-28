#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTime>
#include<QColorDialog>
QColor C;
//#include <dos.h>
using namespace std;

QImage img(600, 600, QImage::Format_RGB888);

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 5 );
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
    ver = 0;
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void dda(Vertex, Vertex);

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start){

        int p,q;
        p = event->pos().x();
        q = event->pos().y();
        vertices[ver].x = p;
        vertices[ver].y = q;


        if(event->button()==Qt::RightButton){
            dda(vertices[0], vertices[ver-1]);
            start = false;
            ver--;
        } else {
            if(ver){
                dda(vertices[ver], vertices[ver-1]);
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(img));
        ver ++;
    }
}

void dda(Vertex p1, Vertex p2){
    int x1 = p1.x;
    int x2 = p2.x;
    int y1 = p1.y;
    int y2 = p2.y;
    float x_inc, y_inc, dx, dy, x, y;
    dx = x2-x1;
    dy = y2-y1;
    int len = abs(dx)>abs(dy)? abs(dx):abs(dy);
    x_inc = dx / len;
    y_inc = dy / len;
    x = x1;
    y = y1;
    for(int i=0; i<len; i++){
//        img.setPixel(x, y, qRgb(25,369,0));
        img.setPixel(x, y, C.rgb());
        x += x_inc;
        y += y_inc;
    }
}

void MainWindow::on_fill_clicked()
{
    // sort(vertices, vertices+ver);
    Line edges[ver];
    int ymin=600 ; //= vertices[0].y;
    int ymax=0 ; //= vertices[ver-1].y;
    for(int i=0; i<ver; i++){
        if(vertices[i].y>ymax) ymax=vertices[i].y;
        if(vertices[i].y<ymin) ymin=vertices[i].y;
    }

    vertices[ver] = vertices[0];
    int vertices_x[ver];

    for(int i=0; i<ver+1;i++){
        edges[i] = Line(vertices[i], vertices[i+1]);
        if(i<ver) vertices_x[i] = vertices[i].x;
    }
    for(float y=ymin; y<=ymax; y++){
        float intersects[ver] = {0};
        int len_intersects = 0;
        for(int i=0; i<ver; i++){
            Line e = edges[i];
            float ret_x = e.get_intersect(Vertex(0, y));
            if(ret_x){

                intersects[len_intersects]=ret_x;
                len_intersects ++;
            }
        }

        sort(intersects, intersects+len_intersects);
        if(len_intersects>2){
            bool found=false;
            for(int i=0; i<len_intersects; i++){
                bool removed = false;
                for(int x: vertices_x){
                    if(x==intersects[i] && found){
                        cout<<"Removing...: "<<x<<" "<<y<<endl;
//                        dda(Vertex(0, y), Vertex(600, y));
                        for(int j=i; j<len_intersects-1; j++){
                            intersects[j] = intersects[i+1];
                        }
                        len_intersects--;
                        removed = true;
                    }
                }
                if(!removed){
                    found = !found;
                }
            }
        }

        for(int i=0; i<len_intersects-1; i+=2){
            Vertex points[2] = {Vertex(intersects[i], y), Vertex(intersects[i+1], y)};

            dda(points[0], points[1]);
            ui->label->setPixmap(QPixmap::fromImage(img));
        }
        delay(20);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    C=QColorDialog::getColor();
}
