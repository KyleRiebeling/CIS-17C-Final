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

void selection(int arr[], int size, int stop) {
   if (stop == 1000) {
      return;
   }

   int max = arr[0];
   int maxIndx = 0;

   for (int i = 0; i < size; i++) {
      if (arr[i] > max) {
         max = arr[i];
         maxIndx = i;
      }
   }

   int tmp = arr[size - 1];
   arr[size - 1] = max;
   arr[maxIndx] = tmp;

   stop++;
   selection(arr, size - 1, stop);

}

int main(int argc, char** argv) {
   srand(time(0));
   const int AMOUNT = 100000;

   long long oper = 0;
   int array[AMOUNT];
   int copy[AMOUNT];

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
      if (i > (AMOUNT - 1050)) {
         cout << copy[i] << " ";
         if (i % 10 == 0)cout << endl;
      }
   }
   cout << endl;

   return 0;
}

