#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QWidget>
#include<QSlider>

class myslider : public QSlider
{
    Q_OBJECT
public:
    explicit myslider(QSlider *parent = 0);

signals:

public slots:

};

#endif // MYSLIDER_H
