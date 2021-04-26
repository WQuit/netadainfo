/*** 
 * @Author: wq
 * @Date: 2021-04-25 20:27:55
 * @LastEditTime: 2021-04-26 00:27:40
 * @LastEditors: wq
 * @Description: 
 * @FilePath: /code/ip/netinfo.cpp
 * @CSDN： https://blog.csdn.net/u011218356 
 * @Git:  https://github.com/WQuit 
 * @Email:  779508400@qq.com  
 * @    星河灿烂，你是人间烟火
 */

#include "netinfo.h"

#define CMD_LINK        "ip -4 -f inet -j link"
#define CMD_ADDRESS     "ip -4 -f inet -j address"
#define MAXLENGTH 2048
int main(int args, char **arg)
{
    std::string retStr;
    char retChar[MAXLENGTH] = {0};
    FILE *fp = nullptr;
    std::string cmd(CMD_ADDRESS);
    fp = popen(cmd.c_str(), "r");
    if(fp == nullptr)
        std::cout << "running cmd is fail! cmd is " << cmd << std::endl;
    while(fgets(retChar, MAXLENGTH, fp) != nullptr)
    {
        int readLength = fread(retChar, sizeof(char), sizeof(retChar), fp);
        // std::cout << "length:" << readLength << std::endl;
        std::cout<< std::string(retChar, readLength) << std::endl;
    }
    return 0;
}