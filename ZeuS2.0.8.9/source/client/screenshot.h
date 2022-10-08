/*
  �������� ���������.
*/
#pragma once

namespace Screenshoot
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
    ������ ��������� ������ � IStream.

    IN mimeType - ������ �����������.
    IN quality  - �������� �������� � ��������� (������ JPEG).
    IN rect     - ������ ������� �������� ������ �������, ��� 0 - ��� �������� ��������� �����
                  ������.

    Return      - IStream - � ������ ������,
                  NULL    - � ������ ������.
  */
  IStream *_screenToIStream(LPWSTR mimeType, DWORD quality, WORD rect);

  /*
    ������ ��������� ������ � �����.

    IN s        - �����.
    IN mimeType - ������ �����������.
    IN quality  - �������� �������� � ��������� (������ JPEG).
    IN rect     - ������ ������� �������� ������ �������, ��� 0 - ��� �������� ��������� �����
                  ������.

    Return      - true  - � ������ ������,
                  false - � ������ ������.
  */
  bool _screenToSocket(SOCKET s, LPWSTR mimeType, DWORD quality, WORD rect);
};
