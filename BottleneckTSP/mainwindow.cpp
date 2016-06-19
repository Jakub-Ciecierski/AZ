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

    //openUSAMap();
}

MainWindow::~MainWindow()
{
    delete fileDialog;

    delete oglWidget;
    delete oglWidget2;
    delete oglWidget3;
}

void MainWindow::openUSAMap(){
    QString path = "../resources/usa115475.tsp";
    //QString path = "../resources/mein.tsp";
    openGraphFile(path);
}

void MainWindow::setupLayout()
{
    mainLayout = new QVBoxLayout;
    oglWidgetLayout = new QHBoxLayout;

    oglWidget = new OglWidget();
    oglWidget2 = new OglWidget();
    oglWidget3 = new OglWidget();

    oglWidgetLayout->addWidget(oglWidget);
    oglWidgetLayout->addWidget(oglWidget2);
    //oglWidgetLayout->addWidget(oglWidget3);

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

    openGraphFile(path);
}

void MainWindow::openGraphFile(QString path, int leap){
    Graph* graph = NULL;
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       vector<Node*> *nodeVector = new vector<Node*>();
       QTextStream in(&inputFile);
       int vectorSize = 0;
       bool readDim = false;
       while (!readDim)
       {
          QString line = in.readLine();
          std::vector<std::string> x = split(line.toStdString(), ' ');
          //printf("%s \n",x.at(0));
          if(!strcmp(x.at(0).c_str(),"DIMENSION:"))
          {
              readDim = true;
              vectorSize = stoi(x.at(1));
              //TMP
              //nodeVector->resize(vectorSize);
              in.readLine();
              in.readLine();
          }
       }
       float minX =1000000000000;
       float minY=1000000000000;
       float maxX = 0;
       float maxY = 0;

       int counter =0;

       int leap = 1000;

       for(int i=0;i<vectorSize;i++)
       {
           QString line = in.readLine();
           counter++;
           if(counter == leap){
           counter =0;
           std::vector<std::string> x = split(line.toStdString(), ' ');
           float xCord = (float)stof(x.at(1));
           if(xCord<minX) minX = xCord;
           if(xCord>maxX) maxX = xCord;
           float yCord = (float)stof(x.at(2));
           if(yCord<minY) minY = yCord;
           if(yCord>maxY) maxY = yCord;
           //TMP
           nodeVector->push_back(new Node(xCord,yCord));
           }
       }
       graph = new Graph(nodeVector,minX,maxX,minY,maxY);
       //oglWidget->graph = new Graph(nodeVector,minX,maxX,minY,maxY);
       //oglWidget2->graph = new Graph(nodeVector,minX,maxX,minY,maxY);

       //Graph* graph = btsp.BTSPApprox(oglWidget->graph);
       //*(oglWidget->graph) = *graph;
       //oglWidget->graph->isInit = true;

       inputFile.close();
    }else{
        std::cout << "No such file: " << path.toStdString() << std::endl;
    }
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
