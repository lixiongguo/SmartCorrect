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
void UTF8Index(const string& s,const string& freq)
{
    string::size_type ix=0;
    int len;
    vector<uint32_t>vec;
    for(ix=0; ix != s.size(); ix++)
    {
        len = getLenOfUTF8(s[ix]);
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
        ofstream ofs;
        ofs.open(filename,ofstream::app);
        if(!ofs)cout << "open fail" << endl;
        ofs << s <<"  "<<freq<< endl;
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
        cout << word << "  "<<freq << endl;
        UTF8Index(word,freq);
    }
    ifs.close();
    return 0;
}
