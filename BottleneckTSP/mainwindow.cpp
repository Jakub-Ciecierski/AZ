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

    openUSAMap();
}

MainWindow::~MainWindow()
{
    delete fileDialog;
}

void MainWindow::openUSAMap(){
    QString path = "../resources/usa115475.tsp";
    openGraphFile(path);
}

void MainWindow::setupLayout()
{
    mainLayout = new QVBoxLayout;
    oglWidgetLayout = new QHBoxLayout;
    oglWidget = new OglWidget();

    oglWidgetLayout->addWidget(oglWidget);
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
}

void MainWindow::openFileDialog()
{
    setlocale(LC_ALL, "C");
    fileDialog->show();
    QString path = fileDialog->getOpenFileName();

    openGraphFile(path);
}

void MainWindow::openGraphFile(QString path){
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
       int leap = 10;
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
       oglWidget->graph = Graph(nodeVector,minX,maxX,minY,maxY);
       inputFile.close();
    }else{
        std::cout << "No such file: " << path.toStdString() << std::endl;
    }
}
