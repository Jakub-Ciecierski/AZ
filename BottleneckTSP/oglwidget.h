#ifndef OGLWIDGET_H
#define OGLWIDGET_H
#include <QGLWidget>
#include "Structures/graph.h"
#include <QSet>
#include <QKeyEvent>
#include <QTime>

class OglWidget : public QGLWidget
{
    Q_OBJECT
public:
     explicit OglWidget(QWidget *parent = 0);
    ~OglWidget();

    Graph* graph;
    bool drawEdges;

    void setRunAnimation(bool);
    bool isRunAnimation();
protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    float xRatio = 1.0f;
    float yRatio = 1.0f;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QSet<int> keysPressed;
    float scale = 0.95f;
    float xTranslation = 0.0f;
    float yTranslation = 0.0f;
    int screenWidth;
    int screenHeight;
    int timerId;

    // Animation
    bool runAnimation;
    QTime timer;
    int dtMS = 100;
    int currentEdgeLimit = 0;

    void timerEvent(QTimerEvent *event);
    void draw();
};

#endif // OGLWIDGET_H
