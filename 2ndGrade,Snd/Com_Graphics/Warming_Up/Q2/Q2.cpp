#include<iostream>
#include<conio.h>
#include<functional> // �Լ������� ���
#include "WarpList.h"
#include "C3Point.h"

using namespace std;
WarpList<C3Point>List;

enum Command {
	Push_Front, Pop_Front,
	Push_Back, Pop_Back,
	Max,Min
};


int InsertCommand();

void ExecutePB(int Command);
void CalcPointLen(int Command);
void Print();
void Clear();

int CalcLength();

int main() 
{

	while (1) {
		Print();
		if (InsertCommand() == 0)
			break;
		system("cls");
	}
	return 0;
}

int InsertCommand()
{
	switch (_getche()) {
	case '+':
		cout << endl;
		ExecutePB(Push_Front);
		break;
	case '-':
		cout << endl;
		ExecutePB(Pop_Front);
		break;
	case 'E':
	case 'e':
		cout << endl;
		ExecutePB(Push_Back);
		break;
	case 'D':
	case 'd':
		cout << endl;
		ExecutePB(Pop_Back);
		break;
	case 'L':
	case 'l':
		cout << endl;
		cout << "Length :: " << CalcLength() << endl;
		break;
	case 'C':
	case 'c':
		cout << endl;
		Clear();
		break;
	case 'M':
	case 'm':
		cout << endl;
		CalcPointLen(Max);
		break;
	case 'N':
	case 'n':
		cout << endl;
		CalcPointLen(Min);
		break;
	case 'Q':
	case 'q':
		cout << endl;
		return 0;
	default:
		break;
	}
	_getch();
	return 1;
}

void ExecutePB(int Command)
{
	double x, y, z;
	switch (Command) {
	case Push_Front:
		if (CalcLength() < 10) {
			cin >> x >> y >> z;
			List.push_front(C3Point(x, y, z));
		}
		else
			cout << "List is Full" << endl;
		
		break;
	case Pop_Front:
		if(CalcLength() != 0)
		List.pop_front();
		else
			cout << "List is Empty" << endl;
		break;
	case Push_Back:
		if (CalcLength() < 10) {
			cin >> x >> y >> z;
			List.push_back(C3Point(x, y, z));
		}
		else
			cout << "List is Full" << endl;
		break;
	case Pop_Back:
		if (CalcLength() != 0)
			List.pop_back();
		else
			cout << "List is Empty" << endl;
		break;
	
	}
	cout << "Executed" << endl;
}

void CalcPointLen(int Command)
{

	int x = 0;
	C3Point point;
	for (auto &p : List)
	{
		if(Command == Command::Max)
		if (p.GetLength() >= point.GetLength())
			point.InsertPoint(p.GetX(), p.GetY(), p.GetZ());
		if (Command == Command::Min) {
			if(x==0) point.InsertPoint(p.GetX(), p.GetY(), p.GetZ());
			if (p.GetLength() <= point.GetLength())
				point.InsertPoint(p.GetX(), p.GetY(), p.GetZ());
		
		}
			
		x++;
	}

	if (x != 0) {
		cout << point;
	}
	else {
		cout << "List is Empty" << endl;
	}

}

void Clear()
{
	List.remove_if([](const decltype(List)::type& data) -> bool {
		return (data.Delete());
	});
	cout << "Executed" << endl;
}

int CalcLength()
{

	int x = 0;
	for (auto &p : List)
	{
		x++;
	}
	return x;
}

void Print() {

	cout << "+ : �� ���� ����" << endl;
	cout << "- : �� ���� ����" << endl;
	cout << "e : �� �Ʒ� ����" << endl;
	cout << "d : �� �Ʒ� ����" << endl;
	cout << "l : ����Ʈ ���� ���" << endl;
	cout << "c : ����Ʈ�� �����" << endl;
	cout << "m : �������� ���� �ָ��ִ� ��ǥ����?" << endl;
	cout << "n : �������� ���� ������ �ִ� ��ǥ����?" << endl;
	cout << "q : ���α׷� ����" << endl;

	int x = 0;
	for (auto &p : List)
	{
		cout << x << p << endl;
		x++;
	}
	cout << "Insert Command :: ";
}