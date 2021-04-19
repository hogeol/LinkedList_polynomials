#include <iostream>
#include "GUI.hpp"
#include "LinkedList.h"

using namespace std;
using namespace nlinkedlist;

int main(int argc, char** argv) {
	Polynomial Mpolynomial1;
	Polynomial Mpolynomial2;
	Polynomial Mresult;
	char Mpoly1[61] = {}, Mpoly2[61] = {};
	char MappendTerm[11] = {};
	bool isError = 0;
	Start();
	isError = Input_polynomial(Mpoly1, Mpoly2);
	if (isError == 0) {
		cerr << "Error has occurred while receiving input\n\n";
		return -1;
	}
	Interim_inspection(Mpoly1, Mpoly2);
	Mpolynomial1.Input_Linkedlist(Mpoly1);
	Mpolynomial2.Input_Linkedlist(Mpoly2);


	int flag = Append_term();
	switch (flag) {
	case 1:
		Input_Append(MappendTerm);
		Mpolynomial1.Append_term(MappendTerm);
		break;
	case 2:
		Input_Append(MappendTerm);
		Mpolynomial2.Append_term(MappendTerm);
		break;
	default:
		break;
	}
	flag = Select_operation();
	switch (flag) {
	case 1:
		Mpolynomial1.Add_poly(&Mpolynomial2);
		break;
	case 2:
		Mpolynomial1.Multy_poly(&Mpolynomial2);
		break;
	default:
		cout << "\n You don't want to calculate. It just display your input polynomials\n\n";
		Mpolynomial1.Display_after_calculate();
		Mpolynomial2.Display_after_calculate();
		break;
	}
	Mpolynomial1.Display_after_calculate();
	cout << endl << endl;
	return 0;
}