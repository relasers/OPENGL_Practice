#include <iostream>
#include <Windows.h>
using namespace std;

class CFramework {
private:
	int count{ 0 }; // ���� �ʱ�ȭ
public:
	void Draw();
	void Update();

	void Run();
};

// namespace�� �̸��� �� �پ����� �� :: �� cpp ���� �������� ����� �����ϴ�
// �͸� namespace,��� :: static
// �������� ����ϱ� ���� �� 
namespace {
	CFramework framework;
};

int main() {
	framework.Run();
}

void CFramework::Draw()
{
	system("cls");
	
	cout << "���� õ���. (" << count++ << ")" << endl;
}

void CFramework::Update()
{
	Sleep(1000);
}

void CFramework::Run()
{
	while (true) {
		Update();
		Draw();
	}
}
