#include<iostream>
#include<gl/glut.h>
#include<deque>
#include<Windows.h>
#include<chrono>
#include<cmath>
#include"Vec3D.h"
using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 800;
constexpr int Base_Size = 200;
constexpr float PI = 3.141592;





enum DrawMode {
	Circle = 0, Sin, Cos, ZigZag, Free, Spring
};

class Points {
public:
	Vec3f m_pt;
	int index;
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
GLvoid DrawShape();
void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
void DrawRactangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis);
///////////////<����>//////////////////////////
deque<Points> free_point;




int mode = DrawMode::Circle;

Vec3f t_point{0,0,0};
Vec3f t_size{0,0,0};
Vec3f t_axis{0,0,1};
int t_angle = 0;	// �ﰢ�� ����
int t_alphasize = 0;
int t_currindex = 0;


bool dir = true; // true == �Ʒ�, false = ��

bool is_sizeud = true;
bool shape = true;
bool is_trispin = false;	// �ﰢ�� ���� �ϴ���?
bool is_move = false;
/////////////////////////////////////////////







void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]Q12"); // ������ ���� (������ �̸�)
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
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
								  // ���� �����ϰ� �簢�� �׸���

	glColor4f(1.0, 1.0, 1.0, 1.0f);

	/////////////<��ǥ�� �׸�>//////////////////
	glBegin(GL_LINES);
	glVertex2f(-400.0, 0.0);
	glVertex2f(400.0, 0.0);
	glVertex2f(0.0, -400.0);
	glVertex2f(0.0, 400.0);
	glEnd();
	//////////////////////////////////////////
	glLoadIdentity();

	
	
	////////////////<����>////////////////////
	glPushMatrix();
	////////////////////////////////////
	switch (mode) {
		case DrawMode::Circle: 
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 360; ++i) {
				glVertex3f(cos(i*PI/180.0)*Base_Size, sin(i*PI / 180.0) * Base_Size,0);
			}
			glEnd();

			DrawShape();
			
			break;
		}
		case DrawMode::Sin: 
		{
			glBegin(GL_LINE_STRIP);
			for (int i = -360; i < 360; ++i) {
				glVertex3f(i, sin(i*PI / 180.0) * Base_Size, 0);
			}
			glEnd();

			DrawShape();
			break;
		}
		case DrawMode::Cos:
		{
			glBegin(GL_LINE_STRIP);
			for (int i = -360; i < 360; ++i) {
				glVertex3f(i, cos(i*PI / 180.0) * Base_Size, 0);
			}
			glEnd();
			DrawShape();
			break;
		}
		case DrawMode::ZigZag:
		{
			glBegin(GL_LINE_STRIP);
			for (auto p : free_point) {
				glVertex2f(p.m_pt.x, p.m_pt.y);
			}
			glEnd();

			DrawShape();
			break;
		}
		case DrawMode::Free:
		{
			glBegin(GL_LINE_STRIP);
			for (auto p : free_point) {
				glVertex2f(p.m_pt.x, p.m_pt.y);
			}
			glEnd();

			if (free_point.size() != 0) {
				DrawShape();
			}
			break;
		}
		case DrawMode::Spring:
		{

			glBegin(GL_LINE_STRIP);
			for (int i = -600; i < 600; ++i) {
				glVertex3f(cos(3.1415927 / 180 * (i)) * Base_Size/1.5 + i*0.5, sin(3.1415927 / 180 * (i)) * Base_Size/1.5, 0);
			}
			glEnd();

			DrawShape();


			break;
		}
	}


	
	////////////////////////////////////
	glPopMatrix();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ� (glflushȿ���� �ִ�.)
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400.0, 400, -400.0, 400, -400.0, 400.0); // x�� �ּ�,�ִ�, y�� �ּ�,�ִ�, z�� �ּ� �ִ�
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '0') {
		t_angle = 0;
		mode = DrawMode::Circle;
	}	// ���׷���

	if (key == '1') {
		t_angle = 0;
		mode = DrawMode::Sin;
	}	// ����

	if (key == '2') {
		t_angle = 0;
		mode = DrawMode::Cos;
	}	// �ڻ���

	if (key == '3') {
		t_angle = 0;

		free_point.clear();

		for (int i = -10; i < 10; ++i) {
			if(i%2 == 0)
			free_point.push_back({ {i*20,200,0},i+10 });
			else
			free_point.push_back({ { i * 20,-200,0 },i });

		}

		t_point.x = free_point.at(0).m_pt.x;
		t_point.y = free_point.at(0).m_pt.y;
		t_currindex = 0;

		mode = DrawMode::ZigZag;
	}	// �������

	if (key == '4') {
		t_angle = 0;
		is_move = false;
		free_point.clear();
		mode = DrawMode::Free;
	}	// ����


	if (key == '5') {
		t_angle = 0;
		mode = DrawMode::Spring;
	}	// ������

	if (key == 'z' || key == 'Z') {
		is_sizeud = 1 - is_sizeud;
	}	// Ȯ�� ���?
	if (key == 'x' || key == 'X') {
		is_trispin = 1 - is_trispin;
	}	// ���� ���ư�?
	if (key == 'c' || key == 'C') {
		shape = 1 - shape;
	}	// �������?
	if (key == 'q' || key == 'Q') {
		exit(0);
	}	// ����
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Vec3f temp{ x-400,Window_Height - y - 400,0 };

		if (mode == DrawMode::Free) {
			is_move = false;
			if (free_point.size() == 0) {
				t_point.x = temp.x;
				t_point.y = temp.y;
			}

			free_point.push_back({temp,0});
			if (free_point.size() > 6) {


				if (t_currindex == 0) {
					t_point.x = free_point.at(1).m_pt.x;
					t_point.y = free_point.at(1).m_pt.y;
				}

				free_point.pop_front();
			}

			if (free_point.size() != 0) {
				t_point.x = free_point.at(0).m_pt.x;
				t_point.y = free_point.at(0).m_pt.y;
			}

		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (mode == DrawMode::Free) {
			is_move = true;
			t_currindex = 0;

			if (free_point.size() != 0) {
				t_point.x = free_point.at(0).m_pt.x;
				t_point.y = free_point.at(0).m_pt.y;
			}
			
		}
		
	}

}

