#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int nrOfWords;
    std::vector<std::string> words;
    /* bitset used to memorise if a specific letter appears or not in words */
    std::bitset<26> letterOccurances;

    void read_input() {
        std::ifstream fin("statistics.in");
        fin >> nrOfWords;
        for (int i = 0; i < nrOfWords; i++) {
            std::string currentString;
            fin >> currentString;
            for (unsigned int i = 0; i < currentString.size(); i++) {
                letterOccurances.set(currentString[i] - 'a', true);
            }
            words.push_back(currentString);
        }
        fin.close();
    }

    /* 
     * calculates the advantage of a specific letter over
     * the rest letters in a given word
     *      return: 0 - the letter occurances is half of the word's length
     *              >0 - number of appearances over half of the word's length
     *              <0 - number of necessary letters so the letter
     *                   would be half of the word's length
     */
    int calculateLeverage(std::string word, char letter) {
        int letterOccurances = 0;

        for (unsigned int i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                letterOccurances++;
            }
        }

        return 2 * letterOccurances - word.size();
    }

    /* calculates the maximum number of words
     * which can be chosen in order to 
     * respect the rule given in the task, for a specific letter
     * A greedy aproach is used.
     */
    int letterMaxWords(char letter) {
        int wordsNumber = 0;

        std::vector<int> leverages;
        for (int i = 0; i < nrOfWords; i++) {
            leverages.push_back(calculateLeverage(words[i], letter));
        }

        std::sort(leverages.begin(), leverages.end());

        int wordsLeverage = leverages[leverages.size() - 1];
        int i = leverages.size() - 1;
        while (wordsLeverage > 0 && i >= 0) {
            wordsNumber++;
            wordsLeverage += leverages[--i];
        }

        return wordsNumber;
    }

    int get_result() {
        int result = 0;

        for (int i = 0; i < 26; i++) {
            if (letterOccurances[i] == true) {
                char currentLetter = 'a' + i;
                int currentLetterMax = letterMaxWords(currentLetter);
                if (currentLetterMax > result) {
                    result = currentLetterMax;
                }

                currentLetter++;
            }
        }

        return result;
    }

    void print_output(int result) {
        std::ofstream fout("statistics.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new Task();
    if (!task) {
        std::cerr << "Task #2 constructor failed!\n";
        return -1;
    }

    task->solve();
    delete task;

    return 0;
}
