#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


#define BUFLEN 512

using namespace std;

int main(int argc, char **argv) 
{
    WSADATA wsaData;
	cout << "Khoi tao Winsock" << endl;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "Failed with error : " << WSAGetLastError() << endl;
        return 1;
    }
	cout<<"WSAStartup OK"<<endl;

	sockaddr_in server;
	int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        printf("Socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
	cout<<"ConnectSocket = socket OK"<<endl;

	int port = 81;
	const char *IP="127.0.0.1";
	memset((char*)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(IP);
	while(true){

        //----------------------AAAAAA------------------------------
        string infor;
        string name,age,msv;

        cout<<"-Nhap thong tin sinh vien:\n";
        cout<<"--Nhap ma sinh vien: ";
        getline(cin,msv);
        cout<<"--Nhap ten sinh vien: ";
        getline(cin,name);
        cout<<"--Nhap tuoi sinh vien: ";
        getline(cin,age);

        infor = msv + "," + name + "," + age;

        // ------------------------------------------------------

        // send the message
        if (sendto(client_socket, infor.c_str(), infor.size(), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }

        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char answer[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if (answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        // --------------------------------AAAAAAA----------------------------------

        string s(answer);

        cout<<"\n------Danh sach sinh vien sau khi them-------\n";

        stringstream ss(s);
        string token;

        while(getline(ss,token,';')){
            cout<<token<<endl;
        }

        cout<<endl;

        //--------------------------------------------------------------------

	}

    closesocket(client_socket);
    WSACleanup();
	getchar();
    return 0;
}

