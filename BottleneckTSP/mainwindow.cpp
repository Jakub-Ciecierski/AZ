#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    fileDialog = new QFileDialog(this);
    setupLayout();
    setupMenuBar();
}

MainWindow::~MainWindow()
{
    delete fileDialog;

    delete oglWidget;
    delete oglWidget2;
}

void MainWindow::setupLayout()
{
    mainLayout = new QVBoxLayout;
    oglWidgetLayout = new QHBoxLayout;

    oglWidget = new OglWidget();
    oglWidget->isDrawInfo = true;

    oglWidget2 = new OglWidget();

    oglWidgetLayout->addWidget(oglWidget);
    oglWidgetLayout->addWidget(oglWidget2);

    mainLayout->addLayout(oglWidgetLayout);

    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    centralWidget->setLayout(mainLayout);
}

void MainWindow::setupMenuBar()
{
    fileMenu = menuBar()->addMenu("File");
    openFile = new QAction(tr("Open file"),this);
    connect(openFile,SIGNAL(triggered(bool)),this,SLOT(openFileDialog()));
    fileMenu->addAction(openFile);

    experimentsMenu = menuBar()->addMenu("Run");
    runBrutForceAction = new QAction(tr("Run BruteForce"),this);
    runUSASmallAction = new QAction(tr("Run USA Small"),this);
    runUSAMediumAction = new QAction(tr("Run USA Medium"),this);
    runUSALargeAction = new QAction(tr("Run USA Big"),this);

    experimentsMenu->addAction(runBrutForceAction);
    experimentsMenu->addAction(runUSASmallAction);
    experimentsMenu->addAction(runUSAMediumAction);
    experimentsMenu->addAction(runUSALargeAction);

    connect(runBrutForceAction,SIGNAL(triggered(bool)),this,SLOT(runBruteforceExperiment()));
    connect(runUSASmallAction,SIGNAL(triggered(bool)),this,SLOT(runUSASmallExperiment()));
    connect(runUSAMediumAction,SIGNAL(triggered(bool)),this,SLOT(runUSAMediumExperiment()));
    connect(runUSALargeAction,SIGNAL(triggered(bool)),this,SLOT(runUSABigExperiment()));

    editMenu = menuBar()->addMenu("Edit");
    runAnimationAction = new QAction(tr("Animation on/off"),this);
    editMenu->addAction(runAnimationAction);
    connect(runAnimationAction,SIGNAL(triggered(bool)),this,SLOT(runAnimation()));
}

void MainWindow::openFileDialog()
{
    setlocale(LC_ALL, "C");
    fileDialog->show();
    QString path = fileDialog->getOpenFileName();

    //openGraphFile(path);
}

void MainWindow::setResult(BTSPResult result, bool drawEdges){
    if(oglWidget->graph != NULL)
        delete oglWidget->graph;
    if(oglWidget2->graph != NULL)
        delete oglWidget2->graph;

    oglWidget->graph = result.originalGraph;
    oglWidget->drawEdges = drawEdges;

    oglWidget2->graph = result.btspGraph;
}

void MainWindow::runBruteforceExperiment(){
    BTSPWorkshop btspWorkshop;

    BTSPResult result = btspWorkshop.runBruteForce();
    setResult(result);
}

void MainWindow::runUSASmallExperiment(){
    BTSPWorkshop btspWorkshop;

    BTSPResult result = btspWorkshop.runUSASmall();

    setResult(result, false);
}

void MainWindow::runUSAMediumExperiment(){
    BTSPWorkshop btspWorkshop;

    BTSPResult result = btspWorkshop.runUSAMedium();

    setResult(result, false);
}

void MainWindow::runUSABigExperiment(){
    BTSPWorkshop btspWorkshop;

    BTSPResult result = btspWorkshop.runUSABig();

    setResult(result, false);
}

void MainWindow::runAnimation(){
    bool currentValue = oglWidget2->isRunAnimation();
    oglWidget2->setRunAnimation(!currentValue);
}
