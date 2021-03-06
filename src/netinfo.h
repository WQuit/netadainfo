/*** 
 * @Author: wq
 * @Date: 2021-04-25 20:28:56
 * @LastEditTime: 2021-04-26 23:45:11
 * @LastEditors: wq
 * @Description: get netinfo for using cmd <ip -4 -f inet -j address> 
 * @FilePath: /code/netadainfo/src/netinfo.h
 * @CSDN： https://blog.csdn.net/u011218356 
 * @Git:  https://github.com/WQuit 
 * @Email:  779508400@qq.com  
 * @    星河灿烂，你是人间烟火
 */
#ifndef NETINFO_H_
#define NETINFO_H_

#include <iostream>
#include <nlohmann/json.hpp>
#include <cstring>
#include <vector>

#define KSUCCESS (0)
#define KFAIL  (-1)
#define UKFAIL (-2)

template <class T>
inline void get_value(const nlohmann::json& j, const char* key, T& val)
{
    if(j.at(key).is_null())
    {
        val = T{};
    }
    else
    {
        val = j.value(key, T{});
    }
}

struct addrInfo
{
    std::string family;
    std::string local;
    int prefixlen;
    std::string broadcast;
    std::string scope;
    bool dynamic;
    int validLifeTime;
    int preferredLifeTime;
};

struct address
{
    int ifIndex;
    std::string ifName;
    std::vector<std::string> flags;
    int mtu;
    std::string group;
    int txqlen;
    std::string linkType;
    std::string address;
    std::vector<addrInfo> addrInfos;
};

struct netadaInfo{
    std::vector<address>  adds;
    using json = nlohmann::json;
    bool parseJsonObject(std::string data)
    {
        try
        {
            auto j = json::parse(data.c_str());
            for(json::iterator it = j.begin(); it != j.end(); it++)
            {
                address addressItem;
                get_value(*it, "ifindex", addressItem.ifIndex);
                get_value(*it, "ifname", addressItem.ifName);
                get_value(*it, "flags", addressItem.flags);
                get_value(*it, "mtu", addressItem.mtu);
                get_value(*it, "group", addressItem.group);
                get_value(*it, "txqlen", addressItem.txqlen);
                get_value(*it, "link_type", addressItem.linkType);
                get_value(*it, "address", addressItem.address);
                json addrInfoJ;
                get_value(*it, "addr_info", addrInfoJ);
                for(json::iterator jItem = addrInfoJ.begin(); jItem != addrInfoJ.end(); jItem++ )
                {
                    addrInfo addrItem;
                    get_value(*jItem, "family", addrItem.family);
                    get_value(*jItem, "local", addrItem.local);
                    get_value(*jItem, "prefixlen", addrItem.prefixlen);
                    if(addrItem.family == std::string("inet") && addrItem.local != std::string("127.0.0.1"))
                    {
                        get_value(*jItem, "broadcast", addrItem.broadcast);
                        //get_value(*jItem, "dynamic", addrItem.dynamic);
                    }
                    get_value(*jItem, "scope", addrItem.scope);
                    get_value(*jItem, "valid_life_time", addrItem.validLifeTime);
                    get_value(*jItem, "preferred_life_time", addrItem.preferredLifeTime);
                    addressItem.addrInfos.push_back(addrItem);
                }
                adds.push_back(addressItem);              
            }
            return KSUCCESS;
        }
        catch(const std::exception& e)
        {
           std::cout << "json parse faild: " << e.what() << std::endl;;
           return KFAIL;
        }
    }    
};

struct outputInfo
{
    std::string ifName;
    std::string ipAddress;
    std::string macAddress;
};

class netInfo
{
    public:
        netInfo();
        void getNetInfo(std::string info);
        std::vector<outputInfo> getOnlineNetInfo();
        std::vector<outputInfo> getEthNetInfo();
        std::vector<outputInfo> getWifiInfo();
    private:
        netadaInfo _info;
};

#endif