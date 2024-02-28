#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Vertex{
public:
    float x, y;
    Vertex(){x=0,y=0;}
    Vertex(int x, int y){
        this->x = x;
        this->y = y;
    }
    Vertex(float x, float y){
        this->x = x;
        this->y = y;
    }
    Vertex(int x, float y){
        this->x = x;
        this->y = y;
    }
    bool operator >(Vertex p){
        return y>p.y;
    }
    bool operator <(Vertex p){
        return y<p.y;
    }
};

class Line{
    Vertex p1, p2;
    float one_by_m;
public:
    Line(){}
    Line(Vertex p1, Vertex p2){
        this->p1 = p1;
        this->p2 = p2;
        one_by_m = (p2.x - p1.x)/(p2.y - p1.y);
    }
    float get_intersect(Vertex p){
        if((p.y-p1.y)*(p.y-p2.y)>0 || p.y==p1.y) return 0;
        float ret_x = float(p.y - p2.y)*one_by_m + p2.x;
        return ret_x;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *event);

    void on_fill_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int num_vals = 20;
    int ver;
    Vertex vertices[20];
    bool start;

};
#endif // MAINWINDOW_H
