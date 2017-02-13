#pragma once

#include <cstdlib>
#include <chrono>
#include <glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
								  // ���� �����ϰ� �簢�� �׸���
	
	srand((unsigned)time(nullptr));
	int dice = 1 + rand() % 6;
	for (int i = 0; i < dice; ++i) {
		for (int j = 0; j < dice; ++j)
		{
			switch ((i + j)%2) {
			case 0:
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'blue' ���� ����
				break;
			case 1:
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // �׸��� ���� 'red' ���� ����
				break;

			}

			glRectf(2.0f / (float)dice*j - 1.0f,
				2.0f / (float)dice*i - 1.0f,
				2.0f / (float)dice*(j + 1) - 1.0f,
				2.0f / (float)dice*(i + 1) - 1.0f); // �簢�� �׸���
		}
	}

	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}
