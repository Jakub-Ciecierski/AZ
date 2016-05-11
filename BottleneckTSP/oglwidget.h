#ifndef OGLWIDGET_H
#define OGLWIDGET_H
#include <QGLWidget>
#include "graph.h"

class OglWidget : public QGLWidget
{
    Q_OBJECT
public:
     explicit OglWidget(QWidget *parent = 0);
    ~OglWidget();
    Graph graph;

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    float xRatio = 1.0f;
    float yRatio = 1.0f;

private:

    int screenWidth;
    int screenHeight;
    int timerId;
    void timerEvent(QTimerEvent *event);
    void draw();
};

#endif // OGLWIDGET_H
