#include "CppUnitTest.h"
#include "../Text Analizer/analyzer.h"
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testanalyzer
{
	TEST_CLASS(testanalyzer)
	{
	public:
		
		TEST_METHOD(TestParadigmWordsNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmWords para(text);

			int number = para.number_of_words();

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmWordsEmptyString)
		{
			std::string text = "";
			ParadigmWords para(text);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmWordsCorruptedText1)
		{
			std::string text = "By the waters of Babylon , there we sat down and wept , when we remembered Zion . ";
			ParadigmWords para(text);

			int number = para.number_of_words();

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmWordsCorruptedText2)
		{
			std::string text = "By the waters of Babylon ,Zion43[[[[ :D4'' '' '8' ";
			ParadigmWords para(text);

			int number = para.number_of_words();

			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestParadigmLongerThanNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmLongerThan para(text, 3);

			int number = para.number_of_words();

			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestParadigmLongerThanEmptyText)
		{
			std::string text = "";
			ParadigmLongerThan para(text, 3);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmLongerThanNegativeLen)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmLongerThan para(text, -10);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmLongerThanCorruptedText)
		{
			std::string text = "By the waters of Babylon ,Zion43[[[[ :D4'' '' '8' ";
			ParadigmLongerThan para(text, 1);

			int number = para.number_of_words();

			Assert::AreEqual(number, 7);
		}

		TEST_METHOD(TestParadigmShorterThanNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmShorterThan para(text, 4);

			int number = para.number_of_words();

			Assert::AreEqual(number, 7);
		}

		TEST_METHOD(TestParadigmShorterThanNegativeLen)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmShorterThan para(text, -10);

			int number = para.number_of_words();

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmEqualLengthNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmEqualLength para(text, 2);

			int number = para.number_of_words();

			Assert::AreEqual(number, 4);
		}

		TEST_METHOD(TestParadigmEqualLengthNegativeLen)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			ParadigmEqualLength para(text, -2);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "B";
			ParadigmStartsWithSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 2);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceEmptyPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "";
			ParadigmStartsWithSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceLongPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "ylon";
			ParadigmStartsWithSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceEmptyString)
		{
			std::string text = "";
			std::string letter = "e";
			ParadigmStartsWithSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceLongString)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "wep";
			ParadigmStartsWithSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 1);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "e";
			ParadigmEndsOnSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 4);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceEmptyPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::string letter = "";
			ParadigmEndsOnSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceEmptyString)
		{
			std::string text = "";
			std::string letter = "eo";
			ParadigmEndsOnSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceLongPattern)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion waters ";
			std::string letter = "ers";
			ParadigmEndsOnSequence para(text, letter);

			int number = para.number_of_words();

			Assert::AreEqual(number, 2); //
		}

		TEST_METHOD(TestParadigmIntersection1)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::pair <char, std::string> a1(1, "2");
			std::pair <char, std::string> a2(2, "6");
			std::vector< std::pair<char, std::string> > list = {a1, a2};
			int number = ParadigmIntersection(text, list);


			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestParadigmIntersection2)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			std::pair <char, std::string> a1(4, "w");
			std::pair <char, std::string> a2(1, "2");
			std::pair <char, std::string> a3(2, "6");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a3 };
			int number = ParadigmIntersection(text, list);

			Assert::AreEqual(number, 2);
		}

		TEST_METHOD(TestParadigmUnion1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			std::pair <char, std::string> a1(4, "w");
			std::pair <char, std::string> a2(1, "2");
			std::pair <char, std::string> a3(2, "6");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a3 };
			int number = ParadigmUnion(text, list);

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmUnion2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			std::pair <char, std::string> a1(1, "5");
			std::pair <char, std::string> a2(2, "3");
			std::pair <char, std::string> a3(3, "4");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a3 };
			int number = ParadigmUnion(text, list);

			Assert::AreEqual(number, 11);
		}

		TEST_METHOD(TestParadigmUnion3)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			std::pair <char, std::string> a1(4, "B");
			std::pair <char, std::string> a2(5, "n");
			std::pair <char, std::string> a3(3, "2");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a3 };
			int number = ParadigmUnion(text, list);

			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestEreaseParadigmOneElement)
		{
			std::pair <char, std::string> a1(4, "B");
			std::pair <char, std::string> a2(5, "n");
			std::pair <char, std::string> a3(3, "2");
			std::pair <char, std::string> a4(1, "2");
			std::pair <char, std::string> a5(0, "");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a3, a4, a5 };
			int index = 3;

			list = erease_paradigm(list, index);

			std::vector< std::pair<char, std::string> > expected_list = {a1, a2, a4, a5};
			bool out;

			list == expected_list ? out = true : out = false;

			Assert::AreEqual(out, true);
		}

		TEST_METHOD(TestEreaseParadigmTwoElements)
		{
			std::pair <char, std::string> a1(4, "B");
			std::pair <char, std::string> a2(5, "n");
			std::pair <char, std::string> a3(3, "2");
			std::pair <char, std::string> a4(1, "2");
			std::pair <char, std::string> a5(0, "");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a4, a5 };

			int index = 3;
			list = erease_paradigm(list, index);
			index = 4;
			list = erease_paradigm(list, index);

			std::vector< std::pair<char, std::string> > expected_list = { a2, a4, a5 };

			bool out;
			list == expected_list ? out = true : out = false;

			Assert::AreEqual(out, true);
		}

		TEST_METHOD(TestEreaseParadigmAllElements)
		{
			std::pair <char, std::string> a1(4, "B");
			std::pair <char, std::string> a2(5, "n");
			std::pair <char, std::string> a3(3, "2");
			std::pair <char, std::string> a4(1, "2");
			std::pair <char, std::string> a5(0, "");
			std::vector< std::pair<char, std::string> > list = { a1, a2, a4, a5 };

			int index = 3;
			list = erease_paradigm(list, index);
			index = 4;
			list = erease_paradigm(list, index);
			index = 5;
			list = erease_paradigm(list, index);
			index = 0;
			list = erease_paradigm(list, index);
			index = 1;
			list = erease_paradigm(list, index);

			std::vector< std::pair<char, std::string> > expected_list = {};

			bool out;
			list == expected_list ? out = true : out = false;

			Assert::AreEqual(out, true);
		}
	};
}
