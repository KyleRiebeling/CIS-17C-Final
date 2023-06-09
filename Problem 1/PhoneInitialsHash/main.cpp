/* 
 * File:   main.cpp
 * Author: Kyle
 *
 * Created on June 6, 2023, 3:02 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "LinkedList.h"

using namespace std;

int hashPhone(string s) {
   int hash = 0;

   switch (s[0]) {
      case 'A':
      case 'B':
      case 'C':
         hash += 200;
         break;
      case 'D':
      case 'E':
      case 'F':
         hash += 300;
         break;
      case 'G':
      case 'H':
      case 'I':
         hash += 400;
         break;
      case 'J':
      case 'K':
      case 'L':
         hash += 500;
         break;
      case 'M':
      case 'N':
      case 'O':
         hash += 600;
         break;
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
         hash += 700;
         break;
      case 'T':
      case 'U':
      case 'V':
         hash += 800;
         break;
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
         hash += 900;
         break;
      default:
         hash -=100000;
   }
   
   switch (s[1]) {
      case 'A':
      case 'B':
      case 'C':
         hash += 20;
         break;
      case 'D':
      case 'E':
      case 'F':
         hash += 30;
         break;
      case 'G':
      case 'H':
      case 'I':
         hash += 40;
         break;
      case 'J':
      case 'K':
      case 'L':
         hash += 50;
         break;
      case 'M':
      case 'N':
      case 'O':
         hash += 60;
         break;
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
         hash += 70;
         break;
      case 'T':
      case 'U':
      case 'V':
         hash += 80;
         break;
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
         hash += 90;
         break;
      default:
         hash -=100000;
   }
   
   switch (s[2]) {
      case 'A':
      case 'B':
      case 'C':
         hash += 2;
         break;
      case 'D':
      case 'E':
      case 'F':
         hash += 3;
         break;
      case 'G':
      case 'H':
      case 'I':
         hash += 4;
         break;
      case 'J':
      case 'K':
      case 'L':
         hash += 5;
         break;
      case 'M':
      case 'N':
      case 'O':
         hash += 6;
         break;
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
         hash += 7;
         break;
      case 'T':
      case 'U':
      case 'V':
         hash += 8;
         break;
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
         hash += 9;
         break;
      default:
         hash -=100000;
   }
   
   return hash % 512;
}

int main(int argc, char** argv) {
   srand(time(0));
   string tmp = "   ";
   LinkedList<string> list[512];

   
   for (int i = 0; i < 512; i++){
      tmp[0] = (rand() % 26) + 65;
      tmp[1] = (rand() % 26) + 65;
      tmp[2] = (rand() % 26) + 65;
      list[hashPhone(tmp)].pushFront(tmp);
   }
   
   int values[10] = {0,0,0,0,0,0,0,0,0,0};
   
   for (int i = 0; i < 512; i++){
      values[list[i].getSize()]++;
   }
   
   float numCollisions = 0;
   for (int i = 2; i < 10; i++){
      numCollisions += values[i];
   }
   
   for (int i = 0; i < 10; i++){
      cout << "Number of indexes with " << i << " links: "
              << values[i] << endl;
   }
   cout << "Collision rate: " << (numCollisions/512) * 100 << "%" << endl;
   
   return 0;
}

