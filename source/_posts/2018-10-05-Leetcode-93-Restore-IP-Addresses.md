---
title: Leetcode 20. Valid Parentheses
date: 2018-10-05 14:09:31
updated: 2018-10-05 14:09:31
categories: Leetcode
tags: Leetcode
top:
---

# Question

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

**Example:**
> **Input:** "25525511135"
> **Output:** `["255.255.11.135", "255.255.111.35"]`

<!--more-->

---

# Analyze

**题目要求**：从一串数字里面还原出来IP地址，将可能的情况全部列出来。

- IP地址由32位二进制数组成，以`XXX.XXX.XXX.XXX`形式表现，每组XXX代表小于或等于255的10进制数。所以说IP地址总共有四段，每一段可能有一位，两位或者三位，范围是[0, 255]
- 输入字符串只含有数字，所以当某段是三位时，我们要判断其是否越界（>255)，还有一点很重要的是，
- 只有一位时，0可以成某一段，如果有两位或三位时，像`00， 01， 001， 011，000`等都是不合法的
- 需要在字符串里面加入三个点，将字符串分为四段，并且需要检查每一段是否合法。

使用递归的方式来求出所有的情况。

---

# Solution

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
      vector<string> res;
      digit_to_ip(s, 4, "", res);
      return res;
    }

    void digit_to_ip(string s, int n, string out, vector<string>& res) {
      // If the n = 0, then this is the last one. Don't do anything.
      if(n==0) {
        if( s.empty() ) res.push_back(out);
        // std::cout << "[INFO] Out=" << out << std::endl;
        // else return false;
      }
      else {  // If n > 0, to get each substring by recursion
        for(int i = 1; i <= 3; ++i) {
          if( s.size() >= i && isVaild( s.substr(0, i))) {
            // std::cout << "[INFO] n =" << n << std::endl;
            if(n == 1) {
              // std::cout<< "[INFO] n == 1"<< std::endl;
              digit_to_ip(s.substr(i), n - 1, out+s.substr(0, i), res);
            } //Deal with the last one
            else digit_to_ip(s.substr(i), n - 1, out+s.substr(0, i)+'.', res);
          }
        }
      }
    }
    // Check the subddr is not more than 255
    bool isVaild(string s) {
      if(s.empty() || s.size() > 3 || (s.size() > 1 && s[0] == '0') ) return false; 
      int ipsubaddr = atoi(s.c_str());
      return ipsubaddr <= 255 && ipsubaddr >= 0;
    }
};
```