void TimerFunction(int value)
{



	if (is_sizeud) {
		for (int i = 0;i<3;++i)(++t_alphasize) %= 360;
		t_size.x = 100 + sin(t_alphasize*3.141592 / 180) * 70;
		t_size.y = 100 + sin(t_alphasize*3.141592 / 180) * 70;
	}
	

	switch (mode) {
	case DrawMode::Circle:
	{
		(++t_angle) %= 360;
		t_point.x = cos(t_angle*PI / 180.0) * Base_Size;
		t_point.y = sin(t_angle*PI / 180.0) * Base_Size;
		break;
	}
	case DrawMode::Sin:
	{
		(++t_angle) %= 720;
		t_point.x = t_angle-360;
		t_point.y = sin((t_angle-360)*PI / 180.0)*Base_Size;
		break;
	}
	case DrawMode::Cos:
	{
		(++t_angle) %= 720;
		t_point.x = t_angle - 360;
		t_point.y = cos((t_angle - 360)*PI / 180.0)*Base_Size;
		break;
	}
	case DrawMode::ZigZag:
	{
		(++t_angle) %= 720;
		int i = 0;
		Vec3f target{0,0,0};
		for (auto p : free_point) {
			p.index = i;
			++i;
		}

		if (t_currindex != 20)
		{
			target.x = free_point.at(t_currindex + 1).m_pt.x;
			target.y = free_point.at(t_currindex + 1).m_pt.y;
			target.z = free_point.at(t_currindex + 1).m_pt.z;

		}
		Vec3f force{ target.x - t_point.x, target.y - t_point.y,  target.z - t_point.z };
		force.Normalize();
		t_point += force*5;

		if (t_point.x >= target.x) {
			t_currindex++;
			t_point = target;
			if (t_currindex == 19) {
				t_currindex = 0;
				t_point = free_point.at(0).m_pt;
			}
		}


		break;
	}
	case DrawMode::Free:
	{	
		int i = 0;
		(++t_angle) %= 720;
		Vec3f target{ 0,0,0 };
		for (auto p : free_point) {
			p.index = i;
			++i;
		}

		if (t_currindex != free_point.size())
		{
			if (free_point.size() > 1) {
				if (free_point.size() >= t_currindex) {
					target.x = free_point.at(t_currindex + 1).m_pt.x;
					target.y = free_point.at(t_currindex + 1).m_pt.y;
					target.z = free_point.at(t_currindex + 1).m_pt.z;

				}
				}
			

		}
		Vec3f force{ target.x - t_point.x, target.y - t_point.y,  target.z - t_point.z };
		force.Normalize();

		if (free_point.size() > 1 && is_move == true) {
		
			for (int i = 0; i < 16; ++i) {
				Vec3f temp;
				temp = force;
				temp.Divide(16);
				t_point += temp;

				if (t_point == target) {
					t_currindex++;
					t_point = target;
					break;
				}
			}
		
		}

		if (t_currindex >= free_point.size()-1 && free_point.size() != 0) {
			t_currindex = 0;
			t_point = free_point.at(0).m_pt;
		}

		break;
	}


	case DrawMode::Spring:
	{
		(++t_angle) %= 1200;

		t_point.x = cos(3.1415927 / 180 * (t_angle-600)) * Base_Size / 1.5 + (t_angle - 600 )*0.5;
		t_point.y = sin(3.1415927 / 180 * (t_angle - 600)) * Base_Size / 1.5;

		break;
	}


	}



	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));


}

void DrawTriangle(Vec3f Position, Vec3f Size, int angle, Vec3f axis)
{
	glPushMatrix();

	glTranslatef(Position.x,Position.y,Position.z);
	glRotatef(angle,axis.x,axis.y,axis.z);

	glBegin(GL_LINE_LOOP);
	glVertex3f((Size.x) / 2, -Size.y / 2, Size.z);
	glVertex3f(-Size.x / 2, -Size.y / 2, Size.z);
	glVertex3f(0.0, Size.y/2, Size.z);
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
/*

*/
GLvoid DrawShape() {


	if (shape) {
		if (is_trispin)DrawTriangle(t_point, t_size, t_angle, t_axis);
		if (!is_trispin)DrawTriangle(t_point, t_size, 0, t_axis);
	}
	if (!shape) {
		if (is_trispin)DrawRactangle(t_point, t_size, t_angle, t_axis);
		if (!is_trispin)DrawRactangle(t_point, t_size, 0, t_axis);
	}

}