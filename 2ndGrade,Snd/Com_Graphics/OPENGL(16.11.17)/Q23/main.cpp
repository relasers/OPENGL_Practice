#include<iostream>
#include<gl/glut.h>
#include "Vec3D.h"
#include "Camera.h"
#include <list>
#include <cmath>
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;

constexpr float axis_size = 120.0;
constexpr float floor_size = 120.0;

class CRing {
private:
	Vec3f m_pt = {0.0f,floor_size,0.0f};
	int m_height{5};
	int m_size{50};
	int m_angle{};

	bool m_isDrop = true;
public:
	void Rander() {
	
		glPushMatrix();
		{
			
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			glRotatef(90, 1, 0, 0);
			glColor3f(0.8f, 0.3f, 0.0f);
			glutWireTorus(m_height, m_size,10,100);
		}
		glPopMatrix();

	}
	void Update() {
		for (int i = 0; i < 5;++i)(++m_angle) %= 360;

		if (m_isDrop) 
		{
			m_pt.x = cos(m_angle*PI / 180.0)*(m_size - m_height * 2);
			m_pt.z = sin(m_angle*PI / 180.0)*(m_size - m_height * 2);
			m_pt.y -= 1;
		}
	}

	bool CollisionCheck(int floor,int x) {
		if(m_isDrop)
		if (floor + x*m_height*2 > m_pt.y-m_height) {
			m_isDrop = false;
			m_pt.x = 0;
			m_pt.y = floor + x*m_height*2;
			m_pt.z = 0;
			return true;
		}
		return false;
	}

};
class CPaper {
private:
	Vec3f m_pt = { 0.0f,floor_size,0.0f };
	int m_height{ 5 };
	int m_size{ 120 };
	int m_angle{};

	bool m_isDrop = true;
public:
	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glScalef(1,1/m_size,1);
			glRotatef(m_angle,0,1,0);
			glColor3f(1.0f, 1.0f, 0.0f);
			glutSolidCube(m_size);
		}
		glPopMatrix();

	}
	void Update() {
		if (m_isDrop)
		{
			for (int i = 0; i < 5; ++i)(++m_angle) %= 360;
			m_pt.y -= 1;
		}
	}

	bool CollisionCheck(int floor, int x) {
		if (m_isDrop)
			if (floor + x*m_height * 2 > m_pt.y - m_height) {
				m_isDrop = false;
				m_pt.x = 0;
				m_pt.y = floor + x*m_height * 2 + m_height;
				m_pt.z = 0;
				return true;
			}
		return false;
	}

};




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
list<CRing>ring;
list<CPaper>paper;

int counter = 1;
bool can_craft = true;

bool shading = true;
bool culling = false;
bool depth_test = true;

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Q23"); // ������ ���� (������ �̸�)
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
	if (depth_test)
	glEnable(GL_DEPTH_TEST);
	if (!depth_test)
	glDisable(GL_DEPTH_TEST);

	if (culling)
		glEnable(GL_CULL_FACE);
	if (!culling)
		glDisable(GL_CULL_FACE);

	if (shading)
		glShadeModel(GL_SMOOTH); // �Ǵ� glShadeModel (GL_FLAT)
	if (!shading)
		glShadeModel(GL_FLAT);

	glFrontFace(GL_CW);
	camera.Rander();

	glPushMatrix();
	{
		DrawAxis();
		DrawFloor();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		glPushMatrix();
		
		glRotatef(90, 1, 0, 0);
		glScalef(1,1,floor_size);
		glutSolidTorus(1,2,10,10);
		glPopMatrix();

		for (auto &p : ring) {
			p.Rander();
		}
		for (auto &p : paper) {
			p.Rander();
		}


	}
	glPopMatrix();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ� (glflushȿ���� �ִ�.)
}

void TimerFunction(int value)
{
	camera.Update();

	for (auto &p : ring) {
		p.Update();
		if (p.CollisionCheck(-floor_size, ring.size())) {
			can_craft = true;
		}
	}

	for (auto &p : paper) {
		p.Update();
		if (p.CollisionCheck(-floor_size, ring.size())) {
			can_craft = true;
		}
	}

	if (can_craft) {
		
		if (counter > 35) {
			paper.clear();
			ring.clear();
			counter = 1;
		}

		if (counter %3 == 0) {
			paper.push_front(CPaper());
		}
		else
		{
			ring.push_front(CRing());
		}
	
		counter++;
		can_craft = false;
	
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y)
{
	camera.KeyInput(key, x, y);

	if (key == 'z' || key == 'Z') {
		shading = 1 - shading;
	}
	if (key == 'x' || key == 'X') {
		culling = 1 - culling;
	}
	if (key == 'c' || key == 'C') {
		depth_test = 1 - depth_test;
	}
	if (key == 'a') {
		ring.push_back(CRing());
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

