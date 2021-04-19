#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "LinkedList.h"

//�Է¹��� �� Linked list�� �Է��ϴ� �Լ�
void nlinkedlist::Polynomial::Input_Linkedlist(char* polynomial)
{
	int size = strlen(polynomial) + 1;
	char* polytmp = new char[size];
	int i = 0, j = 0, o = 0;
	vector<float> coeftmp;
	vector<int> expotmp;
	bool flag = 0;
	bool minus = 0;
	bool isExist = 0;
	char tmp[10] = {};

	//����ڰ� �Է��� �Ŀ��� space�� �����Ѵ�.
	Delete_space(polynomial, polytmp);

	//����ڰ� �Է��� ���׽��� x�� ������ �������� �����Ѵ�.
	char* copy = strtok(polytmp, "+ ");
	while (copy != NULL)
	{
		//���׽Ŀ� ������(x)�� �ִ��� ��������� ����Ѵ�
		for (int p = 0; p < strlen(copy); p++)
		{
			if (copy[p] == 'x') {
				flag = 1;
				break;
			}
		}
		//���׽��� �������� ������ ���̸�
		if (flag == 1) {
			for (j = 0; j < strlen(copy); j++)
			{
				//x�� ������ ���ϰ�
				if (copy[j] == '^') {
					for (int k = j + 1; k < strlen(copy); k++)
					{
						tmp[k - j - 1] = copy[k];
					}
					//����ڰ� ���� ������ ���� �������� �ߺ� �Է��Ͽ����� ����Ѵ�.
					for (o = 0; o < expotmp.size(); o++)
					{
						if (atoi(tmp) == expotmp.at(o)) {
							isExist = 1;
							break;
						}
					}
					//�ߺ��Էµ� ���� ������ x�� ������ ���Ѵ�.
					if (isExist == 0) {
						expotmp.push_back(atoi(tmp));
						break;
					}
				}
			}
			//�ߺ� �Էµ� ���̶�� x�� ����� �̹� �Էµ� ����� ���Ѵ�.
			if (isExist == 1) {
				// -1�� ����� ����� �ȵǾ ���� ���Ͽ���.
				if (copy[0] == '-' && copy[1] == 'x') {
					coeftmp.at(o) = coeftmp.at(o) - 1;
				}
				else
					coeftmp.at(o) += atof(copy);
			}
			//�ߺ� �Էµ� ���� ������ x�� ����� �߰��Ѵ�.
			else {
				if (copy[0] == 'x') {
					coeftmp.push_back(1);
				}
				else if (copy[0] == '-' && copy[1] == 'x')
					coeftmp.push_back(-1);
				else
					coeftmp.push_back(atof(copy));

				if (coeftmp.size() != expotmp.size())
					expotmp.push_back(1);
			}
		}
		//����ڰ� �Է��� ���� ����̸� ����� �߰��Ѵ�.
		else {
			for (o = 0; o < expotmp.size(); o++) {
				if (expotmp.at(o) == 0) {
					isExist = 1;
					coeftmp.at(o) += atof(copy);
					break;
				}
			}
			if (isExist == 0) {
				coeftmp.push_back(atof(copy));
				expotmp.push_back(0);
			}
		}
		isExist = 0;
		o = 0;
		flag = 0;
		copy = strtok(NULL, "+ ");
	}
	//����ڰ� �Է��� ���� ����� �������� �������� �����Ѵ�.
	Insert_sort(coeftmp, expotmp);
	//���� Linked list �� �Է��Ѵ�.
	Make_polynomials_List(coeftmp, expotmp);
}

//Linked list ����� ���� �� ���� �ϱ� ���� space�� �����ϴ� �Լ�
void nlinkedlist::Polynomial::Delete_space(char* polynomial, char* tmp)
{
	int size = strlen(polynomial) + 1;
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		tmp[j++] = polynomial[i];
		if (polynomial[i] == ' ' && polynomial[i + 1] != '-') {
			j--;
		}
		else if (polynomial[i] == '-' && polynomial[i - 1] != ' ') {
			tmp[j--] = '-';
			tmp[j++] = ' ';
			j++;
		}
	}
	tmp[j] = '\0';
}

