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
constexpr float floor_size = 240.0;

constexpr int Rotate_Speed = 10;
constexpr int BuildingNum = 5;

enum Direction {
	Left, Right, Stay
};

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

		glScalef(m_right - m_left, m_top - m_bottom, m_far - m_near);
		glutWireCube(1);

		glPopMatrix();
	}
	void SetBB(Vec3f pt, Vec3i size) {
		m_left = pt.x - size.x;
		m_right = pt.x + size.x;

		m_bottom = pt.y - size.y;
		m_top = pt.y + size.y;

		m_near = pt.z - size.z;
		m_far = pt.z + size.z;

	}
	bool CollisionCheck(Bound_Box bb2) {
		if (m_left > bb2.m_right) return false;
		if (m_right < bb2.m_left) return false;
		if (m_far < bb2.m_near) return false;
		if (m_near > bb2.m_far) return false;
		if (m_bottom > bb2.m_top) return false;
		if (m_top < bb2.m_bottom) return false;
		return true;
	}

};
class Particle {
private:
	Vec3f m_pt;
	Vec3f m_direction;
	float m_speed;
	int m_lifetime{100};
public:
	Particle(Vec3f pt) {
		m_pt = pt;
		Vec3f dir{ -floor_size + float(rand() % (int)floor_size * 2),-floor_size + float(rand() % (int)floor_size * 2),-floor_size + float(rand() % (int)floor_size * 2) };
		m_direction = dir - m_pt;
		Normalize(m_direction);
		m_speed = 1 + rand() % 10;
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			glColor3f(rand() % 10 * 0.1f , rand() % 10 * 0.1f, rand() % 10 * 0.1f);
			glRotatef(rand()%360,1,1,1);
			glutWireCube(m_lifetime*0.6);
			glutSolidSphere(m_lifetime*0.3,6,6);
		}
		glPopMatrix();
	}
	void Update() {
		m_lifetime--;
		m_pt += m_direction*m_speed;
		m_speed = max(1, m_speed - 0.01);
	}

	int GetLife() { return m_lifetime; }
};



class Car {
private:
	Vec3f m_pt{};
	Bound_Box bb{};


	int dir = 1;
	int speed = 1;
	int base_angle{ 90 };
	int m_wheel_angle{};

	int m_jumper_angle{};
	int m_xdir{};
	float m_jump_gravity{};


	int m_size = 30;
	float m_wheelsize = 5;

