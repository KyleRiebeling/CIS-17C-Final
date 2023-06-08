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

void selection(int *arr, int size, int stop) {
   if (stop == 10000) {
      return;
   }

   int maxIndx = stop;
   int minIndx = stop;

   for (int i = stop; i < size; i++) {
      if (arr[i] > arr[maxIndx]) {
         maxIndx = i;
      } else if (arr[i] < arr[minIndx]) {
         minIndx = i;
      }
   }
   size--;
   //Swap max
   if (maxIndx != size) {
      int tmp = arr[size];
      arr[size] = arr[maxIndx];
      arr[maxIndx] = tmp;
   }
   //Swap min
   if (minIndx != stop) {
      int tmp = arr[stop];
      arr[stop] = arr[minIndx];
      arr[minIndx] = tmp;
   }

   selection(arr, size, stop + 1);
}

int main(int argc, char** argv) {
   srand(time(0));
   const int AMOUNT = 100000;

   long long oper = 0;
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
   selection(copy, AMOUNT, 0);

   stop = high_resolution_clock::now();
   duration = duration_cast<microseconds>(stop - start);

   cout << "Selection took " << duration.count() << " microseconds with " << oper << " operations" << endl;

   for (int i = 0; i < AMOUNT; i++) {
      //if (i < 1020) {
         //cout << copy[i] << " ";
         //if (i % 10 == 0)cout << endl;
      //}
      //if (i > (AMOUNT - 1020)) {
         cout << copy[i] << " ";
         if (i % 10 == 0)cout << endl;
      //}
   }
   cout << endl;

   return 0;
}

