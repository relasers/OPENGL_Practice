#pragma once
#include<iostream>
#include<gl/glut.h>
#include "Vector3D.h"
#include "Camera.h"
#include "Player.h"
#include "CombatDrone.h"
#include "HexTechTower.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 120.0;
constexpr float floor_size = 128.0;

//////////////<�⺻ �Լ�>//////////////////////////
GLvoid RanderScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void DrawAxis();
void DrawFloor();
//////////////////////////////////////////////////
CCamera camera;
CPlayer player;
CCombatDrone combatdrone;
CHexTechTower tower;
void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Model_Viewer"); // ������ ���� (������ �̸�)
	glutDisplayFunc(RanderScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMouseFunc(Mouse);
	glutTimerFunc(1, TimerFunction, 1);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();


}

GLvoid RanderScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
														// ���� �����ϰ� �簢�� �׸���
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);	glEnable(GL_COLOR_MATERIAL);	glShadeModel(GL_SMOOTH);	GLfloat AmbientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPos[] = { camera.GetEye().x, camera.GetEye().y, camera.GetEye().z, 1.0 };		glEnable(GL_LIGHTING);	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);	glEnable(GL_LIGHT0);

	camera.Rander();

	glPushMatrix();
	{
		DrawAxis();
		//DrawFloor();
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glutWireCube(2048);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		
		tower.Rander();

		glTranslatef(600,0,600);
		player.Rander();

		glTranslatef(-1200, 0, -1200);
		combatdrone.Rander();
	}
	glPopMatrix();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ� (glflushȿ���� �ִ�.)
}

void TimerFunction(int value)
{
	camera.Update();
	player.Update();
	tower.Update();
	combatdrone.Update();
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y)
{
	camera.KeyInput(key, x, y);
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
	gluPerspective(60.0f, w / h, 1.0, 10000.0); // fovy :: �ִ� 180(�Ѿ�� �Ųٷ� ����), �������� ũ�� ����
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

