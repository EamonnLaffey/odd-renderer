# odd-renderer

Uses SDL2: https://www.libsdl.org/

Immidiate style renderer. Also included is an action system.

# Setup before drawing
Before you draw to the screen you dynamically specify image assets that are to be included in a single spritesheet. For example:

```c++
renderer::make_sheet({"hi.png", "line.png"});
```

# To draw an image
When you draw an image is is drawn until the screen is cleared during the next frame. For this reason you need to renderer::draw() every frame. Note when specifying the image file, just use the filename, the renderer automatically will handle the processing to do with the spritesheet. For example:

```c++
renderer::draw("line.png")
      .pos(vec2(50, 50))
      .rotation(M_PI)
      .cam(&position) // you can specify the camera position if you want
      .alpha(0.5f)
      .scale(1.0f);
```

# Action system
Also included is an easy way to queue animations. Create actions as; and use it to pass through values that can be changed based on a function such as quadratic_ease_in() or linear()

```c++
as.sequence({&as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out(),
             &as.make<float>(30).value(&alpha).towards(0.0f).cubic_ease_in_out(),
             &as.make<float>(30).value(&alpha).towards(1.0f).cubic_ease_in_out().callback(game::action_done)});
// ...
void game::action_done() {
   cout << "calling back" << endl;
}


```
