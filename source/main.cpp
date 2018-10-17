#include "common.h"
#include "game.h"
#include "renderer.h"

// touch touchFromtfinger(SDL_TouchFingerEvent tfinger) {
//   touch t;
//   t.pos = vec2(tfinger.x * pool::get().screen.w, (1 - tfinger.y) * pool::get().screen.h);
//   t.moved = vec2(tfinger.dx * pool::get().screen.w, (1 - tfinger.dy) * pool::get().screen.h);
//   t.time = tfinger.timestamp;
//   return t;
//}

int main(int argc, char *argv[]) {
   // seed();

   SDL_Init(SDL_INIT_EVERYTHING);
   IMG_Init(IMG_INIT_PNG);
   TTF_Init();

   SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   SDL_SetHint("SDL_HINT_ORIENTATIONS", "LandscapeRight");
   SDL_DisplayMode mode;
   SDL_GetDisplayMode(0, 0, &mode);

// int sw, sh;
#if MOBILE
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   renderer::screen = {mode.w, mode.h};
   SDL_Window *window =
      SDL_CreateWindow(NULL, 0, 0, renderer::screen.w, renderer::screen.h,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
   SDL_Joystick *accelerometer = SDL_JoystickOpen(0);
#elif PC
   renderer::screen = {1920, 1080};
   SDL_Window *window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, renderer::screen.w / 2,
                       renderer::screen.h / 2, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
#endif
   cout << "screen size: " << renderer::screen << endl;

   SDL_GLContext context = SDL_GL_CreateContext(window);
   if (!context) cout << "Couldn't create context: " << SDL_GetError() << endl;

   SDL_GL_SetSwapInterval(1);
   SDL_Event event;
   // SDL_GL_GetDrawableSize(window, &sw, &sh);
   //   cout << "DRAWABLE SIZE: width: " << pool::get().screen.w << "   height: " <<
   //   pool::get().screen.h
   //        << endl;

   glClearColor(1.0, 0.0, 1.0, 1.0);
   // glEnable(GL_CULL_FACE);
   glEnable(GL_BLEND);
   // glEnable(GL_DEPTH_TEST);
   // glEnable(GL_ALPHA_TEST);
   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glViewport(0, 0, renderer::screen.w, renderer::screen.h);

   game g;

#if PC
   const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
#endif

   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   while (true) {

      while (SDL_PollEvent(&event)) {
#if MOBILE
         if (event.type == SDL_FINGERDOWN) {
            //            w->touch_down(touchFromtfinger(event.tfinger));
         }
         if (event.type == SDL_FINGERUP) {
            //            w->touch_up(touchFromtfinger(event.tfinger));
         }
         if (event.type == SDL_FINGERMOTION) {
            //            w->touch_moved(touchFromtfinger(event.tfinger));
         }
#endif
         if (event.type == SDL_QUIT) goto quit;
      }

#if MOBILE
      SDL_TouchID tId = SDL_GetTouchDevice(0);
      int numTouches = SDL_GetNumTouchFingers(tId);
      //      w->touches.clear();
      for (int i = 0; i < numTouches; i++) {
         //         SDL_Finger *finger = SDL_GetTouchFinger(tId, i);
         //         touch t;
         //         t.pos = vec2(finger->x * sw, (1 - finger->y) * sh);
         //         w->touches.push_back(t);
      }
      float ax = SDL_JoystickGetAxis(accelerometer, 0);
      float ay = SDL_JoystickGetAxis(accelerometer, 1);
      float az = SDL_JoystickGetAxis(accelerometer, 2);
      float k = 0x7FFF;
      ax *= SDL_IPHONE_MAX_GFORCE / k;
      ay *= SDL_IPHONE_MAX_GFORCE / k;
      az *= SDL_IPHONE_MAX_GFORCE / k;
//      w->accel_update(vec3(ax, ay, az));
#endif
      SDL_PumpEvents();

#if PC
      g.keyboard_update(keyboard);
      //g.keyboard_update(w->keys);
#endif
      g.update();
      renderer::draw_all();

      SDL_GL_SwapWindow(window);
      glClear(GL_COLOR_BUFFER_BIT);
   }

quit:
   SDL_Quit();
   IMG_Quit();
   TTF_Quit();
   return 0;
}