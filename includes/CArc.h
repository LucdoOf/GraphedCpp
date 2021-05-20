//
// Created by eliott on 21/04/2021.
//

#ifndef MATRIXEDCPP_CARC_H
#define MATRIXEDCPP_CARC_H

/**
 * CArc class
 *
 * Representation of a graph arc between two vertices
 * This class don't contains any information about the starting vertex.
 * To get the starting vertex of an arc, please use CGraph::GRAGetVertexById.
 *
 * @warning It is not recommended to have two same arc instance in a same graph, some behaviors would be undefined
 */
class CArc {

private:
    /**
     * Identifier of the destination vertex
     */
    int iARCDestination;

public:
    /**
     * CArc constructor
     *
     * @param iARCDestination Destination vertex identifier
     */
    explicit CArc(int iARCDestination);
    /**
     * CArc copy constructor
     */
    CArc(CArc &);
    /**
     * CArc destructor
     */
    ~CArc() = default;
    /**
     * Retrieves the identifier of the destination vertex
     *
     * @return The identifier of the destination vertex
     */
    int ARCGetDestination() const;

};

#endif //MATRIXEDCPP_CARC_H
