// Adam Majchrzak 25.03.2020
// Algorytm EBC

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <ctime>
#include <random>
#include <cstdlib>

const int n = 8; // wartosc n=8 bo pracujemy na 64 bitach


int main()
{
	//vectory do lewej i prawej strony
	std::vector<std::bitset<8>> left;
	std::vector<std::bitset<8>> right;
	std::vector<std::bitset<8>> new_key_56;
	std::vector<std::bitset<8>> new_key_48;
	//generator liczb losowych
	srand(time(NULL));
	//int liczba;
	//int random_numb;
	char litera;
	std::cout << "Wprowadz 8 znakowy klucz dla tej operacji DES: ";
	std::vector<std::bitset<8>> klucz;
	for (int i = 0; i < n; ++i) {
		std::cin >> litera;
		klucz.push_back(litera);
	}
	std::cout << "\nKlucz w postaci bitowej: \t";
	for (int i = 0; i < klucz.size(); ++i) {
		std::cout << klucz[i] << " ";
	}
	int tablica[8] = {1,2,3,4,5,6,7,8};
	int e;
	for (int i = 0; i < 7; i++)
	{
		do
		{
			e = rand() % 8;
		} while((tablica[0] == e) || (tablica[1] == e) || (tablica[2] == e) || (tablica[3] == e) || (tablica[4] == e) || (tablica[5] == e) || (tablica[6] == e)/* || (tablica[7] == e)*/);
		tablica[i] = e;
		new_key_56.push_back(klucz[tablica[i]]);
	}
	std::cout << '\n';
	std::cout << "Klucz 56 bitow: ";
	for (int i = 0; i < new_key_56.size(); ++i) {
		std::cout << new_key_56[i] << " ";
	}
	int tablica1[7] = { 1,2,3,4,5,6,7 };
	for (int i = 0; i < 6; i++)
	{
		do
		{
			e = rand() % 7;
		} while ((tablica1[0] == e) || (tablica1[1] == e) || (tablica1[2] == e) || (tablica1[3] == e) || (tablica1[4] == e) || (tablica1[5] == e) || (tablica1[6] == e));
		tablica1[i] = e;
		new_key_48.push_back(klucz[tablica1[i]]);
	}
	std::cout << '\n';
	std::cout << "Klucz 48 bitow: ";
	for (int i = 0; i < new_key_48.size(); ++i) {
		std::cout << new_key_48[i] << " ";
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
	std::cout << "\nPlease enter plain text: ";
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
	//podziel tekst jawny na 2 połowy lewa i prawa
	for (int i = 0; i < szyfr.size(); ++i) {
		if (i < 4) {
			left.push_back(szyfr[i]);
		}
		else {
			right.push_back(szyfr[i]);
		}
	}
	//wypisz prawa i lewa stronę na ekran 
	/*for (int i = 0; i < left.size(); i++) {
		std::cout << "left: " << left[i] << "\n right: " << right[i] << '\n';
	}*/

	std::cout << "\nZapis bitowy: \t";
	for (int i = 0; i < szyfr.size(); ++i) {
		std::cout << std::bitset<8>(szyfr[i]) << " ";
	}
	std::cout << '\n' << "Left: \t";
	for (int i = 0; i < left.size(); ++i) {
		std::cout << std::bitset<8>(left[i]) << " ";
	}
	std::cout << '\n' << "Right: \t";
	for (int i = 0; i < right.size(); ++i) {
		std::cout << std::bitset<8>(right[i]) << " ";
	}
	std::bitset<8> random_numb;
	for (int i = 0; i < 2; ++i) {
		random_numb = rand() % 100000;
		right.push_back(random_numb);
	}
	std::cout << '\n' << "Right after extend: \t";
	for (int i = 0; i < right.size(); ++i) {
		std::cout << std::bitset<8>(right[i]) << " ";
	}

	std::vector<std::bitset<8>> score_after_xor;
	for (int i = 0; i < right.size(); ++i) {
		score_after_xor.push_back((right[i] ^ new_key_48[i]));
	}
	std::cout << '\n';
	for (int i = 0; i < score_after_xor.size(); ++i) {
		std::cout << score_after_xor[i] << " ";
	}

	int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

	ost.close();
	//otwieram plik do odczytu
	std::ifstream ist(oname.c_str());
	std::cout << "\nKlucz: \t\t";
	for (int i = 0; i < klucz.size(); ++i) {
		std::cout << std::bitset<8>(klucz[i]) << " ";
	}
	std::cout << "\nSzyfrogram: \t";
	for (int i = 0; i < klucz.size();) {
		while (ist.get(ch)) {
			std::cout << (std::bitset<8>(ch) ^ std::bitset<8>(klucz[i])) << " "; //używam operacji XOR i dostaje szyfrogram 
			++i;
		}
	}
	ist.close();
}
