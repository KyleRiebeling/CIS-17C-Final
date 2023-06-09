/* 
 * File:   Link.h
 * Author: Kyle
 *
 * Created on April 19, 2023, 4:48 PM
 */

#ifndef LINK_H
#define LINK_H
#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
struct Link {
   T data;
   Link *next;
};

template <typename T>
class LinkedList {
private:
   Link<T> *first;
public:

   LinkedList() {
      first = NULL;
   };
   
   int getSize(){
      if (first == NULL)return 0;
      
      Link<T> *curr = first;
      int i = 0;
      
      while (curr != NULL) {
         i++;
         curr = curr->next;
      }
      return i; 
   }

   void pushFront(T n) {
      if (first == NULL) {
         first = new Link<T>;
         first->data = n;
         first->next = NULL;

      } else {
         Link<T> *tmp = new Link<T>;
         tmp->data = n;
         tmp->next = first;
         first = tmp;
      }
   }

   void pushBack(T n) {
      if (first == NULL) {
         first = new Link<T>;
         first->data = n;
         first->next = NULL;
      } else {
         Link<T> *tmp = new Link<T>;
         tmp->data = n;
         tmp->next = NULL;

         Link<T> *curr = first;

         while (curr && curr->next) {
            curr = curr->next;
         }

         curr->next = tmp;
      }
   }

   void popFront() {
      Link<T> *tmp = first;
      first = first->next;
      delete tmp;
   }

   void popBack() {
      Link<T> *curr = first;

      while (curr->next && curr->next->next) {
         curr = curr->next;
      }
      
      Link<T> *tmp = curr->next;
      curr->next = NULL;

      delete tmp;
   }

   void print() {
      if (first == NULL)return;
      
      Link<T> *curr = first->next;
      int i = 0;
      
      while (curr != NULL) {
         i++;
         cout << curr->data << " ";
         curr = curr->next;
         if (i == 10){
            cout << endl;
            i = 0;
         }
      }
      cout << endl;
   }

   void destroyList() {
      while (first != NULL) {
         Link<T> *tmp = first;
         first = first->next;
         delete tmp;
      }
   }

};


#endif /* LINK_H */

