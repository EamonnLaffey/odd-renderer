#pragma once
#include <stdlib.h>
#include <iostream>
#include <random>
#include <cassert>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "transformations.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

// vec2 *screen;
/*const*/ // int sw;
/*const*/ // int sh;

typedef unsigned long long ull;

#if __IPHONEOS__ || __ANDROID__
#define MOBILE 1
#endif

#if __MACOSX__ || __WINDOWS__ || __LINUX__
#define PC 1
#endif

#if TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
inline void glBindVertexArray(GLuint id1) {
   glBindVertexArrayOES(id1);
}
inline void glGenVertexArrays(GLsizei n, GLuint *ids) {
   glGenVertexArraysOES(n, ids);
}
inline void glDeleteVertexArrays(GLsizei n, const GLuint *ids) {
   glDeleteVertexArraysOES(n, ids);
}
#elif TARGET_OS_MAC
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
inline void glBindVertexArray(GLuint id1) {
   glBindVertexArrayAPPLE(id1);
}
inline void glGenVertexArrays(GLsizei n, GLuint *ids) {
   glGenVertexArraysAPPLE(n, ids);
}
inline void glDeleteVertexArrays(GLsizei n, const GLuint *ids) {
   glDeleteVertexArraysAPPLE(n, ids);
}
#endif

inline string get_path(string filename) {
   char *base = SDL_GetBasePath();
   string path(base + filename);
   free(base);
   return path;
}

using namespace std;