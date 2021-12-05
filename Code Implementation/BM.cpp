/* C++ Program for Bad Character Rule of Boyer Moore String Matching Algorithm */
#include <bits/stdc++.h>
#include <iostream>

void badCharRule(std::string str, int size, int badChar[256]){
    for (int i = 0; i < 256; i++)
        badChar[i] = -1;


    for (int i = 0; i < size; i++)
        badChar[(int) str[i]] = i;
}

void BMsearch(std::string text, std::string pattern) {
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
            std::cout << shift << " " << std::endl;

            shift += (shift + pattLength < textLength)? pattLength - badChar[text[shift + pattLength]] : 1;
        } else
            shift += std::max(1, j - badChar[text[shift + j]]);
    }
}

int main()
{
    std::string text = "ABAAABCDABC";
    std::string pattern = "ABC";
    BMsearch(text, pattern);
    return 0;
}