#ifndef _APP_H_
#define _APP_H_

static int stageWidth = 100;
static int stageHeight = 100;

// Инициализация
int Init();

void renderFrame();
bool setupGraphics(int w, int h);

// Прорисовка каждый фрейм
int Render();

// Клик мышкой (точем)
int MouseDown(int x, int y);


// Клик мышкой (точем)
int MouseUp(int x, int y);


// Клик мышкой (точем)
int MouseMove(int x, int y);


// Клик мышкой (точем)
int KeyDown(int key);

// Клик мышкой (точем)
int KeyUp(int key);


// Клик мышкой (точем)
int Activate();

// Клик мышкой (точем)
int Deactivate();

#endif