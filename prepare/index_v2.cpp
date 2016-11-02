#include<fstream>
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<map>
#include<vector>
using namespace std;

int getLenOfUTF8(unsigned  char c)
{
    int cnt =0;
    while(c & (1 << 7-cnt))++cnt;
    return cnt;
}
void UTF8Index(const string& s,const int freq)
{
    string::size_type ix=0;
    int len;
    len = getLenOfUTF8(s[ix]);
    vector<uint32_t>vec;
    for(ix=0; ix != s.size(); ix++)
    {
        uint32_t t = (unsigned char)s[ix];
        if(len > 1)
        {

            len--;
            while(len > 0)
            {
                t = (t<<8)+(unsigned char)s[++ix];
                len --;
            }
        }
       vec.push_back(t);
    }
    for(ix=0; ix!=vec.size(); ix++)
    {
        char filename[128]="";
        ::sprintf(filename,"./dat/%lx.txt",vec[ix]);
        map<string,int>word_cnt;
        ifstream ifs;
        ifs.open(filename);
        string word,old_freq;
        while(ifs >> word)
        {
            ifs >> old_freq;
            word_cnt[word]= ::atoi(old_freq.c_str());
        }
        ifs.close();
        ofstream ofs;
        ofs.open(filename,ofstream::app);
        int new_freq;
        for(map<string,int>::iterator it = word_cnt.begin(); it != word_cnt.end(); ++it){
            new_freq = it->second;
            new_freq += freq;
            ofs << it->first <<"  "<<new_freq << endl;
        }
       ofs.close();
    }
}
int main(int argc, const char *argv[])
{
    ifstream ifs;
    ifs.open(argv[1]);
    if(!ifs)cout <<"open failed" << endl;
    string word,freq;
    int freq_int;
    while(ifs >> word)
    {
        ifs >> freq;
        freq_int = ::atoi(freq.c_str());
        cout << word << "  "<<freq_int << endl;
        UTF8Index(word,freq_int);
    }
    ifs.close();
    return 0;
}
