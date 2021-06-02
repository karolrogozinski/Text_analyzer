#include "CppUnitTest.h"
#include "../Text Analizer/analyzer.h"
#include <string>
#include <sstream>
#include <iostream>

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

		//TEST_METHOD(TestOutFunctionPure)
		//{
		//	std::stringstream output;
		//	std::string expected_output, given_output;
		//	std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
		//	ParadigmWords para(text);

		//	output << para;
		//	given_output = output.str();
		//	expected_output = "Words' number is 15.";
		//	//std::vector< std::pair<char, std::string> > list = { a1, a2, a3 };
		//	//int number = ParadigmUnion(text, list);

		//	Assert::AreEqual(given_output, expected_output);
		//}

		TEST_METHOD(TestParadigmName1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmWords p(text);
			std::string expected = "Number of words ";
			Assert::AreEqual(expected, p.name());
		}

		TEST_METHOD(TestParadigmName2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmLongerThan p(text, 2);
			std::string expected = "Words longer than 2 chars ";
			Assert::AreEqual(expected, p.name());
		}

		TEST_METHOD(TestParadigmName3)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmStartsWithSequence p(text, "B");
			std::string expected = "Words starting with 'B' ";
			Assert::AreEqual(expected, p.name());
		}

		TEST_METHOD(TestParadigmName4)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmEndsOnSequence p(text, "ajwar");
			std::string expected = "Words ending on 'ajwar' ";
			Assert::AreEqual(expected, p.name());
		}

		TEST_METHOD(TestParadigmContainSequence1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmContainSequence p(text, "he water");
			Assert::AreEqual(p.number_of_words(), (int) 1);
		}

		TEST_METHOD(TestParadigmContainSequence2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion";
			ParadigmContainSequence p(text, "er");
			Assert::AreEqual(p.number_of_words(), (int)3);
		}

		TEST_METHOD(TestParadigmContainSequence3)
		{
			std::string text = "By the waters of Babylon there we sat down ande w glorious almie wghty ";
			ParadigmContainSequence p(text, "e w");
			Assert::AreEqual(p.number_of_words(), (int)4);
		}

		TEST_METHOD(TestParadigmContainSequenceSpace)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmContainSequence p(text, " ");
			Assert::AreEqual(p.number_of_words(), (int)0);
		}

		TEST_METHOD(TestParadigmContainSequenceSpaces)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmContainSequence p(text, "       ");
			Assert::AreEqual(p.number_of_words(), (int)0);
		}

		TEST_METHOD(TestParadigmContainSequenceEmpty)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmContainSequence p(text, "");
			Assert::AreEqual(p.number_of_words(), (int)0);
		}

		TEST_METHOD(TestParadigmContainSequenceEqual)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion  ";
			std::string text1 = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmContainSequence p(text, text1);
			Assert::AreEqual(p.number_of_words(), (int)1);
		}

		TEST_METHOD(TestParadigmCustom1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmCustom p(text, "(\\w+)");
			Assert::AreEqual(p.number_of_words(), (int)15);
		}

		TEST_METHOD(TestParadigmCustom2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmCustom p(text, "(\\w+){3}");
			Assert::AreEqual(p.number_of_words(), (int)11);
		}

		TEST_METHOD(TestParadigmCustom3)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			ParadigmCustom p(text, "(\\w+){6}");
			Assert::AreEqual(p.number_of_words(), (int)3);
		}

		TEST_METHOD(TestDescribeFilters)
		{
			std::pair<char, std::string> a1 = { 2, "3" };
			std::pair<char, std::string> a2 = { 5, "rura" };
			std::vector <std::pair<char, std::string>> filters = { a1, a2 };
			std::vector <std::string> description = describe_filters(filters);
			std::vector <std::string> expected = { "Length shorter than: 3", "End with sequence: rura" };

			bool out;
			description == expected ? out = true : out = false;
			Assert::AreEqual(out, true);
		}
	};




}
