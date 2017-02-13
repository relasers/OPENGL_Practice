#include <iostream>
#include <conio.h>
#include "Hero.h"

using namespace std;

constexpr int N_of_hero = 2;

CHero * hero_A = new CHero();
CHero * hero_B = new CHero();

void CreateHero();
void Battle();
void Result();

int main()
{
	CreateHero();
	Battle();
	Result();

	return 0;
}

void CreateHero()
{

	CHero * p = hero_A;
	for (int i = 0; i < N_of_hero; ++i) {
		CHero * new_hero = new CHero(true);
		new_hero->LinkPrevNode(p);
		p->LinkNextNode(new_hero);
		hero_B->LinkNextNode(new_hero);
		p = p->GetNext();
	}

}

void Battle()
{
	while (1) {

		hero_A->GetNext()->InterActHero(
			hero_B->GetNext()->Attack()
		);

		if (hero_A->GetNext()->GetHP() <= 0) return;
		hero_B->GetNext()->InterActHero(
			hero_A->GetNext()->Attack()
		);

		if (hero_B->GetNext()->GetHP() <= 0) return;
	}

}

void Result()
{
	CHero * p = hero_A->GetNext();
	while (p != nullptr) {
		p->Isalive();
		p = p->GetNext();
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////
/*

0���� ũ�ų� ���� ���� ����� �Լ��� �ۼ��� ���
bool CheckDead() {  return(hp <= 0) } --> �̷��� ����ȭ ���Ѷ�

 �� ���ư� { if(IsDead) �̷� ������}

 �ڵ�� ���� �������� {�ǹ� ������ ���� �������}
 :: �� ������ � �ǹ̸� ������ �ֱ��� :: �ľ� ����

 ������ ������ �۲��� �����ʺ� �۲��� ����϶� 
 --> ���� :: ���̹� D2Coding, Consolas
*/
/////////////////////////////////////////////////////////////////////////////////////////