//������ �߰� �Լ�
void nlinkedlist::Polynomial::Append_term(char* term)
{
	int size = strlen(term) + 1;
	char* tmpterm = new char[size];
	float coef = 0;
	int expo = 0;
	bool flag = 0;

	//space ����
	Delete_space(term, tmpterm);

	//����������� ���θ� ���Ѵ�.
	for (int i = 0; i < size; i++)
	{
		if (tmpterm[i] == 'x') {
			flag = 1;
			break;
		}
	}
	int i = 0;
	char* tokstr = strtok(tmpterm, "+ ");
	while (tokstr != NULL) {
		if (flag == 1) {
			if (tmpterm[0] == 'x')
				coef = 1;
			else
				coef = atof(tmpterm);
			if (tmpterm[++i] == '^') {
				char exptmp[6] = {};
				int j = 0;
				while (tmpterm[i] != '\0')
					exptmp[j++] = tmpterm[++i];
				expo = atoi(exptmp);
				break;
			}
			else
				expo = 1;
		}
		else {
			coef = atof(tmpterm);
			expo = 0;
		}
		tokstr = strtok(NULL, "+ ");
	}
	vector<float> coeff(1, coef);
	vector<int> expon(1, expo);

	//���� �߰��Ѵ�.
	Make_polynomials_List(coeff, expon);
	Display_after_calculate();
}

void nlinkedlist::Polynomial::Make_polynomials_List(vector<float> coef, vector<int> expo)
{
	int cnt = 1;
	bool flag = 0;
	LinkedList* _newlist = (LinkedList*)malloc(sizeof(LinkedList));

	//����ڰ� �Է��� ���� Linkedlist�� �Է��Ѵ�.
	if (mhead == nullptr) {
		_newlist->mcoef = coef.at(0);
		_newlist->mexpo = expo.at(0);
		mhead = _newlist;
		mhead->mlink = nullptr;
		mlast = mhead;
		while (cnt < coef.size())
		{
			mlast->mlink = (LinkedList*)malloc(sizeof(LinkedList));
			if (coef.at(cnt) != 0) {
				(mlast->mlink)->mcoef = coef.at(cnt);
				(mlast->mlink)->mexpo = expo.at(cnt++);
				mlast = mlast->mlink;
			}
		}
		mlast->mlink = nullptr;
	}
	//�Է¹��� ���� Append term�� ��
	else {
		LinkedList* appendlist = mhead;
		while (appendlist != nullptr) {
			//���� ������ ���� ���� �����ϸ� ���� ����� ���Ѵ�.
			if (appendlist->mexpo == expo.front()) {
				appendlist->mcoef += coef.front();
				flag = 1;
				break;
			}
			appendlist = appendlist->mlink;
		}
		//���� ������ ���� ���� ���ٸ� ���� List�� �߰��Ѵ�.
		if (flag == 0) {
			LinkedList* tmplist = (LinkedList*)malloc(sizeof(LinkedList));
			appendlist = mhead;
			while (appendlist != nullptr) {
				if (appendlist->mexpo < expo.front()) {
					tmplist->mcoef = coef.front();
					tmplist->mexpo = expo.front();
					tmplist->mlink = mhead;
					mhead = tmplist;
					tmplist = nullptr;
					break;
				}
				if ((appendlist->mlink != nullptr) && (((appendlist->mlink)->mexpo) < expo.front())) {
					tmplist->mcoef = coef.front();
					tmplist->mexpo = expo.front();
					tmplist->mlink = appendlist->mlink;
					appendlist->mlink = tmplist;
					break;
				}
				else if ((appendlist->mlink) == nullptr) {
					tmplist->mcoef = coef.front();
					tmplist->mexpo = expo.front();
					appendlist->mlink = tmplist;
					tmplist->mlink = nullptr;
					break;
				}
			}
		}
	}
	_newlist = mhead;
	LinkedList* deletezero = (LinkedList*)malloc(sizeof(LinkedList));
	//����� 0�� Link�� �����Ѵ�.
	while (_newlist != nullptr) {
		if (mhead->mcoef == 0) {
			mhead = mhead->mlink;
			_newlist->mlink = nullptr;
			_newlist = mhead;
		}
		else {
			deletezero = _newlist;
			_newlist = _newlist->mlink;
			if (_newlist != nullptr && _newlist->mcoef == 0) {
				if (_newlist->mlink == nullptr) {
					deletezero->mlink = nullptr;
					_newlist = mlast;
					break;
				}
				deletezero->mlink = _newlist->mlink;
				_newlist = deletezero;
			}
		}
	}
}

