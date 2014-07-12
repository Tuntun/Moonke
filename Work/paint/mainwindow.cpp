#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"painter.h"
#include<QImage>
#include<QDialog>
#include<QAction>
#include<QWidget>
#include<QString>
#include<QMenu>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QToolBar>
#include<QPainter>
#include<QPaintDevice>
#include<QPaintEngine>
#include<QCloseEvent>
#include<QInputDialog>
#include<QColorDialog>
#include<QByteArray>
#include<QUndoStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mypainter = new myPainter;

    myundostack = new QUndoStack(this);
//    myslider = new QSlider;
//    myslider->setAutoFillBackground(autoFillBackground());
    setCentralWidget(mypainter);
    setWindowTitle(tr("画图"));
    newmenu();
    resize(800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newmenu()
{
    QMenu *File = menuBar()->addMenu(tr("&File"));
    newimageact = new QAction(QIcon(":/images/file-open"),tr("&New..."),this);
    newimageact->setShortcuts(QKeySequence::New);
    connect(newimageact,&QAction::triggered,this,&MainWindow::newimage);

    openimageact = new QAction(QIcon(":/images/file-open"),tr("&Open..."),this);
    openimageact->setShortcuts(QKeySequence::Open);
    connect(openimageact,&QAction::triggered,this,&MainWindow::openimage);

    saveimageact = new QAction(QIcon(":/images/file-open"),tr("&Save..."),this);
    saveimageact->setShortcuts(QKeySequence::Save);
    connect(saveimageact,&QAction::triggered,this,&MainWindow::saveimage);

    exitact = new QAction(QIcon(":/images/file-open"),tr("&Exit..."),this);
    exitact->setShortcuts(QKeySequence::Quit);
    connect(exitact,&QAction::triggered,this,&MainWindow::close);

    File->addAction(newimageact);
    File->addAction(openimageact);
    File->addAction(saveimageact);
    File->addSeparator();
    File->addAction(exitact);

    //编辑
    QMenu *Compile = menuBar()->addMenu(tr("&Compile"));
    backoutact = new QAction(QIcon(":/images/compile-backout"),tr("&Backout..."),this);
    backoutact->setShortcuts(QKeySequence::Back);
    connect(backoutact,&QAction::triggered,this,&MainWindow::backout);

    recoveract = new QAction(QIcon(":/images/compile-backout"),tr("&Recover..."),this);
    recoveract->setShortcuts(QKeySequence::Refresh);
    connect(recoveract,&QAction::triggered,this,&MainWindow::recover);

    clearimageact = new QAction(QIcon(":/images/compile-backout"),tr("&ClearImage..."),this);
    clearimageact->setShortcuts(QKeySequence::Back);
    connect(clearimageact,&QAction::triggered,mypainter,&myPainter::clearimage);
    Compile->addAction(backoutact);
    Compile->addAction(recoveract);
    Compile->addAction(clearimageact);
    //工具

    QMenu *polygonMenu = new QMenu(tr("&Polygon..."),this);
    Lineact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Line..."),this);
    connect(Lineact,&QAction::triggered,this,&MainWindow::useLine);

    Ellipseact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Ellipse..."),this);
    connect(Ellipseact,&QAction::triggered,this,&MainWindow::useEllipse);

    Circleact = new QAction(QIcon(":/images/polygonmenu-line"),tr("& Circle..."),this);
    connect( Circleact,&QAction::triggered,this,&MainWindow::useCircle);

    Rectangleact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Rectangle..."),this);
    connect(Rectangleact,&QAction::triggered,this,&MainWindow::useRectangle);

    Polygonact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Polygon..."),this);
    connect(Polygonact,&QAction::triggered,this,&MainWindow::usePolygon);

    Pathact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Path..."),this);
    connect(Pathact,&QAction::triggered,this,&MainWindow::usePath);

    Arcact = new QAction(QIcon(":/images/polygonmenu-line"),tr("&Arc..."),this);
    connect(Arcact,&QAction::triggered,this,&MainWindow::useArc);

    polygonMenu->addAction(Lineact);
    polygonMenu->addAction(Ellipseact);
    polygonMenu->addAction(Circleact);
    polygonMenu->addAction(Arcact);
    polygonMenu->addAction(Rectangleact);
    polygonMenu->addAction(Polygonact);
    polygonMenu->addAction(Pathact);

    QMenu *Tool = menuBar()->addMenu(tr("&Tool"));
    penact = new QAction(QIcon(":/images/tool-pen"),tr("&PenSize..."),this);
    connect(penact,&QAction::triggered,this,&MainWindow::setpen);

    brushact = new QAction(QIcon(":/images/tool-pen"),tr("&BrushSize..."),this);
    connect(brushact,&QAction::triggered,this,&MainWindow::setbrush);

//    erasersize = new QAction(QIcon(":/images/tool-pen"),tr("&Erasersize..."),this);
//    connect(erasersize,&QAction::triggered,this,&MainWindow::seteraser);

//    QMenu *eraseract = new QMenu(tr("Eraser..."),this);
//    eraseract->addAction(erasersize);
//    eraseract->addActions(erasetype);

    eraseract = new QAction(QIcon(":/images/tool-Eraser"),tr("&Eraser..."),this);
    connect(eraseract,&QAction::triggered,this,&MainWindow::seteraser);

    Textact = new QAction(QIcon(":/images/tool-line"),tr("&Text..."),this);
    connect(Textact,&QAction::triggered,this,&MainWindow::useText);


    Tool->addAction(penact);
    Tool->addAction(brushact);
//    Tool->addMenu(eraseract);
    Tool ->addAction(eraseract);
    Tool->addMenu(polygonMenu);
    Tool->addAction(Textact);

    usepenact = new QAction(QIcon(":/image/Pen"),tr("&Pen..."),this);
    connect(usepenact,&QAction::triggered,this,&MainWindow::usepen);
    QToolBar *toolbar1 = addToolBar(tr("&Pen"));
    toolbar1->addAction(usepenact);

    usebrushact = new QAction(QIcon(":/image/Brush"),tr("&Brush..."),this);
    connect(usebrushact,&QAction::triggered,this,&MainWindow::usebrush);
    QToolBar *toolbar2 = addToolBar(tr("&Brush"));
    toolbar2->addAction(usebrushact);

    useeraseract = new QAction(QIcon(":/image/Eraser"),tr("&Eraser..."),this);
    connect(useeraseract,&QAction::triggered,this,&MainWindow::useeraser);
    QToolBar *toolbar3 = addToolBar(tr("&Eraser"));
    toolbar3->addAction(useeraseract);

    coloract = new QAction(QIcon(":/image/Color"),tr("&Color..."),this);
    connect(coloract,&QAction::triggered,this,&MainWindow::setcolor);
    QToolBar *toolbar4 = addToolBar(tr("&Color"));
    toolbar4->addAction(coloract);

}

void MainWindow::openimage()
{
    QString lay = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
    if(!lay.isEmpty())
    {
        mypainter->openimage(lay);
    }
}

void MainWindow::saveimage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),QDir::currentPath(),tr("%1 Files (*.%2);;All Files (*)"));
       if (!fileName.isEmpty())
       {
           mypainter->saveimage(fileName);
       }
}

