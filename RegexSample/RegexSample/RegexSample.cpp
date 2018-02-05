// RegexSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <list>

int main()
{
	std::string s = "Some people, when confronted with a problem, think "
		"\"I know, I'll use regular expressions.\" "
		"Now they have two problems.";

	std::regex self_regex("RESULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);

	if (std::regex_search(s, self_regex)) {
		std::cout << "Text contains the phrase 'regular expressions'\n";		// DO
	}

	std::regex word_regex("(\\S+)");

	auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
	auto words_end = std::sregex_iterator();

	std::cout << "Found " << std::distance(words_begin, words_end) << "words\n";	// 19 words

	const int N = 6;

	std::cout << "Words greater than " << N << " characters:\n";		// 6

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {

		std::smatch match = *i;
		std::string match_str = match.str();

		if (match_str.size() > N) {
			std::cout << " " << match_str << "\n";						// people, confronted problem, regular expressions." problems
		}
	}

	std::regex long_words_regex("(\\w{7,})");

	std::string new_s = std::regex_replace(s, long_words_regex, "[$&]");
	std::cout << new_s << std::endl;									// Some people, when [confronted] with a [problem], think 
																		// "I know, I'll use [regular] [expressions]." Now they have two [problems].


	std::string t1 = "1 2 5 8 11 12 AB";
	
	std::regex s2("(?!(^1|1\\s)|(^2|2\\s)|(^8|8\\s)|(^12$|12\\s|\\s12$))\\d+");

	if (std::regex_search(t1, s2)) {
		std::cout << "searched" << std::endl;
	}
	else {
		std::cout << "unsearched" << std::endl;
	}

	if (std::regex_match(t1, s2)) {
		std::cout << "matched" << std::endl;
	}
	else {
		std::cout << "unmatched" << std::endl;
	}

	auto words_begin2 = std::sregex_iterator(t1.begin(), t1.end(), s2);
	auto words_end2 = std::sregex_iterator();

	std::cout << "Found = " << std::distance(words_begin2, words_end2) << std::endl;
	
	for (std::sregex_iterator i = words_begin2; i != words_end2; ++i) {

		std::smatch match = *i;
		std::string match_str = match.str();

		std::cout << " " << match_str << "\n";						// people, confronted problem, regular expressions." problems
	}

	std::list<int> v = { 1, 2, 8, 12 };
	// 이걸로 가야겠네
	std::regex s3("[^ \\t\\r\\n\\v\\fA-Za-z]+");
	
	auto begin2 = std::sregex_iterator(t1.begin(), t1.end(), s3);
	auto end2 = std::sregex_iterator();

	std::cout << "Split Found = " << std::distance(begin2, end2) << std::endl;

	for (auto i = begin2; i != end2; ++i) {

		std::smatch match = *i;
		std::string match_str = match.str();

		int number = std::stoi(match_str);

		std::cout << "matched str = " << number << std::endl;

		if (number != 1 && number != 2 && number != 8 && number != 12) {
			std::cout << "non fastmode" << std::endl;
		}

		auto itor = std::find_if_not(v.begin(), v.end(), [number](int i) { return i == number; });

		if (itor != std::end(v)) {
			std::cout << number << "is not fast speed mode" << std::endl;
		}
	}

    return 0;
}

