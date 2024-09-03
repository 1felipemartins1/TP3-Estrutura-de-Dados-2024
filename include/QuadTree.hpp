#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "MaxHeap.hpp"
#include "Pares.hpp"
#include "Operadores.hpp"
#include "funcoes.hpp"
#include <string>
#define INF 0x3f3f3f3f

struct QuadNode
{
   Point point;
   bool isActive;
   std::string id;
   int NE, NW, SE, SW;
   double maxX, minX, maxY, minY;

   QuadNode(const Point &pt = Point(), const std::string &id = "-1", double maxX = 0, double minX = 0, double maxY = 0, double minY = 0);
   QuadNode &operator=(const QuadNode &other);
};

class QuadTree
{
public:
   QuadNode *nodes;
   int capacity;
   int n_nodes;

   void insert(int nodeIdx, const Point &point, std::string id);
   int find(const Point &p, std::string id);
   void knn_query(int nodeIdx, const Point &target, maxheap<Distpair> &maxHeap, int k);
   bool explorar(int childIdx, const Point &target, double maxDist);
   QuadTree(int capacity = 50);
   void insert(const Point &point, const std::string &id);
   ~QuadTree();
   bool activate(const Point &p, std::string id);
   bool deactivate(const Point &p, std::string id);
   Distpair *knn(Point &p, int k);
};
double minDistanceToQuadrant(double minX, double maxX, double minY, double maxY, const Point &target);
double calculateDistance(const Point &a, const Point &b);


#endif // QUADTREE_HPP
