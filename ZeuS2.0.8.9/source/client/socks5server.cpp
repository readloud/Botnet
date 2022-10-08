#include <windows.h>
#include <ws2tcpip.h>

#include "defines.h"
#include "socks5server.h"

#include "..\common\mem.h"
#include "..\common\wsocket.h"

//��������� �����.
#define S5_CLIENT_IS_IPV4    0x0  //������ ��������� �� IPv4 ���������.
#define S5_CLIENT_IS_IPV6    0x1  //������ ��������� �� IPv6 ���������.
#define S5_ONREPLY_PEER_NAME 0x2  //����������� ��� Socks5Reply, � �������� ��� ����� ������� ��
                                  //��������� ������ ������, � ���������.
#pragma pack(push, 1)
typedef struct
{
  //BYTE  version;
  BYTE  command;
  WORD  destPort;
  DWORD destIp;
}SOCKS4_QUERY;

typedef struct
{
  BYTE  version;
  BYTE  replyCode;
  WORD  destPort;
  DWORD destIp;
}SOCKS4_REPLY;

typedef struct
{
  BYTE version;  //������
  BYTE command;  //�������
  BYTE reserved; //���������������
  BYTE addrType; //��� ������
}SOCKS5_QUERY;

typedef struct
{
  BYTE version;   //������
  BYTE replyCode; //��� ������
  BYTE reserved;  //���������������
  BYTE addrType;  //��� ������
}SOCKS5_REPLY;

typedef struct
{
  WORD reserved;  //���������������
  BYTE fragment;  //������� ����� ���������
  BYTE addrType;  //��� ������
}UDP_QUERY;
#pragma pack(pop)

void Socks5Server::init(void)
{

}

void Socks5Server::uninit(void)
{

}

/*
  �������� ������ ������� Socks5.

  IN sourceSocket - �����, �� ������� ����� ��������� �����.
  IN nameSocket   - �����, ������ �������� ����� �������� ��� INVALID_SOCKET ��� ������ � IP �
                    ������ ����������� ������.
  IN replyCode    - ��� ������.
  IN flags        - ����� S5_*.
  
  Return          - (-1) - � ������ ������ ��������� ������ �� IP, ����� ��� ���� �� ������������,
                           � ������ �������� �� �������� �������� ���
                           (nameSocket == INVALID_SOCKET),
                      0  - � ������ ������ � ��������� ��� ������� ����������,
                      1  - � ������ �������� �������� ������.
*/
static int socks5Reply(SOCKET sourceSocket, SOCKET nameSocket, BYTE replyCode, DWORD flags)
{
  SOCKS5_REPLY sr;
  BYTE replyBuf[sizeof(SOCKS5_REPLY) + IPv6_SIZE + IP_PORT_SIZE + 10];
  LPBYTE ip = replyBuf + sizeof(SOCKS5_REPLY);
  int size;
  
  //�������������� �������� ������ ������, ���� ��� ����������.
  if(nameSocket != INVALID_SOCKET)
  {
    SOCKADDR_STORAGE psa;
    size = sizeof(SOCKADDR_STORAGE);

    if(flags & S5_ONREPLY_PEER_NAME)
    {
      if(CWA(ws2_32, getpeername)(nameSocket, (sockaddr *)&psa, &size) != 0)return -1; //������ �������.
    }
    else 
    {
      if(CWA(ws2_32, getsockname)(nameSocket, (sockaddr *)&psa, &size) != 0)return -1; //������ �������.
    }
    
    if(psa.ss_family == AF_INET)//IPv4
    {
      sr.addrType = 1; //IPv4
      Mem::_copy(ip,             &((SOCKADDR_IN *)&psa)->sin_addr.S_un.S_addr, IPv4_SIZE);
      Mem::_copy(ip + IPv4_SIZE, &(((SOCKADDR_IN *)&psa)->sin_port),           IP_PORT_SIZE);
      size = IPv4_SIZE + IP_PORT_SIZE;
    }
    else if(psa.ss_family == AF_INET6)//IPv6
    {
      sr.addrType = 4; //IPv6
      Mem::_copy(ip,               ((SOCKADDR_IN6 *)&psa)->sin6_addr.u.Byte, IPv6_SIZE);
      Mem::_copy(ip + IPv6_SIZE , &(((SOCKADDR_IN6 *)&psa)->sin6_port),      IP_PORT_SIZE);
      size = IPv6_SIZE + IP_PORT_SIZE;
    }
    //�� ���������� ������.
    else return -1; //������ �������.
  }
  else
  {
    Mem::_zero(ip, sizeof(replyBuf) - sizeof(SOCKS5_REPLY));
    if(flags & S5_CLIENT_IS_IPV6){sr.addrType = 4; /*IPv6*/ size = IPv6_SIZE + IP_PORT_SIZE;}
    else {sr.addrType = 1; /*IPv4*/ size = IPv4_SIZE + IP_PORT_SIZE;}
  }
  
  sr.version   = 5;
  sr.reserved  = 0;
  sr.replyCode = replyCode;

  Mem::_copy(replyBuf, &sr, sizeof(SOCKS5_REPLY));
  return WSocket::tcpSend(sourceSocket, replyBuf, sizeof(SOCKS5_REPLY) + size) ? 1 : 0;
}

