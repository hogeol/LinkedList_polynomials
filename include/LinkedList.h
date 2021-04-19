#include <vector>
#ifndef __LINKEDLIST
#define __LINKEDLIST



namespace nlinkedlist {
	class LinkedList
	{
	private:
		float mcoef;
		int mexpo;
		LinkedList* mlink;

		friend class Polynomial;
	public:
		LinkedList() : mcoef(0.0), mexpo(0), mlink(nullptr) {}
	};

	class Polynomial
	{
	private:
		LinkedList* mhead;
		LinkedList* mlast;
	public:
		Polynomial() :mhead(nullptr), mlast(nullptr) {}
		void Input_Linkedlist(char* polynomial);
		void Delete_space(char* polynomial, char* tmp);
		void Append_term(char* term);
		void Make_polynomials_List(std::vector<float> coef, std::vector<int> expo);
		void Add_poly(Polynomial *second_term);
		void Multy_poly(Polynomial* second_term);
		void Display_after_calculate();
		void Insert_sort(std::vector<float>& coef, std::vector<int>& expo);
	};
}
#endif __LINKEDLIST