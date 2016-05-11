#include "oglwidget.h"

OglWidget::OglWidget(QWidget *parent): QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    timerId = startTimer(17);
    this->setFocusPolicy(Qt::ClickFocus);
    this->installEventFilter(this);
}
OglWidget::~OglWidget()
{
    killTimer(timerId);
}

QSize OglWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OglWidget::sizeHint() const
{
    return QSize(400, 400);
}

void OglWidget::initializeGL()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable ( GL_COLOR_MATERIAL );
}

void OglWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void OglWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
    if(width>height){
        xRatio = (float)width/(float)height;
        yRatio = 1.0f;
    }
    else if(height>width){
        xRatio = 1.0f;
        yRatio = (float)height/(float)width;
    }
    else{xRatio = 1.0f;yRatio=1.0f;}
}

void OglWidget::timerEvent(QTimerEvent *event)
{
   updateGL();
}

void OglWidget::draw()
{
    if(!graph.isInit) return;
    glEnable(GL_BLEND);
    glBlendEquation(GL_MAX);
    glLineWidth(1);
    glBegin(GL_POINTS);
    for(int i=0;i<graph.nodeVector->size();i++)
    {
        glVertex2f(graph.nodeVector->at(i).getY()/xRatio,graph.nodeVector->at(i).getX()/yRatio);
    }
    glEnd();
}
