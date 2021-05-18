//
// Created by eliott on 21/04/2021.
//

#ifndef MATRIXEDCPP_CGRAPHE_H
#define MATRIXEDCPP_CGRAPHE_H

#include "CSommet.h"
#include <malloc.h>

class CGraph {

private:
    CList<CSommet*>* pGRAVertices;
public:
    CGraph();
    CGraph(CGraph&);
    void print();
    inline CList<CSommet*>* GRAGetVertices();
    void addVertex(CSommet* vertex);
    void deleteVertex(CSommet* vertex);
    CSommet* getVertexById(int id);
    CGraph* GRAInvert();

};
#endif //MATRIXEDCPP_CGRAPHE_H
