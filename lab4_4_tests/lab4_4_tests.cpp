#include "pch.h"
#include "CppUnitTest.h"
#include "../lab4_4/lab4_4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab44tests
{
	TEST_CLASS(lab44tests)
	{
	public:
		
		TEST_METHOD(MatrixMultiply_CorrectValue)
		{
			int k1, k2, k3, n1, n2, n3;
			int** m1 = GetMatrixFromFile("C:\\TEMPORARY\\lab4_4\\lab4_4\\matrix1.txt", k1, n1);
			int** m2 = GetMatrixFromFile("C:\\TEMPORARY\\lab4_4\\lab4_4\\matrix2.txt", k2, n2);
			int** exp = GetMatrixFromFile("C:\\TEMPORARY\\lab4_4\\lab4_4\\result.txt", k3, n3);

			int** result = MatrixMultiply(k1, n1, m1, k2, n2, m2);

			for (int i = 0; i < k3; i++) {
				for (int j = 0; j < n3; j++) {
					Assert::AreEqual(exp[i][j], result[i][j]);
				}
			}
		}
	};
}
