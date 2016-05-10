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
    screenWidth = width;
    screenHeight = height;
}

void OglWidget::timerEvent(QTimerEvent *event)
{
   updateGL();
}

void OglWidget::draw()
{
    glEnable(GL_BLEND);
    glBlendEquation(GL_MAX);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glEnd();
}
