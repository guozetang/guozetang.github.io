
******

**Problem 5:**

> Please show how you can use sniffex to capture the password when somebody is using telnet on the network that you are monitoring. You may need to modify the sniffex.c a little bit if needed. You also need to start the telnetd server on your VM. If you are using our pre-built VM, the telnetd server is already installed; just type the following command to start it.
`% sudo service openbsd-inetd start`

******

### Task 2: Spoofing

**Problem 6:**

> Please use your own words to describe the sequence of the library calls that are essential for packet spoofing. This is meant to be a summary.


**Problem 7:**

> Why do you need the root privilege to run the programs that use raw sockets? Where does the program fail if executed without the root privilege?

**Problem 8:**

> Please combine your sniffing and the spoofing programs to implement a sniff-and-then-spoof program. This program monitors its local network; whenever it sees an ICMP echo request packet,it spoofs an ICMP echo reply packet. Therefore, even if the victim machine pings a non-existing machine,it will always see that the machine is alive. Please include screendump in your report to show that your program works. Please also attach the code in your report.