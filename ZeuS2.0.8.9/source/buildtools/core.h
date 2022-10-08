/*
  ����.
*/
#pragma once

//��������� ��� �������� �������� ������ ��������.
typedef struct
{
  DWORD exitCode;           //��� ������
  struct
  {
    int argsCount;          //���������� ���������� � ��������� ������.
    LPWSTR *args;           //������ ��������� ������.
  }commandLine;
  WCHAR fileName[MAX_PATH]; //������� ��� �����.
}COREDATA;
extern COREDATA coreData;

namespace Core
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ����� ��������.
  */
  void showLogo(void);
};
