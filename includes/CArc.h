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
    /**
     * Unitary cost of the arc
     */
    int iCost;
    /**
     * Maximum flow supported by the arc
     */
    int iMaximumFlow;
    /**
     * Temporary flow amount, used to test the conservation law and the maximum flow.
     * Be aware that this variable is temporary and its content will be removed someday
     */
    int iTempFlow;

public:
    /**
     * CArc constructor
     *
     * @param iARCDestination Destination vertex identifier
     */
    explicit CArc(int iARCDestination, int iCost, int iMaximumFlow);
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
    /**
     * Retrieves the unitary cost of the arc
     *
     * @return The unitary cost of the arc
     */
    int ARCGetCost() const;
    /**
     * Retrieves the maximum flow supported by the arc
     *
     * @return The maximum flow supported by the arc
     */
    int ARCGetMaximumFlow() const;
    /**
     * Set the temporary flow value of the arc
     *
     * @param iTemporaryFlow New value of the temporary value
     */
    void ARCSetTemporaryFlow(int iTemporaryFlow);
    /**
     * Retrieves the temporary flow value of the arc
     *
     * @return The temporary flow value of the arc
     */
    int ARCGetTemporaryFlow() const;

};

#endif //MATRIXEDCPP_CARC_H
