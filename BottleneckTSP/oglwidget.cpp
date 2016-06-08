#include "oglwidget.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
OglWidget::OglWidget(QWidget *parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
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
    glClearColor(0.0, 0.0, 0.0, 1.0);

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
    if(!graph->isInit) return;
    glEnable(GL_BLEND);
    glBlendEquation(GL_MAX);
    glLineWidth(1);
    glBegin(GL_POINTS);

    float mapColor[4] = {0.0f, 0.7f, 0.0f, 1.0f};
    glColor4f(mapColor[0], mapColor[1], mapColor[2], mapColor[3]);
    mat4 transMat;
    transMat = glm::scale(transMat,vec3(scale));
    transMat = glm::translate(transMat,vec3(xTranslation,yTranslation,0.0));
    //vec3 scalingFactor = glm::vec3(scale);

    for(int i=0;i<graph->nodeVector->size();i++)
    {

        vec4 tmpVec = vec4(vec2(graph->nodeVector->at(i)->getY(),graph->nodeVector->at(i)->getX()),1.0,1.0);
                tmpVec = transMat  * tmpVec;
        glVertex2f((tmpVec.x/xRatio * -1),
                   tmpVec.y/yRatio + 0.5);
    }
    glEnd();
}


void OglWidget::keyPressEvent(QKeyEvent *event)
{
    keysPressed += event->key();

    if(keysPressed.contains(Qt::Key_W)){
            yTranslation -= 0.05f;
    }
    if(keysPressed.contains(Qt::Key_S)){
            yTranslation += 0.05f;
    }
    if(keysPressed.contains(Qt::Key_A)){
        xTranslation+=0.05f;
    }
    if(keysPressed.contains(Qt::Key_D)){
        xTranslation-=0.05f;
    }
    if(keysPressed.contains(Qt::Key_Q)){
        scale+=0.1f;
    }
    if(keysPressed.contains(Qt::Key_E)){
        scale-=0.1f;
    }
}

void OglWidget::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed-= event->key();
}
