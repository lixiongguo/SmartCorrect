/*************************************************************************
  > File Name: query.cpp
  > Author: Comst
  > Mail:750145240@qq.com 
  > Created Time: Sat 26 Jul 2014 08:02:28 PM CST
 ************************************************************************/

#include "../include/query.h"
#include "../include/Edist.h"
using namespace std;

void vecdo(vector<Data> &vec){
    sort(vec.begin(),vec.end());
    vector<Data>::iterator end_queue=unique(vec.begin(),vec.end());
    vec.erase(end_queue,vec.end());
}

void  query(string query, string& result1, string& result2)
{
    vector<Data>vec0;
    vector<Data>vec1;
    vector<Data>vec2;
    char filename[128];
    vector<uint32_t>vec;
    parseUTF8String(query,vec);
    for(int i=0; i != vec.size(); i++){
        ::sprintf(filename,"../dat/%x.txt",vec[i]);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs){printf("%s\n",filename);perror("open");}

        string word,freq;
        Data data;
        while(ifs >> word ){
            data.word_ = word;
            ifs >>freq;	
            data.freq_ = ::atoi(freq.c_str());
            if(::abs((int)(query.size()-word.size()))<=3)
            {
                int edist = Edist(query,word);
                if(edist==0)
                {
                    vec0.push_back(data);
                }
                else if(edist==1)
                {
                    vec1.push_back(data);
                }
                else if(edist==2)
                {
                    vec2.push_back(data);
                }

            }
        }
        ifs.close();
    }
    ostringstream  os;
    ostringstream  os2;
    if(vec0.begin()==vec0.end()
            &&vec1.begin()==vec1.end()
            &&vec2.begin()==vec2.end())
    {
        os << "no find" << endl;
        os2 << "no find" << '\r';
    }
    vecdo(vec0);
    vecdo(vec1);
    vecdo(vec2);
    const int max=10;
    int show = 0;
    for(vector<Data>::const_iterator it = vec0.begin(); it != vec0.end(); ++ it){
        if(show > max)break;
        os << it->word_ << endl;
        os2 << it->word_  << ' ';
        show++;
    }
    for(vector<Data>::const_iterator it = vec1.begin(); it != vec1.end(); ++ it){
        if(show > max)break;
        os << it->word_ << endl;
        os2 << it->word_ << ' ';
        show++;
    }
    for(vector<Data>::const_iterator it = vec2.begin(); it != vec2.end(); ++ it){
        if(show > max)break;
        os << it->word_ << endl;
        os2 << it->word_<< ' ';
        show++;
    }
    result1 = os.str();
    result2 = os2.str();
}   

