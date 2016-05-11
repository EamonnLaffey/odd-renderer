#pragma once
#include "common.h"
#include "textures.h"
#include "shaders.h"
#include "sprite.h"

struct surface {
   string filename;
   SDL_Surface *sdl_surface;
   ivec2 pos_in_sheet;
};

struct vertexes {
   vec2 size;
   vector<vec2> vertex_coords;
   vector<vec2> texture_coords;
};

class sheet {
private:
   GLuint vao;
   GLuint program;
   GLuint texture;
   GLuint vert_coords_buffer;
   GLuint tex_coords_buffer;
   GLuint m_buffer;
   GLuint alpha_buffer;
   // GLuint index_buffer;
   int max_sprites;
   vector<sprite> sprites;
   vector<string> load_filenames();

   void delete_buffers();
   void delete_vao();

   // texture stuff
   void add_glyph(string glyph_name);
   void add_image(string filename);
   GLuint generate_texture();

   ivec2 atlas_size;
   vector<surface> surfaces;
   set<string> imgs_loaded;
   vector<vec2> get_vertex_coords(string filename);
   vector<vec2> get_texture_coords(string filename);
   vec2 get_sprite_size(string filename);
   unordered_map<string, vertexes> vertex_data;
   TTF_Font *font;

public:
   sheet(initializer_list<string> img_filename);
   sheet(string font_name, int font_size);
   // sheet(const renderer &other);
   // sheet &operator=(renderer other);
   ~sheet();

   vec2 get_size(string filename);
   void init_gl();
   sprite &make_image(string filename);
   void draw_image(string filename, vec2 pos, float rotation);
   void draw_text(string text, vec2 pos);
   void draw();
};