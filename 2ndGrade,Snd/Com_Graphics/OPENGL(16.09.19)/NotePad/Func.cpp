#include "Func.h"
/*
��� : ������ ���
���� : ������ ���� ���
*/
GLvoid drawScene(GLvoid)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < count; ++i)
	{
		DrawRect(rect[i]);
	}
	

	glFlush();	//glutSwapBuffer();
}

/*
��� : ������ �� ���
���� : ������Ʈ �� ȭ���� �ٽ� �׸���.
*/
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(0, 0, Width, Height, -1.0, 1.0);
	

	glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);
}


void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (count < 10) {
			rect[count].x = x;
			rect[count].y = Height - y;
		count++;
		}
	}
}

/*
��� : �簢�� ���
���� : ���콺�� ���� ���� �Է� ���� ����Ʈ�� �޾Ƽ� �簢������ �ٲپ� ����Ѵ�.
*/
void DrawRect(Point rt) {

	
	Point v1 = { 20 , 0 }, v2 = { 0 , 20 }, v3 = { 20, 20 };

	v1 = { rt.x + v1.x, rt.y + v1.y };
	v2 = { rt.x + v1.x, rt.y + v1.y };
	v3 = { rt.x + v1.x, rt.y + v1.y };

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(rt.x, rt.y);
		glVertex2i(v1.x, v1.y);
		glVertex2i(v3.x, v3.y);
		glVertex2i(v2.x, v2.y);
	glEnd();
	
	
	/*
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(rt.x, rt.y + 20); //v1
		glVertex2i(rt.x, rt.y); //v2
		glVertex2i(rt.x + 20, rt.y); //v3
		glVertex2i(rt.x + 20, rt.y + 20); //v4
	glEnd();
	*/
	
}


void TimerFunction(int value)
{

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}