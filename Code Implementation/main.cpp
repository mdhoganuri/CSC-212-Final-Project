#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "Timer.h"

////////////////////////////////////////////////////////////////////////////////
// KMP Algorithm & Associated Functions																				//
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
// BM Algorithm & Associated Functions																				//
////////////////////////////////////////////////////////////////////////////////

void badCharRule(std::string str, int size, int badChar[256]){
    for (int i = 0; i < 256; i++)
        badChar[i] = -1;


    for (int i = 0; i < size; i++)
        badChar[(int) str[i]] = i;
}

void BM(std::string text, std::string pattern) {
    int pattLength = pattern.size();
    int textLength = text.size();

    int badChar[256];

    badCharRule(pattern, pattLength, badChar);

    int shift = 0;
    while(shift <= (textLength - pattLength))
    {
        int j = pattLength - 1;

        while(j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0)
        {
            std::cout << shift << " ";

            shift += (shift + pattLength < textLength)? pattLength - badChar[text[shift + pattLength]] : 1;
        } else
            shift += std::max(1, j - badChar[text[shift + j]]);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Main & Driver Functions																										//
////////////////////////////////////////////////////////////////////////////////

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

			std::cout << "Test Knuth-Morris-Pratt Algorithm" << std::endl;
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

			std::cout << "Test Boyer-Moore Algorithm" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "Enter Input: ";
			std::cin >> text;

			std::cout << "Enter Pattern: ";
			std::cin >> pattern;
			std::cout << "--------------------------------------------------" << std::endl;

			std::cout << "The pattern " << pattern << " occurs at ";
    	BM(text, pattern);
			std::cout << std::endl;
		}

		else if (input.compare("3") == 0) {
			std::ofstream outFile ("KMP.csv");

			std::cout << "Benchmark Knuth-Morris-Pratt Algorithm" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			if (outFile.is_open()) {
				std::string text[] = {"abcabcabcabcabcabc","abcabcabcabcabcabc","abcabcabcabcabcabcabc","abcabcabcabcabcabcabcabc","abcabcabcabcabcabcabcabcabc"},
				pattern = "abc";
				Timer timer;

				for (int i = 0; i < 4; i++) {
					std::cout << "Running case " << (i+1) << "; text = " << text[i] << "; ";

					timer.start();
					KMP(pattern, text[i]);
					timer.stop();

					outFile << std::fixed << std::setprecision(3) << text[i] << "," << timer.getDuration() << std::endl;

					std::cout << std::fixed << std::setprecision(3) << "; Took " << timer.getDuration() << "ms" << std::endl;
				}
				
				std::cout << "--------------------------------------------------" << std::endl;
				std::cout << "Benchmarking complete; \"KMP.csv\" saved." << std::endl;
			} else {
				std::cout << "ERROR - Unable to access file." << std::endl;
				std::cout << "--------------------------------------------------" << std::endl;
				std::cout << "Benchmarking incomplete!" << std::endl;
			}
		}

		else if (input.compare("4") == 0) {
			std::ofstream outFile ("BM.csv");

			std::cout << "Benchmark Boyer-Moore Algorithm" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			if (outFile.is_open()) {
				std::string text[] = {"abcabcabcabcabcabc","abcabcabcabcabcabc","abcabcabcabcabcabcabc","abcabcabcabcabcabcabcabc","abcabcabcabcabcabcabcabcabc"},
				pattern = "abc";
				Timer timer;

				for (int i = 0; i < 4; i++) {
					std::cout << "Running case " << (i+1) << "; text = " << text[i] << "; ";

					timer.start();
					BM(text[i], pattern);
					timer.stop();

					outFile << std::fixed << std::setprecision(3) << text[i] << "," << timer.getDuration() << std::endl;

					std::cout << std::fixed << std::setprecision(3) << "; Took " << timer.getDuration() << "ms" << std::endl;
				}
				
				std::cout << "--------------------------------------------------" << std::endl;
				std::cout << "Benchmarking complete; \"BM.csv\" saved." << std::endl;
			} else {
				std::cout << "ERROR - Unable to access file." << std::endl;
				std::cout << "--------------------------------------------------" << std::endl;
				std::cout << "Benchmarking incomplete!" << std::endl;
			}
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