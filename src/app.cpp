
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int stageWidth = 100;
static int stageHeight = 100;

GLuint gProgram = 0;

GLuint geom_id = 0;

GLuint Position_loc = 0;

struct Vertex {
	float x, y, z;
	//unsigned char r, g, b, a;
};

const Vertex gTriangleVertices[] = {
	{  0.f, .5f, 0.f }, //, 255, 0, 0, 255
	{ -.5f, -.5f, 0.f }, //, 0, 255, 0, 255
	{ .5f, -.5f, 0.f } //, 0, 0, 255, 255
};

// �������������
int Init()
{
	
	return 0;
}

// ���������� ������ �����
int Render()
{

	return 0;
}

// ���� ������ (�����)
int MouseDown(int x, int y)
{

	return 0;
}

// ���� ������ (�����)
int MouseUp(int x, int y)
{

	return 0;
}

// ���� ������ (�����)
int MouseMove(int x, int y)
{

	return 0;
}

// ���� ������ (�����)
int KeyDown(int key)
{

	return 0;
}

// ���� ������ (�����)
int KeyUp(int key)
{

	return 0;
}

// ���� ������ (�����)
int Activate()
{

	return 0;
}

// ���� ������ (�����)
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


bool setupGraphics(int w, int h) 
{
	glViewport(0, 0, w, h);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	//LOGI("setupGraphics(%d, %d)", w, h);
	gProgram = createProgram("attribute vec4 vPosition;                     \n"
							 "void main() {                                 \n"
							 "  gl_Position = vPosition;                    \n"
							 "}                                             \n",
							 "precision mediump float;                      \n"
							 "void main() {                                 \n"
							 "  gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);    \n"
							 "}                                             \n");
	if (!gProgram) {
		//LOGE("Could not create program.");
		return false;
	}
	
	
	glGenBuffers(1, &geom_id);
	
	glBindBuffer(GL_ARRAY_BUFFER, geom_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(Position_loc);
	//gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
	//checkGlError("glGetAttribLocation");
	//LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);


	checkGlError("glViewport");
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
	glEnableVertexAttribArray(Position_loc);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
}

