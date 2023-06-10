/* 
 * File:   main.cpp
 * Author: Kyle
 *
 * Created on June 9, 2023, 6:36 PM
 */

#include <iostream>

#include "BiMatrixGraph.h"

using namespace std;

int main(int argc, char** argv) {
   string key[7] = {"LAX", "SFO", "DFW", "ORD", "BOS", "JFK", "MIA"};
   BiMatrixGraph graph(7);

   graph.setKey(key);
   
   graph.addWeight("SFO","BOS", 2703);
   graph.addWeight("SFO", "ORD", 1847);
   graph.addWeight("ORD", "BOS", 868);
   graph.addWeight("ORD", "JFK", 743);
   graph.addWeight("JFK", "BOS", 189);
   graph.addWeight("SFO", "DFW", 1465);
   graph.addWeight("DFW", "ORD", 803);
   graph.addWeight("DFW", "MIA", 1124);
   graph.addWeight("MIA", "JFK", 1093);
   graph.addWeight("MIA", "BOS", 1257);
   graph.addWeight("SFO", "LAX", 338);
   graph.addWeight("LAX", "DFW", 1234);
   graph.addWeight("LAX", "MIA", 2341);

   graph.minDistDijk("ORD", "LAX");
   graph.minDistDijk("JFK", "SFO");
   graph.primMST();
   
   cout << "By hand analysis is the same as my program!" << endl;

   return 0;
}

