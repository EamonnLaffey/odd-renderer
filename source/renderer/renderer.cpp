#include "renderer.h"

map<string, sheet *> renderer::sheets_map;
vector<sheet *> renderer::sheets_vector;
map<pair<string, int>, sheet *> renderer::font_sheets_map;
vector<sheet *> renderer::font_sheets_vector;
ivec2 renderer::screen;
ull renderer::frames = 0;

void renderer::make_sheet(initializer_list<string> filenames) {
   sheet *s = new sheet(filenames);
   sheets_vector.push_back(s);
   for (auto &f : filenames) sheets_map[f] = s;
}

void renderer::make_font_sheet(string filename, int font_size) {
   sheet *s = new sheet(filename, font_size);
   font_sheets_vector.push_back(s);
   font_sheets_map[make_pair(filename, font_size)] = s;
}

void renderer::remove_sheets() {
   for (sheet *s : sheets_vector) delete s;
   for (sheet *s : font_sheets_vector) delete s;
   sheets_vector.clear();
   sheets_map.clear();
   font_sheets_vector.clear();
   font_sheets_map.clear();
}

sprite &renderer::draw(string filename) {
   return sheets_map[filename]->make_image(filename);
}

void renderer::draw_text(string text, vec2 pos, string filename, int font_size) {
   font_sheets_map[make_pair(filename, font_size)]->draw_text(text, pos);
}

void renderer::draw_all() {
   ++frames;
   for (sheet *s : sheets_vector) s->draw();
   for (sheet *s : font_sheets_vector) s->draw();
}