bool MainWindow::maybesave()
{
    if(mypainter->ischangeing())
    {
        QMessageBox::StandardButton ask;
        ask = QMessageBox::warning(this,tr("画图"),tr("图片已发生改变,你想要修改吗?"),QMessageBox::Save |  QMessageBox::Cancel);
        if(ask == QMessageBox::Save)
        {
            saveimage();
            return true;
        }
    }
    return false;
}

void MainWindow::newimage()
{
    bool ok,ko;
    maybesave();
   int weight = QInputDialog::getInt(this,tr("新建宽度"),tr("请输入宽度："),1,0,2147483647,1,&ok);
   if(!ok) return ;
   int height = QInputDialog::getInt(this,tr("新建高度"),tr("请输入高度:"),1,0,2147483647,1,&ko);
   if(ko)
   {
       mypainter->newimage(weight,height);
   }
}

void MainWindow::backout()
{

}

void MainWindow::recover()
{

}


void MainWindow::setpen()
{
    bool ok;
   int newsize = QInputDialog::getInt(this, tr("设置笔宽"),tr("请选择笔宽:"),1,1,50,1,&ok);
        if (ok)
            mypainter->setpensize(newsize);
}

void MainWindow::setbrush()
{

}

void MainWindow::seteraser()
{
    bool ok;
    int size = QInputDialog::getInt(this,tr("设置橡皮擦大小"),tr("请选择大小:"),1,10,30,1,&ok);
    if(ok) mypainter->seterasersize(size);
}


void MainWindow::usePolygon()
{
    mypainter->setdrawstyle("Polygon");
}

void MainWindow::useLine()
{
    mypainter->setdrawstyle("Line");
}

void MainWindow::useCircle()
{
    mypainter->setdrawstyle("Circle");
}

void MainWindow::useRectangle()
{
    mypainter->setdrawstyle("Rectangle");
}

void MainWindow::useEllipse()
{
    mypainter->setdrawstyle("Ellipse");
}

void MainWindow::useArc()
{
    mypainter->setdrawstyle("Arc");
}

void MainWindow::useText()
{
    mypainter->setdrawstyle("Text");
}

void MainWindow::usePath()
{
    mypainter->setdrawstyle("Path");
}

void MainWindow::usepen()
{
    mypainter->setdrawstyle("Nothing");
    mypainter->closebrushmode();
}

void MainWindow::usebrush()
{
     mypainter->openbrushmode();
}

void MainWindow::useeraser()
{
     mypainter->setdrawstyle("Eraser");
     mypainter->closebrushmode();
}

void MainWindow::setcolor()
{
    QColor newcolor = QColorDialog::getColor();
    mypainter->setpencolor(newcolor);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybesave())
    {
        event->accept();
    }
    else
        event->accept();
}


