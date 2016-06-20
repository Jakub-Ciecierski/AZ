#include "btsp_workshop.h"
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QFile>
#include "bottlenecktsp.h"
#include <btsp_bruteforce.h>

BTSPWorkshop::BTSPWorkshop(){

}

std::vector<std::string> & BTSPWorkshop::split(const std::string &s, char delim,
                                               std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> BTSPWorkshop::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

Graph* BTSPWorkshop::openGraphFile(QString path, int leap){
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
       float minX = 1000000000000;
       float minY = 1000000000000;
       float maxX = 0;
       float maxY = 0;

       int counter =0;
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
    return graph;
}

BTSPResult BTSPWorkshop::runTest(QString path, int leap){
    BottleneckTSP btsp;

    Graph* originalGraph = openGraphFile(path, leap);
    if(originalGraph == NULL){
        return BTSPResult{NULL, NULL};
    }

    Graph* resultGraph = btsp.BTSPApprox(originalGraph);

    BTSPResult results{originalGraph, resultGraph};

    resultGraph->getBottleneck();
    resultGraph->calculateSumOfWeights();

    resultGraph->name = "BTSP Approx";
    originalGraph->name = "Original USA";

    return results;
}

BTSPResult BTSPWorkshop::runBruteForce(){
    BottleneckTSP btsp;
    QString path = "../resources/usa_base_DO_NOT_USE.tsp";
    int leap = 11000; // usa, leap 11000 yeilds 10 vertices.

    Graph* originalGraph = openGraphFile(path, leap);
    if(originalGraph == NULL){
        return BTSPResult{NULL, NULL};
    }

    Graph* btspAproxxGraph = btsp.BTSPApprox(originalGraph);

    BTSPBruteforce btspBruteforce(originalGraph);
    Graph* bruteforceGraph = btspBruteforce.solve(0);

    BTSPResult results{btspAproxxGraph, bruteforceGraph};

    float approxBottlneck = btspAproxxGraph->getBottleneck();
    float bruteBottlneck = bruteforceGraph->getBottleneck();

    float approxSumOfWeights = btspAproxxGraph->calculateSumOfWeights();
    float bruteSumOfWeights = bruteforceGraph->calculateSumOfWeights();

    btspAproxxGraph ->name = "BTSP Approx";
    bruteforceGraph->name = "BTSP Bruteforce";

    return results;
}

BTSPResult BTSPWorkshop::runUSASmall(){
    QString path = "../resources/usa_base_DO_NOT_USE.tsp";
    int leap = 750;

    return runTest(path, leap);
}

BTSPResult BTSPWorkshop::runUSAMedium(){
    QString path = "../resources/usa_base_DO_NOT_USE.tsp";
    int leap = 500;

    return runTest(path, leap);
}

BTSPResult BTSPWorkshop::runUSABig(){
    QString path = "../resources/usa_base_DO_NOT_USE.tsp";
    int leap = 250;

    return runTest(path, leap);
}

BTSPResult BTSPWorkshop::runCustomExperiment(QString path){
    int leap = 1;
    return runTest(path, leap);
}
