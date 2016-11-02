#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
    map<string,string>word_set;
    ifstream ifs_a;
    ifstream ifs_b;
    ifs_a.open("../dat/cache_a.txt");
    ifs_b.open("../dat/cache_b.txt");
    if(!ifs_a)printf("open failed in cache_a");
    if(!ifs_b)printf("open failed in cache_b");

    string word;
    string result;
    while(getline(ifs_a, word) && getline(ifs_b, result))
    {
        word_set[word] = result;
    }

    ofstream ofs_a;
    ofstream ofs_b;
    ofs_a.open("../dat/cache_a.txt");
    if(!ofs_a)printf("open failed out cache_a");
    ofs_b.open("../dat/cache_b.txt");
    if(!ofs_b)printf("open failed out cache_b");

    map<string,string>::iterator it = word_set.begin();
    while(it != word_set.end())
    {
        ofs_a<<it->first<<endl;
        ofs_b<<it->second<<endl;
        it++;
    }
    return 0;
}


