#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

inline int nodeCounter;

template <typename T>
class Node {
private:
   int height;
public:
   T data;
   Node *left;
   Node *right;

   Node(T t) {
      data = t;
      height = 1;
      left = NULL;
      right = NULL;
   }

   int getHeight(Node<T> *n) {
      if (n == NULL) {
         return 0;
      }
      return n->height;
   }

   void setHeight(int h) {
      height = h;
   }

   int getBalance(Node *n) {
      if (n == NULL)
         return 0;
      return getHeight(n->left) - getHeight(n->right);
   }
};

template <typename T>
class AVLTree {
private:
   Node<T> *root = NULL;

   Node<T> *insert(Node<T> *n, T t) {
      //Basic tree insert
      if (n == NULL) {
         return new Node(t);
      } else if (t < n->data) {
         n->left = insert(n->left, t);
      } else if (t > n->data) {
         n->right = insert(n->right, t);
      } else {
         //Return and skip balancing if this key already exists
         return n;
      }

      //Update heights and check the balance after insert recursion is done
      n->setHeight(1 + max(n->getHeight(n->right), n->getHeight(n->left)));

      int balance = n->getBalance(n);

      //Left Left
      if (balance > 1 && t < n->left->data) {
         return rRotate(n);
      }

      //Right Right
      if (balance < -1 && t > n->right->data) {
         return lRotate(n);
      }

      //Left Right
      if (balance > 1 && t > n->left->data) {
         n->left = lRotate(n->left);
         return rRotate(n);
      }

      //Right Left
      if (balance < -1 && t < n->right->data) {
         n->right = rRotate(n->right);
         return lRotate(n);
      }

      //No balance needed
      return n;
   }

   Node<T> *deleteNode(Node<T> *n, T t) {
      //Find value
      //Base Case
      if (n == NULL) {
         return n;
      }
      //Less than current node
      if (t < n->data) {
         n->left = deleteNode(n->left, t);
      }//greater than current node
      else if (t > n->data) {
         n->right = deleteNode(n->right, t);
      }
      //Once value is found, modify children nodes, then delete the node
      else {
         //Node has no children
         if (n->left == NULL && n->right == NULL)return NULL;
         //Node with right child
         else if(n->left == NULL){
            Node<T> * temp = n->right;
            free(n);
            return temp;
         } //Node with right child
         else if(n->right == NULL){
            Node<T> *temp = n->left;
            free(n);
            return temp;
         }
         //Node with 2 children nodes
         Node<T> * temp = minChildVal(n->right);
         //Set node to new lowest
         n->data = temp->data;
         //Restart recursive delete at next highest node
         n->right = deleteNode(n->right,temp->data);
      }
      //If no children nodes, you are done
      if (n == NULL){return n;}
      
      //Update height and balance for new node
      n->setHeight(1 + max(n->getHeight(n->right), n->getHeight(n->left)));
      int balance = n->getBalance(n);
      
      //Check balance factor and balance if needed
      
      //Left Left
      if (balance > 1 && n->getBalance(n->left) >= 0){return rRotate(n);}
      //Right Right
      if (balance < -1 && n->getBalance(n->right) <= 0){return lRotate(n);}
      //Left Right
      if (balance > 1 && n->getBalance(n->left) < 0){
         n->left = lRotate(n->left);
         return rRotate(n);
      }
      //Right Left
      if (balance < -1 && n->getBalance(n->right) > 0){
         n->right = rRotate(n->right);
         return lRotate(n);
      }
      return n;
   }

   Node<T> *minChildVal(Node<T> *n){
      Node<T> *min = n;
      
      while(min && min->left != NULL){min = min->left;}
      
      return min;
   }

   //a, b, and c as in :
   //       a
   //      /
   //    b
   //  /
   //c

   Node<T> *rRotate(Node<T> *a) {
      Node<T> *b = a->left;
      a->left = b->right;
      b->right = a;

      //readjust heights
      a->setHeight(1 + max(a->getHeight(a->right), a->getHeight(a->left)));
      b->setHeight(1 + max(b->getHeight(b->right), b->getHeight(b->left)));

      return b;
   }

   //a, b, and c as in :
   // a
   //  \
   //    b
   //     \
   //      c

   Node<T> *lRotate(Node<T> *a) {
      Node<T> *b = a->right;
      a->right = b->left;
      b->left = a;

      //readjust heights
      a->setHeight(1 + max(a->getHeight(a->right), a->getHeight(a->left)));
      b->setHeight(1 + max(b->getHeight(b->right), b->getHeight(b->left)));

      return b;
   }
   //Print Left Right
   void preOrder(Node<T> *n) {
      if (n == NULL) return;
      cout << n->data << " ";
      preOrder(n->left);
      preOrder(n->right);
   }

   //Left Print Right
   void inOrder(Node<T> *n) {
      if (n == NULL) return;
      inOrder(n->left);
      cout << n->data << " ";
      inOrder(n->right);
   }
   
   //Print down each level left to right, h increased each time in order to travel deeper
   void levelOrder(Node<T> *n, int h){
      if (n == NULL)return;
      if (h == 1){
         cout << n->data << " ";
      }
      else if (h > 1){
         levelOrder(n->left, h-1);
         levelOrder(n->right, h-1);
      }
   }
   
   //Left Right Print
   void postOrder(Node<T> *n){
      if (n == NULL) {return;}
      postOrder(n->left);
      postOrder(n->right);
      cout << n->data << " ";
   }

   void display(Node<T> *n, int level) {
      int i;
      if (n != NULL) {
         display(n->right, level + 1);
         cout << endl;
         if (n == root)
            cout << "R -> ";
         for (i = 0; i < level && n != root; i++)
            cout << "     ";
         cout << n->data;
         display(n->left, level + 1);
      }
   }
   
   Node<T> *findNode(Node<T> *n, T t){
      if (n == NULL) {
         return n;
      }
      nodeCounter++;
      //Less than current node
      if (t < n->data) {
         n->left = findNode(n->left, t);
      }//greater than current node
      else if (t > n->data) {
         n->right = findNode(n->right, t);
      }
      //Once value is found, modify children nodes, then delete the node
      else {
         T x = n->data;
         n->right = findNode(n->right,x);
      }
      return n;
   }

public:

   void insert(T t) {
      root = insert(root, t);
   }

   void deleteNode(T t) {
      root = deleteNode(root, t);
   }

   void preOrder() {
      preOrder(root);
      cout << endl;
   }

   void inOrder() {
      inOrder(root);
      cout << endl;
   }

   void postOrder(){
      postOrder(root);
      cout << endl;
   }

   void levelOrder(){
      int h = root->getHeight(root);
      for (int i = 1; i <= h; i++) levelOrder(root,i);
      cout << endl;
   }

   void display() {
      display(root, 1);
   }
   
   void findNode(T t){
      root = findNode(root,t);
   }
};
#endif /* AVLTREE_H */

