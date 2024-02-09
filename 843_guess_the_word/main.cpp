#include <iostream>
#include <vector>
#include <exception>
#include <random>
#include <unordered_set>

#include "master.h"

int NumSharedLetters(std::string a, std::string b)
{
    int shared = 0;

    if (a.length() == b.length())
    {
        for (int i = 0; i < a.length(); i++)
        {
            shared = (a[i] == b[i]) ? shared + 1 : shared;
        }
    }
    else
    {
        throw std::invalid_argument("Arguments have different length!");
    }

    return shared;
}

std::string GetNextGuess(
    std::string lastGuess, 
    int lastCorrect, 
    std::vector<std::string> &words, 
    std::unordered_set<std::string>& guessed)
{
    // The first guess is random.
    if (lastGuess.empty() == true)
    {
        std::random_device seed;
        std::mt19937 gen{seed()};
        std::uniform_int_distribution<> dist{ 0, (int)(words.size() - 1) };
        int guessIndex = dist(gen);
        return words[guessIndex];
    }

    // For subsequent guesses, chose an un-guessed word that shares the same number of letters
    // with the last guess as the last guess shares with the secret.
    for (std::string word : words)
    {
        if (guessed.count(word) == 0)
        {
            if (lastCorrect == 0)
            {
                return word;
            }
            else
            {
                if (NumSharedLetters(word, lastGuess) == lastCorrect)
                {
                    return word;
                }
            }
        }
    }

    return std::string();
}

void findSecretWord(std::vector<std::string> &words, Master &master)
{
    static constexpr int perfectMatch = 6;
    int correct = 0;
    std::unordered_set<std::string> guessed;
    std::string guessWord;
    int numGuesses = 1;

    while (correct != perfectMatch)
    {
        guessWord = GetNextGuess(guessWord, correct, words, guessed);
        if (guessWord.empty() == true)
        {
            std::cout << "All guesses exhausted!" << std::endl;
            return;
        }

        correct = master.guess(guessWord);
        if (correct == perfectMatch)
        {
            std::cout << "Correctly guessed " << guessWord << " after " << numGuesses << " guesses!" << std::endl;
            return;
        }

        guessed.insert(guessWord);
        numGuesses++;
    }
}

int main()
{
    std::vector<std::string> words = {"gaxckt","trlccr","jxwhkz","ycbfps","peayuf","yiejjw","ldzccp","nqsjoa","qrjasy","pcldos","acrtag","buyeia","ubmtpj","drtclz","zqderp","snywek","caoztp","ibpghw","evtkhl","bhpfla","ymqhxk","qkvipb","tvmued","rvbass","axeasm","qolsjg","roswcb","vdjgxx","bugbyv","zipjpc","tamszl","osdifo","dvxlxm","iwmyfb","wmnwhe","hslnop","nkrfwn","puvgve","rqsqpq","jwoswl","tittgf","evqsqe","aishiv","pmwovj","sorbte","hbaczn","coifed","hrctvp","vkytbw","dizcxz","arabol","uywurk","ppywdo","resfls","tmoliy","etriev","oanvlx","wcsnzy","loufkw","onnwcy","novblw","mtxgwe","rgrdbt","ckolob","kxnflb","phonmg","egcdab","cykndr","lkzobv","ifwmwp","jqmbib","mypnvf","lnrgnj","clijwa","kiioqr","syzebr","rqsmhg","sczjmz","hsdjfp","mjcgvm","ajotcx","olgnfv","mjyjxj","wzgbmg","lpcnbj","yjjlwn","blrogv","bdplzs","oxblph","twejel","rupapy","euwrrz","apiqzu","ydcroj","ldvzgq","zailgu","xgqpsr","wxdyho","alrplq","brklfk"};
    Master master(words, "sorbte");

    for (int i = 0; i < 10; i++)
    {
        findSecretWord1(words, master);
    }
}