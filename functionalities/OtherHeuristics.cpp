//
// Created by Ramos on 5/30/2023.
//

#include <cmath>
#include "OtherHeuristics.h"

OtherHeuristics::OtherHeuristics(std::shared_ptr<Graph> graph) : graph(graph) {}

int OtherHeuristics::nearestNeighbours(Tour &tour){

    if (graph->getNumVertex() == 0)
        return 1;

    for (Vertex* vertex: graph->getVertexSet()) {
        vertex->setVisited(false);
    }

    std::vector<Vertex*> vertexSet = graph->getVertexSet();

    std::vector<Edge*> tourEdges;

    Vertex* origin = vertexSet[0];

    Vertex* currentVertex = origin;

    bool travelling = true;

    while (travelling){

        currentVertex->setVisited(true);

        Edge *minEdge = nullptr;

        for (Edge *edge: currentVertex->getAdj()) {
            if (!edge->getDest()->isVisited()) {
                if (minEdge == nullptr) {
                    minEdge = edge;
                } else if (edge->getWeight() < minEdge->getWeight()) {
                    minEdge = edge;
                }
            }
        }

        if (minEdge == nullptr) {
            for (Edge *edge: currentVertex->getAdj()) {
                if (edge->getDest() == origin) {
                    minEdge = edge;
                    travelling = false;
                    break;
                }
            }
        }
        tourEdges.push_back(minEdge);

        currentVertex = minEdge->getDest();
    }

    tour.setTour(tourEdges);

    return 0;
}

Tour OtherHeuristics::twoOptSwap(Tour &tour, int i, int j){

    std::vector<Edge*> tourEdges = tour.getEdges();

    Tour newTour;
    std::vector<Edge*> newTourEdges;

    for (int c = 0; c < i; c++){
        newTourEdges.push_back(tourEdges[c]);
    }

    Edge* e1 = graph->getEdge(tourEdges[i]->getOrig()->getId(), tourEdges[j]->getOrig()->getId());
    newTourEdges.push_back(e1);
    for (int c = j - 1; c > i; c--){
        Edge* edge = tourEdges[c];
        newTourEdges.push_back(edge->getReverse());
    }

    Edge* e2 = graph->getEdge(tourEdges[i]->getDest()->getId(), tourEdges[j]->getDest()->getId());
    newTourEdges.push_back(e2);

    for (int c = j + 1; c < tourEdges.size(); c++){
        newTourEdges.push_back(tourEdges[c]);
    }

    newTour.setTour(newTourEdges);

    return newTour;
}

int OtherHeuristics::twoOpt(Tour &tour){

    unsigned int improvements = 20;

    while (improvements){

        improvements--;

        std::vector<Edge*> tourEdges = tour.getEdges();

        double bestCost = tour.getCost();

        for (int i = 0; i < tourEdges.size() - 1; i++){

            int x = 1;

            for (int j = i + 1; j < tourEdges.size(); j += x){

                Tour newTour = twoOptSwap(tour,i,j);

                if (round(newTour.getCost() * 1000) < round(bestCost * 1000)){
                    tour = newTour;
                    improvements = 20;
                    bestCost = newTour.getCost();
                    x = 1;
                } else {
                    x *= 2;
                }
            }
        }
    }
    return 0;
}
