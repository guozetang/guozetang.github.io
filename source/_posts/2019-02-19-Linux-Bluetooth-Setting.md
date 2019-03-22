---
title: Linux Bluetooth Setting
date: 2019-02-19 13:55:25
updated: 2019-02-19 13:55:25
categories: 
- [Notes]
tags: Node
notshow: true
mathjax: true
top:
---

# Introduce

[I ran into this issue on my Lenovo P51 running Ubuntu 18.04, and I discovered that the pactl module "module-bluetooth-discover" was not loading properly at boot time. I fixed the issue by replacing it with "module-bluez5-discover" in my pulse configuration.

You can test this by running:  
`sudo pactl unload-module module-bluetooth-discover`  
`sudo pactl load-module module-bluez5-discover`

And try to repair/reconnect your devices. If it works, replicate the following configuration in your /etc/pulse/default.pa config.
](
4

I ran into this issue on my Lenovo P51 running Ubuntu 18.04, and I discovered that the pactl module "module-bluetooth-discover" was not loading properly at boot time. I fixed the issue by replacing it with "module-bluez5-discover" in my pulse configuration.

You can test this by running:  
`sudo pactl unload-module module-bluetooth-discover`  
`sudo pactl load-module module-bluez5-discover`

And try to repair/reconnect your devices. If it works, replicate the following configuration in your /etc/pulse/default.pa config.

```
# Modify: /etc/pulse/default.pa
# Comment out the following line

.ifexists module-bluetooth-discover.so
load-module module-bluetooth-discover
.endif

# Replace it with ...

.ifexists module-bluez5-discover.so
load-module module-bluez5-discover
.endif

```

My suspicion is that this is a change that was made during the switch from Unity to Gnome and the leftover configurations remained, leaving the standard Bluetooth modules behind which don't load correctly.

After switching to bluez5, I have since had no issues, and Bluetooth connects without complaint on my mobile phone, mouse, and headset. :)

EDIT: I also followed several steps mentioned here:  [Bluetooth doesn't work after resuming from sleep, Ubuntu 18.04 LTS](https://askubuntu.com/questions/1036195/bluetooth-doesnt-work-after-resuming-from-sleep-ubuntu-18-04-lts?noredirect=1&lq=1)

To exactly replicate my configuration, make sure you  `apt-get install bluez blueman pulseaudio`to have all the same packages. As was suggested in the referenced problem, I believe this was caused by upgrading to 18.04 from 17.04.)




## update bluez to >=5.28.2

18.04 ships with a buggy bluez package for now; newer version is available from this PPA:  [https://launchpad.net/~bluetooth/+archive/ubuntu/bluez](https://launchpad.net/~bluetooth/+archive/ubuntu/bluez):

```
sudo add-apt-repository ppa:bluetooth/bluez
sudo apt install bluez

```

----------

### workaround for buggy Bluetooth applet (Unity specific?)

This is probably the issue @solstice mentioned - BT menu applet doesn't let me enable Bluetooth after resuming from sleep. No matter if the toggle switch is off or on, the BT icon is disabled, and rfkill output doesn't change:

```
$ rfkill list
0: phy0: Wireless LAN
    Soft blocked: no
    Hard blocked: no
12: hci0: Bluetooth
    Soft blocked: no
    Hard blocked: no

```

You can toggle BT manually by running (substitute your own ID):

```
rfkill block 12
rfkill unblock 12

```

and BT applet should pick it up correctly now. At this point, you should be able to connect to your devices. For now I've hacked it together using a script that does this automatically after resume:

```
$ cat /lib/systemd/system-sleep/bt
#!/bin/sh

case $1 in
  post)
    sleep 5
    rfkill block `rfkill list | grep hci | cut -d: -f1`
    sleep 1
    rfkill unblock `rfkill list | grep hci | cut -d: -f1`
    ;;
esac

```

The ID number next to hci0 in rfkill list output seems to increment after every suspend/resume. Disabling/enabling BT using the BT menu should change the output ('soft blocked: yes' for BT disabled via menu), but it doesn't. My guess is that the applet remembers the wrong device ID and is thus trying to enable a device that no longer exists.