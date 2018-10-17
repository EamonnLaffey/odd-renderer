#include "sheet.h"
#include "renderer.h"

#include <dirent.h>
#include <iostream>

vec2 sheet::get_size(string filename) {
   return vertex_data[filename].size;
}
vector<vec2> sheet::get_vertex_coords(string filename) {
   return vertex_data[filename].vertex_coords;
}
vector<vec2> sheet::get_texture_coords(string filename) {
   return vertex_data[filename].texture_coords;
}
vec2 sheet::get_sprite_size(string filename) {
   return vertex_data[filename].size;
}
sheet::sheet(string font_name, int font_size) {
   max_sprites = 7 * 6;
   font = TTF_OpenFont("font.ttf", 30);

   string capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   string lowercase = "abcdefghijklmnopqrstuvwxyz";
   string numbers = "0123456789";
   string misc = " ~!@#$%^&*()_+`-={}|[]:;'<>?,./'";
   string glyphs = lowercase + capital + numbers + misc;

   if (glyphs.size() > 0) {
      for (const auto c : glyphs) {
         string tmp;
         tmp.push_back(c);
         add_glyph(tmp);
      }
   }
   texture = generate_texture();
   init_gl();
}
sheet::sheet(initializer_list<string> img_filenames) {
   max_sprites = 7 * 6;
   font = TTF_OpenFont("futura.ttf", 30);

   for (const auto &filename : img_filenames) {
      //cout << filename << endl;
      //SDL_log("%s", filename.c_str());
      add_image(filename);
   }
   texture = generate_texture();
   init_gl();
}
void sheet::add_glyph(string glyph_name) {
   SDL_Color black;
   black.a = 255;
   black.r = 255;
   black.g = 255;
   black.b = 255;
   SDL_Surface *glyph = TTF_RenderGlyph_Blended(font, glyph_name[0], black);
   assert(glyph != nullptr);
   surface s;
   s.filename = glyph_name;
   s.sdl_surface = glyph;
   surfaces.push_back(s);
   imgs_loaded.insert(glyph_name);
}
void sheet::add_image(string filename) {
   SDL_Surface *img = IMG_Load(filename.c_str());
   assert(img != nullptr);
   surface s;
   s.filename = filename;
   s.sdl_surface = img;
   surfaces.push_back(s);
   imgs_loaded.insert(filename);
}
GLuint sheet::generate_texture() {
   sort(surfaces.begin(), surfaces.end(),
        [](surface a, surface b) { return a.sdl_surface->h > b.sdl_surface->h; });

   vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

   int area = 0;
   for (auto &s : surfaces) {
      SDL_Surface *sdl_surface = s.sdl_surface;
      area += sdl_surface->w * sdl_surface->h;
   }

   bool found_one = false;
   for (int s : sizes) {
      if (area <= (s * s)) {
         found_one = true;
         atlas_size = ivec2(s, s);
         cout << "sprite sheet size found : " << s << endl;
         break;
      }
   }
   if (!found_one) {
      cerr << "we could not find a size" << endl;
      exit(1);
   }
   packer p(atlas_size);
   for (auto &s : surfaces) {
      ivec2 size = vec2(s.sdl_surface->w, s.sdl_surface->h);
      s.pos_in_sheet = vec2(0, 0);
      bool could_fit = p.fit(s.pos_in_sheet, size);
      if (!could_fit) {
         cerr << "we could not fit maybe we should try again?  " << atlas_size << endl;
         exit(1);
      }
   }
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   SDL_Surface *empty = SDL_CreateRGBSurface(0, atlas_size.w, atlas_size.h, 32, 0, 0, 0, 0);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas_size.w, atlas_size.h, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                empty->pixels);
   SDL_FreeSurface(empty);

   for (auto &s : surfaces) {
      ivec2 size = vec2(s.sdl_surface->w, s.sdl_surface->h);
      ivec2 pos = s.pos_in_sheet;
      glTexSubImage2D(GL_TEXTURE_2D, 0, pos.x, pos.y, size.w, size.h, GL_BGRA, GL_UNSIGNED_BYTE,
                      s.sdl_surface->pixels);
      SDL_FreeSurface(s.sdl_surface);
      vertexes v;
      if (size.x % 2) ++size.x;
      if (size.y % 2) ++size.y;
      v.vertex_coords.push_back(vec2(0, 0));
      v.vertex_coords.push_back(vec2(size.x, 0));
      v.vertex_coords.push_back(vec2(0, size.y));
      v.vertex_coords.push_back(vec2(0, size.y));
      v.vertex_coords.push_back(vec2(size.x, 0));
      v.vertex_coords.push_back(vec2(size.x, size.y));
      vec2 u_size = static_cast<vec2>(size) / static_cast<vec2>(atlas_size);
      vec2 u_pos = static_cast<vec2>(pos) / static_cast<vec2>(atlas_size);
      v.texture_coords.push_back(vec2(u_pos.x, u_pos.y + u_size.y));
      v.texture_coords.push_back(vec2(u_pos.x + u_size.x, u_pos.y + u_size.y));
      v.texture_coords.push_back(vec2(u_pos.x, u_pos.y));
      v.texture_coords.push_back(vec2(u_pos.x, u_pos.y));
      v.texture_coords.push_back(vec2(u_pos.x + u_size.x, u_pos.y + u_size.y));
      v.texture_coords.push_back(vec2(u_pos.x + u_size.x, u_pos.y));
      v.size = size;
      vertex_data[s.filename] = v;
   }
   TTF_CloseFont(font);
   return texture;
}

