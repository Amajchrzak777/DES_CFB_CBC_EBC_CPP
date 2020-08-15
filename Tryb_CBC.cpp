// Adam Majchrzak 25.03.2020
// Algorytm CBC

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <ctime>
#include <random>
#include <cstdlib>

const int n = 8; // wartosc n=8 bo pracujemy na 8 bitach




int main()
{
	//generator liczb losowych
	srand(time(NULL));
	int liczba;
	std::vector<int> klucz;
	for (int i = 0; i < n; ++i) {
		liczba = rand() % 1000000;
		klucz.push_back(liczba);
	}
	std::vector<char> wektor_inicjujcacy;
	char initial_vector;
	std::cout << "Wprowadz 8 znakow ktore beda wektorem inicjujacym: ";
	for (int i = 0; i < n; ++i) {
		std::cin >> initial_vector;
		wektor_inicjujcacy.push_back(initial_vector);
	}
	std::cout << "Wektor inicjujacy w postaci binarnej: ";
	for (int i = 0; i < wektor_inicjujcacy.size(); ++i) {
		std::cout << std::bitset<8> (wektor_inicjujcacy[i]) << " ";
	}
	char x;
	char ch;
	//inicjuje vector do ktorego zapisze szyfrowany tekst
	std::vector<char> szyfr;
	std::string oname;
	//Zaczynam od wczytania pliku
	std::cout << "\nPlease enter output file name: ";
	std::cin >> oname;
	//otwieram plik do zapisu
	std::ofstream ost(oname.c_str());
	if (!ost) std::cerr << "Can't open the file";
	//wpisuje szyfr do pliku
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		szyfr.push_back(x);
	}
	for (int i = 0; i < szyfr.size(); ++i) {
		ost << szyfr[i];
	}
	std::cout << "Tekst jawny: \t";
	for (int i = 0; i < szyfr.size(); ++i) {
		std::cout << szyfr[i];
	}
	std::cout << "\nZapis bitowy: \t";
	for (int i = 0; i < szyfr.size(); ++i) {
		std::cout << std::bitset<8>(szyfr[i]) << " ";
	}
	ost.close();
	//otwieram plik do odczytu
	std::ifstream ist(oname.c_str());
	std::cout << "\nKlucz: \t\t";
	for (int i = 0; i < klucz.size(); ++i) {
		std::cout << std::bitset<8>(klucz[i]) << " ";
	}
	std::cout << "\nSzyfrogram: \t";
	for (int i = 0; i < wektor_inicjujcacy.size();) {
		while (ist.get(ch)) {
			std::cout << ((std::bitset<8>(ch) ^ std::bitset<8>(wektor_inicjujcacy[i])) ^ (std::bitset<8>(klucz[i]))) << " "; //używam operacji XOR i dostaje szyfrogram 
			++i;
		}
	}
	ist.close();
}