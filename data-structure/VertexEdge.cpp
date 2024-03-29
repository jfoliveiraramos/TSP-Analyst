/** @file VertexEdge.cpp
 *  @brief Contains the VertexEdge Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id, std::shared_ptr<Coordinates> coordinates) : id(id), coordinates(coordinates) {}

Edge *Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                } else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true;
        } else {
            it++;
        }
    }
    return removedEdge;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

std::shared_ptr<Coordinates> Vertex::getCoordinates() const {
    return this->coordinates;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w) :
        orig(orig), dest(dest), weight(w) {}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

double Edge::getMinResidual() {
    return maxResidual;
}

void Edge::setMinResidual(int minResidual) {
    this->maxResidual = minResidual;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setUsed(bool used) {
    this->used = used;
}

bool Edge::isUsed() const {
    return this->used;
}

// function to overload < so, edges with less weight come first in priority queue