/*
  RFC 1928:http://www.opennet.ru/base/net/socks5_rfc1928.txt.html
*/
bool Socks5Server::_start5(SOCKET s, DWORD timeout)
{  
  DWORD flags = WSocket::getFamily(s) == AF_INET6 ? S5_CLIENT_IS_IPV6 : S5_CLIENT_IS_IPV4;
  
  //A�������������.
  {
    BYTE methodsCount;
    BYTE methods[MAXBYTE];

    if(!WSocket::tcpRecvAll(s, &methodsCount, sizeof(BYTE), timeout) || methodsCount == 0 ||
       !WSocket::tcpRecvAll(s, methods, methodsCount, timeout))return false;
           
    WORD authReply = Mem::_getR(methods, 0, methodsCount) == NULL ? MAKEWORD(5, 0xFF) : MAKEWORD(5, 0);
    if(!WSocket::tcpSend(s, &authReply, sizeof(authReply)))return false;

    //������ �������������� �� �������.
    if(authReply == MAKEWORD(5, 0xFF))return true;
  }

  //��������� �������.
  SOCKS5_QUERY sq;
  BYTE replyCode = 0; //��������    

  if(!WSocket::tcpRecvAll(s, &sq, sizeof(SOCKS5_QUERY), timeout) || sq.version != 5/*������ ���������*/)return false;

  //��������� ���� IP ��� ������� � DNS.
  int familyList[2];
  if(flags & S5_CLIENT_IS_IPV6)
  {
    familyList[0] = AF_INET6;
    familyList[1] = AF_INET;
  }
  else
  {
    familyList[0] = AF_INET;
    familyList[1] = AF_INET6;
  }

  //��������� ������ ����������.
  SOCKADDR *destAddr = NULL;
  switch(sq.addrType)
  {
    //IPv4  
    case 1: 
    {
      BYTE bIP[IPv4_SIZE];
      if(!WSocket::tcpRecvAll(s, bIP, sizeof(bIP), timeout))return false;
      if((destAddr = (SOCKADDR *)Mem::alloc(sizeof(SOCKADDR_IN))) == NULL)replyCode = 1; //������ SOCKS-�������
      else
      {
        SOCKADDR_IN *t = (SOCKADDR_IN *)destAddr;
        t->sin_family = AF_INET;
        Mem::_copy(&t->sin_addr, bIP, sizeof(bIP));
      }
      break;
    }

    //IPv6
    case 4: 
    {
      BYTE bIP[IPv6_SIZE];
      if(!WSocket::tcpRecvAll(s, bIP, sizeof(bIP), timeout))return false;
      if((destAddr = (SOCKADDR *)Mem::alloc(sizeof(SOCKADDR_IN6))) == NULL)replyCode = 1; //������ SOCKS-�������
      else
      {
        SOCKADDR_IN6 *t = (SOCKADDR_IN6 *)destAddr;
        t->sin6_family = AF_INET6;
        Mem::_copy(&t->sin6_addr, bIP, sizeof(bIP));
      }
      break;
    }

    //�����
    case 3: 
    {
      BYTE domain[MAXBYTE + 1];
      BYTE domainLen;
      if(!WSocket::tcpRecvAll(s, &domainLen, sizeof(BYTE), timeout) || domainLen == 0 /*������ ���������*/ ||
         !WSocket::tcpRecvAll(s, domain, domainLen, timeout))return false;

      domain[domainLen] = 0;
        
      //������ � DNS
      struct addrinfo *addrInfoList = NULL;
      if(CWA(ws2_32, getaddrinfo)((char *)domain, NULL, NULL, &addrInfoList) != 0)replyCode = 4; //���� ����������
      else
      {
        //���� ��� ������ IPv4 � IPv6.
        for(register BYTE i = 0; i < sizeof(familyList) / sizeof(int); i++)
        {
          register struct addrinfo *curAddrInfo = addrInfoList;
          while(curAddrInfo)
          {
            if(curAddrInfo->ai_family == familyList[i])
            {
              if((destAddr = (SOCKADDR *)Mem::copyEx(curAddrInfo->ai_addr, curAddrInfo->ai_addrlen)) == NULL)replyCode = 1; //������ SOCKS-�������
              else HZ_IPV6_CLEAR(destAddr);
              goto IP_FOUNDED;
            }
            curAddrInfo = curAddrInfo->ai_next;
          }
        }

//�� �� ������.
//IP_NOTFOUNDED:
        replyCode = 4; //���� ����������

//�� ������ ��� ������.
IP_FOUNDED:
        CWA(ws2_32, freeaddrinfo)(addrInfoList);
      }        
      break;
    }

    default: return false;
  }
            
  //�������� ����.
  u_short port;
  if(!WSocket::tcpRecvAll(s, &port, sizeof(u_short), timeout))
  {
    Mem::free(destAddr);
    return false;
  }
  
  //if(replyCode == 0 && destAddr == NULL)�ReplyCode = 1; //������ SOCKS-�������
  
  //������ � ���� ��������� IP �� �������, ������� �������.
  bool retVal = true;
  if(replyCode == 0)
  {
    //�� ����� ������, ������� ����������.
    //if(destAddr->sa_family == AF_INET)((SOCKADDR_IN *)destAddr)->sin_port = port;
    //else 
    ((SOCKADDR_IN6 *)destAddr)->sin6_port = port;

    //������ ������� 
    switch(sq.command)
    {
      //Connect  
      case 1:
      {
        SOCKET destSocket = WSocket::tcpConnect((SOCKADDR_STORAGE *)destAddr);
        if(destSocket == INVALID_SOCKET)replyCode = 5; //����� � ����������
        else
        {
          WSocket::tcpDisableDelay(destSocket, true);
          int l = socks5Reply(s, destSocket, replyCode, flags);
          if(l == 1)WSocket::tcpTunnel(s, destSocket);
          else if(l == -1)replyCode = 1;//������ SOCKS-�������
          else retVal = false;
          WSocket::tcpClose(destSocket);
        }
        break;
      }

      //Bind
      case 2:
      {
        SOCKET destSocket;

        //� ���� � ��� ����� ������ ���������� ����� rfc � �������� ������������,
        //� ������ ������� �� ����������� ���� �� ��� IP �������, � ����� �� ��� ���� ������� ��
        //������ ��� ���������. �������� ���� ���� � ����������� FlashFXP 3.6.0. �.�. � destAddr
        //�� ���������� ����� �� ������ �������. � �� rfc, ��� � �����, ��� ������ ���� ������
        //����-�������, ��� ����� ����� ���������.
        
        //���� ��������� ����.
        ((SOCKADDR_IN6 *)destAddr)->sin6_port = 0;
        if(destAddr->sa_family == AF_INET6)Mem::_zero(&(((SOCKADDR_IN6 *)destAddr)->sin6_addr), IPv6_SIZE);
        else ((SOCKADDR_IN *)destAddr)->sin_addr.S_un.S_addr = 0;
        
        if((destSocket = WSocket::tcpListen((SOCKADDR_STORAGE *)destAddr, 1)) == INVALID_SOCKET)replyCode = 5; //����� � ����������
        else
        {
          int l = socks5Reply(s, destSocket, replyCode, flags);
          if(l == 1)
          {
            SOCKET incomingSocket = WSocket::tcpWaitForIncomingAndAccept(&destSocket, 1, 0, NULL, NULL, &s, 1);
            WSocket::tcpClose(destSocket);

            if(incomingSocket == INVALID_SOCKET)replyCode = 1; //������ SOCKS-�������
            else
            {
              WSocket::tcpDisableDelay(incomingSocket, true);
              if((l = socks5Reply(s, incomingSocket, replyCode, flags | S5_ONREPLY_PEER_NAME)) == 1)WSocket::tcpTunnel(s, incomingSocket);
              WSocket::tcpClose(incomingSocket);
            }
          }
          else WSocket::tcpClose(destSocket);

          if(l == -1)replyCode = 1; //������ SOCKS-�������
          else if(l != 1)retVal = false;
        }
        break;
      }      

      //UDP
      case 3:
      {
        SOCKADDR_STORAGE saLocal;
        SOCKADDR_STORAGE saRemote;
        int sizeLocal = sizeof(SOCKADDR_STORAGE);
        int sizeRemote = sizeof(SOCKADDR_STORAGE);
        
        //����������� ������ � �������.
        if(CWA(ws2_32, getsockname)(s, (sockaddr *)&saLocal, &sizeLocal) != 0 || CWA(ws2_32, getpeername)(s, (sockaddr *)&saRemote, &sizeRemote) != 0)replyCode = 1; //������ SOCKS-�������
        else
        {
          //������� UDP ���� ��� ������� � ��������, �� ��������� IP, � �������� ��������� ������.
          ((SOCKADDR_IN6 *)&saLocal)->sin6_port = 0;
          HZ_IPV6_CLEAR(&saLocal);
          SOCKET clientSocket = WSocket::udpListen(&saLocal);
          
          if(clientSocket == INVALID_SOCKET)replyCode = 1; //������ SOCKS-�������
          else
          {
            #define UDP_BUFFER 65535
            LPBYTE udpBuf = (LPBYTE)Mem::alloc(UDP_BUFFER);
            if(udpBuf == NULL)replyCode = 1; //������ SOCKS-�������
            else
            {
              int l = socks5Reply(s, clientSocket, replyCode, flags);
              if(l == 1)
              {
                SOCKET serverSocket = INVALID_SOCKET; //����� ��� ������� � ��������.
                int serverBuffer = 0;                //������ ������ ���������� ��� ��������� SOCKS-UDP ���������.
                int serverFamily = 0;

                //������ � ����� ��� ��������� ������->������.
                SOCKADDR_STORAGE saClient;
                int clientSize = 0;
                
                for(;;)
                {
                  fd_set fd;
                  fd.fd_count = serverSocket == INVALID_SOCKET ? 2 : 3;
                  fd.fd_array[0] = s;
                  fd.fd_array[1] = clientSocket;
                  fd.fd_array[2] = serverSocket;
                
                  if(CWA(ws2_32, select)(0, &fd, NULL, NULL, NULL) <= 0)break; //������, ����� ����������� ����������.

                  if(WSocket::_fdIsSet(s, &fd))
                  {   
                    //UDP-����� ����������, ����� ���������� TCP-���������� ����������� ������ UDP ASSOCIATE.
                    if(CWA(ws2_32, recv)(s, (char  *)udpBuf, UDP_BUFFER, 0) <= 0)break;
                  }
                
                  int saLen = sizeof(SOCKADDR_STORAGE);

                  //������ �� �������.
                  if(WSocket::_fdIsSet(clientSocket, &fd))
                  {
                    //�������� ������.
                    int len = CWA(ws2_32, recvfrom)(clientSocket, (char *)udpBuf, UDP_BUFFER, 0, (sockaddr *)&saLocal, &saLen);
                    if(len <= 0)break;

                    //����� ������� ���, ����������.
                    if(len < sizeof(UDP_QUERY) + 2/*AS DOMAIN: SIZE+CHAR*/)goto NEXT1;

                    //�������� IP �����������.
                    if(saRemote.ss_family != saLocal.ss_family)goto NEXT1;
                    else if(saLocal.ss_family == AF_INET){if(((SOCKADDR_IN *)&saRemote)->sin_addr.S_un.S_addr != ((SOCKADDR_IN *)&saLocal)->sin_addr.S_un.S_addr)goto NEXT1;}
                    else if(saLocal.ss_family == AF_INET6){if(Mem::_compare(((SOCKADDR_IN6 *)&saRemote)->sin6_addr.u.Byte, ((SOCKADDR_IN6 *)&saLocal)->sin6_addr.u.Byte, IPv6_SIZE) != 0)goto NEXT1;}

                    //�������� ���������.
                    if(((UDP_QUERY *)udpBuf)->fragment != 0 || ((UDP_QUERY *)udpBuf)->reserved != 0)goto NEXT1;

                    //��������� ������ �� ���������� UDP �����, �� ������� ����� ������������ ������ � �������.
                    if(clientSize == 0)
                    {
                      Mem::_copy(&saClient, &saLocal, saLen);
                      HZ_IPV6_CLEAR(&saClient);
                      clientSize = saLen;                      
                    }
                    
                    //������� IP � ��������� � saLocal.
                    int offset = sizeof(UDP_QUERY);
                    Mem::_zero(&saLocal, sizeof(SOCKADDR_STORAGE));
                    switch(((UDP_QUERY *)udpBuf)->addrType)
                    {
                      //IPv4  
                      case 1:
                        if(len <= offset + IPv4_SIZE + IP_PORT_SIZE)goto NEXT1;
                        saLen = sizeof(SOCKADDR_IN);
                        saLocal.ss_family = AF_INET;
                        Mem::_copy(&(((SOCKADDR_IN *)&saLocal)->sin_addr), udpBuf + offset, IPv4_SIZE);
                        offset += IPv4_SIZE;
                        break;

                      //IPv6
                      case 4: 
                        if(len <= offset + IPv6_SIZE + IP_PORT_SIZE)goto NEXT1;                      
                        saLen = sizeof(SOCKADDR_IN6);
                        saLocal.ss_family = AF_INET6;
                        Mem::_copy((((SOCKADDR_IN6 *)&saLocal)->sin6_addr.u.Byte), udpBuf + offset, IPv6_SIZE);
                        offset += IPv6_SIZE;
                        break;
              
                      //�����
                      case 3: 
                      {
                        BYTE domainLen = udpBuf[offset];
                        if(domainLen == 0 || len <= (int)(offset + domainLen + sizeof(BYTE) + IP_PORT_SIZE))goto NEXT1;

                        BYTE domain[MAXBYTE + 1];
                        Mem::_copy(domain, udpBuf + offset + sizeof(BYTE), domainLen) ;
                        domain[domainLen] = 0;
                        offset += domainLen + sizeof(BYTE);

                        //������ � DNS
                        struct addrinfo *addrInfoList = NULL;
                        if(CWA(ws2_32, getaddrinfo)((char *)domain, NULL, NULL, &addrInfoList) != 0)goto NEXT1;

                        //���� ��� ������ IPv4 � IPv6.
                        for(register BYTE i = 0; i < sizeof(familyList) / sizeof(int); i++)
                        {
                          register struct addrinfo *curAddrInfo = addrInfoList;
                          while(curAddrInfo)
                          {
                            if(curAddrInfo->ai_family == familyList[i])
                            {
                              saLen = curAddrInfo->ai_addrlen;
                              Mem::_copy(&saLocal, curAddrInfo->ai_addr, saLen);
                              HZ_IPV6_CLEAR(&saLocal);
                              goto UDP_IP_FOUNDED;
                            }
                            curAddrInfo = curAddrInfo->ai_next;
                         }
                        }
                        //�� �� ������.
                        goto NEXT1;

                        //�� ������
UDP_IP_FOUNDED:
                        CWA(ws2_32, freeaddrinfo)(addrInfoList);
                        break;
                      }        

                      default: goto NEXT1;
                    }

                    //�������� ����.
                    ((SOCKADDR_IN6 *)&saLocal)->sin6_port = *((u_short *)(udpBuf + offset));
                    offset += IP_PORT_SIZE;

                    //������� ����� ��� ������� ���� ��� �� ���������.
                    //saLocal - �������� ������  ��� �������, ������� ����� � ������� ������� IP,
                    //�� � ��������� �� ���� IP, �.�. �� �������� � ������ IP ���� �������������
                    //������� � ��������.
                    if(serverSocket == INVALID_SOCKET)
                    {
                      SOCKADDR_STORAGE sockAddr;
                      Mem::_zero(&sockAddr, sizeof(SOCKADDR_STORAGE));
                      serverFamily = sockAddr.ss_family = saLocal.ss_family;

                      if((serverSocket = WSocket::udpListen(&sockAddr)) == INVALID_SOCKET)break;
                      serverBuffer = sizeof(UDP_QUERY) + (serverFamily == AF_INET6 ? IPv6_SIZE : IPv4_SIZE) + IP_PORT_SIZE;
                    }
                    
                    //���������� �����.
                    if(len > offset && serverFamily == saLocal.ss_family)CWA(ws2_32, sendto)(serverSocket, (char *)(udpBuf + offset), len - offset, 0, (sockaddr *)&saLocal, saLen);
                  }                                                                             
NEXT1:    
                  //������ �� �������.
                  if(serverSocket != INVALID_SOCKET && WSocket::_fdIsSet(serverSocket, &fd))
                  {
                    int len = CWA(ws2_32, recvfrom)(serverSocket, (char *)(udpBuf + serverBuffer), UDP_BUFFER - serverBuffer, 0, (sockaddr *)&saLocal, &saLen);
                    if(len <= 0 && serverFamily != saLocal.ss_family)goto NEXT2;//?

                    //��������� ������.
                    ((UDP_QUERY *)udpBuf)->reserved = 0;
                    ((UDP_QUERY *)udpBuf)->fragment = 0;
                    ((UDP_QUERY *)udpBuf)->addrType = saLocal.ss_family == AF_INET6 ? 4 /*IPv6*/ : 1 /*IPv4*/;
                    
                    if(serverFamily == AF_INET6)Mem::_copy(udpBuf + sizeof(UDP_QUERY), &(((SOCKADDR_IN6 *)&saLocal)->sin6_addr), IPv6_SIZE);
                    else if(serverFamily == AF_INET)Mem::_copy(udpBuf + sizeof(UDP_QUERY), &(((SOCKADDR_IN *)&saLocal)->sin_addr), IPv4_SIZE);
                    else goto NEXT2;

                    Mem::_copy(udpBuf + serverBuffer - IP_PORT_SIZE, &(((SOCKADDR_IN6 *)&saLocal)->sin6_port), IP_PORT_SIZE);

                    CWA(ws2_32, sendto)(clientSocket, (char *)udpBuf, len + serverBuffer, 0, (sockaddr *)&saClient, clientSize);
                  }
NEXT2:;
                }

                WSocket::tcpClose(serverSocket);
              }
              else if(l == -1)replyCode = 1; //������ SOCKS-�������
              else retVal = false;

              Mem::free(udpBuf);
            }
            WSocket::tcpClose(clientSocket);
          }
        }
        break;
      }
      
      //������
      default: replyCode = 7; //������� �� ��������������
    }
  }
  
  Mem::free(destAddr);

  //��������� ������.  
  return (retVal == true && replyCode != 0) ?
         (socks5Reply(s, INVALID_SOCKET, replyCode, flags) != 0 ? true : false) :
         retVal;
}

