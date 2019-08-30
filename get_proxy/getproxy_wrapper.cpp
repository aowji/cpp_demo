#include <Windows.h>
#include <winhttp.h>
#include <cstdio>
#include <iostream>
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>


DWORD ReadRegistryValueOfDWORD(HKEY key, std::string name){
    DWORD data = {0};
    DWORD datalen;
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, &data, &datalen);
    return data;
}


std::string ReadRegistryValueOfString(HKEY key, std::string name){
	DWORD datalen = {0};
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, NULL, &datalen);
    uint8_t *data = new uint8_t[datalen]();
    RegGetValueA(key, NULL, name.c_str(), RRF_RT_REG_DWORD, NULL, data, &datalen);
    std::string str((char*)data);
    delete[] data;
    return str;
}


bool IsProxyEnabled() {
	HKEY key;
	RegOpenKeyA(HKEY_CURRENT_USER, R"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", &key);
	auto dwdIsEnabled = ReadRegistryValueOfDWORD(key, "ProxyEnable");
	RegCloseKey(key);
	return dwdIsEnabled == 1;
}

std::string GetProxyServer() {
	HKEY key;
	RegOpenKeyA(HKEY_CURRENT_USER, R"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", &key);
	auto proxyServer = ReadRegistryValueOfString(key, "ProxyServer");
	RegCloseKey(key);
	return proxyServer;
}

std::string GetProxyOverride() {
	HKEY key;
	RegOpenKeyA(HKEY_CURRENT_USER, R"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", &key);
	auto proxyOverride = ReadRegistryValueOfString(key, "ProxyOverride");
	RegCloseKey(key);
	return proxyOverride;
}

std::string GetAutoConfigURL() {
	HKEY key;
	RegOpenKeyA(HKEY_CURRENT_USER, R"(Software\Microsoft\Windows\CurrentVersion\Internet Settings)", &key);
	auto url = ReadRegistryValueOfString(key, "AutoConfigURL");
	RegCloseKey(key);
	return url;
}

BOOST_PYTHON_MODULE(getproxy)
{
	using namespace boost::python;
	def("IsProxyEnabled", IsProxyEnabled);
	def("GetProxyServer", GetProxyServer);
	def("GetProxyOverride", GetProxyOverride);
	def("GetAutoConfigURL", GetAutoConfigURL);
}


