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

std::string GetRandomGuess(std::vector<std::string>& possibles)
{
    static std::random_device seed;
    static std::mt19937 gen{seed()};
    std::uniform_int_distribution<> dist{ 0, (int)(possibles.size() - 1) };
    int guessIndex = dist(gen);

    return possibles[guessIndex];
}

std::vector<std::string> GetPossiblesList(std::vector<std::string>& words, std::string lastGuess, int numCorrect)
{
    std::vector<std::string> temp;

    for (std::string word : words)
    {
        if (NumSharedLetters(word, lastGuess) == numCorrect)
        {
            temp.push_back(word);
        }
    }

    return temp;
}

void findSecretWord(std::vector<std::string> &words, Master &master)
{
    static constexpr int perfectMatch = 6;
    int numCorrect = 0;
    std::string guessWord;
    int numGuesses = 1;
    std::vector<std::string> possibles;

    guessWord = GetRandomGuess(words);
    numCorrect = master.guess(guessWord);
    possibles = GetPossiblesList(words, guessWord, numCorrect);
    if (possibles.empty() == true)
    {
        std::cout << "All guesses exhausted!" << std::endl;
        return;
    }

    while (numCorrect != perfectMatch)
    {
        guessWord = GetRandomGuess(possibles);

        numCorrect = master.guess(guessWord);

        std::vector<std::string> newPossibles;
        newPossibles = GetPossiblesList(possibles, guessWord, numCorrect);
        possibles = newPossibles;
        if (possibles.empty() == true)
        {
            std::cout << "All guesses exhausted!" << std::endl;
            return;
        }

        numGuesses++;
    }

    std::cout << "Correctly guessed " << guessWord << " after " << numGuesses << " guesses!" << std::endl;
}

int main()
{
    std::vector<std::string> words = {"gaxckt","trlccr","jxwhkz","ycbfps","peayuf","yiejjw","ldzccp","nqsjoa","qrjasy","pcldos","acrtag","buyeia","ubmtpj","drtclz","zqderp","snywek","caoztp","ibpghw","evtkhl","bhpfla","ymqhxk","qkvipb","tvmued","rvbass","axeasm","qolsjg","roswcb","vdjgxx","bugbyv","zipjpc","tamszl","osdifo","dvxlxm","iwmyfb","wmnwhe","hslnop","nkrfwn","puvgve","rqsqpq","jwoswl","tittgf","evqsqe","aishiv","pmwovj","sorbte","hbaczn","coifed","hrctvp","vkytbw","dizcxz","arabol","uywurk","ppywdo","resfls","tmoliy","etriev","oanvlx","wcsnzy","loufkw","onnwcy","novblw","mtxgwe","rgrdbt","ckolob","kxnflb","phonmg","egcdab","cykndr","lkzobv","ifwmwp","jqmbib","mypnvf","lnrgnj","clijwa","kiioqr","syzebr","rqsmhg","sczjmz","hsdjfp","mjcgvm","ajotcx","olgnfv","mjyjxj","wzgbmg","lpcnbj","yjjlwn","blrogv","bdplzs","oxblph","twejel","rupapy","euwrrz","apiqzu","ydcroj","ldvzgq","zailgu","xgqpsr","wxdyho","alrplq","brklfk"};
    Master master(words, "hbaczn");

    for (int i = 0; i < 10; i++)
    {
        findSecretWord(words, master);
    }
}