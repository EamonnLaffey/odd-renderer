#pragma once
#include "common.h"
#include "sheet.h"
#include "actions.h"

class game {
private:
   vec2 position = vec2(0);
   vec2 velocity = vec2(0);
   float angle = 0;
   float angular_velocity = 0;
   bool left = false;
   bool right = false;
   bool boost = false;
   
   float alpha = 0.0f;
   float scale = 1.0f;
   
   actions as;
   //action *a;

public:
   void bloop();
   void done_making_invisible();
   void done_making_visible();

   game();
   ~game();
   void update();
   void keyboard_update(const Uint8 *keyboard);
};