void nlinkedlist::Polynomial::Add_poly(Polynomial* second_term)
{
	vector<float> ftmp;
	vector<int> itmp;
	LinkedList* tmp = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* cpy = (LinkedList*)malloc(sizeof(LinkedList));

	//ù��° �װ� �ι�° ���� ������ ���ϸ鼭 ���� ������ ������ ����� �����ְ� �� ��° ���� ����� 0���� ������ش�.
	tmp = mhead;
	cpy = second_term->mhead;
	while (tmp != nullptr) {
		while (cpy != nullptr) {
			if (cpy->mexpo == tmp->mexpo) {
				tmp->mcoef += cpy->mcoef;
				cpy->mcoef = 0;
				cpy = cpy->mlink;
			}
			else {
				cpy = cpy->mlink;
			}
		}
		tmp = tmp->mlink;
	}
	LinkedList* _newlist = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* deletezero = (LinkedList*)malloc(sizeof(LinkedList));
	_newlist = mhead;

	//���� ������ ���� ���� �Ŀ��� ����� 0�� Link�� �����Ѵ�.
	while (_newlist != nullptr) {
		if (mhead->mcoef == 0) {
			mhead = mhead->mlink;
			_newlist->mlink = nullptr;
			_newlist = mhead;
		}
		else {
			deletezero = _newlist;
			_newlist = _newlist->mlink;
			if (_newlist != nullptr && _newlist->mcoef == 0) {
				if (_newlist->mlink == nullptr) {
					deletezero->mlink = nullptr;
					_newlist = mlast;
					break;
				}
				deletezero->mlink = _newlist->mlink;
				_newlist = deletezero;
			}
		}
	}

	//�� ��° �Ŀ��� ���� ������ ������ ����� 0���� ����� �־����Ƿ� 0�� ����� ���� �͵��� �����Ѵ�.
	_newlist = second_term->mhead;
	while (_newlist != nullptr) {
		if ((second_term->mhead)->mcoef == 0) {
			second_term->mhead = (second_term->mhead)->mlink;
			_newlist->mlink = nullptr;
			_newlist = second_term->mhead;
		}
		else {
			deletezero = _newlist;
			_newlist = _newlist->mlink;
			if (_newlist != nullptr && _newlist->mcoef == 0) {
				if (_newlist->mlink == nullptr) {
					deletezero->mlink = nullptr;
					_newlist = mlast;
					break;
				}
				deletezero->mlink = _newlist->mlink;
				_newlist = deletezero;
			}
		}
	}
	//Append term�� ���� ������� ���� �׵��� ����Ѵ�.
	_newlist = second_term->mhead;
	while (_newlist != nullptr) {
		ftmp.push_back(_newlist->mcoef);
		itmp.push_back(_newlist->mexpo);
		Make_polynomials_List(ftmp, itmp);
		ftmp.pop_back();
		itmp.pop_back();
		_newlist = _newlist->mlink;
	}
}
void nlinkedlist::Polynomial::Multy_poly(Polynomial* second_term)
{
	LinkedList* firsttmp = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* secondtmp = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* copytmp = (LinkedList*)malloc(sizeof(LinkedList));
	bool flag = 0;
	copytmp = second_term->mhead;
	firsttmp = mhead;
	secondtmp = second_term->mhead;
	vector<float> ftmp;
	vector<int> itmp;
	//�� �׵��� ����� ���ϰ� ������ ���Ѵ�.
	while (firsttmp != nullptr) {
		while (secondtmp != nullptr) {
			float coeff = firsttmp->mcoef * secondtmp->mcoef;
			int expon = firsttmp->mexpo + secondtmp->mexpo;
			if (flag == 0) {
				ftmp.push_back(coeff);
				itmp.push_back(expon);
				flag = 1;
			}
			else {
				for (int i = 0; i < itmp.size(); i++)
				{
					//������ �� �� �̹� �����ϴ� x�� ������ ������ ����� ���� ���� ���� �Ŀ� �����ش�.
					if (itmp.at(i) == expon) {
						ftmp.at(i) += coeff;
						break;
					}
					//�׷��� ������ ������ ���ϰ� ����� ���� ���� �ִ´�.
					if (i == itmp.size() - 1) {
						itmp.push_back(expon);
						ftmp.push_back(coeff);
						break;
					}
				}
			}
			secondtmp = secondtmp->mlink;
		}
		secondtmp = second_term->mhead;
		firsttmp = firsttmp->mlink;
	}
	mhead = nullptr;
	Insert_sort(ftmp, itmp);
	Make_polynomials_List(ftmp, itmp);
}

