#include"../include/Edist.h"
using namespace std;

int getLenOfUTF8(unsigned  char c)
{
    int cnt =0;
    while(c & (1 << 7-cnt))++cnt;
    return cnt;
}
void parseUTF8String(const string& s, vector<uint32_t>& vec)
{
    string::size_type ix;
    int len;
    vec.clear();
    for(ix=0; ix!=s.size(); ix++)
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
}
int MIN(int a, int b, int c)
{   
    if(a > b)
    {
        if(b > c)
            return c;
        else 
            return b;
            
    }
    else
    {
        if(a > c)
            return c;
        else 
            return a;
    }            
}
int vec_dist(const vector<uint32_t>& w1,const vector<uint32_t>& w2)
{

    int len_a = w1.size();
    int len_b = w2.size();
    int memo[100][100];
    memset(memo, 0x00, 100 * 100 * sizeof(int));
    for (int i = 1; i <= len_a; ++i) {
        memo[i][0] = i;
    }
    for (int j = 1; j <= len_b; ++j) {
        memo[0][j] = j;
    }
    for (int i = 1; i <= len_a; ++i) {
        for (int j = 1; j <= len_b; ++j) {
                if(w1[i-1]==w2[j-1]){
                memo[i][j] = memo[i - 1][j - 1];
            } else {
                memo[i][j] = MIN(memo[i - 1][j - 1], memo[i][j - 1],
                        memo[i - 1][j]) + 1;
            }
        }
    }
    return memo[len_a][len_b];
}
int Edist(const string& s1, const string& s2)
{
    vector<uint32_t>vec_s1;
    parseUTF8String(s1, vec_s1);
    vector<uint32_t>vec_s2;
    parseUTF8String(s2, vec_s2);
    return vec_dist(vec_s1, vec_s2);
}
