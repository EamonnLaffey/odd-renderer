#include "shaders.h"
#include <fstream>
#include <sstream>
#include <string>

map<string, GLuint> shaders::programs;

GLuint shaders::load_shader(string filename) {
   size_t last = filename.find_last_of(".");
   string ext = filename.substr(last);
   GLenum shader_type;
   if (ext == ".vsh") {
      shader_type = GL_VERTEX_SHADER;
   } else if (ext == ".fsh") {
      shader_type = GL_FRAGMENT_SHADER;
   } else {
      cerr << "UNKOWN EXTENSION: " << ext << endl;
      exit(1);
   }

   ifstream in_file(get_path(filename));
   if (!in_file.good()) {
      cerr << "Could not read file: " << filename << endl;
      exit(1);
   }
   stringstream stream;
   stream << in_file.rdbuf();
   string str = "";
#if MOBILE
   str = "precision highp float;\n";
#endif
   str += stream.str();
   const char *c_str = str.c_str();

   GLuint shader = glCreateShader(shader_type);
   glShaderSource(shader, 1, &c_str, nullptr);
   glCompileShader(shader);

   GLint compile_success;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);
   if (compile_success == GL_FALSE) {
      GLint length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      string log(length, ' ');
      glGetShaderInfoLog(shader, length, &length, &log[0]);
      cerr << "SHADER ERROR IN " << filename << ":   " << log << endl;
      exit(1);
   }
   return shader;
}

void shaders::load(string shader_name) {
   GLuint vertex_shader = load_shader(shader_name + ".vsh");
   GLuint fragment_shader = load_shader(shader_name + ".fsh");
   programs[shader_name] = glCreateProgram();
   glAttachShader(programs[shader_name], vertex_shader);
   glAttachShader(programs[shader_name], fragment_shader);
   glLinkProgram(programs[shader_name]);
}

GLuint shaders::get_program(string shader_name) {
   if (programs.find(shader_name) == programs.end()) load(shader_name);
   return programs[shader_name];
}