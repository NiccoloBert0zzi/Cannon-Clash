#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;
uniform vec3 outlineColor; // Colore dell'outline
uniform float outlineThickness; // Spessore dell'outline

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    
    // Applichiamo l'outline al testo
    float outline = smoothstep(0.5 - outlineThickness, 0.5, sampled.r);
    vec3 outlinedColor = mix(outlineColor, textColor, outline);
    
    // Applichiamo il colore all'outline
    color = vec4(outlinedColor, 1.0);
}
