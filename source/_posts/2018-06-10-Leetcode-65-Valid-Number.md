---
title: Leetcode 65. Valid Number
date: 2018-06-10 23:30:32
categories: Leetcode
tags: Leetcode
---

﻿Validate if a given string is numeric.
Some examples:  
`"0"`  =>  `true`  
`" 0.1 "`  =>  `true`  
`"abc"`  =>  `false`  
`"1 a"`  =>  `false`  
`"2e10"`  =>  `true`

**Note:**  It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.

**Update (2015-02-10):**  
The signature of the  `C++`  function had been updated. If you still see your function signature accepts a  `const char *`  argument, please click the reload button to reset your code definition.
<!--more-->
## Analyze
在字符串中, 所有的字符可以分为六类: 空格，符号，数字，小数点，自然底数e和其他字符;只要出现了其他字符就可以`return false`, 出现其他几个字符是可以的, 在这里我们设置`num, dot, exp, sign`分别表示数字，小数点，自然底数和符号是否出现，另外设置numberAfterE表示自然底数后面是否有数字出现, 这几种情况下详细分析:
- 空格： 我们需要排除的情况是，当前位置是空格而后面一位不为空格，但是之前有数字，小数点，自然底数或者符号出现时返回false。
- 符号：符号前面如果有字符的话必须是空格或者是自然底数，标记sign为true。
- 数字：标记num为true, 如果前面出现了自然底数, 那么标记numAfterE为true。
- 小数点：如果之前出现过小数点或者自然底数，返回false，否则标记dot为true。
- 自然底数：如果之前出现过自然底数或者之前从未出现过数字，返回false，否则标记exp为true，numAfterE为false。
- 其他字符：返回false。
最后返回num && numAfterE即可。

## Solution
```cpp
class Solution {
public:
    bool isNumber(string s) {
        bool num = false, dot = false, numberAfterE = true, exp = false, sign = false;
        
        int len = s.size();

        for(int i = 0; i < len; ++i){
            if (s[i] == ' ') {
                if ( ((i < len -1) && s[i + 1] != ' ') && (num || dot || sign) ) return false;
            } else if (s[i] == '+' || s[i] == '-') {
                if(i > 0 && s[i - 1] != 'e' && s[i -1] != 'E' && s[i - 1] != ' '  ) return false;
                sign = true;
            } else if (s[i] == 'e' || s[i] == 'E') {
                if(!num || exp) return false;
                exp = true;
                numberAfterE = false;
            } else if (s[i] == '.') {
                if(dot || exp) return false;
                dot = true;
            } else if (s[i] >= '0' && s[i] <= '9') {
                numberAfterE = true;
                num = true;
            } else
                return false; 
            
        }
        return num && numberAfterE;
    }
};
```
