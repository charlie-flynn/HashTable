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
			HashTable hash = HashTable(32);
		}

		TEST_METHOD(InitializerListConstructor)
		{
			HashTable hash = { "i'm gonna esplode i sweaar", "AAAAAAAAAAA" };
		}
	};
}