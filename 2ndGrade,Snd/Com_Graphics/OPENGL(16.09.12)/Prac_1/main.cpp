#include <glut.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
								  // ���� �����ϰ� �簢�� �׸���
	
	glColor4f(0.0f, 1.0f, 0.5f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-1.0f, 1.0f, -0.7f, 0.7f); // �簢�� �׸���
	
	glColor4f(1.0f, 1.0f, 0.2f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(0.7f, 1.0f, 1.0f, 0.7f);

	glColor4f(0.7f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-0.3f, 0.3f, 0.3f, -0.3f);

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-1.0f, -1.0f, -0.7f, -0.7f);

	glColor4f(0.0f, 0.5f, 0.6f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(0.7f, -1.0f, 1.0f, -0.7f);

	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
