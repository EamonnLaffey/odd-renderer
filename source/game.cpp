#include "game.h"
#include "vec2.h"
#include "renderer.h"

game::game() {
   renderer::make_sheet({"space.png"});
   renderer::make_sheet({"hi.png", "line.png"});
   renderer::make_font_sheet("font.ttf", 30);
   position = {0, 1000};

   as.sequence({&as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(0.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(0.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(0.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out(),
                &as.make<float>(30).value(&alpha).towards(0.0f).cubic_ease_in_out().
                    callback(game::bloop)});

   // auto a = &game::bloop;
   // function<void()> f = bind(&game::bloop, this);
   // as.make<float>()
   // as.make<float>(60).value(&angle).towards(10);
   // as.make(&alpha, 60).towards(1.0f);
   //   as.make<float>(30)
   //      .value(&alpha)
   //      .callback(game::bloop)
   //      .towards(1.0f)
   //      .delay(60)
   //      .start_at(0.0f)
   //      .repeat();
   // as.make<float>(30).value(&alpha).towards(1).callback(game::done_making_invisible);

   // auto fp = &linear;
   // position = {0, 0};
   // as.make<vec2>(200).value(&position).towards({500,
   // 500}).elastic_ease_out().delay(20).callback(game::bloop).repeat(5).start_at({-500, -1000});
   // as.make(&scale, 60).towards(10.0f);
}

game::~game() {}

void game::done_making_invisible() {
   // as.make(&alpha, 60).towards(0.0f);
}

void game::done_making_visible() {
   // as.make(&alpha, 60).towards(0.0f);
}

void game::bloop() {
   // delete a;
   cout << "calling back" << endl;
}

void game::update() {
   as.tick();
   // a->tick();
   const float rotation_speed = 0.03;
   const float angular_friction = 0.7;

   if (left) angular_velocity += rotation_speed;
   if (right) angular_velocity -= rotation_speed;

   angular_velocity *= angular_friction;
   angle += angular_velocity;

   if (angle > M_PI * 2) angle -= M_PI * 2;
   if (angle < 0) angle += M_PI * 2;

   float a = angle + M_PI / 2;

   vec2 wind = {0, 0.1};
   wind -= velocity;
   float dotted = wind.x * cos(a) + wind.y * sin(a);
   // if (boost) dotted *= 2;
   velocity.x += dotted * cos(a);
   velocity.y += dotted * sin(a);
   velocity.y -= 0.1;
   if (boost) {
      position += velocity * 2;
   } else {
      position += velocity;
   }

   renderer::draw("line.png")
      .pos(position)
      .rotation(angle)
      .cam(&position)
      .alpha(alpha)
      .scale(scale);
   renderer::draw("space.png").x(0).y(0).cam(&position);

   vector<string> debug_statements = {"angle " + to_string(angle), "hello", to_string(boost),
                                      "pos " + to_string(position.x) + " " + to_string(position.y)};

   ivec2 cur = {0, renderer::screen.h - 30};
   for (string &s : debug_statements) {
      renderer::draw_text(s, cur, "font.ttf", 30);
      cur.y -= 40;
   }
}

void game::keyboard_update(const Uint8 *keyboard) {
   left = keyboard[SDL_SCANCODE_LEFT] || keyboard[SDL_SCANCODE_Z];
   right = keyboard[SDL_SCANCODE_RIGHT] || keyboard[SDL_SCANCODE_SLASH];
   boost = keyboard[SDL_SCANCODE_SPACE] || keyboard[SDL_SCANCODE_UP];
}