#include "Scene.h" // �ڱ� �ڽ��� ���� �������� ��Ŭ����Ѵ�.
CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
}

void CScene::Rander()
{
}

void CScene::InputKeyboard(unsigned char key, int x, int y)
{
}

void CScene::InputMouse(int button, int state, int x, int y)
{
}

void CScene::BuildScene(CGLFramework * pFramework, CurrentScene tag)
{
	m_pMasterFramework = pFramework;
	m_iTag = tag;
}
