#include <Windows.h>
#include <winhttp.h>
#include <cstdio>
#include <iostream>


DWORD ReadRegistryValueOfDWORD(HKEY key, std::string name){
    DWORD data;
    DWORD datalen;
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, &data, &datalen);
    return data;
}


std::string ReadRegistryValueOfString(HKEY key, std::string name){
    DWORD datalen;
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, NULL, &datalen);
    uint8_t *data = new uint8_t[datalen]();
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, data, &datalen);
    std::string str((char*)data);
    delete[] data;
    return str;
}

int main()
{
    HKEY key;
    RegOpenKeyA(HKEY_CURRENT_USER, R"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", &key);

    std::cout << "ProxyEnable: " << ReadRegistryValueOfDWORD(key, "ProxyEnable") << std::endl;
    std::cout << "ProxyServer: " << ReadRegistryValueOfString(key, "ProxyServer") << std::endl;
    std::cout << "ProxyOverride: " << ReadRegistryValueOfString(key, "ProxyOverride") << std::endl;
    std::cout << "AutoConfigURL: " << ReadRegistryValueOfString(key, "AutoConfigURL") << std::endl;
}