//��� ����ϴ� �Լ�
void nlinkedlist::Polynomial::Display_after_calculate()
{
	LinkedList* tmp = mhead;
	cout << "\n\nAfter Calcluate >>  ";
	vector<float> coefficient;
	vector<int> exponent;
	while (mhead != nullptr) {
		coefficient.push_back(mhead->mcoef);
		exponent.push_back(mhead->mexpo);
		mhead = mhead->mlink;
	}
	mhead = tmp;
	for (int i = 0; i < coefficient.size(); i++) {
		if (i != 0) {
			if (coefficient.at(i) < 0) {
				if (coefficient.at(i) == -1) {
					if (exponent.at(i) == 0)
						cout << " -1";
					else
						cout << " - ";
				}
				else
					cout << " - " << fabs(coefficient.at(i));
				if (exponent.at(i) != 0) {
					if (exponent.at(i) == 1)
						cout << "x";
					else
						cout << "x^" << exponent.at(i);
				}
			}
			else {
				if (coefficient.at(i) == 1) {
					if (exponent.at(i) == 0)
						cout << " + 1 ";
					else
						cout << " + ";
				}
				else
					cout << " + " << coefficient.at(i);
				if (exponent.at(i) != 0) {
					if (exponent.at(i) == 1)
						cout << "x";
					else
						cout << "x^" << exponent.at(i);
				}
			}
		}
		//ù ��° ���� ' + '�� ����ϸ� �� �Ǳ� ������ ���� �������ش�.
		else {
			if (coefficient.at(i) > 0) {
				if (coefficient.at(i) != 1)
					cout << coefficient.at(i);
			}
			else {
				if (coefficient.at(i) != -1)
					cout << " - " << fabs(coefficient.at(i));
			}
			if (exponent.at(i) != 0)
				cout << "x^" << exponent.at(i);
		}
	}
}



//��������
void nlinkedlist::Polynomial::Insert_sort(vector<float>& coef, vector<int>& expo)
{
	float coefkey = 0;
	int expokey = 0;
	int j = 0;
	for (int i = expo.size() - 2; i >= 0; i--)
	{
		expokey = expo.at(i);
		coefkey = coef.at(i);
		for (j = i + 1; j < expo.size(); j++)
		{
			if (expokey < expo.at(j)) {
				expo.at(j - 1) = expo.at(j);
				coef.at(j - 1) = coef.at(j);
			}
			else
				break;
		}
		expo.at(j - 1) = expokey;
		coef.at(j - 1) = coefkey;
	}
}
