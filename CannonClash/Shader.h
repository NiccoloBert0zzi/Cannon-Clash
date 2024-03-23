#pragma once
#include "Lib.h"

class Shader
{
private:
	static unsigned int programId, programId_text;
	static char* vertexShader, * fragmentShader;


	public:
	static void INIT_SHADER(void);
	static unsigned int getProgramId(void);
	static unsigned int getProgramId_text(void);
	static char* getVertexShader(void);
	static char* getFragmentShader(void);

	private:
		static GLuint createProgram(char* vertexfilename, char* fragmentfilename);
		static char* readShaderSource(const char* shaderFile);
};

