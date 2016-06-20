#include "oglwidget.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QTime>
#include <iostream>

using namespace glm;

OglWidget::OglWidget(QWidget *parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent){

    timerId = startTimer(17);
    this->setFocusPolicy(Qt::ClickFocus);
    this->installEventFilter(this);

    graph = NULL;
    drawEdges = true;
    runAnimation = false;

    timer.start();

    isDrawInfo = false;
}

OglWidget::~OglWidget()
{
    killTimer(timerId);
}

void OglWidget::setRunAnimation(bool value){
    this->runAnimation = value;

    currentEdgeLimit = 0;
    timer.start();
}

bool OglWidget::isRunAnimation(){
    return this->runAnimation;
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

   int elapsed = timer.elapsed();
   if(elapsed > dtMS){
       if(graph != NULL){
           currentEdgeLimit++;
           if(currentEdgeLimit >= graph->edgesVector.size()){
               currentEdgeLimit = 0;
           }
       }

       timer.start();
   }
}

void OglWidget::draw()
{
    if(isDrawInfo)
        drawInfo();
    if(graph == NULL) return;

    glEnable(GL_BLEND);
    glBlendEquation(GL_MAX);

    float nodeSize = 4.0f;
    float rootSize = 6.0f;

    float mapColor[4] = {0.0f, 0.7f, 0.0f, 1.0f};
    float rootColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};

    float edgesColor[4] = {0.5f, 0.4f, 0.0f, 0.5f};
    float bottleneckColor[4] = {0.9f, 0.8f, 0.0f, 0.9f};


    mat4 transMat;
    transMat = glm::scale(transMat,vec3(scale));
    transMat = glm::translate(transMat,vec3(xTranslation,yTranslation,0.0));
    //vec3 scalingFactor = glm::vec3(scale);


    for(int i=0;i<graph->nodeVector.size();i++)
    {
        if(graph->nodeVector.at(i) == graph->root){
            glColor4f(rootColor[0], rootColor[1], rootColor[2], rootColor[3]);
            glPointSize(rootSize);
        }else{
            glColor4f(mapColor[0], mapColor[1], mapColor[2], mapColor[3]);
            glPointSize(nodeSize);
        }
            glBegin(GL_POINTS);
        vec4 tmpVec = vec4(vec2(graph->nodeVector.at(i)->getY(),graph->nodeVector.at(i)->getX()),1.0,1.0);
        tmpVec = transMat  * tmpVec;
        glVertex2f((tmpVec.x/xRatio * -1),
                   tmpVec.y/yRatio + 0.5);
            glEnd();
    }

    if(drawEdges){
        for(int i=0;i<graph->edgesVector.size();i++){
            if(runAnimation){
                if(i > currentEdgeLimit) break;
            }

            if(graph->bottleneckIndex == i){
                glColor4f(bottleneckColor[0], bottleneckColor[1],
                        bottleneckColor[2], bottleneckColor[3]);
                glLineWidth(1.5f);
            }else{
                glColor4f(edgesColor[0], edgesColor[1],
                        edgesColor[2], edgesColor[3]);
                glLineWidth(0.5f);
            }

            glBegin(GL_LINES);
            vec4 tmpVec1 = vec4(vec2(graph->edgesVector.at(i)->nodes.at(0)->getY(),graph->edgesVector.at(i)->nodes.at(0)->getX()),1.0,1.0);
                    tmpVec1 = transMat  * tmpVec1;
            vec4 tmpVec2 = vec4(vec2(graph->edgesVector.at(i)->nodes.at(1)->getY(),graph->edgesVector.at(i)->nodes.at(1)->getX()),1.0,1.0);
                    tmpVec2 = transMat  * tmpVec2;
            glVertex2f((tmpVec1.x/xRatio * -1),
                       tmpVec1.y/yRatio + 0.5);
            glVertex2f((tmpVec2.x/xRatio * -1),
                       tmpVec2.y/yRatio + 0.5);

            glEnd();
        }
    }
    drawGraphInfo(this->graph, -0.75);
}

void OglWidget::drawGraphInfo(Graph* graph, float yStart){
    std::vector<string> infos = graph->toString();
    float x,y,z;
    x = -1;
    y = yStart;
    z = 0;
    float dt = 0.05;
    for(unsigned int i = 0; i < infos.size(); i++){
        drawText(x,y,z, QString::fromStdString(infos[i]));
        y -= dt;

    }
}

void OglWidget::drawInfo(){
    std:vector<std::string> infos;
    infos.push_back("Run->Experiment_X");
    infos.push_back("Edit->Animation on/off");
    infos.push_back("Green dots: Cities");

    infos.push_back("Red dot: Root");
    infos.push_back("Thin (Brownish) Edges: Edges");
    infos.push_back("Thick (Yelloish) Edge: Bottleneck");
    infos.push_back("Edges are omitted in original full graph");

    float x,y,z;
    x = -1.0;
    y = 0.95f;
    z = 0;
    float dt = 0.05;
    for(unsigned int i = 0; i < infos.size(); i++){
        drawText(x,y,z, QString::fromStdString(infos[i]));
        y -= dt;
    }
}

void OglWidget::drawText(double x, double y, double z, QString txt) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    float fontSize = 15;
    float maxScreenHeight = 1250;
    float fact = screenHeight / maxScreenHeight;
    fontSize *= fact;

    qglColor(Qt::green);
    renderText(x, y, z, txt, QFont("Sans Serif", fontSize, QFont::ExtraLight, false) );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
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

