#include "painter.h"
#include<QPainter>
#include<QRect>
#include<QSize>
#include<QMouseEvent>
#include <QWidget>
#include<QPoint>
#include<QImage>
#include<QString>
#include<QPaintEvent>
#include<QResizeEvent>


myPainter::myPainter(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    pensize = 1;
    drawing = false;
    brushmode = false;
    changeing = false;
    drawtype = "Nothing";
    erasersize = 15;
//    myslider = new QSlider;
//    myslider->setAutoFillBackground(autoFillBackground());
    color = Qt::black;
}

void myPainter::newimage(int w, int h)
{
    QImage newone (QSize(w,h),QImage::Format_RGB32);
    newone.fill(qRgb(255,255,255));
    image = newone;
    changeing = false;
    update();
}

void myPainter::openimage(const QString &filename)
{
    QImage newimage;
    if(!newimage.load(filename)) return ;

    QSize newsize = newimage.size().expandedTo(size());
    setnewimage(&newimage,newsize);
    image = newimage;
    drawing = false;
    update();
}

void myPainter::saveimage(const QString &filename)
{
    QImage simage = image;
    setnewimage(&simage,size());
    if(simage.save(filename))
        changeing = false;
}

void myPainter::clearimage()
{
    image.fill(qRgb(255,255,255));
    drawing = false;
    update();
    changeing = true;
}

void myPainter::setpencolor(QColor newcolor)
{
    color = newcolor;
}

void myPainter::seterasersize(int newsize)
{
    erasersize = newsize;
}

void myPainter::setpensize(int newpensize)
{
    pensize = newpensize;
}

void myPainter::setnewimage(QImage *image, QSize newsize)
{
    if(image->size()== newsize)
        return ;
    QImage NEWIMAGE(newsize,QImage::Format_RGB32);
    NEWIMAGE.fill(qRgb(255,255,255));
    QPainter painter(&NEWIMAGE);
    painter.drawImage(QPoint(0,0),*image);
    *image = NEWIMAGE;
}


void myPainter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void myPainter::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
            int newWidth = qMax(width() , image.width());
            int newHeight = qMax(height() , image.height());
            setnewimage(&image, QSize(newWidth, newHeight));
            update();
    }

    QWidget::resizeEvent(event);
}

void myPainter::drawtime(QPoint lastpoint, QPoint endpoint)
{
    QPainter ipainter(&image);
    ipainter.setPen(QPen(color,pensize,Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    if(brushmode)
        ipainter.setBrush(QBrush(color,Qt::CrossPattern));
    if(drawtype=="Line" || drawtype=="Nothing" )  //直线
    {
        ipainter.drawLine(lastpoint,endpoint);
    }
    else if( drawtype=="Eraser")  //橡皮擦
    {
        ipainter.setPen(QPen(QColor(qRgb(255,255,255)),erasersize,Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
        ipainter.drawLine(lastpoint,endpoint);
    }
    else if(drawtype == "Ellipse")   //椭圆
    {
        ipainter.drawEllipse(QRectF(lastpoint.rx(),lastpoint.ry(),endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry()));
    }
    else if(drawtype == "Circle")   //圆
    {
        ipainter.drawEllipse(QPointF((endpoint.rx()+lastpoint.rx())/2.0,(endpoint.ry()+lastpoint.ry())/2.0),qMin(endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry()),qMin(endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry()));
    }
    else if(drawtype=="Arc")  //圆弧
    {
        ipainter.drawArc(QRectF(lastpoint.rx(),lastpoint.ry(),endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry()),30*16,120*16);
    }
    else if(drawtype == "Rectangle")   //矩形
    {
        ipainter.drawRect(lastpoint.rx(),lastpoint.ry(),endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry());
    }
    else if(drawtype =="Polygon")   //多边形
    {

    }
    else if(drawtype == "Text")  //文本
    {
        ipainter.drawText(QRectF(lastpoint.rx(),lastpoint.ry(),endpoint.rx()-lastpoint.rx(),endpoint.ry()-lastpoint.ry()),tr("Qt\nSo...."));
    }
    else if(drawtype=="Path")   //路径
    {
        QPainterPath *path = new QPainterPath(QPointF(lastpoint));
        path->cubicTo(QPointF(endpoint.rx(),lastpoint.ry()),(lastpoint+endpoint)/2,endpoint);
        ipainter.drawPath(*path);
    }

    drawing = true;
    changeing = true;
    update();
}

void myPainter::setdrawstyle(QString newstyle)
{
    drawtype = newstyle;
}

void myPainter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {  
            lastpoint = endpoint = event->pos();
            drawing = true;
            remimage = image;
            remfirst = lastpoint;
    }
}

void myPainter::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()& Qt::LeftButton)
    {
        if(drawtype == "Nothing" || drawtype=="Eraser" || drawtype=="Brush")
            lastpoint = endpoint;

        endpoint = event->pos();

        if(drawtype != "Text" )
        {
            if(drawtype != "Nothing" && (drawtype!="Eraser"|| drawtype=="Brush"))
                image = remimage;
            drawtime(lastpoint,endpoint);
        }
    }
}

void myPainter::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() ==Qt::LeftButton)
    {
        endpoint = event->pos();
        drawtime(lastpoint,endpoint);
        drawing = false;
    }
}


