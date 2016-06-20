#ifndef BTSP_WORKSHOP_H
#define BTSP_WORKSHOP_H

#include <Structures/graph.h>
#include <QString>
#include <sstream>

struct BTSPResult{
    Graph* originalGraph;
    Graph* btspGraph;
};

class BTSPWorkshop
{
private:
    std::vector<std::string> &split(const std::string &s, char delim,
                                    std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);

    Graph* openGraphFile(QString path, int leap = 1);
    BTSPResult runTest(QString path, int leap);
public:

    BTSPWorkshop();

    BTSPResult runBruteForce(QString path);
    BTSPResult runBruteForce();

    BTSPResult runUSASmall();
    BTSPResult runUSAMedium();
    BTSPResult runUSABig();
    BTSPResult runCustomExperiment(QString path);
};

#endif // BTSP_WORKSHOP_H
