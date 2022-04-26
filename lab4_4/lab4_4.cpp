// lab4_4.cpp 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int** CreateMatrix(int&, int&);
void PrintMatrix(int, int, int**);
int** MatrixMultiply(int, int, int**, int, int, int**);
void CreateMatrixTextfile(const char*, int, int, int**);
void PrintMatrixFromFile(const char*);
int** GetMatrixFromFile(const char*, int&, int&);
void Menu(const char**);
int MatrixSlotsMenu(const char**, int);
void MatrixCreateMenu(const char*);
void MatrixShowMenu(const char*);
void MatrixMultiplyMenu(const char*, const char*, const char*);

int main() {
	const auto filenames = new const char*[3] { "matrix1.txt", "matrix2.txt", "result.txt" };
	Menu(filenames);

	return 0;
}
int** CreateMatrix(int &n, int &m) {
	int** matrix;

	cout << "Enter rows count: "; cin >> n;
	cout << "Enter cols count: "; cin >> m;
	matrix = new int*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << "Enter El[" << i << "][" << j << "]: ";
			cin >> matrix[i][j];
		}
	}

	return matrix;
}
void PrintMatrix(int n, int m, int** matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
int** MatrixMultiply(int k1, int n1, int** m1, int k2, int n2, int** m2) {
	if (k2 != n1)
		return 0;
	int** result;
	result = new int* [k1];
	for (int i = 0; i < k1; i++)
		result[i] = new int[n2];

	for (int i = 0; i < k1; i++) {
		for (int j = 0; j < n2; j++) {
			int sum = 0;
			for (int k = 0; k < k2; k++) {
				sum += m1[i][k] * m2[k][i];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

void CreateMatrixTextfile(const char* filename, int n, int m, int **matrix) {
	ofstream fout(filename);
	fout << n << " " << m << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fout << matrix[i][j] << " ";
		}
		fout << endl;
	}

	fout.close();
}
void PrintMatrixFromFile(const char* filename) {
	int n, m;
	int** matrix = GetMatrixFromFile(filename, n, m);
	if (matrix != 0)
		PrintMatrix(n, m, matrix);
	else
		MatrixCreateMenu(filename);
}
int** GetMatrixFromFile(const char* filename, int& n, int& m) {
	int** matrix;
	ifstream fin(filename);
	fin >> n;
	if (!(n > 0)) {
		fin.close();
		return 0;
	}
	fin >> m;
	matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fin >> matrix[i][j];
		}
	}

	fin.close();
	return matrix;
}

void Menu(const char** filenames) {
	system("CLS");
	int choice;
	cout << "1 - Create matrix\n";
	cout << "2 - Show matrix\n";
	cout << "3 - Multiply matrixes\n";
	cout << "0 - Close application\n";
	cout << " >> "; cin >> choice;
	if (choice == 0)
		return;
	else if (!(choice >= 1 && choice <= 3)) {
		cout << "Wrong choice, try again!";
		system("pause");
		Menu(filenames);
		return;
	}
	MatrixSlotsMenu(filenames, choice);
}
int MatrixSlotsMenu(const char** filenames, int func) {
	system("CLS");
	int n1, m1, n2, m2;
	int** s1 = GetMatrixFromFile(filenames[0], n1, m1);
	int** s2 = GetMatrixFromFile(filenames[1], n2, m2);
	bool s1_IsEmpty = s1 == 0;
	bool s2_IsEmpty = s2 == 0;

	if (func == 2 && s1_IsEmpty && s2_IsEmpty) {
		cout << "There is nothing to show!\n\n You will be redirected to the main menu in 3 seconds\n";
		sleep_for(seconds(3));
		Menu(filenames);
	}

	cout << "Choose slot: \n";
	if (!s1_IsEmpty)
		cout << "1 - [Matrix 1]\n";
	else if (func != 2)
		cout << "1 - [Empty slot]\n";
	if (!s2_IsEmpty)
		cout << "2 - [Matrix 2]\n";
	else if (func != 2)
		cout << "2 - [Empty slot]\n";
	cout << "0 - Return to the main menu\n";

	int choice;
	cout << " >> "; cin >> choice;
	if (choice == 0) {
		Menu(filenames);
	}
	else if (!(choice >= 1 && choice <= 2)) {
		cout << "Wrong choice, try again\n\n";
		system("pause");
		MatrixSlotsMenu(filenames, func);
	}

	int choice2;
	switch (func) {
	case 1:
		MatrixCreateMenu(filenames[choice - 1]);
		Menu(filenames);
		break;
	case 2:
		MatrixShowMenu(filenames[choice - 1]);
		Menu(filenames);
		break;
	case 3:
		choice2 = MatrixSlotsMenu(filenames, 0);
		MatrixMultiplyMenu(filenames[choice - 1], filenames[choice2 - 1], filenames[2]);
		Menu(filenames);
		break;
	default:
		break;
	}
	return choice;
}
void MatrixCreateMenu(const char* filename) {
	system("CLS");
	int n, m;
	int** result = CreateMatrix(n, m);
	CreateMatrixTextfile(filename, n, m, result);
	cout << endl;
	system("pause");
}
void MatrixShowMenu(const char* filename) {
	system("CLS");
	PrintMatrixFromFile(filename);
	cout << endl;
	system("pause");
}
void MatrixMultiplyMenu(const char* filename1, const char* filename2, const char* filename3) {
	system("CLS");
	int n1, m1;
	int** s1 = GetMatrixFromFile(filename1, n1, m1);
	int n2, m2;
	int** s2 = GetMatrixFromFile(filename2, n2, m2);

	cout << "Matrix 1:\n";
	PrintMatrixFromFile(filename1);
	cout << "Matrix 2:\n";
	PrintMatrixFromFile(filename2);
	int** matrix3 = MatrixMultiply(n1, m1, s1, n2, m2, s2);
	if (matrix3 == 0) {
		cout << "Unable to multiply these matrixes.\n You will be redirected to the main menu in 3 seconds";
		sleep_for(seconds(3));
		return;
	}
	cout << "Matrix 1 * Matrix 2: \n";
	CreateMatrixTextfile(filename3, n2, m1, matrix3);
	PrintMatrixFromFile(filename3);
	cout << endl;
	system("pause");
}