# Question

Given two strings **s1** and **s2**, write a function to return true if **s2** contains the permutation of **s1**. In other words, one of the first string's permutations is the **substring** of the second string.

**Example 1:** 
> **Input:**s1 = "ab" s2 = "eidbaooo"
> **Output:**True
> **Explanation:** s2 contains one permutation of s1 ("ba").

**Example 2:** 

> **Input:** s1= "ab" s2 = "eidboaoo"
> **Output:** False

**Note:**

1. The input strings only contain lower case letters.
2. The length of both given strings is in range [1, 10,000].

<!--more-->

---

# Analyze

This is a question about the strings operated. The input is string include the `char`, if we use the `vector` to save all of the input, this will be complext becasue `The length of both given strings is in range [1, 10,000].` So, I consided to use the `char` letter as the vector index, and the `value` is the number of this char. As a result, the process of this question likes followed.

- Read each `char` from the s1，use vec1[s1[i]]++; Read each `char` from the s2，use vec1[s2[i]]++. In this case, use the length of `s1` as the constraint conddition.
- If vec1 == vec2, return true
- Read the [n1, n2] char from the `s2`, each time read one letter and remove one letter from the first of s2[j-n1]
- Compare the `vec1 and vec2`

---

# Solution

```cpp
class Solution {
 public:
  bool checkInclusion(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<int> vec1(127), vec2(127);
    for (int i = 0; i < n1; ++i) {
      vec1[s1[i]]++;
      vec2[s2[i]]++;
    }

    if (vec1 == vec2) return true;
    for (int i = n1; i < n2; ++i) {
      --vec2[s2[i - n1]];
      ++vec2[s2[i]];
      if (vec1 == vec2) return true;
    }
    return false;
  }
};
```