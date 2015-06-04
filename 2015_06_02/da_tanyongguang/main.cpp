#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

bool GetLongestZeroSeq(std::string & src, int &begin, int &end){
    int size = src.length();
    if (size == 0){
        printf("empty string!\n");
        return false;
    }
    int * pBufferN = new int[size + 1];
    int * pBufferP = new int[size + 1];
    pBufferP[0] = -1;
    int posP = 0 ;
    int posN = 0;
    int longest_pos = 0;
    int longest_dist = 0;
    int longest_value = 0;
    bool isPositive = false;
    int cur_value = 0;
    for(int  i= 0; i < size; ++ i){
        if (src[i] == '0'){
            cur_value -= 1;
        }else if (src[i] == '1'){
            cur_value += 1;
        }
        int * pInsertBuf = cur_value >= 0 ? pBufferP:pBufferN;
        int * pos = cur_value >= 0 ? &posP:&posN;
        int abs_value = abs(cur_value);
        if (abs_value > *pos){
            *pos = abs_value;
            pInsertBuf[abs_value] = i;
        }else if (abs_value <= *pos){
            int dist = i - pInsertBuf[abs_value];
            if (dist > longest_dist){
                longest_dist = dist;
                longest_pos = i;
                longest_value = abs_value;
                isPositive = cur_value >= 0 ? true : false;
            }
        }
    }
    if (longest_pos > 0){
        int * pInsertBuf = isPositive ? pBufferP:pBufferN;
        end =  longest_pos;
        begin =  pInsertBuf[longest_value] + 1;
        delete [] pBufferN;
        delete [] pBufferP;
        return true;
    }
    delete [] pBufferN;
    delete [] pBufferP;
    return false;
}

int main(int argc, char **argv)
{
    if (argc != 2){
        printf("error param\n");
        return 1;
    }
    std::string src = argv[1];
    std::cout<<"src:"<<src<<std::endl;
    int begin = 0;
    int end = 0;
    bool isFind = GetLongestZeroSeq(src, begin, end);
    if (isFind){
        std::cout<<"begin:"<<begin<<" end:"<<end<<" dist:"<<end -begin + 1<<std::endl;
    }else{
        std::cout<<"Can't found"<<std::endl;
    }
    return 0;
}
