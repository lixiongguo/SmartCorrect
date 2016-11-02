#include "../include/query.h"
using namespace std;
int main(int argc, const char *argv[])
{
    string query_word;
    while(1)
    {
        cout <<"input query string: "<< endl;
        cin >> query_word;
        string result1,result2;
        query(query_word,result1,result2);
        cout << result1 << endl;
        cout <<"--------------"<<endl;
    }
    return 0;
}


