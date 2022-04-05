/*
*	Author:	CS
*	Date:	2022_03_21	YYYY_MM_DD
*
*	A text file of Dorian Gray (public domain) is "cleaned up"
*	-	punctuation is deleted (rather than replaced with whitespace as per the question)
*	-	words are put into lowercase
*	-	don't is replaced with do not (shouldn't - should not)
*	-	plurals are replaced with their singular form (if two words are matching minus terminating s in one, the nonplural is set for all)
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

void convert_strvect_to_lowercase(std::vector<std::string>& vect);
void replace_contradictions(std::vector<std::string>& vect);
void delete_punctuation(std::vector<std::string>& vect);
void delete_plurals(std::vector<std::string>& vect); // only deletes plurals where singular form is shown

int main() {
	std::vector<std::string> vect;
	std::ifstream in{ "book.txt" };
	while (in)
	{
		std::string temp;
		in >> temp;
		if (in)
			vect.push_back(temp);
	}

	convert_strvect_to_lowercase(vect);
	replace_contradictions(vect);
	delete_punctuation(vect);
	delete_plurals(vect);

	std::ofstream out{ "output.txt" };
	for (auto temp : vect)
		out << temp << ' ';
	std::cout << "output.txt created." << std::endl;
	while (true)
	{
		// Enter for the number of occurences of x in the file
		std::cout << "Enter a word:" << std::endl;
		std::string query;
		std::cin >> query;
		int count{ 0 };
		for (int i = 0; i < vect.size(); i++)
			if (vect[i] == query)
				++count;
		std::cout << query << " appeared " << count;
		if (count == 1)
			std::cout << " time." << std::endl;
		else
			std::cout << " times." << std::endl;

		// (For question 14)
		// The work that occurs the most frequency:

		// The longest word is

		// The shortest word is

		// Enter string for all words starting with

		// All four letter words as follows
				// collect four letter words and sort
	}		

	return 0;
}

void convert_strvect_to_lowercase(std::vector<std::string>& vect) {
	// make lowercase
	for (int i = 0; i < vect.size(); ++i){
		for (int j = 0; j < vect[i].size(); ++j)
			if (isupper(vect[i][j]))
				vect[i][j] += 32;
	}
}

void replace_contradictions(std::vector<std::string>& vect) {
	// replace contractions (requires punctuation characters)
	for (int i = 0; i < vect.size(); i++) {
		if (vect[i] == "don't")
			vect[i] = "do not";
		else if (vect[i] == "shouldn't")
			vect[i] = "should not";
	}
}

void delete_punctuation(std::vector<std::string>& vect) {
	// delete punctuation characters (warning, including -) //empty entries are kept
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); ++j)
			if (ispunct(vect[i][j])) {
				auto string_it = vect[i].begin();
				std::advance(string_it, j);
				vect[i].erase(string_it);
				--i;
			}
	}
}

void delete_plurals(std::vector<std::string>& vect) {
	// identify words ending with an s and store them in a vector, sort this vector and unique it.
// use this to find if theres any words that match this bar the s, if so - delete all instances of the s version
	std::vector<std::pair<std::string, bool>> possible_plurals;
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i].size() > 0 && vect[i][vect[i].size() - 1] == 's')
			possible_plurals.push_back({ vect[i], false });
	}
	std::sort(possible_plurals.begin(), possible_plurals.end());
	possible_plurals.erase(std::unique(possible_plurals.begin(), possible_plurals.end()), possible_plurals.end());
	// now we have a list of all plurals, if we test for a single s deviation, mark the plural as true
	for (int i = 0; i < possible_plurals.size(); ++i)
	{
		if (possible_plurals[i].first.size() > 0) {
			std::string singular = possible_plurals[i].first;
			singular.pop_back();
			for (int j = 0; j < vect.size(); j++)
			{
				if (vect[j] == singular)
				{
					possible_plurals[i].second = true;
					j = vect.size();
				}
			}
		}
	}

	// trim possible plurals to confirmed plurals
	for (int i = 0; i < possible_plurals.size(); i++)
		if (possible_plurals[i].second == false)
		{
			auto it = possible_plurals.begin();
			std::advance(it, i);
			possible_plurals.erase(it);
			--i;
		}

	// pop the s off all matches
	for (int i = 0; i < possible_plurals.size(); ++i)
		for (int j = 0; j < vect.size(); ++j)
			if (possible_plurals[i].first == vect[j])
				vect[j].pop_back();
}