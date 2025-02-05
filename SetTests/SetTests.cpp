#include "pch.h"
#include "CppUnitTest.h"
#include "../Set/Set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SetTests
{
	TEST_CLASS(SetTests)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
		}

		TEST_METHOD(InitializerListConstructor)
		{
			Set<int> set = { 10, 20, 30, 40, 50 };

			Iterator<Pair<int, int>> iter = set.begin();

			Assert::AreEqual(5, set.GetLength());

			Assert::AreEqual(10, (*iter).value);
			iter++;
			Assert::AreEqual(20, (*iter).value);
			iter++;
			Assert::AreEqual(30, (*iter).value);
			iter++;
			Assert::AreEqual(40, (*iter).value);
			iter++;
			Assert::AreEqual(50, (*iter).value);
		}
	};
}
