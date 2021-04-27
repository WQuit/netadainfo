/*** 
 * @Author: wq
 * @Date: 2021-04-25 20:27:55
 * @LastEditTime: 2021-04-26 23:52:35
 * @LastEditors: wq
 * @Description: 
 * @FilePath: /code/netadainfo/src/main.cpp
 * @CSDN： https://blog.csdn.net/u011218356 
 * @Git:  https://github.com/WQuit 
 * @Email:  779508400@qq.com  
 * @    星河灿烂，你是人间烟火
 */

#include "netinfo.h"

#define CMD_LINK        "ip -4 -f inet -j link"
#define CMD_ADDRESS     "ip -4 -f inet -j address"
#define CMD_ALL         "ip -j address"
#define MAXLENGTH       256

netInfo::netInfo():_info({})
{

}

void netInfo::getNetInfo(std::string info)
{
    _info.parseJsonObject(info);
}

std::vector<outputInfo> netInfo::getOnlineNetInfo()
{
    std::vector<outputInfo> outputs;
    for(auto it : _info.adds)
    {
        outputInfo output;
        if(it.flags.empty())
            continue;
        bool online = false;
        for(auto status : it.flags)
        {
            if(status == std::string())
            {
                
            }
        }
        output.ifName = it.ifName;
        output.macAddress = it.address;
        for(auto item : it.addrInfos)
        {
            if(item.family == std::string("inet"))
            {
                output.ipAddress = item.local;
                break;
            }
        }
        std::cout << output.ifName << " : " << output.ipAddress << " : " << output.macAddress << std::endl;
        outputs.push_back(output);
    }
    return outputs;
}

std::vector<outputInfo> netInfo::getEthNetInfo()
{
    
}

std::vector<outputInfo> netInfo::getWifiInfo()
{
    
}

int main(int args, char **arg)
{
    std::string retStr;
    char retChar[MAXLENGTH] = {0};
    FILE *fp = nullptr;
    std::string cmd(CMD_ALL);
    fp = popen(cmd.c_str(), "r");
    if(fp == nullptr)
        std::cout << "running cmd is fail! cmd is " << cmd << std::endl;
    std::string jStr;
    while(fgets(retChar, MAXLENGTH, fp) != nullptr)
    {
        jStr += std::string(retChar, strlen(retChar));
    }
    pclose(fp);
    netInfo net;
    net.getNetInfo(jStr);
    net.getOnlineNetInfo();
    return 0;
}