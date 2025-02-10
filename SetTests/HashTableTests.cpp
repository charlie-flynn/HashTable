#include "pch.h"
#include "CppUnitTest.h"
#include "../Set/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(SetTests)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
		}

		TEST_METHOD(InitializerListConstructor)
		{
			HashTable hash = { "100", "forty thousand", "oh god do i have to cast all of these" };
			hash.GetLength();
		}
	};
}
