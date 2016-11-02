/*************************************************************************
	> File Name: main.cpp
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Sat 26 Jul 2014 02:34:44 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<ctype.h>
#include<map>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;


void normalize()
{
    FILE *fr = fopen("../dat/big.txt","rb");
    FILE *fw = fopen("../dat/big1.txt","wb");
    char c;
    while((c = fgetc(fr)) != EOF)
    {
        if(ispunct(c))
            fputc( ' ',fw);
        else if(isupper(c))
            fputc( c - 'A' + 'a',fw);
         else
             fputc( c ,fw);
    }
    fclose(fr);
    fclose(fw);
}
int main(int argc, char *argv[]){
	ifstream is;
	ofstream os;
    normalize();
	is.open("../dat/big1.txt");
	os.open("../dat/words.txt");
	string word;
	map<string,int>word_count;
	while(is >> word){
		word_count[word]++;
		cout << word << endl;
	}
		ofstream ofcs[26];
	for(char c='a'; c <= 'z'; c++){
		char filename[128];
		::sprintf(filename,"../dat/%c.txt",c);
		ofcs[c-'a'].open(filename);
	}
		ofstream ofds[10];
	for(char c='0'; c<='9';c++){	
		char filename[128];
		::sprintf(filename,"../dat/%c.txt",c);
		ofds[c-'0'].open(filename);
	}
	int flag;
	for(map<string,int>::iterator it = word_count.begin();it != word_count.end(); ++it){
      os << it->first <<" " << it->second << endl;
	  string word = it->first;
		for(int i=0;word[i] != '\0';i++){
			char c=word[i];
			flag=0;
			for(int j=0; j<i; j++)
				if(word[j] == word[i]){flag=1;break;}
			if(flag == 0)
			{
			if(::isalpha(c))
			ofcs[c-'a']<< it->first<<" "<< it->second << endl;
			if(::isdigit(c))
			ofds[c-'0']<< it->first<<" "<< it->second << endl;
			}
		}
	}
}
