# Aoyama ![](https://img.shields.io/badge/Version-2.0-brightgreen.svg)  ![](https://img.shields.io/badge/license-GPL2.0-green.svg)
Aoyama is a New version of Python3 botnet, old version: http://github.com/Leeon123/Python3-botnet

Aoyama is for ddos(Maybe add more function later, such as...keylogger?)

***PLS Don't scan the executable file generated from pyinstaller or py2exe on any virus scanner(such as VirusTotal), if you want to keep using this project(i will continue update the code) and not be detected*** 

**~~Plese run the cnc.py in linux, run in windows will have bug when login to cnc(idk why but i will try to fix it)~~**

**Fixed**

**Test video(OLD): https://www.youtube.com/watch?v=W4YR-cf3xD0**

[Virustotal (Old)](https://www.virustotal.com/gui/file/4d4ef809d67cd70708567527e48540fdce61d76f0034b774396130612e17e0da/detection)
## News&Features
**BOT(V2):**
- [x] **Added Port Scanner**
- [x] Improved Code
- [x] Added Slowloris attack
- [x] Improved attack process
- [x] Auto enable ssl when attack
- [x] Encrypted traffic(xor)
- [x] Deamon(only linux)(PS: You can use pyinstaller option '--noconsole' on windows)
- [x] Hide itself(linux: Deamon + delete itself | windows: Hide sys.argv[0])
- [x] Added single instance mode
- [x] Startup delay 30~90(random) seconds to bypass some sandbox scanning

**CNC(V2):**
- [x] Decrease delay of send command
- [x] Support Telnet Login
- [x] Encrypted traffic(xor)
- [x] Coloured CNC
- [x] Using login.txt to check account.(Need improve, sometime may have bugs)
- [x] Keep-alive connection
- [x] Using putty raw-mode login(on windows) and telnet(on linux)
- [x] Using 'ping/pong' to check bot connection status(use 'scan' to check it by yourself or it checks every **15 seconds**.)

## Opinion:
In my opinion, best way is using **python v3.4.3** and **pyinstaller v3.2**. They are the best pattern i tested and used.

## Usage:
***Change*** the cnc server ip and port into the client.py **at first**.

Then, edit the password of cnc.py and run the cnc.py:

    python3 cnc.py <port>
    
At Last, run the bot.py in any python3 environment(IDE, codeanywhere,etc.) or u can use pyinstaller to help u

then the **Bot** is online.

***To login cnc***, using **telnet(Updated after v2)** connect it then

It should be show like this:

        Username:
        
At this moment, u should create a file called login.txt and input the username and password in it

Like this:

        Leeon123 test

After that, Just input ur username and password.
        
                    
            Username:Leeon123
            Password:test
            
