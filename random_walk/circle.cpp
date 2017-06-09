#include <QtGui>
#include <QApplication>
#include <QGlobal.h>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QVector>
#include <QBrush>
#include <qtimer.h>

#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include<cstdio>

#define max 1000			/* number of steps */
#define tmax 10
#define seed 11168			/* seed for number generator */
#define SQRT_2    1.4142135623730950488

class  myMainWindow:public QMainWindow
{
public:
    myMainWindow():
    QMainWindow()
    {};
    ~myMainWindow(){};
    
  //  int x,y;
    const int radius=150;
    const float Pi = 3.14159f;
    int i,j;
    double x, y;
   

    void paintEvent(QPaintEvent*)
    {
        
        QPainter painter(this);
        QVector <QPointF> points;
        QTimer *timer;
        QGraphicsScene *scene;
        
             {
  
            x=0; y=0;
            
            for (i=1;i<=max; i++)
            {
                x = x+(drand48() - 0.5)*10.0*SQRT_2;	/* Position X and Y coord updated by rand. numbers                        
                                                         /* between */
                y = y+(drand48() - 0.5)*10.0*SQRT_2;	/* -sqrt(2) and sqrt(2) */
                points.append(QPointF(x, y));
                
            };
        };
        
        for(int p = 1; p<points.size(); p++)
        {
            painter.setBrush(Qt::red);
            painter.drawEllipse(500+points[p].x(), 500+points[p].y(),6, 6);
            //    painter.drawLine(175+points[i].x(), 175+points[i].y(),175+points[i-1].x(), 175+points[i-1].y());
        };
      
    };

};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    myMainWindow *window = new myMainWindow();
    
    window->setWindowTitle(QString::fromUtf8("Brownian random motion with white noise"));
    window->resize(1000, 1000);
    window->show();
    // generate some data:
    // create graph and assign data to it:
   
    return app.exec();
}

