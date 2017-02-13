#include<iostream>
#include<gl/glut.h>
#include<ctime>
#include"Vec3D.h"
#include"Camera.h"
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


class Bound_Box {
public:
	int m_left{};
	int m_right{};
	int m_top{};
	int m_bottom{};
	int m_near{};
	int m_far{};
public:
	void Rander() {
		glPushMatrix();
		glColor3f(1.0,0.0,0.0);
		glScalef(m_right - m_left, 10, m_far - m_near);
		glutWireCube(1);

		glPopMatrix();
	}
	void SetBB(Vec3f pt, Vec3i size) {
		m_left = pt.x - size.x;
		m_right = pt.x + size.x;

		m_top = pt.y - size.y;
		m_bottom = pt.y + size.y;

		m_near = pt.z - size.z;
		m_far = pt.z + size.z;

	}
	bool CollisionCheck(Bound_Box bb2) {
		if (m_left > bb2.m_right) return false;
		if (m_right < bb2.m_left) return false;
		if (m_far < bb2.m_near) return false;
		if (m_near > bb2.m_far) return false;
		return true;
	}

};

class Gate {
private:
	float m_size{15};
	float m_gatesize{ 15 };
	int alphasize{};
	int angle{};
	Vec3f m_pt{0.0f,m_size/2,0.0f};
	Bound_Box bb{};
public:
	void Rander() {
		
		glPushMatrix(); 
		{
			
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);

			glColor3f(0.2, 0.2, 0.1);

			glPushMatrix();
			{
				
				glTranslatef(-m_gatesize, m_size, 0);
				glScalef(1, 3, 1);
				glutSolidCube(m_size);
				glTranslatef(m_gatesize * 2, 0, 0);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glTranslatef(0, m_size *2, 0);
			glScalef(1+m_gatesize/8,1,1);
			glutSolidCube(m_size);
		}
		glPopMatrix();


	}
	void Update() {
		(++alphasize) %= 180;
		bb.SetBB(m_pt, {m_size*1.5f,0.0f,m_size/2});
		m_gatesize = max(m_size/2,m_size/2 + sin((float)alphasize*PI / 180.0)*m_size/2);
	}

};
class SquareTree {
private:
	float m_size{ 15 };
	int angle{};
	Vec3f m_pt{-floor_size/2,0.0f,-floor_size/2};
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			
			
			
			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.5, 0.5, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glColor3f(0.0,0.7,0.1);
			glTranslatef(0, m_size*3, 0);
			glRotatef(angle, 0, 1, 0);
			glScalef(m_size/2, 1, m_size/2);
			glutSolidCube(m_size/2);
			
		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 360;
		bb.SetBB(m_pt, { m_size/2,0.0f,m_size/2 });
	}
};
class RoundTree {
private:
	float m_size{ 10 };
	float m_leafsize{10};
	int angle{};
	Vec3f m_pt{ floor_size / 2,0.0f,-floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);



			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.5, 0.5, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glColor3f(0.0, 0.7, 0.1);
			glTranslatef(0, m_size * 3, 0);
			glRotatef(angle, 0, 1, 0);
			glutWireSphere(m_leafsize,10,10);

		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 180;
		bb.SetBB(m_pt, { m_size / 2,0.0f,m_size / 2 });
		m_leafsize = max(m_size, m_size + sin((float)angle*PI / 180.0)*m_size);

	}
};
class Elevator {
private:
	float m_size{ 15 };
	int angle{};
	Vec3f m_pt{ floor_size / 2,0.0f,floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glPushMatrix();
			{
				glTranslatef(0, m_size*1.5, 0);

				glScalef(1, 3, 1);
				glColor3f(0.9, 0.1, 0.5);
				glutSolidCube(m_size);
			}
			glPopMatrix();

			glTranslatef(0, m_size*2 + sin(angle*PI / 180)*m_size, 0);
			glRotatef(90,1,0,0);
			glColor3f(0.9, 0.1, 0.9);
			glutWireTorus(m_size/3,m_size,10,10);

		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 360;
	}
};
class ConeBuilding {
private:
	float m_size{ 25 };
	float m_topsize{};
	float m_bottomsize{};

