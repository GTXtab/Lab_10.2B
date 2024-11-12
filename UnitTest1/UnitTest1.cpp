#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.2 B/Lab_10.2 B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student student1;
			student1.ocinkaFizyka = 4;
			student1.ocinkaMatematika = 5;
			student1.ocinkaProgramming = 4; // для спеціальності KN

			// Очікуваний середній бал: (4 + 5 + 4) / 3 = 4.33
			Assert::AreEqual(student1.avg(), 4.33, 0.01);
		}
	};
}
