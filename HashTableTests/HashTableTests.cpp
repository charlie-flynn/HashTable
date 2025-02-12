#include "pch.h"
#include "CppUnitTest.h"

#include "../Set/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
		TEST_METHOD(InitializerListConstructor)
		{
			HashTable hash = { "the entire bee movie script", "uhhh", "joker the jimbo", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony"};

			Assert::AreEqual(4, hash.GetCount());

			Assert::AreEqual((unsigned char*)"the entire bee movie script", hash["the entire bee movie script"]);
			Assert::AreEqual((unsigned char*)"uhhh", hash["uhhh"]);
			Assert::AreEqual((unsigned char*)"joker the jimbo", hash["joker the jimbo"]);
			Assert::AreEqual((unsigned char*)"agony", hash["agony"]);

			Assert::IsNull(hash["chat is this null? is this null pointer? oh my god it's f###ing null pointer. are you kidding me. god dammit. ####."]);
			Assert::IsNull(hash["jimbo the joker"]);
			Assert::IsNull(hash["yagon"]);
		}
	};
}
