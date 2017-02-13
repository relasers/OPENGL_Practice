#pragma once
#include <iostream>
#include <gl/glut.h>
#include "Scene.h"
#include "LobbyScene.h"
#include "TitleScene.h"

class CScene;

template<typename Ty>
struct Point2D {
	Ty x, y;
};

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;

template<typename Enum>				// Enum class�� �������� �˷��־� ���ڿ� �����ϴ� ���� ��ȯ�ϴ� �Լ��Դϴ�.
inline constexpr auto GetEnumValueByType(Enum enumerator) noexcept	// enum class E : int { a,b,c }; �� ��,
{																	// auto data = GetEnumValueByType(E::a);
	return static_cast<std::underlying_type_t<Enum>>(enumerator);	// data�� ������ int �̰�, ���� 0 �Դϴ�.
}

#define GetSceneEnumInt(Enum) GetEnumValueByType(CScene::CurrentScene::Enum)

class CGLFramework
{
private:
	
	char	m_szTile[64]	= "Tutering Sample_2016_2";
	Point2i m_ptWindowPos	{ 100,100 };
	Point2i m_ptWindowSize	{ 800,600 };
	int		m_iFPS			= 16;

	CScene			*m_pCurrentScene;
	CScene			*m_arrScene[GetEnumValueByType(CScene::CurrentScene::Count)];

	void	(*m_pfReshape)(int w, int h)							{ nullptr } ;
	void	(*m_pfDrawScene)()										{ nullptr } ;
	void	(*m_pfTimer)(int val)									{ nullptr } ; // �Լ� ������
	void	(*m_pfInputKey)(unsigned char key, int x, int y)		{ nullptr } ;
	void	(*m_pfInputMouse)(int button, int state, int x, int y)	{ nullptr } ;

public:

	CGLFramework() = default;
	~CGLFramework() = default;
	
public:

	GLvoid Initialize(GLvoid);

	GLvoid Reshape(int w, int h);
	GLvoid drawScene(GLvoid);
	GLvoid Timer(int val);
	GLvoid InputKeyboard(unsigned char key,int x,int y);
	GLvoid InputMouse(int button,int state,int x,int y);
	
	GLvoid Run();

	void SetReshapeFunc			(void(*func)(int, int))	{ m_pfReshape = func; }
	void SetDrawFunc			(void(*func)())			{ m_pfDrawScene = func; }
	void SetTimerFunc			(void(*func)(int))		{ m_pfTimer = func; }
	void SetInputKeyboardFunc	(void(*func)(unsigned char, int, int)) { m_pfInputKey = func; }
	void SetInputMouseFunc		(void(*func)(int, int, int, int)) { m_pfInputMouse = func; }

	void ChangeScene(CScene::CurrentScene tag, bool bDestroy = false);
};

