#ifndef _APP_H_
#define _APP_H_

static int stageWidth = 100;
static int stageHeight = 100;

// �������������
int Init();

void renderFrame();
bool setupGraphics(int w, int h);

// ���������� ������ �����
int Render();

// ���� ������ (�����)
int MouseDown(int x, int y);


// ���� ������ (�����)
int MouseUp(int x, int y);


// ���� ������ (�����)
int MouseMove(int x, int y);


// ���� ������ (�����)
int KeyDown(int key);

// ���� ������ (�����)
int KeyUp(int key);


// ���� ������ (�����)
int Activate();

// ���� ������ (�����)
int Deactivate();

#endif