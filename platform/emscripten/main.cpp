/*
(c) 2014 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1201
*/

#define GL_GLEXT_PROTOTYPES

#include <cstdio>
#include <cassert>
#include <GL/glut.h>
#include "../../src/app.h"

struct Context
{
   int width, height;
   GLuint vert_id, frag_id;
   GLuint prog_id, geom_id;
   GLint u_time_loc;
   
   enum { Position_loc, Color_loc };

   Context():
   width(800), height(600),
   vert_id(0), frag_id(0),
   prog_id(0), geom_id(0),
   u_time_loc(-1)
   {}

} g_context;



void resize(int width, int height)
{
   printf("resize(%d, %d)\n", width, height);
   
   g_context.width = width;
   g_context.height = height;
}

void draw()
{
   //glViewport(0, 0, g_context.width, g_context.height);
   //glClear(GL_COLOR_BUFFER_BIT);

   renderFrame();
   // glUniform1f(g_context.u_time_loc, glutGet(GLUT_ELAPSED_TIME) / 1000.f);
   //glDrawArrays(GL_TRIANGLES, 0, 3);
   
   glutSwapBuffers();
}

void update()
{
   glutPostRedisplay();   
}

int main(int argc, char *argv[])
{
   printf("main()\n");

   glutInit(&argc, argv);
   glutInitWindowSize(g_context.width, g_context.height);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   glutCreateWindow("Hello Triangle! | 4FipS.com");


   setupGraphics(g_context.width, g_context.height);

   glutReshapeFunc(resize);
   glutDisplayFunc(draw);
   glutIdleFunc(update);

   

   glutMainLoop();

   return 0;
}
