#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void processCrudeDoc(const char *arg1, const char *arg2)
{
    ifstream ifs;
    ofstream ofs;
    ifs.open(arg1);
    ofs.open(arg2);
    string word;
    map<string, int>word_cnt;
    while(ifs >> word)
    {
        word_cnt[word]++;        
    }
    for(map<string,int>::iterator it = word_cnt.begin(); it != word_cnt.end(); ++it){
        ofs << it->first <<"  "<< it->second << endl;    
    }
}
void mergeProcessedDoc(const char* arg1,const char* arg2,const char* arg3)
{
    
    ifstream ifs1;
    ifstream ifs2;
    ifs1.open(arg1);
    ifs2.open(arg2);


    string word,freq;
    int freq_int;
    map<string,int>word_cnt;
    while(ifs1 >> word)
    {
        ifs1 >> freq;
        freq_int = ::atoi(freq.c_str());
        cout << word << " " << freq_int << endl;
        word_cnt[word]+=freq_int;
    }
    ifs1.close();
    while(ifs2 >> word)
    {
        ifs2 >> freq;
        freq_int = ::atoi(freq.c_str());
        cout << word << " " << freq_int << endl;
        word_cnt[word]+=freq_int;
    }
    ifs2.close();

    ofstream ofs;
    ofs.open(arg3);
    for(map<string,int>::iterator it = word_cnt.begin(); it != word_cnt.end(); ++it){
        ofs << it->first << "  "<<it->second << endl;    
    }
    ofs.close();
}   

int main(int argc, const char *argv[])
{
//    mergeProcessedDoc(argv[1],argv[2],argv[3]);
    processCrudeDoc(argv[1],argv[2]);
    return 0;
}
