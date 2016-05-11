#include "common.h"
#include "renderer.h"
#include "easing_functions.h"

#include <functional>

class node {
public:
   ull start_frame;
   ull end_frame;
   int duration;

   virtual void tick() = 0;
   virtual ~node() {}
};

template <typename T> class action : public node {
private:
   function<void()> normal_callback = nullptr;
   function<void(action *a)> remove_callback = nullptr;

   T *v = nullptr;
   T beginning;
   T destination;

   bool loop_forever = false;
   bool loop = false;
   int loops_left;

   enum ease_function {
      LINEAR,
      QUADRATIC_EASE_IN,
      QUADRATIC_EASE_OUT,
      QUADRATIC_EASE_IN_OUT,
      CUBIC_EASE_IN,
      CUBIC_EASE_OUT,
      CUBIC_EASE_IN_OUT,
      QUARTIC_EASE_IN,
      QUARTIC_EASE_OUT,
      QUARTIC_EASE_IN_OUT,
      QUINTIC_EASE_IN,
      QUINTIC_EASE_OUT,
      QUINTIC_EASE_IN_OUT,
      SINE_EASE_IN,
      SINE_EASE_OUT,
      SINE_EASE_IN_OUT,
      CIRCULAR_EASE_IN,
      CIRCULAR_EASE_OUT,
      CIRCULAR_EASE_IN_OUT,
      EXPONENTIAL_EASE_IN,
      EXPONENTIAL_EASE_OUT,
      EXPONENTIAL_EASE_IN_OUT,
      ELASTIC_EASE_IN,
      ELASTIC_EASE_OUT,
      ELASTIC_EASE_IN_OUT,
      BACK_EASE_IN,
      BACK_EASE_OUT,
      BACK_EASE_IN_OUT,
      BOUNCE_EASE_IN,
      BOUNCE_EASE_OUT,
      BOUNCE_EASE_IN_OUT
   } function_to_use = LINEAR;

public:
   action(int time, function<void(action *a)> cb) {
      duration = time;
      start_frame = renderer::frames;
      end_frame = start_frame + duration;
      remove_callback = cb;
   }

   ~action() override {}

   void tick() override {
      if (renderer::frames >= start_frame) {
         if (v != nullptr) {
            double percent_done = (double)(renderer::frames - start_frame) / (double)duration;
            float ease;
            if (function_to_use == LINEAR) {
               ease = easing::linear(percent_done);
            } else if (function_to_use == QUADRATIC_EASE_IN) {
               ease = easing::quadratic_ease_in(percent_done);
            } else if (function_to_use == QUADRATIC_EASE_OUT) {
               ease = easing::quadratic_ease_out(percent_done);
            } else if (function_to_use == QUADRATIC_EASE_IN_OUT) {
               ease = easing::quadratic_ease_in_out(percent_done);
            } else if (function_to_use == CUBIC_EASE_IN) {
               ease = easing::cubic_ease_in(percent_done);
            } else if (function_to_use == CUBIC_EASE_OUT) {
               ease = easing::cubic_ease_out(percent_done);
            } else if (function_to_use == CUBIC_EASE_IN_OUT) {
               ease = easing::cubic_ease_in_out(percent_done);
            } else if (function_to_use == QUARTIC_EASE_IN) {
               ease = easing::quartic_ease_in(percent_done);
            } else if (function_to_use == QUARTIC_EASE_OUT) {
               ease = easing::quartic_ease_out(percent_done);
            } else if (function_to_use == QUARTIC_EASE_IN_OUT) {
               ease = easing::quartic_ease_in_out(percent_done);
            } else if (function_to_use == QUINTIC_EASE_IN) {
               ease = easing::quintic_ease_in(percent_done);
            } else if (function_to_use == QUINTIC_EASE_OUT) {
               ease = easing::quintic_ease_out(percent_done);
            } else if (function_to_use == QUINTIC_EASE_IN_OUT) {
               ease = easing::quintic_ease_in_out(percent_done);
            } else if (function_to_use == SINE_EASE_IN) {
               ease = easing::sine_ease_in(percent_done);
            } else if (function_to_use == SINE_EASE_OUT) {
               ease = easing::sine_ease_out(percent_done);
            } else if (function_to_use == SINE_EASE_IN_OUT) {
               ease = easing::sine_ease_in_out(percent_done);
            } else if (function_to_use == CIRCULAR_EASE_IN) {
               ease = easing::circular_ease_in(percent_done);
            } else if (function_to_use == CIRCULAR_EASE_OUT) {
               ease = easing::circular_ease_out(percent_done);
            } else if (function_to_use == CIRCULAR_EASE_IN_OUT) {
               ease = easing::circular_ease_in_out(percent_done);
            } else if (function_to_use == EXPONENTIAL_EASE_IN) {
               ease = easing::exponential_ease_in(percent_done);
            } else if (function_to_use == EXPONENTIAL_EASE_OUT) {
               ease = easing::exponential_ease_out(percent_done);
            } else if (function_to_use == EXPONENTIAL_EASE_IN_OUT) {
               ease = easing::exponential_ease_in_out(percent_done);
            } else if (function_to_use == ELASTIC_EASE_IN) {
               ease = easing::elastic_ease_in(percent_done);
            } else if (function_to_use == ELASTIC_EASE_OUT) {
               ease = easing::elastic_ease_out(percent_done);
            } else if (function_to_use == ELASTIC_EASE_IN_OUT) {
               ease = easing::elastic_ease_in_out(percent_done);
            } else if (function_to_use == BACK_EASE_IN) {
               ease = easing::back_ease_in(percent_done);
            } else if (function_to_use == BACK_EASE_OUT) {
               ease = easing::back_ease_out(percent_done);
            } else if (function_to_use == BACK_EASE_IN_OUT) {
               ease = easing::back_ease_in_out(percent_done);
            } else if (function_to_use == BOUNCE_EASE_IN) {
               ease = easing::bounce_ease_in(percent_done);
            } else if (function_to_use == BOUNCE_EASE_OUT) {
               ease = easing::bounce_ease_out(percent_done);
            } else if (function_to_use == BOUNCE_EASE_IN_OUT) {
               ease = easing::bounce_ease_in_out(percent_done);
            }
            *v = (ease * destination) + ((1.0f - ease) * beginning);
         }
      }
      if (renderer::frames >= end_frame) {
         if (normal_callback != nullptr) normal_callback();
         if (loop) {
            --loops_left;
         }
         if (loops_left <= 0) loop = false;
         if (loop_forever || loop) {
            start_frame = renderer::frames + 1;
            end_frame = start_frame + duration;
         } else {
            remove_callback(me);
         }
      }
   }

   action &value(T *val) {
      v = val;
      beginning = *v;
      return *this;
   }
   action &towards(T to) {
      destination = to;
      return *this;
   }
   action &start_at(T start) {
      beginning = start;
      return *this;
   }
   action &_callback(function<void()> cb) {
      normal_callback = cb;
      return *this;
   }
   action &delay(int time) {
      start_frame += time;
      end_frame = start_frame + duration;
      return *this;
   }
   action &repeat() {
      loop_forever = true;
      return *this;
   }
   action &repeat(int number_of_times) {
      loop = true;
      loops_left = number_of_times;
      return *this;
   }
   action &linear() {
      function_to_use = LINEAR;
      return *this;
   }
   action &quadratic_ease_in() {
      function_to_use = QUADRATIC_EASE_IN;
      return *this;
   }
   action &quadratic_ease_out() {
      function_to_use = QUADRATIC_EASE_OUT;
      return *this;
   }
   action &quadratic_ease_in_out() {
      function_to_use = QUADRATIC_EASE_IN_OUT;
      return *this;
   }
   action &cubic_ease_in() {
      function_to_use = CUBIC_EASE_IN;
      return *this;
   }
   action &cubic_ease_out() {
      function_to_use = CUBIC_EASE_OUT;
      return *this;
   }
   action &cubic_ease_in_out() {
      function_to_use = CUBIC_EASE_IN_OUT;
      return *this;
   }
   action &quartic_ease_in() {
      function_to_use = QUARTIC_EASE_IN;
      return *this;
   }
   action &quartic_ease_out() {
      function_to_use = QUARTIC_EASE_OUT;
      return *this;
   }
   action &quartic_ease_in_out() {
      function_to_use = QUARTIC_EASE_IN_OUT;
      return *this;
   }
   action &quintic_ease_in() {
      function_to_use = QUINTIC_EASE_IN;
      return *this;
   }
   action &quintic_ease_out() {
      function_to_use = QUINTIC_EASE_OUT;
      return *this;
   }
   action &quintic_ease_in_out() {
      function_to_use = QUINTIC_EASE_IN_OUT;
      return *this;
   }
   action &sine_ease_in() {
      function_to_use = SINE_EASE_IN;
      return *this;
   }
   action &sine_ease_out() {
      function_to_use = SINE_EASE_OUT;
      return *this;
   }
   action &sine_ease_in_out() {
      function_to_use = SINE_EASE_IN_OUT;
      return *this;
   }
   action &circular_ease_in() {
      function_to_use = CIRCULAR_EASE_IN;
      return *this;
   }
   action &circular_ease_out() {
      function_to_use = CIRCULAR_EASE_OUT;
      return *this;
   }
   action &circular_ease_in_out() {
      function_to_use = CIRCULAR_EASE_IN_OUT;
      return *this;
   }
   action &exponential_ease_in() {
      function_to_use = EXPONENTIAL_EASE_IN;
      return *this;
   }
   action &exponential_ease_out() {
      function_to_use = EXPONENTIAL_EASE_OUT;
      return *this;
   }
   action &exponential_ease_in_out() {
      function_to_use = EXPONENTIAL_EASE_IN_OUT;
      return *this;
   }
   action &elastic_ease_in() {
      function_to_use = ELASTIC_EASE_IN;
      return *this;
   }
   action &elastic_ease_out() {
      function_to_use = ELASTIC_EASE_OUT;
      return *this;
   }
   action &elastic_ease_in_out() {
      function_to_use = ELASTIC_EASE_IN_OUT;
      return *this;
   }
   action &back_ease_in() {
      function_to_use = BACK_EASE_IN;
      return *this;
   }
   action &back_ease_out() {
      function_to_use = BACK_EASE_OUT;
      return *this;
   }
   action &back_ease_in_out() {
      function_to_use = BACK_EASE_IN_OUT;
      return *this;
   }
   action &bounce_ease_in() {
      function_to_use = BOUNCE_EASE_IN;
      return *this;
   }
   action &bounce_ease_out() {
      function_to_use = BOUNCE_EASE_OUT;
      return *this;
   }
   action &bounce_ease_in_out() {
      function_to_use = BOUNCE_EASE_IN_OUT;
      return *this;
   }

   action *me;
};