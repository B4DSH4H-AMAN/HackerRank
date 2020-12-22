#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;
/*
 *
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; 
   int cp; 
   Node* tail; 
   Node* head; 
   virtual void set(int, int) = 0;
   virtual int get(int) = 0; 

};
class LRUCache : public Cache {
public:
    LRUCache(size_t capacity)
    {
        cp = capacity;
        tail = 0;
        head = 0;
    }
    
    ~LRUCache() {
        while(tail) {
            auto node = tail;
            tail = tail->prev;
            delete node;
        }
    }

    void set(int key, int value) {
        Node* node;
        auto it = mp.find(key);
        if(mp.end() == it) {
            if(mp.size() < cp) {
                node = new Node(key, value);
                if(tail) {
                    tail->next = node;
                    node->prev = tail;
                } else {
                    tail = node;
                    head = node;
                }
            } else {
                node = tail;
                mp.erase(tail->value);
            }
            mp.insert(make_pair(key, node));
        } else {
            node = it->second;
        }
        node->key = key;
        node->value = value;
        set_mru(node);
    }

    int get(int key) {
        auto it = mp.find(key);
        if(mp.end() == it)
            return -1;

        auto node = it->second;
        set_mru(node);
        return node->value;
    }

private:
    void set_mru(Node* node) {
        if(node->next) {
            node->next->prev = node->prev;
        }
        if(node->prev) {
            node->prev->next = node->next;
        }
        if(tail == node)
            tail = node->prev;
        node->prev = 0;
        node->next = head;
        head = node;
    }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
