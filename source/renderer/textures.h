#pragma once
#include "common.h"
#include "vec2.h"

#include <unordered_map>
#include <set>

struct block {
   block(int x, int y, int w, int h);
   int x, y, w, h;
   // blocks are managed by packer
   block *right;
   block *down;
   bool used;
};

class packer {
private:
   block *root;
   bool insert(block *b, ivec2 &pos, ivec2 size);
   void copy_block(block *b);
   void delete_block(block *b);

public:
   packer(ivec2 bin_size);
   packer(const packer &other);
   packer &operator=(packer other);
   ~packer();

   bool fit(ivec2 &pos, ivec2 size);
};