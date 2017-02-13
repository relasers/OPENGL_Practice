#pragma once

#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include "Ractangle.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr int Max_Ractangle = 20;

int main_tick = 0;

list <CRectangle> shapes;
list<CRectangle>::iterator itor = shapes.begin();

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
	glutCreateWindow("Prac_5"); // ������ ���� (������ �̸�)
								////////////////<�޴� ����>///////////////////////////////
	GLint SubMenu;
	GLint MainMenu;
	SubMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Shape", SubMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	///////////////////////////////////////////////
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
		for (itor = shapes.begin(); itor != shapes.end(); itor++)
		{
			if (itor->CollisionCheck(x, Window_Height-y)) {
				for (itor = shapes.begin(); itor != shapes.end(); itor++)
				{
					itor->MoveOn();
				}
				break;
			}
		}
	}

}

void TimerFunction(int value)
{

	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Update(Window_Width, Window_Height);
	}

	if (main_tick % 20 == 0) {
		POINT temp{ rand() % Window_Width,rand() % Window_Height };
		if (shapes.size() <= Max_Ractangle) shapes.push_front(CRectangle(temp));
	}
	
	(++main_tick) %= 200;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(20, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
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