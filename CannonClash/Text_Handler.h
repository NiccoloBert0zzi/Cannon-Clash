 #include "Lib.h"
#include <string>

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

void Init_Freetype(void);
void renderText(int Program, mat4 Projection_Text, std::string text, unsigned int VAO_Text, unsigned int VBO_Text,float x, float y, float scale, glm::vec3 color);