	int angle{};
	Vec3f m_pt{ -floor_size / 2,0.0f,floor_size / 2 };
	Bound_Box bb;
public:
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glColor3f(0.2,0.7,1.0);
			glPushMatrix();
			{
			glRotatef(270,1,0,0);
			glutWireCone(m_bottomsize, m_bottomsize,10,10);
			}
			glPopMatrix();

			glTranslatef(0, m_bottomsize+ m_topsize, 0);
			glRotatef(90,1,0,0);
			glutWireCone(m_topsize, m_topsize, 10, 10);
		}
		glPopMatrix();
	}
	void Update() {
		(++angle) %= 180;
		bb.SetBB(m_pt, { m_size,0.0f,m_size});
		m_bottomsize = sin(angle*PI/180)*m_size;
		m_topsize = m_size - m_bottomsize;
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
////////////////////////////////////////////
CCamera camera;

Gate gate;
SquareTree squaretree;
RoundTree roundtree;
Elevator elevator;
ConeBuilding cone;

int height[4] = { 0,0,0,0 };

float points[3][4][3] = {
{
	{ -floor_size,		height[0],-floor_size },
	{ -floor_size / 2 ,	height[1],-floor_size },
	{ floor_size / 2,	height[2],-floor_size },
	{ floor_size,		height[3],-floor_size }
},
{
	{ -floor_size,		height[0],0 },
	{ -floor_size / 2,	height[1],0 },
	{ floor_size / 2,	height[2],0 },
	{ floor_size,		height[3],0 }
},
{
	{ -floor_size,		height[0],floor_size },
	{ -floor_size / 2,	height[1],floor_size },
	{ floor_size / 2,	height[2],floor_size },
	{ floor_size,		height[3],floor_size }
}

};



void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]Q26"); // ������ ���� (������ �̸�)
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



	camera.Rander();
	

	glPushMatrix();
	{




		DrawAxis();

		//////////////////<�ٴ�>////////////////////
		//DrawFloor();

		glColor4f(1.0, 1.0, 1.0, 1.0);
		glutWireCube(floor_size * 2);

		gate.Rander();
		squaretree.Rander();
		roundtree.Rander();
		elevator.Rander();
		cone.Rander();


		glMap2f(GL_MAP2_VERTEX_3,
			0.0, 1.0, 3, 4,
			0.0, 1.0, 12, 3, 
			&points[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// �׸��带 �̿��� ��� �����
		glMapGrid2f(10, 0.0, 1.0,
					10, 0.0, 1.0);

		// ���� �̿��Ͽ� �׸��� ����
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);

		glColor3f(0.0, 0.0, 1.0);
		glPointSize(10.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 4; j++)
				glVertex3fv(points[i][j]);
		glEnd();


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

		if (key == '+') {
			camera.HandleDistance(10);
		}
		if (key == '-') {
			camera.HandleDistance(-10);
		}


		if (key == 'q' || key == 'Q') {
			height[0]++;
		}
		if (key == 'w' || key == 'W') {
			height[1]++;
		}
		if (key == 'e' || key == 'E') {
			height[2]++;
		}
		if (key == 'r' || key == 'R') {
			height[3]++;
		}

		if (key == 'a' || key == 'A') {
			height[0]--;
		}
		if (key == 's' || key == 'S') {
			height[1]--;
		}
		if (key == 'd' || key == 'D') {
			height[2]--;
		}
		if (key == 'f' || key == 'F') {
			height[3]--;
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
	camera.Update();

	gate.Update();
	squaretree.Update();
	roundtree.Update();
	elevator.Update();
	cone.Update();


	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			points[i][j][1] = height[j];
		}
	}


	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
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
		glScalef(2, 0.01, 2);

		{
			glutSolidCube(floor_size);

		}
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
