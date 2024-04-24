#include <iostream>
#include <string>
#include <ft2build.h>
#include "Text_Handler.h"
#include FT_FREETYPE_H

std::map<GLchar, Character> Characters;

void Init_Freetype() {
	// Inizializza FreeType
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		// Se l'inizializzazione fallisce, mostra un errore e termina il programma
		printf("ERROR::FREETYPE: Impossibile inizializzare la libreria FreeType\n");
		exit(-1);
	}

	// Carica il tipo di carattere desiderato
	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) {
		// Se il caricamento del tipo di carattere fallisce, mostra un errore e termina il programma
		printf("ERROR::FREETYPE: Impossibile caricare il tipo di carattere\n");
		exit(-1);
	}
	else {
		// Imposta la dimensione per caricare i glifi
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disabilita la restrizione di allineamento dei byte
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Carica i primi 128 caratteri dell'insieme ASCII
		for (unsigned char c = 0; c < 128; c++) {
			// Carica il glifo del carattere
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				// Se il caricamento del glifo fallisce, continua con il prossimo carattere
				printf("ERROR::FREETYTPE: Impossibile caricare il glifo del carattere\n");
				continue;
			}

			// Genera la texture per il glifo
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// Imposta le opzioni della texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Memorizza il carattere per un utilizzo successivo
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Rilascia le risorse di FreeType una volta terminato
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}
void renderText(int Program, mat4 Projection_text, std::string text, unsigned int VAO_Text, unsigned int VBO_Text, float x, float y, float scale, glm::vec3 color)
{
	// Attiva lo stato di rendering corrispondente
	glUseProgram(Program);
	glUniform3f(glGetUniformLocation(Program, "textColor"), color.x, color.y, color.z); // Imposta il colore del testo
	glUniformMatrix4fv(glGetUniformLocation(Program, "Projection_text"), 1, GL_FALSE, value_ptr(Projection_text)); // Imposta la matrice di proiezione

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO_Text);

	// Itera attraverso tutti i caratteri della stringa di testo
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c]; // Ottieni il carattere corrente

		// Calcola le coordinate del carattere
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		// Aggiorna il buffer dei vertici per ogni carattere
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// Renderizza la texture del carattere su un quadrato
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Aggiorna il contenuto della memoria del buffer dei vertici
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Text);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Renderizza il quadrato
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Avanza il cursore per il prossimo carattere (l'advance è il numero di pixel su 64)
		x += (ch.Advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

