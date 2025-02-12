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

		TEST_METHOD(Add)
		{
			HashTable hash = { "foo", "bar", "x", "y", "z" };

			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			Assert::IsNull(hash["A"]);
			Assert::IsNull(hash["AAA"]);

			// check that things are added
			Assert::AreEqual(true, hash.Add("A"));
			Assert::AreEqual(6, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());
			Assert::AreEqual((unsigned char*)"A", hash["A"]);
			Assert::IsNull(hash["AAA"]);

			// check that you cant add the same thing twice
			Assert::AreEqual(false, hash.Add("A"));
			Assert::AreEqual(6, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());
			Assert::AreEqual((unsigned char*)"A", hash["A"]);
			Assert::IsNull(hash["AAA"]);

			// add somethin else
			Assert::AreEqual(true, hash.Add("AAA"));
			Assert::AreEqual(7, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());
			Assert::AreEqual((unsigned char*)"A", hash["A"]);
			Assert::AreEqual((unsigned char*)"AAA", hash["AAA"]);

			// add a few other things to fill up the hash table
			Assert::AreEqual(true, hash.Add("etcetera,"));
			Assert::AreEqual(true, hash.Add("etcetera..."));
			Assert::AreEqual(true, hash.Add("etcetera!"));

			Assert::AreEqual(10, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"etcetera,", hash["etcetera,"]);
			Assert::AreEqual((unsigned char*)"etcetera...", hash["etcetera..."]);
			Assert::AreEqual((unsigned char*)"etcetera!", hash["etcetera!"]);

			// try yet fail to add something else
			Assert::AreEqual(false, hash.Add("etcetera?????"));

			Assert::AreEqual(10, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			// make sure everything is still in the array
			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::AreEqual((unsigned char*)"x", hash["x"]);
			Assert::AreEqual((unsigned char*)"y", hash["y"]);
			Assert::AreEqual((unsigned char*)"z", hash["z"]);
			Assert::AreEqual((unsigned char*)"A", hash["A"]);
			Assert::AreEqual((unsigned char*)"AAA", hash["AAA"]);
		}
	};
}
