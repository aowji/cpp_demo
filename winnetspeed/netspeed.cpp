#include <windows.h>
#include <Iphlpapi.h>
#include <cstdio>
#include "netspeed.h"

void NetSpeed::start(){
	auto x = new std::thread([this]() {this->calc(); });
	t.reset(x);
}

void NetSpeed::stop(){
    reqStop = true;
    t->join();
}

void NetSpeed::get_speed(int& in, int& out){
    in = in_speed;
    out = out_speed;
}

void NetSpeed::calc(){
    
	PMIB_IFTABLE	m_pTable = NULL;
	DWORD	 m_dwAdapters = 0;
	ULONG	 uRetCode = GetIfTable(m_pTable, &m_dwAdapters, TRUE);
	if (uRetCode == ERROR_NOT_SUPPORTED)
	{
		return;
	}

	if (uRetCode == ERROR_INSUFFICIENT_BUFFER)
	{
		m_pTable = (PMIB_IFTABLE)new BYTE[65535];										//假设端口数不超过65535个
	}

	DWORD	dwLastIn = 0;																					//上一秒钟的接收字节数
	DWORD	dwLastOut = 0;																					//上一秒钟的发送字节数
	DWORD	dwBandIn = 0;																					//下载速度
	DWORD	dwBandOut = 0;																				//上传速度

	while (!reqStop)
	{
		GetIfTable(m_pTable, &m_dwAdapters, TRUE);

		//将所有端口的流量进行统计
		DWORD	dwInOctets = 0;
		DWORD	dwOutOctets = 0;
		for (UINT i = 0; i < m_pTable->dwNumEntries; i++)
		{
			MIB_IFROW	Row = m_pTable->table[i];
			dwInOctets += Row.dwInOctets;
			dwOutOctets += Row.dwOutOctets;
		}


		dwBandIn = dwInOctets - dwLastIn;														//下载速度
		dwBandOut = dwOutOctets - dwLastOut;											//上床速速
		if (dwLastIn <= 0)
		{
			dwBandIn = 0;
		}

		if (dwLastOut <= 0)
		{
			dwBandOut = 0;
		}

		dwLastIn = dwInOctets;
		dwLastOut = dwOutOctets;


        this->in_speed = dwBandIn;
        this->out_speed = dwBandOut;

		// printf("收到字节: %u bytes\n", dwLastIn);
		// printf("发送字节: %u bytes\n", dwLastOut);
		// printf("下行速度: %u KB\n", dwBandIn);
		// printf("上行速度: %u KB\n", dwBandOut);
		// printf("--------------------------\n");
		Sleep(1000);																								//休眠一秒钟
	}

	delete [] m_pTable;
}
