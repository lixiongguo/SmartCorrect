#ifndef EDIST_H_
#define EDIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

int getLenOfUTF8(unsigned  char );
void parseUTF8String(const std::string& , std::vector<uint32_t>& );
int MIN(int, int, int);
int vec_dist(const std::vector<uint32_t>& ,const std::vector<uint32_t>& );
int Edist(const std::string& , const std::string& );
#endif
