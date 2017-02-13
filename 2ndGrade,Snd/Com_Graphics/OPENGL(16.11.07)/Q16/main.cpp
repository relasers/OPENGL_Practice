#include<iostream>
#include<gl/glut.h>
#include<ctime>
#include"Vec3D.h"

using namespace std;

enum Type {
	Cube = 0, Sphere, Cone, Teapot
};

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 50.0;
constexpr float floor_size = 120.0;
constexpr int shape_size = (int)floor_size / 2;
constexpr int Rotate_Speed = 5;
constexpr float PI = 3.141592;


class Ball {
private:
	Vec3f m_pt{};
	Vec3f m_angle{};
	int m_radius = 30;

public:

	void Update() {

	}


	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_radius, m_pt.z);
			glRotatef(m_angle.x, 0, 0, 1);
			glRotatef(m_angle.y, 0, 1, 0);
			glRotatef(m_angle.z, 1, 0, 0);
			glutWireSphere(m_radius, 30, 30);
			//glutWireTeapot(m_radius);

		}
		glPopMatrix();



	}

	void Move(int direction ,float x, Vec3f axis) {
		m_angle -= axis*x*direction;
		m_pt.x += axis.x*x*direction  * PI * m_radius / 360;
		m_pt.y += axis.y*x*direction  * PI * m_radius / 360;
		m_pt.z += axis.z*x*direction  * PI * m_radius / 360;

		m_pt.x = min(floor_size, m_pt.x + m_radius);
		m_pt.y = min(floor_size, m_pt.y + m_radius);
		m_pt.z = min(floor_size, m_pt.z + m_radius);
		m_pt.x = max(-floor_size + m_radius, m_pt.x - m_radius);
		m_pt.y = max(-floor_size + m_radius, m_pt.y - m_radius);
		m_pt.z = max(-floor_size + m_radius, m_pt.z - m_radius);
	}

	void init() {
		m_pt = {0,0,0};
		m_angle = {0,0,0};
	}


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
int x_angle = 0;
int y_angle = 0;
int z_angle = 0;
int z_camera_eye = 0;
////////////////////////////////////////////
Ball ball;





void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]Q16"); // ������ ���� (������ �̸�)
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
														// ���� �����ϰ� �簢�� �׸���
	glEnable(GL_DEPTH_TEST);

	glColor4f(1.0, 1.0, 1.0, 1.0f);

	
	glPushMatrix();
	{
		glTranslated(0, -100.0, z_camera_eye);
		DrawAxis();

		//////////////////<�ٴ�>////////////////////
		DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		ball.Rander();

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
	gluPerspective(60.0f, w / h, 1.0, 1000.0); // fovy :: �ִ� 180(�Ѿ�� �Ųٷ� ����), �������� ũ�� ����
											   //glTranslatef(0.0, 0.0, -300.0);

											   //glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x�� �ּ�,�ִ�, y�� �ּ�,�ִ�, z�� �ּ� �ִ� // ��������




	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
	gluLookAt(0.0, 0.0, -300,		0.0, 0.0, -1.0, /* z���� ũ��� ���� ��� X */		0.0, 1.0, 0.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	{
		if (key == 'x') {
			ball.Move(-1,Rotate_Speed, {1,0,0});
		}
		if (key == 'X') {
			ball.Move(1,Rotate_Speed, { 1,0,0 });
		}
		if (key == 'y') {
			ball.Move(-1,Rotate_Speed, { 0,1,0 });
		}
		if (key == 'Y') {
			ball.Move(1,Rotate_Speed, { 0,1,0 });
		}
		if (key == 'z') {
			ball.Move(-1,Rotate_Speed, { 0,0,1 });
		}
		if (key == 'Z') {
			ball.Move(1,Rotate_Speed, { 0,0,1 });
		}
		if (key == '+') {
			z_camera_eye+= 10;
		}
		if (key == '-') {
			z_camera_eye-= 10;
		}
		if (key == 'i' || key == 'I') {
			ball.init();
		}
	}



	if (key == 'q' || key == 'Q') {
		exit(0);
	}	// ����
}

void Mouse(int button, int state, int x, int y)
{

}

void TimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));

	/*
	Vec3f pt = {-100.0f,(float)(-floor_size+shape_size),20.0f};

	Shape solid = Shape(pt,Type::Cube, shape_size, false);

	pt = { 100.0f,(float)(-floor_size + shape_size),20.0f };
	Shape wire = Shape(pt,Type::Cube, shape_size, true);
	*/


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
	{
		glColor4f(0.2, 0.5, 0.2, 0.7f);
		glBegin(GL_POLYGON);

		glVertex3f(floor_size, 0, -floor_size);
		glVertex3f(-floor_size, 0, -floor_size);
		glVertex3f(-floor_size, 0, floor_size);
		glVertex3f(floor_size, 0, floor_size);

		glVertex3f(floor_size, - 2, -floor_size);
		glVertex3f(-floor_size, - 2, -floor_size);
		glVertex3f(-floor_size, - 2, floor_size);
		glVertex3f(floor_size,  - 2, floor_size);

		glEnd();
	}
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
