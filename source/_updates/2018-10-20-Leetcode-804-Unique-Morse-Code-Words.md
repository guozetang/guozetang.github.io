---
title: Leetcode 804. Unique Morse Code Words
date: 2018-10-20 15:09:31
updated: 2018-10-20 15:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:  `"a"`maps to  `".-"`,  `"b"`  maps to  `"-..."`,  `"c"`  maps to  `"-.-."`, and so on.

For convenience, the full table for the 26 letters of the English alphabet is given below:

```cpp
[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
```

Now, given a list of words, each word can be written as a concatenation of the Morse code of each letter. For example, "cab" can be written as "-.-.-....-", (which is the concatenation "-.-." + "-..." + ".-"). We'll call such a concatenation, the transformation of a word.

Return the number of different transformations among all words we have.

**Example:**
> **Input:** words = ["gin", "zen", "gig", "msg"]
> **Output:** 2
> **Explanation:** 
> The transformation of each word is:
> "gin" -> "--...-."
> "zen" -> "--...-."
> "gig" -> "--...--."
> "msg" -> "--...--."

There are 2 different transformations, "--...-." and "--...--.".

**Note:**

- The length of  `words`  will be at most  `100`.
- Each  `words[i]`  will have length in range  `[1, 12]`.
- `words[i]`  will only consist of lowercase letters.

<!--more-->

---

# Analyze

The input is a `vector<string> words`. There are some words. We need to convert those words to `MorseRepresentations`. And some works may get the same Mores Code. We need output how many different Mores code can get from these words. As a result, I choose `std::unordered_set<std::string>` to save these Morse Code. And return its size.

---

# Solution

```cpp
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
      std::string name[26]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
      std::unordered_set<std::string> myset;

      for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        std::string tmp = "";
        for (char c : *it ) {
          tmp += name[ c- 'a'];
        }
        myset.insert (tmp);
      }
      return myset.size();
    }
};
```