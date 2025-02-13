#include "pch.h"
#include "CppUnitTest.h"

#include "../Set/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
		TEST_METHOD(BaseConstructor)
		{
			HashTable hash = HashTable();
			Assert::AreEqual(100, hash.GetArrayLength());

			HashTable hoosh = HashTable(42);
			Assert::AreEqual(42, hoosh.GetArrayLength());

			HashTable heesh = HashTable(999999);
			Assert::AreEqual(999999, heesh.GetArrayLength());
		}

		TEST_METHOD(CharPointerArrayConstructor)
		{
			char* values[10] = { "bing", "bop", "bam", "pow", "slam", "foo", "bar", "x", "y", "z" };

			HashTable hash = HashTable(values, 10);

			// make sure all of the values are in there
			Assert::AreEqual(10, hash.GetCount());
			Assert::AreEqual(20, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("bing"));
			Assert::IsTrue(hash.Contains("bop"));
			Assert::IsTrue(hash.Contains("bam"));
			Assert::IsTrue(hash.Contains("pow"));
			Assert::IsTrue(hash.Contains("slam"));
			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			Assert::IsFalse(hash.Contains("rab"));
			Assert::IsFalse(hash.Contains("mals"));
			Assert::IsFalse(hash.Contains("Pow"));
		}

		TEST_METHOD(InitializerListConstructor)
		{
			HashTable hash = { "the entire bee movie script", "uhhh", "joker the jimbo", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony", "agony"};

			Assert::AreEqual(4, hash.GetCount());

			// make sure things are in there
			Assert::AreEqual((unsigned char*)"the entire bee movie script", hash["the entire bee movie script"]);
			Assert::AreEqual((unsigned char*)"uhhh", hash["uhhh"]);
			Assert::AreEqual((unsigned char*)"joker the jimbo", hash["joker the jimbo"]);
			Assert::AreEqual((unsigned char*)"agony", hash["agony"]);

			// make sure things that arent  in there arent in there
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

			// return false and do nothing if trying to add nullptr
			Assert::AreEqual(false, hash.Add(nullptr));
			Assert::AreEqual(false, hash.Add(nullptr));

			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

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
			Assert::AreEqual(false, hash.Add("etcetera????????????"));

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
			Assert::AreEqual((unsigned char*)"etcetera,", hash["etcetera,"]);
			Assert::AreEqual((unsigned char*)"etcetera...", hash["etcetera..."]);
			Assert::AreEqual((unsigned char*)"etcetera!", hash["etcetera!"]);
		}

		TEST_METHOD(Remove)
		{
			HashTable hash = { "foo", "bar", "x", "y", "z", "a", "b", "c" };

			// make sure nothing is wrong with the constructor at all
			Assert::AreEqual(8, hash.GetCount());
			Assert::AreEqual(16, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::AreEqual((unsigned char*)"x", hash["x"]);
			Assert::AreEqual((unsigned char*)"y", hash["y"]);
			Assert::AreEqual((unsigned char*)"z", hash["z"]);
			Assert::AreEqual((unsigned char*)"a", hash["a"]);
			Assert::AreEqual((unsigned char*)"b", hash["b"]);
			Assert::AreEqual((unsigned char*)"c", hash["c"]);


			// remove something that does exist and try removing it again
			Assert::AreEqual(true, hash.Remove("a"));
			Assert::AreEqual(false, hash.Remove("a"));
			Assert::AreEqual(false, hash.Remove("a"));

			// check everything all over again
			Assert::AreEqual(7, hash.GetCount());
			Assert::AreEqual(16, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::AreEqual((unsigned char*)"x", hash["x"]);
			Assert::AreEqual((unsigned char*)"y", hash["y"]);
			Assert::AreEqual((unsigned char*)"z", hash["z"]);
			Assert::IsNull(hash["a"]);
			Assert::AreEqual((unsigned char*)"b", hash["b"]);
			Assert::AreEqual((unsigned char*)"c", hash["c"]);

			// remove something that was never in the hash table to begin with
			Assert::AreEqual(false, hash.Remove("u"));
			Assert::AreEqual(false, hash.Remove("L"));
			Assert::AreEqual(false, hash.Remove("position"));

			Assert::AreEqual(7, hash.GetCount());
			Assert::AreEqual(16, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::AreEqual((unsigned char*)"x", hash["x"]);
			Assert::AreEqual((unsigned char*)"y", hash["y"]);
			Assert::AreEqual((unsigned char*)"z", hash["z"]);
			Assert::IsNull(hash["a"]);
			Assert::AreEqual((unsigned char*)"b", hash["b"]);
			Assert::AreEqual((unsigned char*)"c", hash["c"]);

			// destroy a buncha stuff
			Assert::AreEqual(true, hash.Remove("b"));
			Assert::AreEqual(true, hash.Remove("c"));
			Assert::AreEqual(true, hash.Remove("z"));
			Assert::AreEqual(true, hash.Remove("y"));
			Assert::AreEqual(true, hash.Remove("x"));

			Assert::AreEqual(2, hash.GetCount());
			Assert::AreEqual(16, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::IsNull(hash["x"]);
			Assert::IsNull(hash["y"]);
			Assert::IsNull(hash["z"]);
			Assert::IsNull(hash["a"]);
			Assert::IsNull(hash["b"]);
			Assert::IsNull(hash["c"]);

			// add something then remove it immediately
			Assert::AreEqual(true, hash.Add("CORN"));
			Assert::AreEqual(true, hash.Remove("CORN"));
			Assert::AreEqual(true, hash.Add("CORN"));
			Assert::AreEqual(true, hash.Remove("CORN"));

			Assert::AreEqual(2, hash.GetCount());
			Assert::AreEqual(16, hash.GetArrayLength());

			Assert::AreEqual((unsigned char*)"foo", hash["foo"]);
			Assert::AreEqual((unsigned char*)"bar", hash["bar"]);
			Assert::IsNull(hash["CORN"]);
		}

		TEST_METHOD(Resize)
		{
			HashTable hash = { "foo", "bar", "x", "y", "z" };
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			// try resizing it to larger and larger numbers
			hash.Resize(50);
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(50, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			hash.Resize(100);
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(100, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			hash.Resize(10000);
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(10000, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			hash.Resize(500);

			hash.Resize(5);
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(5, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			hash.Resize(1);
			Assert::AreEqual(1, hash.GetCount());
			Assert::AreEqual(1, hash.GetArrayLength());

			// if it contains any of these it's good and it's fine ok ?
			Assert::IsTrue(hash.Contains("foo") ||
				hash.Contains("bar") ||
				hash.Contains("x") ||
				hash.Contains("y") ||
				hash.Contains("z"));
		}

		TEST_METHOD(Contains)
		{
			HashTable hash = { "foo", "bar", "x", "y", "z" };

			// check if it finds what is is the hash table
			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			// and if it doesn't find what isn't in it
			Assert::IsFalse(hash.Contains("FoO"));
			Assert::IsFalse(hash.Contains("Foo"));
			Assert::IsFalse(hash.Contains("fOO"));
			Assert::IsFalse(hash.Contains("BAr"));
			Assert::IsFalse(hash.Contains("BaR"));
			Assert::IsFalse(hash.Contains("X"));
			Assert::IsFalse(hash.Contains("Y"));
			Assert::IsFalse(hash.Contains("Z"));

			// check if it doesn't find things that are removed
			hash.Remove("foo");
			hash.Remove("bar");

			Assert::IsFalse(hash.Contains("foo"));
			Assert::IsFalse(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			// check if it finds them after they're added back
			hash.Add("foo");
			hash.Add("bar");
			
			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			// check if it finds new things added in
			hash.Add("a");
			hash.Add("b");
			hash.Add("c");

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));
			Assert::IsTrue(hash.Contains("a"));
			Assert::IsTrue(hash.Contains("b"));
			Assert::IsTrue(hash.Contains("c"));
		}

		TEST_METHOD(Clear)
		{
			HashTable hash = { "foo", "bar", "x", "y", "z" };
			Assert::AreEqual(5, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("foo"));
			Assert::IsTrue(hash.Contains("bar"));
			Assert::IsTrue(hash.Contains("x"));
			Assert::IsTrue(hash.Contains("y"));
			Assert::IsTrue(hash.Contains("z"));

			hash.Clear();

			Assert::AreEqual(0, hash.GetCount());
			Assert::AreEqual(10, hash.GetArrayLength());

			Assert::IsFalse(hash.Contains("foo"));
			Assert::IsFalse(hash.Contains("bar"));
			Assert::IsFalse(hash.Contains("x"));
			Assert::IsFalse(hash.Contains("y"));
			Assert::IsFalse(hash.Contains("z"));

			hash.Resize(15);

			Assert::AreEqual(15, hash.GetArrayLength());

			hash.Add("MAB");
			hash.Add("BAM");
			hash.Add("PAM");
			hash.Add("MAP");
			hash.Add("MAD");
			hash.Add("DAM");
			hash.Add("DAD");
			hash.Add("DAN");
			hash.Add("FAN");
			hash.Add("FAX");
			hash.Add("TAX");
			hash.Add("SAX");
			hash.Add("WAX");
			hash.Add("WAM");
			hash.Add("MAW");

			Assert::AreEqual(15, hash.GetCount());
			Assert::AreEqual(15, hash.GetArrayLength());

			Assert::IsTrue(hash.Contains("MAB"));
			Assert::IsTrue(hash.Contains("BAM"));
			Assert::IsTrue(hash.Contains("PAM"));
			Assert::IsTrue(hash.Contains("MAP"));
			Assert::IsTrue(hash.Contains("MAD"));
			Assert::IsTrue(hash.Contains("DAM"));
			Assert::IsTrue(hash.Contains("DAD"));
			Assert::IsTrue(hash.Contains("DAN"));
			Assert::IsTrue(hash.Contains("FAN"));
			Assert::IsTrue(hash.Contains("FAX"));
			Assert::IsTrue(hash.Contains("TAX"));
			Assert::IsTrue(hash.Contains("SAX"));
			Assert::IsTrue(hash.Contains("WAX"));
			Assert::IsTrue(hash.Contains("WAM"));
			Assert::IsTrue(hash.Contains("MAW"));

			hash.Clear();

			Assert::AreEqual(0, hash.GetCount());
			Assert::AreEqual(15, hash.GetArrayLength());

			Assert::IsFalse(hash.Contains("MAB"));
			Assert::IsFalse(hash.Contains("BAM"));
			Assert::IsFalse(hash.Contains("PAM"));
			Assert::IsFalse(hash.Contains("MAP"));
			Assert::IsFalse(hash.Contains("MAD"));
			Assert::IsFalse(hash.Contains("DAM"));
			Assert::IsFalse(hash.Contains("DAD"));
			Assert::IsFalse(hash.Contains("DAN"));
			Assert::IsFalse(hash.Contains("FAN"));
			Assert::IsFalse(hash.Contains("FAX"));
			Assert::IsFalse(hash.Contains("TAX"));
			Assert::IsFalse(hash.Contains("SAX"));
			Assert::IsFalse(hash.Contains("WAX"));
			Assert::IsFalse(hash.Contains("WAM"));
			Assert::IsFalse(hash.Contains("MAW"));
		}
	};
}
