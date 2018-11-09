---
title: Leetcode 3. Longgest Substring Without Repeating Characters.
date: 2018-05-11 15:53:37
updated: 2018-05-11 15:53:37
categories: Leetcode
tags: Leetcode
---
# Question

> Given a string, find the length of the longest substring without repeating characters.  
> Examples:  
> Given "abcabcbb", the answer is "abc", which the length is 3.  
> Given "bbbbb", the answer is "b", with the length of 1.  
> Given "pwwkew", the answer is "wke", with the length of 3.   
> Note that the answer must be a substring, "pwke" is a subsequence and not a substring.  

**Difficulty**:Medium
**Category**:String

<!-- more -->

****

# Analyze

思路：其实只需要前面出现过的重复字符的下标即可算出此段不重复子段的长度，核心操作其实是向前检索重复字符。需要注意的是最后循环完成后，需要再算一下没有计算的那段的长度，在这些子段中取最长的。O(n)

# Solution

<!-- ```java
class Solution {
    public int lengthOfLongestSubstring(String s) {
        char[] sc = s.toCharArray(); //string to char 

        Map<Character, Integer> cm = new HashMap<Character, Integer>();  //build a hashmap to save 

        int j = 0, maxLen = 0;
        for(int i = 0;i < sc.length; ++i) { //follow the order to find which is note the similar letter 
            char cur = sc[i];
            if(cm.containsKey(cur)) { 
//if there are some letter which were belonged to Hashmap, then this is a same letter

                maxLen = Math.max(i - j, maxLen); 
// i-j is 
                j = Math.max(j, cm.get(cur) + 1);
//j = length 
            }
            cm.put(cur, i);  //put the char to Hashmap(char, order)
        }
        return Math.max(sc.length - j, maxLen);
    }
}
```

# Follow up

```java
Java String toCharArray()
The java string toCharArray() method converts this string into character array. It returns a newly created character array, its length is similar to this string and its contents are initialized with the characters of this string.

public class StringToCharArrayExample{  
public static void main(String args[]){  
String s1="hello";  
char[] ch=s1.toCharArray();  
for(int i=0;i<ch.length;i++){  
System.out.print(ch[i]);  
}  
}} 
```  -->

1.蛮力法（Brute Force）
首先试了试暴力搜索，遍历一次字符串，遍历过程中，对每个字符都有一个 O(N^2)的处理时间，因为需要遍历该字符之后的字符串，对每个字符，需要和已有的子串相比较，如果不重复，则加入子串，不然就遍历下一个字符。加起来时间复杂度为 O(N^3)。

```c++
int lengthOfLongestSubstring(string s) {
  int length = s.size();
  int maxlength = 0;
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j <= length; j++) {
      if (allUnique(s, i, j)) maxlength = max(maxlength, j - i);
    }
  }
  return maxlength;
}

bool allUnique(string s, int start, int end) {
  set<char> charSet;
  for (int i = start; i < end; i++) {
    char ch = s.at(i);
    if (charSet.count(ch)) return false;
    charSet.insert(ch);
  }
  return true;
}
```

2.Hash法
这类问题应该学会分析结果的特点，比如说前面的最长回文子串，是利用了回文串的对称性，那么无重复子串呢，想到无重复，可以想到可以使用 hash，当新的字符来了，有冲突，就说明前面是有重复的。 算法思想：两次循环得到所有的子串，用 hash 判断是否重复。

代码中需要注意的地方：

以字符对应的 ASCII 码作为 hash 值，visit[s[i]] = 0，说明 s[i] 这个字符还没有出现过，visit[s[i]] = 1 说明有重复。

在每次内层循环重新开始的时候，都要将 visit 初始化为 0，每次内层循环求的是 s[i...j] 之间的最长子串，要判断他们之间是否有重复，所以要确保 i...j 这个范围内的 visit 都没初始化为 0 了，否则出现 i...j 之间的字符和这个范围之外的字符重复就会导致结果出错。

```cpp
int lengthOfLongestSubstring(string s) {
  int length = s.size();
  int maxlength = 0;
  int i, j;
  for (i = 0; i < length; ++i) {
    int visit[128] = {0};
    visit[s[i]] = 1;
    for (j = i + 1; j < length; ++j) {
      if (!visit[s[j]]) {
        visit[s[j]] = 1;
      } else {
        if (j - i > maxlength) {
          maxlength = j - i;
        }
        break;
      }
    }
    if ((j == length) && (j - i > maxlength)) {
      maxlength = j - i;
    }
  }
  return maxlength;
}
```c

3.Sliding Window
Sliding Window方法就是使用了动态规划+HashSet。首先理解，动态规划算法的思想，将问题分解为子问题的解，找到重叠子问题和最优子结构，对需要重复计算的结果进行存储。而使用了HashSet之后，重叠子问题操作可以简单很多，只需要 2N 步就能得出结果。

```cpp
int lengthOfLongestSubstring(string s) {
  int length = s.size();
  int maxlength = 0, i = 0, j = 0;
  set<char> charSet;
  while (i < length && j < length) {
    if (!charSet.count(s.at(j))) {
      charSet.insert(s.at(j++));
      maxlength = max(maxlength, j - i);
    } else {
      charSet.erase(s.at(i++));
    }
  }
  return maxlength;
}
```

4.优化的Sliding Window
使用HashMap和ASCII

使用HashMap

```cpp
int lengthOfLongestSubstring(string s) {
  int length = s.size();
  int maxlength = 0;
  map<char, int> hashMap;
  for (int i = 0, j = 0; j < length; j++) {
    if (hashMap.count(s.at(j))) {
      i = max(hashMap[s.at(j)], i);
      hashMap[s.at(j)] = j + 1;
    } else {
      hashMap.insert(pair<char, int>(s.at(j), j + 1));
    }
    maxlength = max(maxlength, j - i + 1);
  }
  return maxlength;
}
```

使用ASCII

```cpp
int lengthOfLongestSubstring(string s) {
  int length = s.size();
  vector<int> vect(128, -1);
  int maxlength = 0, start = -1;
  for (int i = 0; i < length; i++) {
    start = max(vect[s[i]], start);
    vect[s[i]] = i;
    maxlength = max(maxlength, i - start);
  }
  return maxlength;
}
```