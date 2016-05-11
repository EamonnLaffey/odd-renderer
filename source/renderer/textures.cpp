#include "textures.h"
#include <cassert>
#include <memory>

block::block(int x, int y, int w, int h) {
   this->x = x;
   this->y = y;
   this->w = w;
   this->h = h;
   used = false;
   right = nullptr;
   down = nullptr;
}

// PACKER
packer::packer(ivec2 bin_size) {
   root = new block(0, 0, bin_size.w, bin_size.h);
}
void packer::copy_block(block *b) {
   if (b->right) copy_block(b->right);
   if (b->down) copy_block(b->down);
   b = new block(*b);
}
packer::packer(const packer &other) {
   copy_block(other.root);
}
packer &packer::operator=(packer other) {
   swap(root, other.root);
   return *this;
}
packer::~packer() {
   delete_block(root);
}

bool packer::insert(block *b, ivec2 &pos, ivec2 size) {
   if (!b->used && (size.w <= b->w) && (size.h <= b->h)) {
      b->used = true;
      pos.x = b->x;
      pos.y = b->y;
      size += 1; // 1 px padding
      b->right = new block(b->x + size.w, b->y, abs(b->w - size.w), size.h);
      b->down = new block(b->x, b->y + size.h, b->w, abs(b->h - size.h));
      return true;
   } else if (b->used) {
      if (insert(b->right, pos, size)) {
         return true;
      } else if (insert(b->down, pos, size)) {
         return true;
      } else {
      }
   }
   return false;
}
void packer::delete_block(block *b) {
   if (b->right) delete_block(b->right);
   if (b->down) delete_block(b->down);
   if (b) {
      b->right = nullptr;
      b->down = nullptr;
      delete b;
   }
   return;
}

bool packer::fit(ivec2 &pos, ivec2 size) {
   return insert(root, pos, size);
}