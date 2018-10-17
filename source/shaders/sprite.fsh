varying vec2 texture_varying;
varying float alpha_varying;
uniform sampler2D texture;

void main() {
   vec4 tex = texture2D(texture, texture_varying);
   tex.a -= alpha_varying;
   if (tex.a < 0.0) {
      tex.a = 0.0;
   } else if (tex.a > 1.0) {
      tex.a = 1.0;
   }
   gl_FragColor = tex;
}