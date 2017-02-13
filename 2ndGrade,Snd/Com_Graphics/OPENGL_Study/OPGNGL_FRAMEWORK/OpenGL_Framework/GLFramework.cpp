#include "GLFramework.h"



GLvoid CGLFramework::Initialize(GLvoid)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(m_ptWindowPos.x, m_ptWindowPos.y); // �������� ��ġ����
	glutInitWindowSize(m_ptWindowSize.x, m_ptWindowSize.y); // �������� ũ�� ����
	glutCreateWindow(m_szTile); // ������ ���� (������ �̸�)
	
	glutTimerFunc(m_iFPS, ::TimerFunction, 1);

	glutDisplayFunc(::drawScene); // ��� �Լ��� ����
	glutReshapeFunc(::Reshape); // �ٽ� �׸��� �Լ��� ����
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_ptWindowSize = Point2i{ w,h };

	glViewport(0, 0, w, h);
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}

GLvoid CGLFramework::TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(m_iFPS,::TimerFunction,1); //::TimerFunction -> �����̶� ����Ѵ�.
}

GLvoid CGLFramework::Run()
{
	glutMainLoop();
}
