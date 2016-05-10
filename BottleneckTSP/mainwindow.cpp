#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    fileDialog = new QFileDialog(this);
    setupLayout();
    setupMenuBar();
}

MainWindow::~MainWindow()
{

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
    fileDialog->show();
}