/*
  �������� ������ ������� Socks4.

  IN sourceSocket  - �����, �� ������� ����� ��������� �����.
  IN nameSocket    - �����, ������ �������� ����� �������� ��� INVALID_SOCKET ��� ������ � IP �
                     ������ ����������� ������.
  IN replyCode    - ��� ������.

  Return           - (-1) - � ������ ������ ��������� ������ �� IP, ����� ��� ���� �� ������������,
                            � ������ �������� �� �������� �������� ���
                            (nameSocket == INVALID_SOCKET),
                       0  - � ������ ������ � ��������� ��� ������� ����������,
                       1  - � ������ �������� �������� ������.
*/
static int socks4Reply(SOCKET sourceSocket, SOCKET nameSocket, BYTE replyCode, DWORD flags)
{
  SOCKS4_REPLY sr;

  //�������������� �������� ������ ������, ���� ��� ����������.
  if(nameSocket != INVALID_SOCKET)
  {
    SOCKADDR_IN sa;
    int size = sizeof(SOCKADDR_IN);
    
    if(flags & S5_ONREPLY_PEER_NAME)
    {
      if(CWA(ws2_32, getpeername)(nameSocket, (SOCKADDR *)&sa, &size) != 0)return -1; //������ �������.
    }
    else 
    {
      if(CWA(ws2_32, getsockname)(nameSocket, (SOCKADDR *)&sa, &size) != 0)return -1; //������ �������.
    }
    
    sr.destIp   = sa.sin_addr.S_un.S_addr;
    sr.destPort = sa.sin_port;
  }
  else
  {
    sr.destIp = 0;
    sr.destPort = 0;
  }

  sr.version   = 0;
  sr.replyCode = replyCode;

  return WSocket::tcpSend(sourceSocket, &sr, sizeof(SOCKS4_REPLY)) ? 1 : 0;
}

