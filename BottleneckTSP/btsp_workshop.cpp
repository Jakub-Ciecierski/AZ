#include "btsp_workshop.h"
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QFile>

BTSPWorkshop::BTSPWorkshop(){

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
       float minX =1000000000000;
       float minY=1000000000000;
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


void BTSPWorkshop::runBruteForce(){

}

void BTSPWorkshop::runUSASmall(){

}

void BTSPWorkshop::runUSAMedium(){

}

void BTSPWorkshop::runUSABig(){

}
