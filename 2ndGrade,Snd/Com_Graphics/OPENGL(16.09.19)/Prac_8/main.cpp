#pragma once

#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include "Ractangle.h"
#include"Vec2D.h"
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr int Max_Ractangle = 20;



bool rectexist = false; // Ŭ���� ����
Vec2f rectpt{0,0};
constexpr int RectSize = 40;

list <CRactangle> shapes;
list<CRactangle>::iterator itor = shapes.begin();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);


void main(int argc, char *argv[])
{

	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Prac_8"); // ������ ���� (������ �̸�)
	

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();


}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
								  // ���� �����ϰ� �簢�� �׸���

	if (rectexist) {
		glColor4f(1.0, 5.0, 0.0, 1.0f);
		glBegin(GL_POLYGON);
			glVertex2i(rectpt.x, rectpt.y + RectSize); //v1
			glVertex2i(rectpt.x, rectpt.y); //v2
			glVertex2i(rectpt.x + RectSize, rectpt.y); //v3
			glVertex2i(rectpt.x + RectSize, rectpt.y + RectSize); //v4
		glEnd();
	}
	

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
	if (key == '+')
	{
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->IncreaseSpd();
		}
	}
	if (key == '-')
	{
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->DecreaseSpd();
		}
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rectexist = true;
		rectpt.x = x;
		rectpt.y = Window_Height - y;

	} // ��Ŭ�� :: ��ǥ���� ����
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		POINT temp{ x,Window_Height - y };
		if (shapes.size() >= Max_Ractangle) shapes.pop_back();
		shapes.push_front(CRactangle(temp));
	}// ��Ŭ�� :: �簢�� ����

}

void TimerFunction(int value)
{
	if (rectexist) {
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->Update(Window_Width, Window_Height, rectpt);
		}
	}
	

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void MenuFunc(int button)
{
	switch (button) {
	case 1:
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->ChangeShape(0);
		}
		break;
	case 2:
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			itor->ChangeShape(1);
		}
		break;
	}
	glutPostRedisplay();
}