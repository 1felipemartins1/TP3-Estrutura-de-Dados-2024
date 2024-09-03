#include "QuadTree.hpp"
#include "MaxHeap.hpp"
#include "quicksort.hpp"
#include <cmath>
#include <iostream>

QuadNode::QuadNode(const Point &pt, const std::string &id, double maxX, double minX, double maxY, double minY)
    : point(pt), isActive(true), id(id), NE(-1), NW(-1), SE(-1), SW(-1), maxX(maxX), minX(minX), maxY(maxY), minY(minY) {}

QuadNode &QuadNode::operator=(const QuadNode &other)
{
    if (this != &other)
    {
        point = other.point;
        isActive = other.isActive;
        id = other.id;
        NE = other.NE;
        NW = other.NW;
        SE = other.SE;
        SW = other.SW;
        maxY = other.maxY;
        minY = other.minY;
        maxX = other.maxX;
        minX = other.minX;
       
    }
    return *this;
}

QuadTree::QuadTree(int capacity) : capacity(capacity), n_nodes(0)
{
    
    nodes = new QuadNode[capacity];
    if (nodes == nullptr)
    {
        std::cerr << "Erro: Memória insuficiente para inicializar a QuadTree com capacidade de " << capacity << " nós." << std::endl;
        exit(1);
    }
  /*  if ((int)(capacity * sizeof(QuadNode)) > bytes)
    {
        std::cerr << "node_initialize: smv did not provide enough memory" << std::endl;
        exit(1);
    } */ 
}

QuadTree::~QuadTree()
{
    delete[] nodes;
}

int QuadTree::find(const Point &p, std::string id)
{
    int current = 0;

    while (current != -1)
    {
        if (nodes[current].point.cordx == p.cordx && nodes[current].point.cordy == p.cordy && nodes[current].id == id)
        {
            return current;
        }

        if (nodes[current].point.cordx > p.cordx && nodes[current].point.cordy < p.cordy) // NW
        {
            current = nodes[current].NW;
        }
        else if (nodes[current].point.cordx <= p.cordx && nodes[current].point.cordy < p.cordy) // NE
        {
            current = nodes[current].NE;
        }
        else if (nodes[current].point.cordx > p.cordx && nodes[current].point.cordy >= p.cordy) // SW
        {
            current = nodes[current].SW;
        }
        else // SE
        {
            current = nodes[current].SE;
        }
    }

    return -1;
}

void QuadTree::insert(int nodeIdx, const Point &point, std::string id)
{
    if (nodes[nodeIdx].point.cordx > point.cordx && nodes[nodeIdx].point.cordy < point.cordy) // NW
    {
        if (nodes[nodeIdx].NW == -1)
        {
            nodes[n_nodes] = QuadNode(point, id, nodes[nodeIdx].point.cordx, nodes[nodeIdx].minX, nodes[nodeIdx].maxY, nodes[nodeIdx].point.cordy);
            nodes[nodeIdx].NW = n_nodes++;
        }
        else
        {
            insert(nodes[nodeIdx].NW, point, id);
        }
    }
    else if (nodes[nodeIdx].point.cordx <= point.cordx && nodes[nodeIdx].point.cordy < point.cordy) // NE
    {
        if (nodes[nodeIdx].NE == -1)
        {
            nodes[n_nodes] = QuadNode(point, id, nodes[nodeIdx].maxX, nodes[nodeIdx].point.cordx, nodes[nodeIdx].maxY, nodes[nodeIdx].point.cordy);
            nodes[nodeIdx].NE = n_nodes++;
        }
        else
        {
            insert(nodes[nodeIdx].NE, point, id);
        }
    }
    else if (nodes[nodeIdx].point.cordx > point.cordx && nodes[nodeIdx].point.cordy >= point.cordy) // SW
    {
        if (nodes[nodeIdx].SW == -1)
        {
            nodes[n_nodes] = QuadNode(point, id, nodes[nodeIdx].point.cordx, nodes[nodeIdx].minX, nodes[nodeIdx].point.cordy, nodes[nodeIdx].minY);
            nodes[nodeIdx].SW = n_nodes++;
        }
        else
        {
            insert(nodes[nodeIdx].SW, point, id);
        }
    }
    else // SE
    {
        if (nodes[nodeIdx].SE == -1)
        {
            nodes[n_nodes] = QuadNode(point, id, nodes[nodeIdx].maxX, nodes[nodeIdx].point.cordx, nodes[nodeIdx].point.cordy, nodes[nodeIdx].minY);
            nodes[nodeIdx].SE = n_nodes++;
        }
        else
        {
            insert(nodes[nodeIdx].SE, point, id);
        }
    }
}

