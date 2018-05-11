---
title:     Some issues when I used my MSI GE60 2PG
date:       2018-05-08 12:00:00
categories: Life
tags: Laptop
---
There are some issues when I used my MSI GE60 2PG.  

## 1. Sound Blaster Cinema 1 Potential fix on Windows 10  
A way to get Sound Blaster Cinema 1 fully functional on windows 10 x64 bit. This is a fix for those that attempt to open the program and immediately get a crash or no windows popping up and the system tray icon freezes.
<!-- more -->
> 1. Uninstalled both my realtek HD audio drivers via control panel, and uninstalled SBC. 
> 2. Then rebooted and had ccleaner fix any registry errors. Reinstalled the drivers and SBC. 
> 3. Go into the programs folder here:   
 `C:\Program Files (x86)\Creative\Sound Blaster Cinema\Sound Blaster Cinema`  
  Then delete the SBCinema.exe.config file.

Now the SBC is fully functional on Windows 10 64 bit and hopefully it works for everyone else to!