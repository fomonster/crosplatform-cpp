
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <iostream>
//#include <fstream>
#include <cstdlib>
#include "images.h"
#include "lodepng.h"

using namespace std;


static int stageWidth = 400;
static int stageHeight = 300;

GLuint gProgram = 0;

GLuint geom_id = 0;

GLuint Position_loc = 0;
GLuint Texture_loc = 1;
GLuint Color_loc = 2;

GLuint textureId;

struct Vertex {
	float x, y, z;
	float u, v;
	float r, g, b, a;
};





const Vertex gTriangleVertices[] = {
	{ -.5f, .5f, 0.f, 0.0f, 1.0f, 1.f, 1.f, 1.0f, 1.f },
	{ .5f, .5f, 0.f, 1.0f, 1.0f,  1.f, 1.f, 1.0f, 1.f },
	{ .5f, -.5f, 0.f, 1.0f, 0.0f,  1.f, 1.f, 1.0f, 1.f },

	{ -.5f, .5f, 0.f, 0.0f, 1.0f,  1.f, 1.f, 1.0f, 1.f },
	{ -.5f, -.5f, 0.f, 0.0f, 0.0f,  1.f, 1.f, 1.0f, 1.f },
	{ .5f, -.5f, 0.f, 1.0f, 0.0f,  1.f, 1.f, 1.0f, 1.f }
};

// Инициализация
int Init()
{
	
	return 0;
}

// Прорисовка каждый фрейм
int Render()
{

	return 0;
}

// Клик мышкой (точем)
int MouseDown(int x, int y)
{

	return 0;
}

// Клик мышкой (точем)
int MouseUp(int x, int y)
{

	return 0;
}

// Клик мышкой (точем)
int MouseMove(int x, int y)
{

	return 0;
}

// Клик мышкой (точем)
int KeyDown(int key)
{

	return 0;
}

// Клик мышкой (точем)
int KeyUp(int key)
{

	return 0;
}

// Клик мышкой (точем)
int Activate()
{

	return 0;
}

// Клик мышкой (точем)
int Deactivate()
{

	return 0;
}


static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *)glGetString(s);
	// LOGI("GL %s = %s\n", name, v);
}


static void checkGlError(const char* op) {
	for (GLint error = glGetError(); error; error
		= glGetError()) {
		//LOGI("after %s() glError (0x%x)\n", op, error);
	}
}


GLuint loadShader(GLenum shaderType, const char* pSource) {
	GLuint shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*)malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					//LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
	if (!vertexShader) {
		return 0;
	}

	GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
	if (!pixelShader) {
		return 0;
	}

	GLuint program = glCreateProgram();
	if (program) {
		glAttachShader(program, vertexShader);
		
		//checkGlError("glAttachShader");
		glAttachShader(program, pixelShader);
	
		
		//checkGlError("glAttachShader");
		glLinkProgram(program);

		glBindAttribLocation(gProgram, Position_loc, "vPosition");
		glBindAttribLocation(gProgram, Texture_loc, "vTexture");
		glBindAttribLocation(gProgram, Color_loc, "vColor");

		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*)malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					printf("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
		else 
		{
			printf("Program linked!!\n");
		}
	}
	return program;
}

/*
void printFile()
{
	//Opens .txt file
	ifstream fin;
	string filename = "assets/xml/temp/Comics.xml";
	fin.open(filename);


	//Fail check
	if (fin.fail())
	{
		cout << "File failed to open. " << filename.c_str() << endl;
		return;
	}
	else
	{
		cout << "File opened!" << filename.c_str() << endl;
	}
	
	char temp[1024];
	
	while ( !fin.eof() ) {
		fin.getline(temp, 1024);
		cout << temp << endl;
	}

	//Closes file
	fin.close();
}*/

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels) {
	GLuint texture_object_id;
	glGenTextures(1, &texture_object_id);


	glBindTexture(GL_TEXTURE_2D, texture_object_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D( GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture_object_id;
}


bool setupGraphics(int w, int h) 
{
	//
    
	//printFile();

	//
	glViewport(0, 0, w, h);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	//LOGI("setupGraphics(%d, %d)", w, h);
	gProgram = createProgram("attribute vec4 vPosition;                     \n"
							 "attribute vec4 vColor;                        \n"
							 "attribute vec4 vTexture;                      \n"
							 "varying vec4 v_color;                         \n"
							 "varying vec2 v_texCoord;                      \n"
							 "void main() {                                 \n"
							 "  gl_Position = vPosition;                    \n"
							 "  v_color = vColor;                           \n"
							 "  v_texCoord = vTexture.xy;                   \n"
							 "}                                             \n",
							 "precision mediump float;                      \n"
							 "uniform sampler2D s_texture;                  \n"	
							 "varying vec4 v_color;                         \n"
							 "varying vec2 v_texCoord;                         \n"
							 "void main() {                                 \n"
							 "  gl_FragColor = v_color * texture2D(s_texture, v_texCoord);  \n"
							 "}                                             \n");
	if (!gProgram) {
		//LOGE("Could not create program.");
		return false;
	}
	
	
	glGenBuffers(1, &geom_id);
	
	glBindBuffer(GL_ARRAY_BUFFER, geom_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_STATIC_DRAW);

	//auto offset = [](size_t value) -> const GLvoid *{ return reinterpret_cast<const GLvoid *>(value); };

	Position_loc = glGetAttribLocation(gProgram, "vPosition");
	Texture_loc = glGetAttribLocation(gProgram, "vTexture");
	Color_loc = glGetAttribLocation(gProgram, "vColor");

	glEnableVertexAttribArray(Position_loc);
	glEnableVertexAttribArray(Texture_loc);
	glEnableVertexAttribArray(Color_loc);

	GLuint offset1 = 0;
	glVertexAttribPointer(Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	GLuint offset2 = 3 * sizeof(float);
	glVertexAttribPointer(Texture_loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)12);
	GLuint offset3 = 5 * sizeof(float);
	glVertexAttribPointer(Color_loc, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)20);
	
	// texture

	//FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType("textures/test/nehe_06.png", 0), "textures/test/nehe_06.png");
	
	glEnable(GL_TEXTURE_2D);


	std::vector<unsigned char> png;
	std::vector<unsigned char> image;

	unsigned width, height;
	
	LodePNGState state;
	lodepng_state_init(&state);

	char* filename = "/mnt/sdcard/crate.png";
	
	lodepng::load_file(png, filename);
	
	unsigned res = lodepng::decode(image, width, height, state, png);
		//lodepng::decode(image, width, height, "/mnt/sdcard/crate.png");

	if (res != 0) {
		
		width = 256; 
		height = 256;
		
		textureId = load_texture(width, height, GL_RGBA, decode_image(width, height)); 
	}
	else 
	{
		textureId = load_texture(width, height, GL_RGBA, &image[0]);
	}



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	

	return true;
}



void renderFrame() 
{
	

	static float grey;
	grey += 0.005f;
	if (grey > 1.0f) {
		grey = 0.0f;
	}
	glClearColor(grey, grey, grey, 1.0f);
	//checkGlError("glClearColor"); GL_DEPTH_BUFFER_BIT | 
	glClear(GL_COLOR_BUFFER_BIT);
	//checkGlError("glClear");


	glUseProgram(gProgram);
	//checkGlError("glUseProgram");
	//glEnableVertexAttribArray(Color_loc);
	//glEnableVertexAttribArray(Position_loc);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}

