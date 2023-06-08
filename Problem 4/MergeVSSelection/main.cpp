/* 
 * File:   main.cpp
 * Author: Kyle
 *
 * Created on June 6, 2023, 3:40 PM
 */

#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long oper = 0;

void selection(int *arr, int size, int stop) {
   //Loop and declare variables
   int indx, min;
   oper++; //i = 0
   for (int pos = 0; pos < stop; pos++) {
      oper+=2; //pos<n, pos++
      //Find the smallest in the list, swap after finding
      oper+= 3; // =, =, a[i]
      min = arr[pos];
      indx = pos;
      oper++; //i = 0;
      for (int i = pos + 1; i < size; i++) {
         oper+=2; //i<2,i++
         oper+=2; //a[i], <
         if (arr[i] < min) {
            oper+=3; // a[i], = , =
            min = arr[i];
            indx = i;
         }
      }
      //Perform the swap
      oper+=5; //a[i]x3, =x2
      arr[indx] = arr[pos];
      arr[pos] = min;
   }
}

int main(int argc, char** argv) {
   srand(time(0));
   const int AMOUNT = 100000;
   const int SORT_AMOUNT = 1000;

   int *array = new int[AMOUNT];
   int *copy = new int[AMOUNT];

   for (int i = 0; i < AMOUNT; i++) {
      array[i] = rand() % 1000;
      copy[i] = array[i];
   }



   auto start = high_resolution_clock::now();

   //Do Merge

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);

   cout << "Merge took " << duration.count() << " microseconds with " << oper << " operations" << endl;

   //Reset array so that both sorts face the same array
   for (int i = 0; i < AMOUNT; i++) {
      copy[i] = array[i];
   }

   oper = 0;
   start = high_resolution_clock::now();

   //Do Selection
   selection(copy, AMOUNT, SORT_AMOUNT);

   stop = high_resolution_clock::now();
   duration = duration_cast<microseconds>(stop - start);

   cout << "Selection took " << duration.count() << " microseconds with " << oper << " operations" << endl;

   for (int i = 1; i <= AMOUNT; i++) {
      if (i < SORT_AMOUNT + 50) {
         cout << copy[i-1] << " ";
         if (i % 10 == 0)cout << endl;
      }
   }
   cout << endl;

   return 0;
}

