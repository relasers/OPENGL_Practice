#include<iostream>
#include <cstdlib>
#include <chrono>
#include <gl/glut.h>
#include <list>
#include <Windows.h>
#include "GLFramework.h"


using namespace std;


namespace {
	CGLFramework framework;
}; // �͸� ���� �����̽�


constexpr int Window_Width = 800;
constexpr int Window_Height = 600;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);



// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	framework.drawScene();
}
GLvoid Reshape(int w, int h)
{
	framework.Reshape(w, h);
}

void Keyboard(unsigned char key, int x, int y)
{

}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	framework.TimerFunction(value);
}


void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���

	framework.Initialize();
	framework.Run();
	
	//glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	//glutMouseFunc(Mouse);
	

	
}
