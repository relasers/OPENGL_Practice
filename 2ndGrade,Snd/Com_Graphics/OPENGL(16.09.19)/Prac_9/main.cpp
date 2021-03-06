#include<iostream>
#include <cstdlib>
#include <chrono>
#include <glut.h>
#include <list>
#include <Windows.h>
#include "Madurai.h"
#include"Vec2D.h"

using namespace std;

constexpr int Window_Width = 800;
constexpr int Window_Height = 600;
constexpr int Max_Ractangle = 50;

list <CMadurai> madurai;
list<CMadurai>::iterator itor = madurai.begin();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

void main(int argc, char *argv[])
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("Prac_10"); // 윈도우 생성 (윈도우 이름)


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(1, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop();


}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
								  // 색상 지정하고 사각형 그리기
	glEnable(GL_BLEND);

	glColor4f(0.0, 0.0, 0.0, 0.5f);
	glRectf(0, 0, Window_Width, Window_Height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
	

	for (itor = madurai.begin(); itor != madurai.end(); itor++)
	{
		itor->Draw();
	}

	glDisable(GL_BLEND);

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, Window_Width, 0.0, Window_Height, -1.0, 1.0);

}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '+')
	{
		for (itor = madurai.begin(); itor != madurai.end(); itor++)
		{
			itor->IncreaseSpd();
		}
	}
	if (key == '-')
	{
		for (itor = madurai.begin(); itor != madurai.end(); itor++)
		{
			itor->DecreaseSpd();
		}
	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		POINT temp{ x,Window_Height - y };
			if (madurai.size() >= Max_Ractangle) madurai.pop_back();
			madurai.push_front(CMadurai(temp));
	}// 왼클릭 :: 사각형 생성

}

void TimerFunction(int value)
{

	for (itor = madurai.begin(); itor != madurai.end(); itor++)
	{
		itor->Update(Window_Width, Window_Height);
	}



	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, TimerFunction, 1); // 타이머함수 재 설정
}
