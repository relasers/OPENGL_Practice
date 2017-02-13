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
constexpr int shape_size = (int)floor_size/2;
constexpr int Rotate_Speed = 2;
constexpr float PI = 3.141592;

///////////////<����>//////////////////////////

/////////////////////////////////////////////

class Shape {
private:
	Vec3f m_pt;
	int m_shapetype{};
	int m_shapesize{};
	bool m_iswire{};
	int m_angle{};
	
public:
	Shape() {}
	Shape(Vec3f pt, int shapetype,int shapesize, bool iswire) {
		m_pt = pt;
		m_shapetype = shapetype;
		m_shapesize = shapesize;
		m_iswire = iswire;
	}
	//////////////////////////////////////
	void Rander()
	{
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glRotatef(m_angle, 0, 1, 0);
			RanderObject();

		}
		glPopMatrix();
		
	}
	///////////////////////////////////////
	void Update() 
	{
	
	}
	//////////////////////////////////////
	void switchwire() {
		m_iswire = 1 - m_iswire;
	}
	/////////////////////////////////////
	void switchtype(int shapetype) {
		m_shapetype = shapetype;
	}
	void ChangeType(int Type) {
		m_shapetype = Type;
	}
	void RanderObject() {
		if (m_iswire) {
			switch (m_shapetype) {
			case Type::Cube:
			{
				glutWireCube(m_shapesize);
				break;
			}
			case Type::Sphere:
			{
				glutWireSphere(m_shapesize / 2, 32, 32);
				break;
			}
			case Type::Cone:
			{
				glPushMatrix();
				{
					glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
					//glTranslatef(0, m_shapesize*1.5, 0);
					glutWireCone(m_shapesize / 2, m_shapesize, 32, 32);
				}
				glPopMatrix();
				break;
			}
			case Type::Teapot:
			{
				glutWireTeapot(m_shapesize);
				break;
			}
			}
		}
		if (!m_iswire) {
			switch (m_shapetype) {
			case Type::Cube:
			{
				glutSolidCube(m_shapesize);
				break;
			}
			case Type::Sphere:
			{
				glutSolidSphere(m_shapesize / 2, 32, 32);
				break;
			}
			case Type::Cone:
			{
				glPushMatrix();
				{
					glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
					//glTranslatef(0, m_shapesize*1.5, 0);
					glutSolidCone(m_shapesize / 2, m_shapesize, 32, 32);
				}
				glPopMatrix();
				break;
			}
			case Type::Teapot:
			{
				glutSolidTeapot(m_shapesize);
				break;
			}
			}
		}
	}
	void ChangeAngle(int x) {
		m_angle += x;
	}
};


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
Vec3f pt_1 = { 70.0f,(float)(-floor_size + shape_size/2),20.0f };
Vec3f pt_2 = { -70.0f,(float)(-floor_size + shape_size/2),20.0f };
Shape solid = Shape(pt_1, Type::Cube, shape_size, false);
Shape wire = Shape(pt_2, Type::Cube, shape_size, true);

int x_angle = 0;
int y_angle = 0;
int z_angle = 0;
////////////////////////////////////////////






void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]Q14"); // ������ ���� (������ �̸�)
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

		glRotatef(x_angle, 1, 0, 0);
		glRotatef(y_angle, 0, 1, 0);
		glRotatef(z_angle, 0, 0, 1);
		//

		DrawAxis();
		
		//////////////////<�ٴ�>////////////////////
		DrawFloor();
		
		glColor4f(1.0,1.0,1.0,1.0);
		glutWireCube(floor_size*2);
		
		solid.Rander();
		wire.Rander();
	
	
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
	gluLookAt(0.0, 0.0, -300, 		0.0, 0.0, -1.0, /* z���� ũ��� ���� ��� X */		0.0, 1.0, 0.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1') {
		solid.ChangeType(Type::Cube);
		wire.ChangeType(Type::Cube);
	}
	if (key == '2') {
		solid.ChangeType(Type::Sphere);
		wire.ChangeType(Type::Sphere);
	}
	if (key == '3') {
		solid.ChangeType(Type::Cone);
		wire.ChangeType(Type::Cone);
	}
	if (key == '4') {
		solid.ChangeType(Type::Teapot);
		wire.ChangeType(Type::Teapot);
	}
	if (key == 'l' || key == 'L') {
		solid.ChangeAngle(Rotate_Speed);
		//wire.ChangeAngle(Rotate_Speed);
	}
	if (key == 'r' || key == 'R') {
		//solid.ChangeAngle(-Rotate_Speed);
		wire.ChangeAngle(-Rotate_Speed);
	}
	if (key == 'x') {
		x_angle--;
	}
	if (key == 'X') {
		x_angle++;
	}
	if (key == 'y') {
		y_angle--;
	}
	if (key == 'Y') {
		y_angle++;
	}
	if (key == 'z') {
		z_angle--;
	}
	if (key == 'Z') {
		z_angle++;
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

		glVertex3f(floor_size, -floor_size, -floor_size);
		glVertex3f(-floor_size, -floor_size, -floor_size);
		glVertex3f(-floor_size, -floor_size, floor_size);
		glVertex3f(floor_size, -floor_size, floor_size);

		glVertex3f(floor_size, -floor_size - 2, -floor_size);
		glVertex3f(-floor_size, -floor_size - 2, -floor_size);
		glVertex3f(-floor_size, -floor_size - 2, floor_size);
		glVertex3f(floor_size, -floor_size - 2, floor_size);

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
