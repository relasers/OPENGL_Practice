#include<iostream>
#include<gl/glut.h>
#include <Windows.h>
#include<ctime>
#include<list>
#include"Vector3D.h"
#include "Camera.h"
/*
 I
JKL  :: ī�޶� �����մϴ�
+, - :: ī�޶��� �Ÿ��� �ø��� ���Դϴ�

*/

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 120.0;

constexpr int Rotate_Speed = 10;


class Cube {
private:
	Vec3f m_pt{};
	float m_radius{64};
	int m_angle{};
public:

	void Update() {
		(++m_angle) %= 360;
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);

			glBegin(GL_LINES);
			glVertex3f(0,-120, 0);
			glVertex3f(0, 120, 0);
			glEnd();
		
			glRotatef(m_angle, 0, 1, 0);
			glTranslatef(0,0,m_radius);
			
			glRotatef(m_angle,0,1,0);
			glutSolidCube(m_radius*0.5);

		}
		glPopMatrix();
	}
	void SetPt(Vec3f pt) { m_pt = pt; }

};

class Sphere {
private:
	Vec3f m_pt{};
	float m_radius{ 64 };
	int m_angle{};
public:

	void Update() {
		(++m_angle) %= 360;
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);

			glBegin(GL_LINES);
			glVertex3f(-120, 0, 0);
			glVertex3f(120, 0, 0);
			glEnd();

			glRotatef(m_angle, 1, 0, 0);
			glTranslatef(0, 0, m_radius);

			glRotatef(-m_angle, 1, 0, 0);
			glRotatef(m_angle, 0, 1, 0);
			glLineWidth(6.0);
			glutSolidSphere(m_radius*0.5,50,50);
			glColor3f(1.0,0,0);
			glutWireSphere(m_radius*0.5, 12,12);
			glLineWidth(1.0);
		}
		glPopMatrix();
	}
	void SetPt(Vec3f pt) { m_pt = pt; }

};

class Planet {
private:
	Vec3f m_pt{};
	float m_radius{ 64 };
	int m_angle{};
public:

	void Update() {
		(++m_angle) %= 360;
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);

			glRotatef(45,0,0,1);

			glBegin(GL_LINES);
			glVertex3f(0, -120, 0);
			glVertex3f(0, 120, 0);
			glEnd();

			glRotatef(m_angle, 0, 1, 0);
			glTranslatef(0, 0, m_radius);

			glRotatef(-m_angle, 0, 1, 0);

			glRotatef(m_angle, 0, 1, 0);
			glLineWidth(6.0);
			glColor3f(1.0, 1.0, 0);
			glutSolidSphere(m_radius*0.5, 50, 50);
			glColor3f(1.0, 0, 0);
			glutWireSphere(m_radius*0.5, 12, 12);
			glLineWidth(1.0);
			glRotatef(-m_angle, 0, 1, 0);
			

			glTranslatef( 0, sin(m_angle*PI / 180.0)*m_radius*0.5, cos(m_angle*PI / 180.0)*m_radius*0.5);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(5,m_radius,40,40);
		}
		glPopMatrix();
	}
	void SetPt(Vec3f pt) { m_pt = pt; }

};
///////////////<����>//////////////////////////

/////////////////////////////////////////////

//////////////<�⺻ �Լ�>//////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
//////////////////////////////////////////////////
void InitObjects();


void DrawAxis();
void DrawFloor();

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////////////////////////////////
////////////////////////////////////////////
CCamera camera;

Cube cube;
Sphere sphere;
Planet planet;
//Gate gate;
float ambiant = 0.5;
float specular = 0.5;
float diffuse = 0.5;