	bool m_isalive = true;
	bool m_is_jumped = false;

public:
	void Rander() {

		glPushMatrix();
		{
			glTranslatef(m_pt.x, m_pt.y, m_pt.z);
			glTranslatef(0, m_wheelsize*2.5, 0);
			glRotatef(base_angle, 0, 1, 0);

			if (m_is_jumped)
				glRotatef(m_jumper_angle, 1, 0, 0);

			glColor3f(1.0, 0, 0);

			bb.Rander();

			////<��ü>////
			glPushMatrix();
			{
				glScalef(1, 0.5, 1);
				DrawCube(m_size, 1, true); // base
				glTranslatef(0, m_size*0.5, 0);
				DrawCube(m_size*0.5, 1, true);
			}
			glPopMatrix();
			////<����>////
			glPushMatrix();
			{
				glColor3f(0.5, 0.8, 0.8);
				glTranslatef(m_size / 2, -m_wheelsize, -m_size / 2);
				DrawWheel();
				glTranslatef(0, 0, m_size);
				DrawWheel();
				glTranslatef(-m_size, 0, 0);
				DrawWheel();
				glTranslatef(0, 0, -m_size);
				DrawWheel();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	void Update() {


		bb.SetBB(m_pt, { m_size/2 ,m_size,m_size/2});

		m_wheel_angle += dir*speed;

		m_pt.z += dir*speed;

		if (m_is_jumped) {
			m_pt.x += m_xdir*4.34;
			m_pt.y += m_jump_gravity;
			m_jump_gravity--;
			m_jumper_angle += 8 * m_xdir;
			if (m_pt.y < 0 && -floor_size < m_pt.x && m_pt.x < floor_size) {
				m_is_jumped = false;
				m_jumper_angle = 0;
				m_pt.y = 0;
			}
		}


		if (m_pt.z - m_size < -floor_size)
		{
			dir *= -1;
			m_pt.z = -floor_size + m_size;
		}
		if (m_pt.z + m_size > floor_size)
		{
			dir *= -1;
			m_pt.z = floor_size - m_size;
		}
	}

	void DrawCube(float size, int length, bool isbase) {

		glPushMatrix();

		if (isbase)glTranslatef(-size / 2, 0, 0);
		//if(!isbase)glTranslatef(size/2, 0, 0);
		glutSolidCube(size);
		for (int i = 0; i < length; ++i)
		{
			glTranslatef(size, 0, 0);
			glutSolidCube(size);
		}
		glPopMatrix();

	}

	void DrawWheel() {
		glPushMatrix();
		{
			glRotatef(m_wheel_angle, 0, 0, 1);

			glColor3f(0.8, 0.5, 0.7);
			glutSolidTorus(m_wheelsize / 2, m_wheelsize, 10, 10);
			glColor3f(0.2, 0.5, 0.7);
			glLineWidth(6.0);
			glutWireTorus(m_wheelsize / 2, m_wheelsize, 10, 10);
			glLineWidth(1.0);
		}
		glPopMatrix();
	}

	void RotateBase(int x) {
		base_angle += x;
	}

	void Jump(int Direction) {
		m_is_jumped = true;
		m_jump_gravity = 24;
		if (Direction == Direction::Left) {
			m_xdir = -1;
		}
		else if (Direction == Direction::Right)
		{
			m_xdir = 1;
		}
	}
	Vec3f GetPt() { return m_pt; }
	int GetSize() { return m_size; }
	bool GetIsJump() { return m_is_jumped; }
	Bound_Box GetBB() { return bb; }
	bool IsAlive() { return m_isalive; }

	void DeadEnd() { m_isalive = false; }
};

class Building {
private:
	Vec3f m_pt{};
	float m_height{10 + (float)(rand() % 100) };
	float m_size{20.0f+(float)(rand()%50)};
	Bound_Box bb{};
public:
	void Update() {
		bb.SetBB(m_pt, {floor_size/10,m_height/2,m_size/2});
	}
	void Rander() {
		glPushMatrix();
		{
			glTranslatef(m_pt.x,m_pt.y,m_pt.z);
			bb.Rander();
			glScalef(floor_size/5,m_height,m_size);
			glutSolidCube(1);
		}
		glPopMatrix();
	}
	void setpt(Vec3f pt) { m_pt = pt; }
	bool CollisionCheck(Bound_Box car) { return bb.CollisionCheck(car); }

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
void DrawFloor(int, int);

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////////////////////////////////
////////////////////////////////////////////
CCamera camera;
Car car;
Building building[BuildingNum];
//Gate gate;
Vec3f ambiant;
Vec3f specular;
Vec3f diffuse;
list <Particle> part;
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
	glutCreateWindow("[2013182010�躴��]Q34"); // ������ ���� (������ �̸�)
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
	GLfloat AmbientLight[] = { ambiant.x, ambiant.y, ambiant.z, 1.0f };
	GLfloat DiffuseLight[] = { diffuse.x, diffuse.y, diffuse.z, 1.0f };
	GLfloat SpecularLight[] = { specular.x, specular.y, specular.z, 1.0f };
	GLfloat lightPos[] = { car.GetPt().x,120,car.GetPt().z, 1.0f };
	GLfloat LightModel_Ambiant[] = { 0.5,0.5,0.5,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModel_Ambiant);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	GLfloat Ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
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

	GLfloat spot_dir[] = { 0, -1, 0, 1.0f };
	GLfloat spot_cutoff[] = {40.0f };
	GLfloat spot_exponent[] = { 5.0f };

	//GLfloat spot_constant[] = { 0.0f };
	//GLfloat spot_linear[] = { 0.0f };
	//GLfloat spot_quadratic[] = { 0.0f };


	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	//glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, spot_constant);
	//glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, spot_linear);
	//glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, spot_quadratic);

	glEnable(GL_LIGHT0);


	glColor4f(1.0, 1.0, 1.0, 1.0f);



	camera.Rander();


	glPushMatrix();
	{
		glColor3f(1.0, 0.0, 0.0);

		glPushMatrix();
		{
			glTranslatef(car.GetPt().x, 240, car.GetPt().z);
			glutSolidCone(1, 2, 10, 10);
		}
		glPopMatrix();


		DrawFloor(-floor_size, floor_size / 5);
		DrawFloor(-floor_size + floor_size / 5 * 4 + floor_size *0.1, floor_size / 5);
		DrawFloor(floor_size - floor_size / 5, floor_size / 5);
		DrawAxis();

		for (int i = 0; i < BuildingNum; ++i) {
			building[i].Rander();
		}
		for (auto &p : part) p.Rander();

		if(car.IsAlive())
			car.Rander();
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


		if (key == 'a' || key == 'A') {
			if (!car.GetIsJump()) {
				car.Jump(Direction::Left);
				ambiant.x = rand() % 10 * 0.1f;
				ambiant.y = rand() % 10 * 0.1f;
				ambiant.z = rand() % 10 * 0.1f;
				diffuse.x = rand() % 10 * 0.1f;
				diffuse.y = rand() % 10 * 0.1f;
				diffuse.z = rand() % 10 * 0.1f;
				specular.x = rand() % 10 * 0.1f;
				specular.y = rand() % 10 * 0.1f;
				specular.z = rand() % 10 * 0.1f;
			}
		}
		if (key == 'd' || key == 'D') {
			if (!car.GetIsJump()) {
				car.Jump(Direction::Right);
				ambiant.x = rand() % 10 * 0.1f;
				ambiant.y = rand() % 10 * 0.1f;
				ambiant.z = rand() % 10 * 0.1f;
				diffuse.x = rand() % 10 * 0.1f;
				diffuse.y = rand() % 10 * 0.1f;
				diffuse.z = rand() % 10 * 0.1f;
				specular.x = rand() % 10 * 0.1f;
				specular.y = rand() % 10 * 0.1f;
				specular.z = rand() % 10 * 0.1f;
			}
		}
		if (key == 'w' || key == 'W') {
			if (!car.GetIsJump()) {
				car.Jump(Direction::Stay);
				ambiant.x = rand() % 10 * 0.1f;
				ambiant.y = rand() % 10 * 0.1f;
				ambiant.z = rand() % 10 * 0.1f;
				diffuse.x = rand() % 10 * 0.1f;
				diffuse.y = rand() % 10 * 0.1f;
				diffuse.z = rand() % 10 * 0.1f;
				specular.x = rand() % 10 * 0.1f;
				specular.y = rand() % 10 * 0.1f;
				specular.z = rand() % 10 * 0.1f;
			}

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
	for (int i = 0; i < BuildingNum; ++i) {
		building[i].Update();
	}
	car.Update();

	if(car.IsAlive())
	for (int i = 0; i < BuildingNum; ++i) {
		if (building[i].CollisionCheck(car.GetBB()))
		{
			car.DeadEnd();
			for (int j = 0; j < 50; ++j)
				part.push_back(Particle(car.GetPt()));
		}
		
	}

	for (auto &p : part) p.Update();
	part.remove_if([](auto& data) -> bool {
		return (data.GetLife() <= 0);
	});

	(++lightangle) %= 360;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));

	building[0].setpt({-floor_size+floor_size*0.1,0,floor_size/2});
	building[1].setpt({ -floor_size + floor_size*0.1,0,-floor_size/2 });
	building[2].setpt({ 0,0,floor_size });
	building[3].setpt({ floor_size - floor_size*0.1,0,floor_size/2 });
	building[4].setpt({ floor_size - floor_size*0.1,0,-floor_size/2 });
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

void DrawFloor(int left, int length)
{
	glPushMatrix();
	{
		glColor4f(0.2, 0.5, 0.2, 1.0f);
		glBegin(GL_QUADS);
		if (is_normal)glNormal3f(0, 1, 0);

		int grid = 100;
		for (int i = 0; i < grid; ++i) {
			for (int j = 0; j < grid; ++j) {
				glVertex3d(i*length / grid + left, 0,
					j*floor_size * 2 / grid - floor_size);
				glVertex3d(i*length / grid + left, 0,
					(j + 1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i + 1)*length / grid + left, 0,
					(j + 1)*floor_size * 2 / grid - floor_size);
				glVertex3d((i + 1)*length / grid + left, 0,
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
