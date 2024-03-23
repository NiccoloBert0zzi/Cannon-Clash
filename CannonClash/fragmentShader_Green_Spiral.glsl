#ifdef GL_ES
precision mediump float; // Precisione dei float per OpenGL ES
#endif

uniform float time; // Tempo
uniform vec2 mouse; // Posizione del mouse
uniform vec2 resolution; // Risoluzione dello schermo

void main( void ) {
    // Calcolo della posizione normalizzata del pixel nel range [-0.5, 0.5]
    vec2 position = (gl_FragCoord.xy - resolution * 0.5) / resolution.yy;
    
    // Calcolo dell'angolo polare
    float th = atan(position.y, position.x) / (2.0 * 3.1415926) + 0.5;
    
    // Distanza dal centro dello schermo
    float dd = length(position);
    
    // Offset basato sul tempo
    float d = 0.25 / dd + time;

    // Combinazione di variabili per definire i canali rossi, verdi e blu
    vec3 uv = vec3(th + d, th - d, th + sin(d) * 0.6);
    float a = 0.5 + cos(uv.x * 3.1415926 * 2.0) * 0.5;
    float b = 0.5 + cos(uv.y * 3.1415926 * 2.0) * 0.5;
    float c = 0.5 + cos(uv.z * 3.1415926 * 6.0) * 0.5;

    // Calcolo del colore finale
    vec3 color = mix(vec3(0.1, 0.8, 0.1), vec3(0.1, 0.2, 0.2), pow(a, 0.2)) * 0.75;
    color += mix(vec3(0.1, 0.9, 0.1), vec3(0.1, 0.1, 0.2), pow(b, 0.5)) * 0.75;
    color += mix(vec3(0.2, 0.8, 0.2), vec3(0.2, 0.1, 0.2), pow(c, 0.1)) * 0.75;

    // Assegnazione del colore al pixel
    gl_FragColor = vec4(color * clamp(dd, 0.0, 98.0), 1.0); // Applicazione del colore al pixel con clamp sulla distanza
}
