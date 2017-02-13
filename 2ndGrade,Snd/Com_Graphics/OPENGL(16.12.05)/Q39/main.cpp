#include<iostream>
#include<gl/glut.h>
#include "Vec3D.h"
#include "Camera.h"
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 120.0;
constexpr float floor_size = 120.0;

//////////////<�⺻ �Լ�>//////////////////////////
GLvoid RanderScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void DrawAxis();
void DrawFloor();
void InitObjects();
//////////////////////////////////////////////////
CCamera camera;

float fog_color[4] = { 0.5, 0.5, 0.9, 0.1 };
float fog_density = 0.1;
float fog_start = 200.0f;
float fog_end = 300.0f;
GLenum fog_mode = GL_LINEAR;


void main(int argc, char *argv[])
{
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Q39"); // ������ ���� (������ �̸�)
	glutDisplayFunc(RanderScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMouseFunc(Mouse);
	glutTimerFunc(1, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����

	InitObjects();

	glutMainLoop();


}

GLvoid RanderScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	
	
	
	switch (fog_mode) {
	case GL_LINEAR:
		glFogf(GL_FOG_MODE, GL_LINEAR);
		break;
	case GL_EXP:
		glFogf(GL_FOG_MODE, GL_EXP);
		break;
	case GL_EXP2:
		glFogf(GL_FOG_MODE, GL_EXP2);
		break;
	}


	glFogfv(GL_FOG_COLOR, fog_color); // fog_color�� �Ȱ��� ���� �ǹ��Ѵ�. glFogf(GL_FOG_START, start); // start�� world coordinate�󿡼� �Ȱ� ���� ��ġ�� �ǹ��Ѵ�.
	glFogf(GL_FOG_START, fog_start); // end�� world coordinate�󿡼� �Ȱ� �� ��ġ�� �ǹ��Ѵ�.
	glFogf(GL_FOG_END, fog_end); // end�� world coordinate�󿡼� �Ȱ� �� ��ġ�� �ǹ��Ѵ�.
	glFogf(GL_FOG_DENSITY, fog_density); // fog mode�� GL_EXP, GL_EXP2�� ��� �е��� ������ ����


	glEnable(GL_FOG);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	camera.Rander();

	glPushMatrix();
	{
		DrawAxis();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glutSolidCube(100);

		glTranslatef(0,0,75);
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glutSolidCube(75);

		glTranslatef(0, 0, -150);
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glutSolidCube(75);

	}
	glPopMatrix();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ� (glflushȿ���� �ִ�.)
}

void TimerFunction(int value)
{
	camera.Update();
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y)
{
	camera.KeyInput(key, x, y);

	if (key == '1') 
	{
		fog_mode = GL_LINEAR;
	}
	if (key == '2')
	{
		fog_mode = GL_EXP;
	}
	if (key == '3')
	{
		fog_mode = GL_EXP2;
	}

	if (key == 'z' || key == 'Z')
	{
		fog_density = max(0, fog_density - 0.001);
		cout << "Density ::" << fog_density << endl;
	}
	if (key == 'x' || key == 'X')
	{
		fog_density += 0.001;
		cout << "Density ::" << fog_density << endl;
	}

	if (key == 'q' || key == 'Q')
	{
		fog_end--;
		cout << "End ::" << fog_end << endl;
	}
	if (key == 'w' || key == 'W')
	{
		fog_end++;
		cout << "End ::" << fog_end << endl;
	}

	if (key == 'a' || key == 'A')
	{
		fog_start--;
		cout << "Start ::" << fog_start << endl;
	}
	if (key == 's' || key == 'S')
	{
		fog_start++;
		cout << "Start ::" << fog_start << endl;
	}

}

void Mouse(int button, int state, int x, int y)
{

}

GLvoid Reshape(int w, int h)
{
	//////<����Ʈ ��ȯ ����>////////
	glViewport(0, 0, w, h);


	/////<���� ��Ľ��� �缳��>//////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	///////////<��������>////////////////////////
	gluPerspective(60.0f, w / h, 1.0, 1000.0); // fovy :: �ִ� 180(�Ѿ�� �Ųٷ� ����), �������� ũ�� ����
	glMatrixMode(GL_MODELVIEW);
}

void DrawAxis()
{
	/////////////<��ǥ�� �׸�>//////////////////
	{
		glBegin(GL_LINES);

		/////////////////<x��>///////////////////
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex3f(-axis_size, 0.0, 0.0);
		glVertex3f(axis_size, 0.0, 0.0);
		/////////////////<x��>///////////////////
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glVertex3f(0.0, -axis_size, 0.0);
		glVertex3f(0.0, axis_size, 0.0);
		/////////////////<x��>///////////////////
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, axis_size);
		glVertex3f(0.0, 0.0, -axis_size);


		glEnd();
	}
}

void DrawFloor()
{
	glPushMatrix();
	{
		glColor4f(0.2, 0.5, 0.2, 0.7f);
		glTranslated(0,-floor_size,0);
		glScalef(2, 0.01, 2);

		{
			glutSolidCube(floor_size);
		}
	}
	glPopMatrix();
}

void InitObjects()
{
}

