/*
 * File: main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on Dec 2, 2018, 8:11 PM
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

stack<int> stackG;
stack<int> stackH;

float h(float);
float g(float);


int main(int argc, char** argv) {
   //Testing out recursive trig functions
   //float angDeg = 1;
   float angRad = 3;
   //cout << " sinh = " << sinh(angRad) <<
           //" our h = " << h(angRad) << endl;
   cout << "Angle = " << angRad << " cosh = " << cosh(angRad) <<
           " our g = " << g(angRad) << endl;
   //Exit stage right
   cout << "H calls: " << stackH.size() << endl;
   cout << "G calls: " << stackG.size();
   return 0;
}

float h(float angR) {
   stackH.push(angR);
   float tol = 1e-6;
   if (angR>-tol && angR < tol)return angR + angR * angR * angR / 6;
   return 2 * h(angR / 2) * g(angR / 2);
}

float g(float angR) {
   stackG.push(angR);
   float tol = 1e-6;
   if (angR>-tol && angR < tol)return 1 + angR * angR / 2;
   float b = h(angR / 2);
   return 1 + 2 * b*b;
}
