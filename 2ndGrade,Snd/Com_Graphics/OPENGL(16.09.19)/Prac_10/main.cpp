#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include <Windows.h>
#include "Shape.h"
#include"Vec2D.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr int Max_Ractangle = 20;

list <CShape> shapes;
list<CShape>::iterator itor = shapes.begin();

RECT Main_Field;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void main(int argc, char *argv[])
{
	Main_Field = {
		100,100,
		Window_Width - 100,
		Window_Height - 100,
	};
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Prac_10"); // ������ ���� (������ �̸�)


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
	glEnable(GL_BLEND);

	glColor4f(0.0, 0.0, 0.0, 0.5f);
	glRectf(0, 0, Window_Width, Window_Height);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
		glColor4f(1.0, 1.0, 0.0, 1.0f);
		glBegin(GL_POLYGON);
			glVertex2i(Main_Field.left, Main_Field.top); //v1
			glVertex2i(Main_Field.left, Main_Field.bottom); //v2
			glVertex2i(Main_Field.right, Main_Field.bottom); //v3
			glVertex2i(Main_Field.right, Main_Field.top); //v4
		glEnd();


	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Draw();
	}

	glDisable(GL_BLEND);

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
		POINT temp{ x,Window_Height - y };
		if (PtInRect(&Main_Field, temp)) {
			if (shapes.size() >= Max_Ractangle) shapes.pop_back();
			shapes.push_front(CShape(temp));
		}
	}// ��Ŭ�� :: �簢�� ����

}

void TimerFunction(int value)
{
	
	for (itor = shapes.begin(); itor != shapes.end(); itor++)
	{
		itor->Update(Window_Width, Window_Height);
		itor->IsOutofField(Main_Field);
	}



	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}
