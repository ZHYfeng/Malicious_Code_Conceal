Source: Win32.Cairuh.B@mm
Author: Bull Moose
Type: Retro Worm
Date: 12/6/09

This is a Mass Mailer variant of Cairuh.A that I have implemented to mail itself to all contacts in 
Microsoft Windows Outlook. I have removed the functions that change the registry values in 
exefile and comfile, because it causes too much suspicion and it would counteract with the mass mailing function.

Its features are:
- Anti Virus Terminator
- Optional protecting upon compilation (give makefile.bat the -p argument)
- Mass Mailing
- USB Autorun infection
- P2P Spread
- Network Spread
- File Backdoor
- HOSTS File Infection
- Overwrites all .exe's in current directory
- Uses IsDebuggerPresent() API to return if present
- Stealth Window

I decided to not directly send mail but instead use a VBS script as the middle man to do the work.
The VBS script is dropped and decrypted and filled with REM statements between each line to avoid 
detection both runtime and scantime. Maybe next time I will create a Mass Mailer that uses a MX engine 
and it's own SMTP server.

Here are the other people that I think are cool in (or was in) the vX scene:
Benny, The Mental Driller, hh86, Vecna, herm1t, roy g biv, Gigabyte, Q The Misanthrope, Virus Buster, 
Bumblebee, Z0mbie, and probably more.