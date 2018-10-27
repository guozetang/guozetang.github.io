---
title: Leetcode 819. Most Common Words
date: 2018-10-22 19:09:31
updated: 2018-10-22 19:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words. It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of punctuation. Words in the paragraph are not case sensitive. The answer is in lowercase.

**Example:**

> **Input:**
> paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
> banned = ["hit"]
> **Output:** "ball"
> **Explanation:**s
> "hit" occurs 3 times, but it is a banned word.
> "ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive, that punctuation is ignored (even if adjacent to words, such as "ball,"), and that "hit" isn't the answer even though it occurs more because it is banned.

**Note:**

- `1 <= paragraph.length <= 1000`.
- `1 <= banned.length <= 100`.
- `1 <= banned[i].length <= 10`.
- The answer is unique, and written in lowercase (even if its occurrences in  `paragraph` may have uppercase symbols, and even if it is a proper noun.)
- `paragraph`  only consists of letters, spaces, or the punctuation symbols  `!?',;.`
- There are no hyphens or hyphenated words.
- Words only consist of letters, never apostrophes or other punctuation symbols.

<!--more-->

# Analzye

这一道题目只需要排查被禁止的词汇,找到里面重复最高频率的词汇就可以了，处理方式如下：

- 在`string paragraph`里面找到特殊的符号，将这一些特殊的符号全部是使用`空格`代替，为之后更容易的分割输入做准备
- 使用`istringstream stream(paragraph)`将输入全部转换成以空格分割的输入单词`word`.
- 将每个不在禁止字符串数组里面的单词都插入到一个`unordered_map`，如果原来`unordered_map`里面没有的话，那么就存有1，如果原来里面就已经有数据了，那么就取出来对应的数据，将其加一
- 最后遍历`unordered_map`，找到`currentMax = it->second; arg_max = it->first;`最大的位置，然后返回。

----------

# Solution

```cpp
class Solution {
 public:
  string mostCommonWord(string paragraph, vector<string>& banned) {
    const string symbols = "!?',;.";
    std::unordered_set<std::string> bannedset;
    std::unordered_map<std::string, int> stringMap;
    string word, arg_max;
    unsigned currentMax = 0;

    for (string s : banned) bannedset.emplace(s);
    for (auto it = paragraph.begin(); it != paragraph.end();) {
      if (symbols.find(*it) != std::string::npos) {
        *it = ' ';
      } else {
        *it = tolower(*it);
        ++it;
      }
    }
    istringstream stream(paragraph);
    while (stream >> word) {
      if (bannedset.find(word) == bannedset.end()) {
        auto search = stringMap.find(word);
        if (search == stringMap.end()) {
          stringMap.insert(std::make_pair(word, 1));
        } else {
          stringMap[word] = search->second + 1;
        }
      }
    }

    for (auto it = stringMap.begin(); it != stringMap.end(); ++it) {
      if (it->second > currentMax) {
        arg_max = it->first;
        currentMax = it->second;
      }
    }

    return arg_max;
  }
};

```