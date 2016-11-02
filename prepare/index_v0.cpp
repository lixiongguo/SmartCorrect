#include<fstream>
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdint.h>

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
        char filename[128]="";
        ::sprintf(filename,"./dat/%lx.txt",t);
        ofstream ofs;
        ofs.open(filename,ofstream::app);
        ofs << s <<"  "<<freq << endl;
        ofs.close();
}
int main(int argc, const char *argv[])
{
    ifstream ifs;
    ifs.open("words.txt");
    if(!ifs)cout <<"open failed" << endl;
    string word,freq;
    while(ifs >> word)
    {
        ifs >> freq;
        cout << word << freq << endl;
        UTF8Index(word,freq);
    }
    ifs.close();
    return 0;
}
