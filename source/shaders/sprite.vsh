attribute vec2 vert_coords;
attribute vec2 tex_coords;
attribute mat4 m;
attribute float alpha;
//attribute float index;
uniform mat4 pv;
varying vec2 texture_varying;
varying float alpha_varying;

void main() {
   gl_Position = pv * m * vec4(vert_coords, 0.0, 1.0);
   texture_varying = tex_coords;
   alpha_varying = alpha;
}