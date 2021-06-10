#include "CppUnitTest.h"
#include "../Text Analizer/paradigms.h"
#include "../Text Analizer/paradigm_functions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testanalyzer
{
	TEST_CLASS(testanalyzer)
	{
	public:
		
		TEST_METHOD(TestParadigmWordsNormal)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			ParadigmWords p;

			int number = p.number_of_words(words);

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmWordsEmptyString)
		{
			std::string text = "";
			std::vector <std::string> words = split_string(text);
			ParadigmWords p;

			int number = p.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmWordsCorruptedText1)
		{
			std::string text = "By the waters of Babylon , there we sat down and wept , when we remembered Zion . ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);
			ParadigmWords p;

			int number = p.number_of_words(words);

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmWordsCorruptedText2)
		{
			std::string text = "By the waters of Babylon ,Zion43[[[[ :D4'' '' '8' ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);
			ParadigmWords p;

			int number = p.number_of_words(words);

			Assert::AreEqual(number, 7);
		}
		
		TEST_METHOD(TestParadigmLongerThanNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);
			std::string word = "3";
			ParadigmLongerThan p(word);
			ParadigmWords p2;
			p.find_pattern(words);

			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestParadigmLongerThanEmptyText)
		{
			std::string text = "";
			std::vector <std::string> words = split_string(text);

			ParadigmLongerThan p("3");
			ParadigmWords p2;
			p.find_pattern(words);

			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmLongerThanNegativeLen)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);

			ParadigmLongerThan p("-10");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmLongerThanCorruptedText)
		{
			std::string text = "By the waters of Babylon ,Zion43[[[[ :D4'' '' '8' ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			ParadigmLongerThan p("2");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 4);
		}

		TEST_METHOD(TestParadigmShorterThanNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);


			ParadigmShorterThan p("4");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 7);
		}

		TEST_METHOD(TestParadigmShorterThanNegativeLen)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);


			ParadigmShorterThan p("-10");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmEqualLengthNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			ParadigmEqualLength p("2");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 4);
		}

		TEST_METHOD(TestParadigmEqualLengthNegativeLen)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			ParadigmEqualLength p("-2");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "B";
			ParadigmStartsWithSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 2);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceEmptyPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "";
			ParadigmStartsWithSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceLongPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "ylon";
			ParadigmStartsWithSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceEmptyString)
		{
			std::string text = "";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "e";
			ParadigmStartsWithSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmStartsWithSequenceLongString)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "wep";
			ParadigmStartsWithSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 1);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceNormal)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "e";
			ParadigmEndsOnSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 4);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceEmptyPattern)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "";
			ParadigmEndsOnSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceEmptyString)
		{
			std::string text = "";
			std::vector <std::string> words = split_string(text);

			std::string letter = "eo";
			ParadigmEndsOnSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words); 

			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmEndsOnSequenceLongPattern)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion waters ";
			text = clean_string(text);
			std::vector <std::string> words = split_string(text);

			std::string letter = "ers";
			ParadigmEndsOnSequence p(letter);
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 2); //
		}

		TEST_METHOD(TestParadigmContainSequence1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);

			ParadigmContainSequence p("e");
			ParadigmWords p2;
			
			p.find_pattern(words);
			int number = p2.number_of_words(words);

			Assert::AreEqual(number, 8);
		}
		
		TEST_METHOD(TestParadigmContainSequence2)
		{
			std::string text = "By the waters of Babylon and there we sat down and wept when we remembered Zion and ";
			std::vector <std::string> words = split_string(text);

			ParadigmContainSequence p("and");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 3);
		}
		
		TEST_METHOD(TestParadigmContainSequenceEmpty)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);

			ParadigmContainSequence p("");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmContainSequenceSpaces)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);

			ParadigmContainSequence p("  ");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 0);
		}

		TEST_METHOD(TestParadigmCustom1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			ParadigmCustom p("(\\w+)");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmCustom2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			ParadigmCustom p("(\\w+){3}");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 11);
		}

		TEST_METHOD(TestParadigmCustom3)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			ParadigmCustom p("(\\w+){6}");
			ParadigmWords p2;
			p.find_pattern(words);
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 3);
		}

		TEST_METHOD(TestGetIntersection1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::unique_ptr <IParadigm> p(new ParadigmLongerThan("2"));
			std::unique_ptr <IParadigm> p1(new ParadigmShorterThan("5"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			words = get_intersection(words, paradigms);
			ParadigmWords p2;
			int number = p2.number_of_words(words);
			Assert::AreEqual(number, 7);
		}

		TEST_METHOD(TestGetIntersection2)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("w"));
			std::unique_ptr<IParadigm> p1(new ParadigmLongerThan("2"));
			std::unique_ptr<IParadigm> p2(new ParadigmShorterThan("6"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			words = get_intersection(words, paradigms);
			ParadigmWords P;
			int number = P.number_of_words(words);

			Assert::AreEqual(number, 2);
		}

		TEST_METHOD(TestGetIntersection3)
		{
			std::string text = "By the waters of Babylon, there we sat down and wept, when we there remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::pair <char, std::string> a1(1, "2");
			std::pair <char, std::string> a2(2, "6");
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("th"));
			std::unique_ptr<IParadigm> p1(new ParadigmEndsOnSequence("e"));
			std::unique_ptr<IParadigm> p2(new ParadigmContainSequence("r"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			words = get_intersection(words, paradigms);
			ParadigmWords P;
			int number = P.number_of_words(words);

			Assert::AreEqual(number, 2);
		}

		TEST_METHOD(TestParadigmUnion1)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::pair <char, std::string> a1(4, "w");
			std::pair <char, std::string> a2(1, "2");
			std::pair <char, std::string> a3(2, "6");
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("w"));
			std::unique_ptr<IParadigm> p1(new ParadigmLongerThan("2"));
			std::unique_ptr<IParadigm> p2(new ParadigmShorterThan("6"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			words = get_union(words, paradigms);
			ParadigmWords P;
			int number = P.number_of_words(words);

			Assert::AreEqual(number, 15);
		}

		TEST_METHOD(TestParadigmUnion2)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::unique_ptr<IParadigm> p(new ParadigmLongerThan("5"));
			std::unique_ptr<IParadigm> p1(new ParadigmShorterThan("3"));
			std::unique_ptr<IParadigm> p2(new ParadigmEqualLength("4"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			words = get_union(words, paradigms);
			ParadigmWords P;
			int number = P.number_of_words(words);

			Assert::AreEqual(number, 11);
		}

		TEST_METHOD(TestParadigmUnion3)
		{
			std::string text = "By the waters of Babylon there we sat down and wept when we remembered Zion ";
			std::vector <std::string> words = split_string(text);
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("B"));
			std::unique_ptr<IParadigm> p1(new ParadigmEndsOnSequence("n"));
			std::unique_ptr<IParadigm> p2(new ParadigmEqualLength("2"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			words = get_union(words, paradigms);
			ParadigmWords P;
			int number = P.number_of_words(words);

			Assert::AreEqual(number, 8);
		}

		TEST_METHOD(TestDescribeFilters)
		{
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("B"));
			std::unique_ptr<IParadigm> p1(new ParadigmEndsOnSequence("n"));
			std::unique_ptr<IParadigm> p2(new ParadigmEqualLength("2"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			std::vector <std::string> description = describe_filters(paradigms);
			std::vector <std::string> expected = { "Start with sequence: B", "End with sequence: n", "Length equal: 2" };

			bool out;
			description == expected ? out = true : out = false;
			Assert::AreEqual(out, true);
		}

 
		TEST_METHOD(TestEreaseParadigmOneElement)
		{
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("B"));
			std::unique_ptr<IParadigm> p1(new ParadigmEndsOnSequence("n"));
			std::unique_ptr<IParadigm> p2(new ParadigmEqualLength("2"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));
			int index = 1;

			erease_paradigm(paradigms, index);

			//std::vector <std::unique_ptr<IParadigm>> expected_list;
			//std::unique_ptr<IParadigm> p3(new ParadigmStartsWithSequence("B"));
			//std::unique_ptr<IParadigm> p4(new ParadigmEqualLength("2"));
			//expected_list.push_back(std::move(p3));
			//expected_list.push_back(std::move(p4));
			//bool out;
			
			std::unique_ptr <IParadigm> ptr1 = std::move(paradigms[0]);
			std::unique_ptr <IParadigm> ptr2 = std::move(paradigms[1]);

			std::string param1 = ptr1->get_param();
			std::string param2 = ptr2->get_param();
			std::string to_compare1 = "B";
			std::string to_compare2 = "2";
			Assert::AreEqual(param1, to_compare1);
			Assert::AreEqual(param2, to_compare2);

		}


		TEST_METHOD(TestEreaseParadigmAllElements)
		{
			std::unique_ptr<IParadigm> p(new ParadigmStartsWithSequence("B"));
			std::unique_ptr<IParadigm> p1(new ParadigmEndsOnSequence("n"));
			std::unique_ptr<IParadigm> p2(new ParadigmEqualLength("2"));
			std::vector <std::unique_ptr<IParadigm>> paradigms;
			paradigms.push_back(std::move(p));
			paradigms.push_back(std::move(p1));
			paradigms.push_back(std::move(p2));

			std::vector <int> indexes = { 2, 1, 0 };
			for (auto index : indexes) {
				erease_paradigm(paradigms, index);
			}


			std::vector <std::unique_ptr<IParadigm>> expected_list = {};

			bool out;
			paradigms == expected_list ? out = true : out = false;

			Assert::AreEqual(out, true);
		}
	 };


}
