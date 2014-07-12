#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include"painter.h"
#include<QCloseEvent>
#include<QList>
#include<QUndoStack>
#include<QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newmenu();
    void openimage();
    void saveimage();
    bool maybesave();
    void newimage();
    void backout();
    void recover();

    void setpen();
    void setbrush();
    void seteraser();

    void usePolygon();
    void useLine();
    void useCircle();
    void useRectangle();
    void useEllipse();
    void useArc();
    void useText();
    void usePath();

    void usepen();
    void usebrush();
    void useeraser();
    void setcolor();
protected:
    void closeEvent(QCloseEvent *event);
private slots:

private:
    Ui::MainWindow *ui;
    myPainter *mypainter;
    QAction *openimageact;
    QAction *saveimageact;
    QAction *exitact;
    QAction *newimageact;

    QAction *backoutact;
    QAction *recoveract;
    QAction *clearimageact;

    QAction *usepenact;
    QAction *useeraseract;
    QAction *usebrushact;
    QAction *coloract;

    QAction *penact;
    QAction *brushact;

    QAction *eraseract;

    QAction *wordact;
    QAction *Lineact;
    QAction *Ellipseact;
    QAction *Arcact;
    QAction *Circleact;
    QAction *Rectangleact;
    QAction *Polygonact;
    QAction *Textact;
    QAction *Pathact;
    QUndoStack *myundostack;

//    QSlider *myslider;
};

#endif // MAINWINDOW_H
