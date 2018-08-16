---
title: Redesign The Event Managerment
date: 2018-08-09 11:38:13
categories: Network, C++
tags: Network, C++
---
> 前言： 


<!--more-->
### ID for network Connection information
```c++
/** @brief 5-tuples connect info
 */
struct connect_info_t {
    in_addr src_ip;
    in_addr dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    char protocol;
};
```
