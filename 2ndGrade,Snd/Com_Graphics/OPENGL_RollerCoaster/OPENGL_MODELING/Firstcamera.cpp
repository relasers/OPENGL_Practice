#pragma once
#include "Firstcamera.h"
#include <cmath>
#include <gl/glut.h>

CFirstcamera::CFirstcamera()
{
}


CFirstcamera::~CFirstcamera()
{
}

void CFirstcamera::Rander()
{
	glLoadIdentity(); // ī�޶� ������ �ʱ�ȭ

					  //���Ͽ� ���� ���� ������ ����

	gluLookAt(m_Eye.x, m_Eye.y, m_Eye.z,	// Eye
		m_At.x, m_At.y, m_At.z,					// At
		m_Up.x, m_Up.y, m_Up.z);		// Up


}

bool CFirstcamera::Update()
{
	return false;
}
