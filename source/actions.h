#include "common.h"
#include "action.h"

#include <set>
#include <unordered_map>

#define callback(f) _callback(bind(&f, this))

class actions {
private:
   unordered_map<unsigned long, set<node *>> nodes;
   unordered_map<unsigned long, vector<node *>> to_remove;

public:
   template <typename T> action<T> &make(int time) {
      function<void(action<T> * a)> f = bind(&actions::remove<T>, this, placeholders::_1);
      action<T> *a = new action<T>(time, f);
      a->me = a;
      nodes[typeid(T).hash_code()].insert(a);
      return *a;
   }

   void sequence(initializer_list<node *> nodes) {
      ull last_end_time = renderer::frames;
      for (node *n : nodes) {
         n->start_frame = last_end_time;
         n->end_frame = n->start_frame + n->duration;
         last_end_time = n->end_frame;
      }
   }

   template <typename T> void remove(action<T> *a) {
      to_remove[typeid(T).hash_code()].push_back(a);
   }

   void tick() {
      for (auto &pair : nodes) {
         for (node *n : pair.second) n->tick();
      }
      for (auto &pair : to_remove) {
         for (node *n : pair.second) {
            nodes[pair.first].erase(n);
            delete n;
         }
         pair.second.clear();
      }
   }

   ~actions() {
      for (auto &pair : nodes) {
         for (node *n : pair.second) delete n;
      }
   }
};