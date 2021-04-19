#include <iostream>
#include <Windows.h>
#ifndef __GUI
#define __GUI

enum class Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

void Text_color(int textColor, int backgroundColor);
void Start();
void Flush();
void Input_Append(char* term);
bool Input_polynomial(char* poly1, char* poly2);
bool After_calculate(char* poly);
void Interim_inspection(char* poly1, char* poly2);
int Append_term();
int Select_operation();
void Text_color(int textColor, int backgroundColor)
{
	int color = textColor + backgroundColor * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void Start() {
	std::cout << "Input two Polynomials to calculate" << std::endl;
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	//std::cout << "It only works up to x^10" << std::endl << std::endl;
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
}

inline void Flush()
{
	while (getchar() != '\n');
}

inline void Input_Append(char* term)
{
	std::cout << "\n Input the term you want to append\n\n>>";
	std::cin >> term;
}

bool Input_polynomial(char* poly1, char* poly2)
{
	std::cout << "First polynomials" << std::endl;
	std::cout << ">>";
	std::cin.getline(poly1, 40);
	//Flush();
	std::cout << std::endl;
	std::cout << "Secnod polynomials" << std::endl;
	std::cout << ">>";
	std::cin.getline(poly2, 40);
	//Flush();
	return 1;
}

inline bool After_calculate(char* poly)
{
	std::cout << std::endl;
	std::cout << poly;

	return 1;
}

void Interim_inspection(char* poly1, char* poly2)
{
	std::cout << "\n\nBelow two polynomials is your input\n\n";
	std::cout << "First >> " << poly1 << std::endl;
	std::cout << "Second >> " << poly2 << std::endl << std::endl;
}

int Append_term()
{
	int flag = 0;
	std::cout << "If you want to append one polynomial, select below number\n\n";
	std::cout << "1. first polynomial\n";
	std::cout << "2. second polynomial\n\n";
	Text_color(static_cast<int>(Color::LIGHTRED), static_cast<int>(Color::BLACK));
	std::cout << "If you intput other number except 1 or 2, the program recognize you don't want to append term\n";
	Text_color(static_cast<int>(Color::WHITE), static_cast<int>(Color::BLACK));
	std::cout << ">> ";
	std::cin >> flag;
	std::cout << std::endl;
	Flush();
	return flag;
}

inline int Select_operation()
{
	int selection = 0;
	std::cout << "\n\n Please select operation\n\n 1. Addpoly\n 2. Multipoly\n>>";
	std::cin >> selection;

	return selection;
}

#endif __GUI
