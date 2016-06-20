#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "oglwidget.h"
#include <string>
#include <sstream>
#include <vector>
#include <locale.h>
#include "bottlenecktsp.h"
#include <btsp_workshop.h>

/*namespace Ui {
class MainWindow;
}*/

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QWidget *centralWidget;
    QMenu *fileMenu;    
    QAction *openFile;
    QAction *openBruteFile;

    QMenu *experimentsMenu;
    QAction *runBrutForceAction;
    QAction *runUSASmallAction;
    QAction *runUSAMediumAction;
    QAction *runUSALargeAction;

    QMenu *editMenu;
    QAction *runAnimationAction;

    QFileDialog *fileDialog;

    OglWidget *oglWidget;
    OglWidget* oglWidget2;
    OglWidget* oglWidget3;

    QVBoxLayout *mainLayout;
    QHBoxLayout *oglWidgetLayout;

    void setupLayout();
    void setupMenuBar();

    BottleneckTSP btsp = BottleneckTSP();

private slots:
    void openFileDialog();
    void openFileBruteForceDialog();

    void setResult(BTSPResult result, bool drawEdges = true);

    void runBruteforceExperiment();
    void runUSASmallExperiment();
    void runUSAMediumExperiment();
    void runUSABigExperiment();

    void runAnimation();

};

#endif // MAINWINDOW_H
