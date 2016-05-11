#pragma once
#include "common.h"
#include "sheet.h"

#include <map>

class renderer {
private:
   static map<string, sheet *> sheets_map;
   static vector<sheet *> sheets_vector;
   static map<pair<string, int>, sheet *> font_sheets_map;
   static vector<sheet *> font_sheets_vector;

public:
   static ivec2 screen;
   static ull frames;

   static void make_sheet(initializer_list<string> filenames);
   static void make_font_sheet(string filename, int font_size);
   static sprite &draw(string filename);
   static void draw_text(string text, vec2 pos, string filename, int font_size);
   static void remove_sheets();

   static void draw_all();
};