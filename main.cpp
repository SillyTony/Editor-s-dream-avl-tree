#include <iostream>
#include"ctime"
#include"Avltree_vec.h"
#include <fstream>
#include <string>
#include<ctime>
#include <sstream>
#include <conio.h>
#include <cstdlib>

using namespace std;

void save(avltree<string> [], vector<pair<int, string> > pop, int totalWords, int paragraphNum, double rL, double speed);

int main()
{
    avltree<string>  words[26];
    vector<pair<int,string> > popularWords;
    ifstream input;
    int totalVowels = 0, sentenceNumber = 0, paragraphNumber = 0,lineNumber =0,doubleHyp;
    double readingLevel, speed;
    time_t start = clock(), end;
    int total = 0;
    string word,doubleWord;

    input.open("war and peace.txt");
    if(input.fail())
    {
        cout<<"failed"<<endl;
        exit(0);
    }
    char junk;
    int vowelPosition;
    while(input>>noskipws>>junk)
    {
        if((isalpha(junk)) && input.putback(junk) && input>>word)
        {
            if(word.find_first_of(".!?") != std::string::npos && sentenceNumber++)
                word.erase(word.find_first_of(".!?"));
            while(word.find_first_of(":;,[])*(") != std::string::npos)
                word.erase(word.find_first_of(",*[]:;()"),1);
            while(word.find_first_of('"') != std::string::npos)
                word.erase(word.find_first_of('"'),1);
            if(word.find_first_of('-') != std::string::npos)
                if(word[word.find_first_of('-')+1] == '-' )
                {
                    doubleHyp = word.find_first_of('-');
                    while(word.find_first_of('-') != std::string::npos)
                    {
                        word.erase(word.find_first_of('-'),1);
                    }
                    if(doubleHyp < word.size())
                    {
                        doubleWord = word.substr(doubleHyp);
                        word.erase(doubleHyp);
                        if(isalpha(doubleWord[0]))
                        {
                            doubleWord[0] = toupper(doubleWord[0]);
                            words[doubleWord[0]-65].insert(doubleWord,lineNumber,paragraphNumber);
                        }
                    }
                }
            vowelPosition = word.find_first_of("aeiou");
            while(vowelPosition != string::npos)
            {
                totalVowels++;
                vowelPosition = word.find_first_of("aeiou",vowelPosition+1);
            }
            word[0] = toupper(word[0]);
            words[word[0]-65].insert(word,lineNumber,paragraphNumber);
        }
        (junk == '\n' && lineNumber++ && input.peek() == '\n' && paragraphNumber++);
    }
    end = clock();
    for(int i = 0; i < 26; i++)
        total+=words[i].totalNumItems();
    cout<<"Total number of words is: "<<total<<endl;
    for(int i = 0; i < 26; i++)
        cout<<char(i+65)<<" "<<words[i].totalNumItems()<<endl;
    cout<<"Total number of paragraphs: "<<paragraphNumber<<endl;
    readingLevel = (((.39 * double(total)/sentenceNumber)
                     + (11.8 * (double(totalVowels) / total))) - 15.59);
    cout<<"Reading Level: "<<readingLevel<<endl;
    speed = double(end-start)/CLOCKS_PER_SEC;
    cout<<"SPEED "<<speed<<endl;
    for(int i = 0; i < 26; i++)
        words[i].popularWord(popularWords);
    cout<<"THE MOST POPULAR WORDS"<<endl;
    for(int i = 0; i < 10; i++)
        cout<<popularWords[i].second<<" "<<popularWords[i].first<<endl;
    system("pause");
    for(int i = 0; i < 26; i++)
        words[i].printInOrder();

    save(words,popularWords,total,paragraphNumber,readingLevel,speed);

    return 0;
}

void save(avltree<string> saveInput[], vector<pair<int,string> > pop, int totalWords, int paragraphNum, double rL, double speed)
{
    ofstream output;

    output.open("output.txt");

    cout<<"Would you like to save the summary. Hit y else enter."<<endl;
    if(toupper(_getch()) == 'Y')
    {
        cout<<"Saving Summary."<<endl;
        output<<"Total number of words: "<<totalWords<<endl;
        for(int i = 0; i < 26; i++)
            output<<char(i+65)<<" "<<saveInput[i].totalNumItems()<<endl;
        output<<"Total paragraph numbers: "<<paragraphNum<<endl;
        output<<"Reading level: "<<rL<<endl;
        output<<"Speed "<<speed<<endl;
        output<<"Most popular words: "<<endl;
        for(int i = 0; i < pop.size(); i++)
            output<<pop[i].second<<" "<<pop[i].first<<endl;
    }
    cout<<"Would you like to save the words. Hit y else enter"<<endl;
    if(toupper(_getch()) == 'Y')
    {
        cout<<"Saving Words"<<endl;
        for(int i = 0; i < 26; i++)
            output<<saveInput[i]<<endl;
    }
    output.close();
}
