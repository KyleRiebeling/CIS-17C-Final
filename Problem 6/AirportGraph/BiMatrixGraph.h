/* 
 * File:   BiMatrixGraph.h
 * Author: Kyle
 *
 * Created on June 2, 2023, 10:48 AM
 */

#ifndef BIMATRIXGRAPH_H
#define BIMATRIXGRAPH_H

#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

class BiMatrixGraph {
private:
   int **graph;
   int numVerts;
   string *key;
   bool usingKey = false;

   void printMST(int parent[]) {
      int total = 0;
      if (!usingKey) {
         cout << "     MSP     \n-------------\n";
         cout << "Edge \tWeight" << endl;
         for (int i = 1; i < numVerts; i++) {
            cout << parent[i] << " - " << i << " \t"
                    << graph[i][parent[i]] << endl;
            total += graph[i][parent[i]];
         }
      } else {
         cout << "\tMSP\n-----------------------\n";
         cout << "Edge \t\tWeight" << endl;
         for (int i = 1; i < numVerts; i++) {
            cout << key[parent[i]] << " - " << key[i] << " \t"
                    << graph[i][parent[i]] << endl;
            total += graph[i][parent[i]];
         }
      }

      cout << "Total weight: " << total << endl << endl;
   }

   int minKey(int distance[], bool visited[]) {

      int min = INT_MAX, min_index;

      for (int i = 0; i < numVerts; i++) {
         if (visited[i] == false && distance[i] <= min) {
            min = distance[i], min_index = i;
         }
      }

      return min_index;
   }

public:

   BiMatrixGraph(int verts) {
      numVerts = verts;
      graph = new int *[numVerts];
      for (int i = 0; i < numVerts; i++) {
         graph[i] = new int[numVerts];
         for (int j = 0; j < numVerts; j++) {
            graph[i][j] = 0;
         }
      }
   }

   void setKey(string s[]) {
      key = s;
      usingKey = true;
   }

   void addEdge(string x, string y) {
      int xIndx = 0, yIndx = 0;
      for (int i = 0; i < numVerts; i++) {
         if (key[i] == x)xIndx = i;
         if (key[i] == y)yIndx = i;
      }
      graph[xIndx][yIndx] = 1;
      graph[yIndx][xIndx] = 1;
   }

   void addWeight(string x, string y, int w) {
      int xIndx = 0, yIndx = 0;
      for (int i = 0; i < numVerts; i++) {
         if (key[i] == x)xIndx = i;
         if (key[i] == y)yIndx = i;
      }

      graph[xIndx][yIndx] += w;
      graph[yIndx][xIndx] += w;
   }

   void primMST() {
      // Array to store constructed MST
      int parent[numVerts];

      // Key values used to pick minimum weight edge in cut
      int distance[numVerts];

      // To represent set of vertices included in MST
      bool visited[numVerts];

      // Initialize all keys as INFINITE
      for (int i = 0; i < numVerts; i++) {
         distance[i] = INT_MAX, visited[i] = false;
      }

      // Distance to first vertex to itself is 0
      distance[0] = 0;

      // First node is always root of MST
      parent[0] = -1;

      for (int count = 0; count < numVerts - 1; count++) {

         // Pick the minimum weighted distance to the vertices not visited
         int u = minKey(distance, visited);

         // Add the picked vertex to the visited set
         visited[u] = true;

         for (int v = 0; v < numVerts; v++)

            if (graph[u][v] && visited[v] == false && graph[u][v] < distance[v]) {
               parent[v] = u, distance[v] = graph[u][v];
            }
      }

      // Print the constructed MST
      printMST(parent);
   }

   void minDistDijk(string mainS, string secondK) {
      int distance[numVerts];
      bool visited[numVerts];
      int main;

      for (int i = 0; i < numVerts; i++) {
         if (key[i] == mainS)main = i;
      }

      for (int i = 0; i < numVerts; i++) {
         distance[i] = INT_MAX;
         visited[i] = false;
      }

      distance[main] = 0; // Distance to itself is 0

      for (int i = 0; i < numVerts; i++) {
         //Find min distance
         int min = minKey(distance, visited);
         visited[min] = true;
         for (int j = 0; j < numVerts; j++) {
            //Update distances to neighboring nodes if needed
            if (!visited[j] && graph[min][j] && distance[min] != INT_MAX && distance[min] + graph[min][j] < distance[j]) {
               distance[j] = distance[min] + graph[min][j];
            }
         }
      }

      
      for (int i = 0; i < numVerts; i++) {
         if (key[i] == secondK) {
            cout << key[i] << " is " << distance[i]  << " away from " << key[main]<< endl << endl;
         }
      }

   }
};

#endif /* BIMATRIXGRAPH_H */

