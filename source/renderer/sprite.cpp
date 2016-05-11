#include "sprite.h"

sprite::sprite(string filename) {
   this->filename = filename;
   is_visible = true;
   opacity = 0.0;
   // camera = pool::get().screen / vec2(2);
}

sprite &sprite::pos(vec2 pos) {
   position = pos;
   return *this;
}
sprite &sprite::x(float x) {
   position.x = x;
   return *this;
}
sprite &sprite::y(float y) {
   position.y = y;
   return *this;
}
sprite &sprite::rotation(float r) {
   angle = r;
   return *this;
}
sprite &sprite::alpha(float a) {
   opacity = a;
   return *this;
}
sprite &sprite::scale(float s) {
   _scale = vec2(s);
   return *this;
}
sprite &sprite::scale(vec2 s) {
   _scale = s;
   size *= _scale;
   return *this;
}
sprite &sprite::scale_x(float sx) {
   _scale.x = sx;
   size *= _scale;
   return *this;
}
sprite &sprite::scale_y(float sy) {
   _scale.y = sy;
   size *= _scale;
   return *this;
}
sprite &sprite::index(int i) {
   const int range = 1000;
   assert(i < range && i > 0);
   z = static_cast<float>(i) / static_cast<float>(range);
   assert(z >= -1.0f && z <= 1.0f);
   return *this;
}
sprite &sprite::cam(vec2 *c) {
   camera = c;
   return *this;
}