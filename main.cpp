#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Timer.h"

// Longest proper prefix / suffix
void makeLPS(std::string text, std::vector<int> & lps){
    lps[0] = 0;
    int length = 0;
    int i = 1;
		
    while (i < text.length()){
        if(text[i] == text[length]){
            length++;
            lps[i] = length;
            i++;
        }
        else{
            if(length == 0){
                lps[i] = 0;
                i++;
            }
            else{
                length = lps[length - 1];
          }
        }
    }
}

// Knuth-Morris-Pratt Algorithm
void KMP(std::string pattern,std::string text){
    int textLength = text.length();
    int pattLength = pattern.length();
    std::vector<int> lps (pattLength);

    makeLPS(pattern,lps);

    int i = 0, j = 0;
		
    while(i < textLength){
        if(pattern[j] == text[i]){
					i++;
					j++;
				}
				
        if (j == pattLength) {
            std::cout<< i - pattLength << ' ';
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j == 0){
							i++;
						} else {
                j = lps[j - 1];
						}
        }
    }
}

void printMenu() {
	std::cout << std::endl;
	std::cout << "String Search II Project" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "1\tTest Knuth-Morris-Pratt Algorithm" << std::endl;
	std::cout << "2\tTest Boyer-Moore Algorithm" << std::endl;
	std::cout << "3\tBenchmark Knuth-Morris-Pratt Algorithm" << std::endl;
	std::cout << "4\tBenchmark Boyer-Moore Algorithm" << std::endl;
	std::cout << "5\tExit Program" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Choose an Option: ";
}

int main() {
	std::string input = "";

	while (input.compare("5") != 0) {
		printMenu();
		std::cin >> input;
		std::cout << std::endl;

		if (input.compare("1") == 0) {
			std::string text, pattern;

			std::cout << "Knuth-Morris-Pratt Algorithm" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "Enter Input: ";
			std::cin >> text;

			std::cout << "Enter Pattern: ";
			std::cin >> pattern;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "The pattern " << pattern << " occurs at ";
    	KMP(pattern, text);
			std::cout << std::endl;
		}

		else if (input.compare("2") == 0) {
			std::string text, pattern;

			std::cout << "Boyer-Moore Algorithm" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "Enter Input: ";
			std::cin >> text;

			std::cout << "Enter Pattern: ";
			std::cin >> pattern;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "The pattern " << pattern << " occurs at ";
    	//KMP(pattern, text);
			std::cout << std::endl;
		}

		else if (input.compare("3") == 0) {
			std::string text = "abbbbcbcbabcaaaaaabbbbcabcbbb", pattern = "abc";
			Timer timer;

			timer.start();
			KMP(pattern, text);
			timer.stop();

			std::cout << std::fixed << std::setprecision(6) << "Took " << timer.getDuration() << "s" << std::endl;
		}

		else if (input.compare("4") == 0) {
			
		}

		else if (input.compare("5") == 0) {
			std::cout << "Goodbye!" << std::endl;
		}

		else {
			std::cout << "Invalid input; please enter a number (1 - 3)." << std::endl;
		}
	}

	return 0;
}