#pragma once
#include "common.h"
#include <map>
#include <string>

class shaders {
private:
   static map<string, GLuint> programs;
   static GLuint load_shader(string filename);

public:
   static void load(string shader_name);
   static GLuint get_program(string shader_name);
};