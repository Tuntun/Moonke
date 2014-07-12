#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include<QPoint>
#include<QImage>
#include<QMouseEvent>
#include<QSize>
#include<QString>
#include<QPaintEvent>
#include<QResizeEvent>
#include<QScrollArea>
#include<QSlider>



class myPainter : public QWidget
{
    Q_OBJECT
public:
    explicit myPainter(QWidget *parent = 0);
    void newimage(int w,int h);
    void openimage(const QString &filename);
    void saveimage(const QString &filename);
    bool isdrawing() const {return drawing;};
    bool ischangeing() const {return changeing;};
    void setpencolor(QColor newcolor);
    void seterasersize(int newsize);
    void setpensize(int newpensize);
    void openbrushmode(){brushmode = true;};
    void closebrushmode(){brushmode = false;};
    void setnewimage(QImage *image,QSize newsize);   
    void drawtime(QPoint lastpoint,QPoint endpoint);
    void setdrawstyle(QString newstyle);

signals:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);

public slots:
    void clearimage();

private:
    QColor backgroundcolor;
    QColor color;
    QImage image;
    QImage remimage;
    int pensize;
    QPoint lastpoint,endpoint,remfirst;
    QString drawtype ;
    bool drawing;
    bool changeing;
    bool brushmode;
    int erasersize;
//    QSlider *myslider;
};

#endif // PAINTER_H
