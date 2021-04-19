#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "LinkedList.h"

//입력받은 식 Linked list로 입력하는 함수
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

	//사용자가 입력한 식에서 space를 제거한다.
	Delete_space(polynomial, polytmp);

	//사용자가 입력한 다항식을 x의 지수를 기준으로 정렬한다.
	char* copy = strtok(polytmp, "+ ");
	while (copy != NULL)
	{
		//다항식에 미지수(x)가 있는지 상수항인지 계산한다
		for (int p = 0; p < strlen(copy); p++)
		{
			if (copy[p] == 'x') {
				flag = 1;
				break;
			}
		}
		//다항식이 미지수를 포함한 항이면
		if (flag == 1) {
			for (j = 0; j < strlen(copy); j++)
			{
				//x의 차수를 구하고
				if (copy[j] == '^') {
					for (int k = j + 1; k < strlen(copy); k++)
					{
						tmp[k - j - 1] = copy[k];
					}
					//사용자가 같은 차수를 가진 미지수를 중복 입력하였는지 계산한다.
					for (o = 0; o < expotmp.size(); o++)
					{
						if (atoi(tmp) == expotmp.at(o)) {
							isExist = 1;
							break;
						}
					}
					//중복입력된 항이 없으면 x의 차수를 구한다.
					if (isExist == 0) {
						expotmp.push_back(atoi(tmp));
						break;
					}
				}
			}
			//중복 입력된 항이라면 x의 계수를 이미 입력된 계수에 더한다.
			if (isExist == 1) {
				// -1이 제대로 계산이 안되어서 따로 구하였다.
				if (copy[0] == '-' && copy[1] == 'x') {
					coeftmp.at(o) = coeftmp.at(o) - 1;
				}
				else
					coeftmp.at(o) += atof(copy);
			}
			//중복 입력된 항이 없으면 x의 계수를 추가한다.
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
		//사용자가 입력한 식이 상수이면 상수를 추가한다.
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
	//사용자가 입력한 식을 계수를 기준으로 오름차순 정렬한다.
	Insert_sort(coeftmp, expotmp);
	//식을 Linked list 에 입력한다.
	Make_polynomials_List(coeftmp, expotmp);
}

//Linked list 계산을 조금 더 쉽게 하기 위해 space를 삭제하는 함수
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

//단일항 추가 함수
void nlinkedlist::Polynomial::Append_term(char* term)
{
	int size = strlen(term) + 1;
	char* tmpterm = new char[size];
	float coef = 0;
	int expo = 0;
	bool flag = 0;

	//space 삭제
	Delete_space(term, tmpterm);

	//상수항인지의 여부를 구한다.
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

	//항을 추가한다.
	Make_polynomials_List(coeff, expon);
	Display_after_calculate();
}

void nlinkedlist::Polynomial::Make_polynomials_List(vector<float> coef, vector<int> expo)
{
	int cnt = 1;
	bool flag = 0;
	LinkedList* _newlist = (LinkedList*)malloc(sizeof(LinkedList));

	//사용자가 입력한 식을 Linkedlist로 입력한다.
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
	//입력받은 식이 Append term일 때
	else {
		LinkedList* appendlist = mhead;
		while (appendlist != nullptr) {
			//같은 차수를 가진 항이 존재하면 항의 계수를 더한다.
			if (appendlist->mexpo == expo.front()) {
				appendlist->mcoef += coef.front();
				flag = 1;
				break;
			}
			appendlist = appendlist->mlink;
		}
		//같은 차수를 가진 항이 없다면 항을 List에 추가한다.
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
	//상수가 0인 Link를 삭제한다.
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

	//첫번째 항과 두번째 항의 차수를 비교하면서 같은 차수가 있으면 계수를 더해주고 두 번째 항의 계수를 0으로 만들어준다.
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

	//같은 차수의 항을 더한 식에서 상수가 0인 Link를 삭제한다.
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

	//두 번째 식에서 같은 차수가 없으면 계수를 0으로 만들어 주었으므로 0의 계수를 가진 것들을 삭제한다.
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
	//Append term과 같은 방식으로 남은 항들을 계산한다.
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
	//각 항들의 계수를 곱하고 지수를 더한다.
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
					//연산한 식 중 이미 존재하는 x의 차수가 있으면 계수를 곱한 값만 원래 식에 더해준다.
					if (itmp.at(i) == expon) {
						ftmp.at(i) += coeff;
						break;
					}
					//그렇지 않으면 차수를 더하고 계수를 곱한 값을 넣는다.
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

//결과 출력하는 함수
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
		//첫 번째 항은 ' + '를 출력하면 안 되기 때문에 따로 정리해준다.
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



//삽입정렬
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