// renderer::renderer(const renderer &other) : atlas(other.atlas) {
//   // todo copy resources
//}
// renderer &renderer::operator=(renderer other) {
//   // todo swap resources
//   return *this;
//}
sheet::~sheet() {
   // todo cleanup opengl stuff
   delete_buffers();
   delete_vao();
   glDeleteTextures(1, &texture);
}

void sheet::delete_buffers() {
   glDeleteBuffers(1, &vert_coords_buffer);
   glDeleteBuffers(1, &tex_coords_buffer);
   glDeleteBuffers(1, &m_buffer);
   glDeleteBuffers(1, &alpha_buffer);
}

void sheet::delete_vao() {
   glDeleteVertexArrays(1, &vao);
}

void sheet::init_gl() {
   glGenBuffers(1, &vert_coords_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, vert_coords_buffer);
   glBufferData(GL_ARRAY_BUFFER, max_sprites * sizeof(vec2), nullptr, GL_STREAM_DRAW);

   glGenBuffers(1, &tex_coords_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer);
   glBufferData(GL_ARRAY_BUFFER, max_sprites * sizeof(vec2), nullptr, GL_STREAM_DRAW);

   glGenBuffers(1, &m_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
   glBufferData(GL_ARRAY_BUFFER, max_sprites * sizeof(mat4), nullptr, GL_STREAM_DRAW);

   glGenBuffers(1, &alpha_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, alpha_buffer);
   glBufferData(GL_ARRAY_BUFFER, max_sprites * sizeof(float), nullptr, GL_STREAM_DRAW);

   program = shaders::get_program("sprite");
   GLint vert_coords = glGetAttribLocation(program, "vert_coords");
   GLint tex_coords = glGetAttribLocation(program, "tex_coords");
   GLint m = glGetAttribLocation(program, "m");
   GLint alpha = glGetAttribLocation(program, "alpha");
   GLint pv = glGetUniformLocation(program, "pv");
   glUseProgram(program);

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vert_coords_buffer);
   glEnableVertexAttribArray(vert_coords);
   glVertexAttribPointer(vert_coords, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

   glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer);
   glEnableVertexAttribArray(tex_coords);
   glVertexAttribPointer(tex_coords, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

   glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
   for (int i = 0; i < 4; i++) {
      glEnableVertexAttribArray(m + i);
      glVertexAttribPointer(m + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(sizeof(vec4) * i));
   }

   glBindBuffer(GL_ARRAY_BUFFER, alpha_buffer);
   glEnableVertexAttribArray(alpha);
   glVertexAttribPointer(alpha, 1, GL_FLOAT, GL_FALSE, 0, nullptr);

   glBindVertexArray(0);

   mat4 projection = ortho(0.0f, (float)renderer::screen.w, 0.0f, (float)renderer::screen.h);
   mat4 view = translate(mat4(), vec3(0, 0, 0));
   glUniformMatrix4fv(pv, 1, GL_FALSE, &(projection * view)[0].x);
}

void sheet::draw_text(string text, vec2 pos) {
   // TODO: proper glyph sizing and kerning
   vec2 size = get_sprite_size("o");
   vec2 prev_pos = pos;
   Uint16 prev_char = 'a';
   for (auto &c : text) {
      string tmp;
      tmp.push_back(c);
      sprites.push_back(sprite(tmp));
      sprite *s = &sprites.back();
      s->is_text = true;
      //TTF_SetFontKerning(font, true);
      //cout << TTF_GetFontKerningSize(font, 'a', 'b') << endl;
      //printf("TTF_Init: %s\n", TTF_GetError());

      //cout << TTF_GetFontKerningSize(font, prev_char, c) << endl;
      prev_char = c;
      s->position.x = prev_pos.x + size.w;
      s->position.y = prev_pos.y;
      s->size = size;
      prev_pos = s->position;
   }
}

sprite &sheet::make_image(string filename) {
   sprites.push_back(sprite(filename));
   sprite *s = &sprites.back();
   s->size = get_size(filename);
   return *s;
}

void sheet::draw() {
   vector<vec2> vert_coords_data;
   vector<vec2> tex_coords_data;
   vector<mat4> m_data;
   vector<float> alpha_data;

   if (sprites.size() * 6 > max_sprites) {
      max_sprites = (int)sprites.size() * 6 * 2;
      delete_buffers();
      delete_vao();
      init_gl();
   }

   stable_sort(sprites.begin(), sprites.end(),
               [](const sprite &a, const sprite &b) -> bool { return a.z < b.z; });

   for (auto &s : sprites) {
      // if (!image_loaded(s.filename)) {
      //   cerr << "CANNOT LOAD IMAGE: " << s.filename << endl;
      //   exit(1);
      //}
      if (!s.is_visible) continue;

      vec2 cam = 0;
      if (s.camera) cam = *s.camera - renderer::screen / 2;
      vec2 anchor = s.size / 2;
      vec2 relative_pos = s.position - anchor -  cam;

      //if ((relative_pos.x - s.size.w) > renderer::screen.w) continue;
      //if ((relative_pos.x + s.size.w) < 0) continue;
      //if ((relative_pos.y - s.size.h) > renderer::screen.h) continue;
      //if ((relative_pos.y + s.size.h) < 0) continue;

      vertexes vertex = vertex_data[s.filename];
      s.size = vertex.size;

      vector<vec2> vs = vertex.vertex_coords;
      vector<vec2> ts = vertex.texture_coords;
      vert_coords_data.insert(vert_coords_data.end(), vs.begin(), vs.end());
      tex_coords_data.insert(tex_coords_data.end(), ts.begin(), ts.end());

      // TRANSORMATIONS
      mat4 model = mat4();
      // MOVE
      model = translate(model, vec3(relative_pos));
      // SCALE
      model = scale(model, vec3(s._scale.x, s._scale.y, 1.0f));
      // ROTATE
      model = translate(model, vec3(anchor));
      model = rotate(model, s.angle, vec3(0, 0, 1));
      model = translate(model, -vec3(anchor));

      for (int i = 0; i < 6; i++) {
         m_data.push_back(model);
         alpha_data.push_back(s.opacity);
         // index_data.push_back(s.z);
      }
   }

   glBindBuffer(GL_ARRAY_BUFFER, vert_coords_buffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, vert_coords_data.size() * sizeof(vec2),
                   &vert_coords_data[0]);
   glBindBuffer(GL_ARRAY_BUFFER, tex_coords_buffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, tex_coords_data.size() * sizeof(vec2), &tex_coords_data[0]);
   glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, m_data.size() * sizeof(mat4), &m_data[0]);
   glBindBuffer(GL_ARRAY_BUFFER, alpha_buffer);
   glBufferSubData(GL_ARRAY_BUFFER, 0, alpha_data.size() * sizeof(float), &alpha_data[0]);

   glUseProgram(program);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture);
   glBindVertexArray(vao);
   glDrawArrays(GL_TRIANGLES, 0, (GLint)m_data.size());
   glBindVertexArray(0);

   sprites.clear();
}