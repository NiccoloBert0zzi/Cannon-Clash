#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

// vettore del colore
in vec4 ourColor;
// scelta del modo di disegnare
uniform int scelta_fs;

#define PITCH 3.
#define POWER 130.

float line(vec2 p, vec2 l) {
    return pow(1. - length(p - l), POWER);
}

float map(vec2 p) {
    float c = line(p, vec2(p.x, floor(p.y * PITCH + .5) / PITCH)) + line(p, vec2(floor(p.x * PITCH + .5) / PITCH, p.y)) - 1e-10;
    return clamp(c, 0., 1.);
}

void main(void) {
    if (scelta_fs == 1) {
        // disegna sfondo
        vec2 p = (gl_FragCoord.xy * 2. - resolution.xy) / min(resolution.x, resolution.y);

        vec3 l = vec3(p.x + 1., p.y - 2., 2.5);    //light pos
        vec3 ln = normalize(l);
        float t = time * 1.09;

        vec3 col = vec3(0.1, 0.4, 0.1); // Green base color

        // Aggiunta di sfumatura verde/marrone basata sulla coordinata y
        float gradient = clamp(p.y * 0.5 + 0.5, 0.0, 1.0);
        vec3 brown = vec3(0.3, 0.2, 0.1); // Marrone più scuro
        col = mix(col, brown, gradient);

        float v = map(p);
        if (v > .3) {
            col = vec3(.1, .1, .1);
        } else {
            float dx = map(p + vec2(0.01, 0.)), dy = map(p + vec2(0., 0.01));
            vec3 n = normalize(vec3(v - dx, v - dy, .2));
            v = pow(clamp(dot(ln, n), 0., 1.), 8.);
            col += v;
        }

        gl_FragColor = vec4(col, 1);
    } else {
        // disegna entità normale
        gl_FragColor = ourColor;
    }
}