bool light_0;
bool is_normal = true;
int lightangle = 0;
int snowtick = 0;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]Q32"); // ������ ���� (������ �̸�)
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
	GLfloat AmbientLight[] = { ambiant, ambiant, ambiant, 1.0f };
	GLfloat DiffuseLight[] = { diffuse, diffuse, diffuse, 1.0f };
	GLfloat SpecularLight[] = { specular, specular, specular, 1.0f };
	GLfloat lightPos[] = { 120,120, -120, 1.0f };
	GLfloat LightModel_Ambiant[] = {0.1,0.1,0.1,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModel_Ambiant);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	GLfloat Ambient[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	GLfloat Specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specref);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
														// ���� �����ϰ� �簢�� �׸���
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	if (light_0)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);


	glColor4f(1.0, 1.0, 1.0, 1.0f);



	camera.Rander();
	

	glPushMatrix();
	{
		glColor3f(1.0,0.0,0.0);
		
		glPushMatrix();
		{
			glTranslatef(120,120,-120);
			glutSolidCone(1,2,10,10);
		}
		glPopMatrix();

		

		DrawAxis();



		cube.Rander();
		sphere.Rander();
		planet.Rander();
		//////////////////<�ٴ�>////////////////////

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);


	}
	glPopMatrix();



	glutSwapBuffers(); // ȭ�鿡 ����ϱ� (glflushȿ���� �ִ�.)
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
											   //glTranslatef(0.0, 0.0, -300.0);

											   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x�� �ּ�,�ִ�, y�� �ּ�,�ִ�, z�� �ּ� �ִ� // ��������




	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	{

		if (key == 'l' || key == 'L') {
			camera.HandlePosition(Camera_Speed, { 1,0,0 });
		}
		if (key == 'j' || key == 'J') {
			camera.HandlePosition(-Camera_Speed, { 1,0,0 });
		}
		if (key == 'i' || key == 'I') {
			camera.HandlePosition(Camera_Speed, { 0,1,0 });
		}
		if (key == 'k' || key == 'K') {
			camera.HandlePosition(-Camera_Speed, { 0,1,0 });
		}


		if (key == '1') {
			light_0 = 1 - light_0;
		}

		if (key == 'a') {;
			ambiant = max(0, ambiant - 0.1);
		}
		if (key == 'A') {
			ambiant = min(1, ambiant + 0.1);
		}
		if (key == 's') {
			specular = max(0, specular - 0.1);
		}
		if (key == 'S') {
			specular = min(1, specular + 0.1);
		}
		if (key == 'd') {
			diffuse = max(0, diffuse - 0.1);
		}
		if (key == 'D') {
			diffuse = min(1, diffuse + 0.1);
		}

		if (key == '+') {
			camera.HandleDistance(10);
		}
		if (key == '-') {
			camera.HandleDistance(-10);
		}
		if (key == 'r' || key == 'R') {
			camera.ResetPos();
		}

	}



	if (key == 'p' || key == 'P') {
		exit(0);
	}	// ����
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	snowtick++;
	camera.Update();
	cube.Update();
	sphere.Update();
	planet.Update();

	(++lightangle) %= 360;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
	cube.SetPt({-60,0,0});
	sphere.SetPt({60,0,-60});
	planet.SetPt({60,-60,60});
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
		glColor4f(0.2, 0.5, 0.2, 1.0f);
		glBegin(GL_QUADS);
		if(is_normal)glNormal3f(0,1,0);

		int grid = 2;
		for (int i = 0; i < grid; ++i) {
			for (int j = 0; j < grid; ++j) {
				glVertex3d(i*floor_size*2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
				glVertex3d(i*floor_size * 2 / grid - floor_size, 0,
					(j+1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i+1)*floor_size * 2 / grid - floor_size, 0,
					(j+1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i+1)*floor_size * 2 / grid - floor_size, 0,
					j*floor_size * 2 / grid - floor_size);
			}
		}
		

		glEnd();
		
	}
	glPopMatrix();
}

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis)
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(angle, axis.x, axis.y, axis.z);

	glBegin(GL_LINE_LOOP);
	glVertex3f((Size.x) / 2, -Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, -Size.y / 2, Size.z);
	glVertex3f(0.0, Size.y / 2, Size.z);
	glEnd();


	glPopMatrix();

}

void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis)
{
	glPushMatrix();

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(angle, axis.x, axis.y, axis.z);

	glBegin(GL_LINE_LOOP);
	glVertex3f((Size.x) / 2, Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, -Size.y / 2, Size.z);
	glVertex3f((Size.x) / 2, -Size.y / 2, Size.z);
	glEnd();


	glPopMatrix();

}
