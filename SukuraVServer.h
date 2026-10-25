#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib,"ws2_32.lib")

bool SendAll(SOCKET s,const char* buf,int len);
int RecvAll(SOCKET s, char* buf, int len);
int RecvFrame(SOCKET s, std::string& out);
bool SendFrame(SOCKET s, const std::string& payload);