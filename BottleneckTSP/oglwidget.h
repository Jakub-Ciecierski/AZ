#ifndef OGLWIDGET_H
#define OGLWIDGET_H
#include <QGLWidget>

class OglWidget : public QGLWidget
{
    Q_OBJECT
public:
     explicit OglWidget(QWidget *parent = 0);
    ~OglWidget();
protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:

    int screenWidth;
    int screenHeight;
    int timerId;
    void timerEvent(QTimerEvent *event);
    void draw();
};

#endif // OGLWIDGET_H