void QuadTree::insert(const Point &point, const std::string &id)
{
    if (n_nodes == 0)
    {
        nodes[0] = QuadNode(point, id, INF, -INF, INF, -INF);
        ++n_nodes;
    }
    else
    {
        insert(0, point, id);
    }
}

bool QuadTree::activate(const Point &p, std::string id)
{
    int pos = find(p, id);

    if (pos == -1 || nodes[pos].isActive)
    {
        return false;
    }
    else
    {
        nodes[pos].isActive = true;
        return true;
    }
}

bool QuadTree::deactivate(const Point &p, std::string id)
{
    int pos = find(p, id);

    if (pos == -1 || !nodes[pos].isActive)
    {
        return false;
    }
    else
    {
        nodes[pos].isActive = false;
        return true;
    }
}

double calculateDistance(const Point &a, const Point &b)
{
    double result =std::sqrt((a.cordx - b.cordx) * (a.cordx - b.cordx) + (a.cordy - b.cordy) * (a.cordy - b.cordy));
    return result;
}

Distpair *QuadTree::knn(Point &p, int k)
{
    maxheap<Distpair> maxHeap(k);

    knn_query(0, p, maxHeap, k);

    Distpair *knnResults = new Distpair[k];

    for (int i = k - 1; i >= 0; i--)
    {
        knnResults[i] = maxHeap.top();
        maxHeap.dequeue();
    }

    return knnResults;
}

double minDistanceToQuadrant(double minX, double maxX, double minY, double maxY, const Point &target)
{
    double dy = std::max(0.0, std::max(minY - target.cordy, target.cordy - maxY));
    double dx = std::max(0.0, std::max(minX - target.cordx, target.cordx - maxX));
    return std::sqrt(dx * dx + dy * dy);
}

bool QuadTree::explorar(int childIdx, const Point &target, double maxDist)
{
    if (childIdx == -1)
        return false;

    double minDist = minDistanceToQuadrant(
        nodes[childIdx].minX, nodes[childIdx].maxX,
        nodes[childIdx].minY, nodes[childIdx].maxY,
        target);

    return minDist < maxDist;
}

void QuadTree::knn_query(int nodeIdx, const Point &target, maxheap<Distpair> &maxHeap, int k)
{
    if (nodeIdx == -1)
        return;

    double dist = calculateDistance(nodes[nodeIdx].point, target);

    if (nodes[nodeIdx].isActive)
    {
        if (maxHeap.getSize() < k)
        {
            maxHeap.enqueue({nodes[nodeIdx].id, dist});
        }
        else if (dist < maxHeap.top().distancia)
        {
            maxHeap.dequeue();
            maxHeap.enqueue({nodes[nodeIdx].id, dist});
        }
    }

    int bestQuadrant;
    if (target.cordx > nodes[nodeIdx].point.cordx && target.cordy < nodes[nodeIdx].point.cordy)
        bestQuadrant = nodes[nodeIdx].NE;
    else if (target.cordx <= nodes[nodeIdx].point.cordx && target.cordy < nodes[nodeIdx].point.cordy)
        bestQuadrant = nodes[nodeIdx].NW;
    else if (target.cordx > nodes[nodeIdx].point.cordx && target.cordy >= nodes[nodeIdx].point.cordy)
        bestQuadrant = nodes[nodeIdx].SE;
    else
        bestQuadrant = nodes[nodeIdx].SW;

    knn_query(bestQuadrant, target, maxHeap, k);

    int quadrants[4] = {nodes[nodeIdx].NE, nodes[nodeIdx].NW, nodes[nodeIdx].SE, nodes[nodeIdx].SW};

    for (int i = 0; i < 4; ++i)
    {
        if (quadrants[i] != bestQuadrant && explorar(quadrants[i], target, maxHeap.top().distancia))
        {
            knn_query(quadrants[i], target, maxHeap, k);
        }
    }
}
