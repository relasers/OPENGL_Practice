#pragma once

#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include "Rectangle.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;

list <CRectangle> shapes;
list<CRectangle>::iterator itor = shapes.begin();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Prac_4"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
								  // ���� �����ϰ� �簢�� �׸���



	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Draw();
	}

	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		POINT temp{x,Window_Height-y};
		if (shapes.size() >= 10) shapes.pop_back();
		shapes.push_front(CRectangle(temp));
	}
	
}

void TimerFunction(int value)
{

	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Update();
	}


		glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}
