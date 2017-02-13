#include"stdafx.h"

using namespace std;

//////////////<�⺻ �Լ�>//////////////////////////
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
//////////////////////////////////////////////////
void InitObjects();
///////////////<��ü��>//////////////////////////

int tick = 0;
int notespeed = 1;
CLine line[Number_Line];
CScore score;
CShape mainshape;
list <CNote> note;

/////////////////////////////////////////////

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	InitObjects();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("[2013182010�躴��]PROJECT_1"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutTimerFunc(10, TimerFunction, 1);
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
	for (int i = 0; i < Number_Line; ++i) {
		line[i].draw();
	}
	

	for (auto &p : note)
	{
		p.Draw();
	}
	mainshape.Draw();
	score.Draw();




	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glutReshapeWindow(Window_Width, Window_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);
	glViewport(0, 0, Window_Width, Window_Height);
}

void Keyboard(unsigned char key, int x, int y)
{
	/////////////////<�ݻ�>/////////////////////////
	if (key == 'q')
	{
		mainshape.Reflect(Direction::Left);
	}
	if (key == 'e')
	{
		mainshape.Reflect(Direction::Plus);
	}
	/////////////////<�¿��̵�>/////////////////////////
	if (key == 'a')
	{
		mainshape.InputKeyBoard(Direction::Left);
	}
	if (key == 'd')
	{
		mainshape.InputKeyBoard(Direction::Right);
	}
	/////////////////<Ȯ�� ���>/////////////////////////
	if (key == 'w')
	{
		mainshape.InputKeyBoard(Direction::Plus);
	}
	if (key == 's')
	{
		mainshape.InputKeyBoard(Direction::Minus);
	}
	////////////////////<���ε��� ��纯��>//////////////////////////////////
	if (key == 'j')
	{
		mainshape.Reshape(3);
	}
	if (key == 'i')
	{
		mainshape.Reshape(4);
	}
	if (key == 'o')
	{
		mainshape.Reshape(5);
	}
	if (key == 'p')
	{
		mainshape.Reshape(6);
	}
	/////////////////<���� ����>/////////////////////////////////////////////
	if (key == 'x')
	{
		int moveval = Window_Width / (Number_Line + 1);
		POINT temp = { (moveval / 2) + rand() % 5 * moveval,Window_Height };
		note.push_front(
			CNote(temp, 3 + rand() % 4,notespeed)
		);
	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		POINT temp{ x,Window_Height - y };


	}// ��Ŭ�� :: �簢�� ����

}

void TimerFunction(int value)
{
	(++tick)%= 10000;

	if (tick % 100 == 0) {
		int moveval = Window_Width / (Number_Line + 1);
		POINT temp = { (moveval / 2)+rand()%5*moveval,Window_Height };
		note.push_front(
			CNote(temp,3+rand()%4,notespeed)
			);
	}

	if (tick % 1000 == 0) {
		notespeed = 1+rand()%3;
		for (auto &p : note)
		{
			p.SpeedChange(notespeed);
		}
	}



	mainshape.Update();
	for (auto &p : note)
	{
		p.Update();
	}


	for (auto &p : note)
	{
		p.Update();
		if(p.Check(mainshape.GetPoint(),mainshape.GetSize(), mainshape.GetNVertex()))
			score.GainScore();
	}

	if (score.GetScore() > MaxScore) {
		InitObjects();
	}

	note.remove_if([](auto& data) -> bool {
		return (data.IsOut());
	});
	
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void InitObjects()
{
	srand((unsigned)time(nullptr));
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);
	for (int i = 0; i < Number_Line; ++i) {
		line[i] = CLine(
			i,
			Number_Line,
			Window_Width, 
			Window_Height);
	}
	note.clear();
	score = CScore();
	POINT temp = { 50,50 };
	mainshape = CShape(temp,5);

}