/*
  http://www.sockschain.com/doc/socks4_protocol.htm
*/
bool Socks5Server::_start4(SOCKET s, DWORD timeout)
{
  DWORD flags = WSocket::getFamily(s) == AF_INET6 ? S5_CLIENT_IS_IPV6 : S5_CLIENT_IS_IPV4;
  SOCKS4_QUERY sq;

  //������� ���������.
  if(!WSocket::tcpRecvAll(s, &sq, sizeof(SOCKS4_QUERY), timeout))return false;

  //�������� UserID
  for(;;)
  {
    BYTE tmp;
    if(!WSocket::tcpRecvAll(s, &tmp, sizeof(BYTE), timeout))return false;
    if(tmp == 0)break;
  }
  
  BYTE replyCode = 90; //��������    
  
  //�������� ������ 4a
  DWORD tmpDword = SWAP_DWORD(sq.destIp);

  if(tmpDword > 0 && tmpDword < 256)
  {
    BYTE domain[MAXBYTE + 1];
    for(int i = 0; ; i++)
    {
      BYTE tmpByte;
      if(i > 255 || !WSocket::tcpRecvAll(s, &tmpByte, sizeof(BYTE), timeout))return false;
      domain[i] = tmpByte;
      if(tmpByte == 0)break;
    }
    
    struct addrinfo *addrInfoList = NULL;
    if(CWA(ws2_32, getaddrinfo)((char *)domain, NULL, NULL, &addrInfoList) != 0)replyCode = 91; //request rejected or failed
    else
    {
      //���� ��� ������ IPv4.
      register struct addrinfo *curAddrInfo = addrInfoList;
      while(curAddrInfo)
      {
        if(curAddrInfo->ai_family == AF_INET)
        {
          Mem::_copy(&sq.destIp, &(((SOCKADDR_IN *)(curAddrInfo->ai_addr))->sin_addr), IPv4_SIZE);
          break;
        }
        curAddrInfo = curAddrInfo->ai_next;
      }
      CWA(ws2_32, freeaddrinfo)(addrInfoList);

      //IPv4 �� ������
      if(curAddrInfo == NULL)replyCode = 91; //request rejected or failed
    }
  }

  bool retVal = true;
  
  //��������� �������.
  if(replyCode == 90)
  {
    SOCKADDR_IN sa;
    Mem::_zero(&sa, sizeof(sockaddr_in));
    sa.sin_family = AF_INET;

    switch(sq.command)
    {
      //CONNECT
      case 1:
      {
        sa.sin_port             = sq.destPort;
        sa.sin_addr.S_un.S_addr = sq.destIp;
        
        SOCKET destSocket = WSocket::tcpConnect((SOCKADDR_STORAGE *)&sa);
        if(destSocket == INVALID_SOCKET)replyCode = 91; //request rejected or failed
        else
        {
          WSocket::tcpDisableDelay(destSocket, true);
          int l = socks4Reply(s, destSocket, replyCode, flags);
          if(l == 1)WSocket::tcpTunnel(s, destSocket);
          else if(l == -1)replyCode = 91; //request rejected or failed
          else retVal = false;
          WSocket::tcpClose(destSocket);
        }
        break;
      }
      
      //BIND
      case 2:
      {
        SOCKET destSocket;
        if((destSocket = WSocket::tcpListen((SOCKADDR_STORAGE *)&sa, 1)) == INVALID_SOCKET)replyCode = 91; //request rejected or failed
        else
        {
          int l = socks4Reply(s, destSocket, replyCode, flags);
          if(l == 1)
          {
            SOCKET incomingSocket = WSocket::tcpWaitForIncomingAndAccept(&destSocket, 1, 0, NULL, NULL, &s, 1);
            WSocket::tcpClose(destSocket);

            //������ ����� ����� ��������� � ������� �� IP ����������� ������, �� � �� ������ 
            //��� ������.
            if(incomingSocket == INVALID_SOCKET)replyCode = 91; //request rejected or failed
            else
            {              
              WSocket::tcpDisableDelay(incomingSocket, true);
              if((l = socks4Reply(s, incomingSocket, replyCode, flags | S5_ONREPLY_PEER_NAME)) == 1)
              {
                WSocket::tcpTunnel(s, incomingSocket);                
              }
              WSocket::tcpClose(incomingSocket);
            }
          }
          else WSocket::tcpClose(destSocket);

          if(l == -1)replyCode = 91; //request rejected or failed
          else if(l != 1)retVal = false;
        }
        break;
      }

      default: replyCode = 91; //request rejected or failed
    }
  }   

  //��������� ������.  
  return (retVal == true && replyCode != 90) ?
         (socks4Reply(s, INVALID_SOCKET, replyCode, flags) != 0 ? true : false) :
          retVal;
}

bool Socks5Server::_start(SOCKET s, DWORD timeout)
{
  BYTE socksVersion;
  bool r = false;
  if(WSocket::tcpRecvAll(s, &socksVersion, 1, timeout))
  {
    if(socksVersion == 5)r = _start5(s, timeout);
    else if(socksVersion == 4)r = _start4(s, timeout);
  }
  WSocket::tcpClose(s);
  return r;
}
