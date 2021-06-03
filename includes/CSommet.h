#ifndef GRAPHEDCPP_CSOMMET_H
#define GRAPHEDCPP_CSOMMET_H

#include "CArc.h"
#include <cstdio>
#include "CList.h"

class CSommet {

private:
    /**
     * Vertex identifier
     */
    int iSOMId;
    /**
     * List of incoming arcs
     */
    CList<CArc>* pSOMIncoming;
    /**
     * List of leaving arcs
     */
    CList<CArc>* pSOMLeaving;

public:
    /**
     * CSommet constructor
     *
     * @param iSOMId Vertex identifier
     */
    explicit CSommet(int iSOMId);
    /**
     * CSommet copy constructor
     *
     * Copy the list of leaving and incoming arc
     */
    CSommet(CSommet&);
    /**
     * CSommet destructor
     *
     * Delete the incoming and leaving arc.
     * Please don't use this if you want to remove the vertex from the graph,
     * use the removeVertex method from graph class
     */
    ~CSommet();
    /**
     * Add an incoming arc to the vertex
     *
     * @param CArc New incoming arc (don't add duplicates)
     */
    void SOMAddIncomingArc(CArc* CArc);
    /**
     * Add a leaving arc to the vertex
     *
     * @param CArc New leaving arc (don't add duplicates)
     */
    void SOMAddLeavingArc(CArc* CArc);
    /**
     * Remove an incoming arc from the vertex
     *
     * @param arc Incoming arc to remove (delete the arc)
     */
    void SOMDeleteIncomingArc(CArc* arc);
    /**
     * Remove a leaving arc from the vertex
     *
     * @param arc Leaving arc to remove (delete the arc)
     */
    void SOMDeleteLeavingArc(CArc* arc);
    /**
     * Retrieves the list of the vertex incoming arcs
     *
     * @warning It is not recommended to change the list content, this list is given only for getting purposes,
     * any direct modifications will cause the vertex / graph to be corrupted, please use vertex methods instead
     * @return The list of the incoming vertex arcs
     */
    CList<CArc>* SOMGetIncomingArcs();
    /**
     * Retrieves the list of the vertex leaving arcs
     *
     * @warning It is not recommended to change the list content, this list is given only for getting purposes,
     * any direct modifications will cause the vertex / graph to be corrupted, please use vertex methods instead
     * @return The list of the leaving vertex arcs
     */
    CList<CArc>* SOMGetLeavingArcs();
    /**
     * Retrieves the vertex identifier
     *
     * @return The vertex identifier
     */
    int SOMGetId() const;
    /**
     * Check the incoming and leaving arcs for the conversation law
     *
     * @return True if the conservation law is respected, false if it isn't
     */
    bool SOMTestConservationLaw();
    /**
     * Print the result of the conservation law test
     */
    void SOMPrintConservationLaw();
    /**
     * Compute and retrieves the temporary incoming flow
     *
     * @return The temporary incoming flow
     */
    int SOMComputeTemporaryIncomingFlow();
    /**
     * Compute and retrieves the temporary leaving flow
     *
     * @return The temporary leaving flow
     */
    int SOMComputeTemporaryLeavingFlow();

};

#endif //GRAPHEDCPP_CSOMMET_H