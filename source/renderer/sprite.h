#pragma once
#include "common.h"

struct sprite {
public:
   sprite(string filename);
   sprite &pos(vec2 pos);
   sprite &x(float x);
   sprite &y(float y);
   sprite &rotation(float r);
   sprite &alpha(float a);
   sprite &scale(float s);
   sprite &scale(vec2 s);
   sprite &scale_x(float sx);
   sprite &scale_y(float sy);
   sprite &index(int i);
   sprite &bloop(float i);
   sprite &cam(vec2 *c);
   // private:
   vec2 position = vec2(0);
   vec2 size;
   bool is_text = false;
   vec2 *camera = nullptr;
   float z = 0.0f;
   vec2 _scale = vec2(1.0f);
   float angle = 0.0f;
   float opacity = 1.0f;
   bool is_visible = true;
   string filename;
};
