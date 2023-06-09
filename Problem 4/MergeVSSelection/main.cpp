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

void merge(int a[], int left, int mid, int right) {
   oper+=2;
   int span = right - left;
   oper+=2;
   int count1 = left, countH = mid;
   oper++;
   int *c = new int[span];

   oper++;
   for (int i = 0; i < span; i++) {
      oper+=2;
      oper++;
      if (count1 == mid) {
         oper+=3;
         c[i] = a[countH++];
         oper++;
      } else if (countH == right) {
         oper+=3;
         c[i] = a[count1++];
         oper+=3;
      } else if (a[count1] < a[countH]) {
         oper+=3;
         c[i] = a[count1++];
      } else {
         oper+=3;
         c[i] = a[countH++];
      }
   }

   oper++;
   for (int i = 0; i < span; i++) {
      oper+=2;
      oper+=3;
      a[left + i] = c[i];
   }

   delete []c;
}

void mergeSort(int a[], int begin, int end) {
   oper+=2;
   int mid = (begin + end) / 2;
   oper+=2;
   if ((mid - begin) > 1)mergeSort(a, begin, mid);
   oper+=2;
   if ((end - mid) > 1)mergeSort(a, mid, end);
   merge(a, begin, mid, end);
}

int main(int argc, char** argv) {
   srand(time(0));
   const int AMOUNT = 100000;
   const int SORT_AMOUNT = 20;

   int *array = new int[AMOUNT];
   int copy[AMOUNT]; //for merge sort

   for (int i = 0; i < AMOUNT; i++) {
      array[i] = rand() % 1000;
      copy[i] = array[i];
   }

   auto start = high_resolution_clock::now();
   //Do Merge
   mergeSort(copy, 0, AMOUNT);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << "Merge took " << duration.count() << " microseconds with " << oper << " operations" << endl;

   oper = 0;
   
   start = high_resolution_clock::now();
   //Do Selection
   selection(array, AMOUNT, SORT_AMOUNT);
   stop = high_resolution_clock::now();
   duration = duration_cast<microseconds>(stop - start);
   cout << "Selection with " << SORT_AMOUNT << " elements took " << duration.count() << " microseconds with " << oper << " operations" << endl;
   
   return 0;
}

