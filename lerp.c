#include "lerp.h"

void lerp(vec2 a, vec2 b, vec2 p, float t) {
  p[0] = a[0] + (b[0]-a[0]) * t;
  p[1] = a[1] + (b[1]-a[1]) * t;
}

void quadraticBezier(vec2 a, vec2 b, vec2 c, vec2 p, float t) {
  vec2 d;
  vec2 e;
  lerp(a, b, d, t);
  lerp(b, c, e, t);
  lerp(d, e, p, t);
}

void cubicBezier(vec2 a, vec2 b, vec2 c, vec2 d, vec2 p, float t) {
  vec2 e;
  vec2 f;
  quadraticBezier(a, b, c, e, t);
  quadraticBezier(b, c, d, f, t);
  lerp(e, f, p, t);
}