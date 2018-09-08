---
title: Leetcode 38. Count AndSay
date: 2018-07-29 09:50:32
updated: 2018-09-08 09:50:32
categories: Leetcode
tags: Leetcode
---
## Count AndSay
The count-and-say sequence is the sequence of integers with the first five terms as following:

1. 1
2. 11
3. 21
4. 1211
5. 111221

`1`  is read off as  `"one 1"`  or  `11`.  
`11`  is read off as  `"two 1s"`  or  `21`.  
`21`  is read off as  `"one 2`, then  `one 1"`  or  `1211`.  

Given an integer  _n_, generate the  _n_th  term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

**Example 1:**

**Input:** 1
**Output:** "1"

**Example 2:**

**Input:** 4
**Output:** "1211"

## Solution

```cpp
class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        string res = "1";
        while(--n) {
            string cur = "";
            for (int i=0; i < res.size(); ++i){
                int count = 1;
                while (i+1 < res.size() && res[i+1] == res[i]) {
                    count++;
                    i++;
                }
                cur += to_string(count) + res[i];
            }
            res = cur;
        }
        return res;
        
    }
};
```

其实我们可以发现**字符串中永远只会出现1,2,3这三个字符**，假设第k个字符串中出现了4，那么第k-1个字符串必定有四个相同的字符连续出现，假设这个字符为1，则第k-1个字符串为x1111y。第k-1个字符串是第k-2个字符串的读法，即第k-2个字符串可以读为“x个1,1个1,1个y” 或者“*个x,1个1,1个1,y个*”，这两种读法分别可以合并成“x+1个1,1个y” 和 “*个x，2个1，y个*”，代表的字符串分别是“(x+1)11y” 和 "x21y"，即k-1个字符串为“(x+1)11y” 或 "x21y"，不可能为“x1111y”.