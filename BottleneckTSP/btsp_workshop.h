#ifndef BTSP_WORKSHOP_H
#define BTSP_WORKSHOP_H

#include <Structures/graph.h>
#include <QString>
#include <sstream>

class BTSPWorkshop
{
private:
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }


    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    Graph* openGraphFile(QString path, int leap = 1);

public:

    BTSPWorkshop();

    void runBruteForce();

    void runUSASmall();
    void runUSAMedium();
    void runUSABig();
};

#endif // BTSP_WORKSHOP_H
