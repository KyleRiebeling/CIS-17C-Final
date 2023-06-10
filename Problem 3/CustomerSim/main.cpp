/* 
 * File:   main.cpp
 * Author: Kyle
 *
 * Created on June 9, 2023, 8:02 PM
 */

#include <iostream>
#include <queue>
#include <utility>

using namespace std;

void print(int results[]){
   int maxIndx = 0;
   int i = 0;
   cout << "Amount of customers\tTicks\n";
   while (results[i] + results[i + 1] > 0) {
      if (results[i] > results[maxIndx]) {
         maxIndx = i;
      }
      cout << " " << i << "\t\t\t" << results[i] << endl;
      i++;
   }
   cout << "Most common amount of customers: " << maxIndx << endl;
}

int main(int argc, char** argv) {
   srand(time(0));
   //Program in 15 second ticks or 1/4 minute per tick

   queue<int> custLine;
   float custSpeed = 1.0;
   float lastCust = 0.0;
   float nextCust = 1.0;

   //Ticks to finish with a customer, are they with a customer or not 
   pair<float, bool> clerk1(4, false);
   pair<float, bool> clerk2(8, false);
   pair<float, bool> clerk3(6, false);
   pair<float, bool> clerk4(4, false);
   pair<float, bool> clerk5(4, false);
   pair<float, bool> clerk6(4, false);
   pair<float, bool> clerk7(4, false);
   bool noClerks = false;

   int results[50];

   for (int i = 0; i < 50; i++) {
      results[i] = 0;
   }

   //5 minute simulation
   for (int i = 0; i < 4 * 60 * 5; i++) {
      //Add customer to queue if time is right
      custLine.push(1);


      //Tick down time with customers
      if (clerk1.second) {
         clerk1.first--;
         if (clerk1.first == 0) {
            clerk1.second = false;
            noClerks = false;
         }
      }

      if (clerk2.second) {
         clerk2.first--;
         if (clerk2.first == 0) {
            noClerks = false;
            clerk2.second = false;
         }
      }

      if (clerk3.second) {
         clerk3.first--;
         if (clerk3.first == 0) {
            noClerks = false;
            clerk3.second = false;
         }
      }

      if (clerk4.second) {
         clerk4.first--;
         if (clerk4.first == 0) {
            noClerks = false;
            clerk4.second = false;
         }
      }

      if (clerk5.second) {
         clerk5.first--;
         if (clerk5.first == 0) {
            noClerks = false;
            clerk5.second = false;
         }
      }

      //Send customers to fastest open clerk
      while (!custLine.empty() && !noClerks) {
         if (!clerk1.second) {
            clerk1.second = true;
            custLine.pop();
            clerk1.first = 4;
         } else if (!clerk4.second && custLine.size() >= 5) {
            clerk4.second = true;
            custLine.pop();
            clerk4.first = 4;
         } else if (!clerk5.second && custLine.size() >= 10) {
            clerk5.second = true;
            custLine.pop();
            clerk5.first = 4;
         } else if (!clerk3.second) {
            clerk3.second = true;
            custLine.pop();
            clerk3.first = 6;
         } else if (!clerk2.second) {
            clerk2.second = true;
            custLine.pop();
            clerk2.first = 8;
         } else {
            noClerks = true;
         }
      }
      results[custLine.size()]++;
   }

   cout << "Before randomization \n------------------------\n";
   print(results);

   //Reset Results
   for (int i = 0; i < 50; i++) {
      results[i] = 0;
   }

   //Randomized 30 minutes
   for (int i = 0; i < 4 * 60 * 30; i++) {
      //Add customer to queue if time is right
      if (custSpeed + lastCust >= nextCust) {
         lastCust = nextCust;
         nextCust += custSpeed;
         custSpeed = rand() % 2 + .5;
         custLine.push(1);
      } else {
         custSpeed += custSpeed;
      }

      //Tick down time with customers
      if (clerk1.second) {
         clerk1.first--;
         if (clerk1.first == 0) {
            clerk1.second = false;
            noClerks = false;
         }
      }

      if (clerk2.second) {
         clerk2.first--;
         if (clerk2.first == 0) {
            noClerks = false;
            clerk2.second = false;
         }
      }

      if (clerk3.second) {
         clerk3.first--;
         if (clerk3.first == 0) {
            noClerks = false;
            clerk3.second = false;
         }
      }

      if (clerk4.second) {
         clerk4.first--;
         if (clerk4.first == 0) {
            noClerks = false;
            clerk4.second = false;
         }
      }

      if (clerk5.second) {
         clerk5.first--;
         if (clerk5.first == 0) {
            noClerks = false;
            clerk5.second = false;
         }
      }

      //Send customers to fastest open clerk
      while (!custLine.empty() && !noClerks) {
         if (!clerk1.second) {
            clerk1.second = true;
            custLine.pop();
            clerk1.first = rand() % 5 + 2;
         } else if (!clerk4.second && custLine.size() >= 5) {
            clerk4.second = true;
            custLine.pop();
            clerk1.first = rand() % 5 + 2;
         } else if (!clerk5.second && custLine.size() >= 10) {
            clerk5.second = true;
            custLine.pop();
            clerk1.first = rand() % 5 + 2;
         } else if (!clerk3.second) {
            clerk3.second = true;
            custLine.pop();
            clerk1.first = rand() % 7 + 3;
         } else if (!clerk2.second) {
            clerk2.second = true;
            custLine.pop();
            clerk1.first = rand() % 9 + 4;
         } else {
            noClerks = true;
         }
      }
      results[custLine.size()]++;
   }

   cout << "After randomization \n------------------------\n";
   print(results);
   
   cout << "\n\tAnalysis\n----------------------------\n";
   cout << "When running the normal parameters, the simulation \n" <<
           "quickly comes to a hovering point at around 9\n" <<
           "customers in line. During the random simulation,\n" << 
           "The line mostly sits at zero, with occasional spikes,\n" <<
           "even when running a longer simulation. This is\n" <<
           "happening because the most common thing being modified\n" <<
           "is the customer appearance rate. This means that\n" <<
           "the little bit of extra time given between customers\n" <<
           "is applied to up to 5 clerks. The randomization favors\n" << 
           "the clerks because they all benefit from the extra time." << endl;
   return 0;
}

