#include "pch.h"
#include "CppUnitTest.h"

#include "../Set/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable hash = { "the entire bee movie script", "uhhh", "joker the" };
		}
	};
}
