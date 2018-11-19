---
title: Leetcode 36. Valid Sudoku
date: 2018-11-19 16:09:31
updated: 2018-11-19 16:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated **according to the following rules**:

1. Each row must contain the digits `1-9`  without repetition.
2. Each column must contain the digits `1-9` without repetition.
3. Each of the 9  `3x3`  sub-boxes of the grid must contain the digits `1-9` without repetition.

![](/images/in-post/leetcode/2018-11-19-16-08-05.png)

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character  `'.'`.

**Example 1:**

> **Input:**
> [
>  ["5","3",".",".","7",".",".",".","."],
>  ["6",".",".","1","9","5",".",".","."],
>  [".","9","8",".",".",".",".","6","."],
>  ["8",".",".",".","6",".",".",".","3"],
>  ["4",".",".","8",".","3",".",".","1"],
>  ["7",".",".",".","2",".",".",".","6"],
>  [".","6",".",".",".",".","2","8","."],
>  [".",".",".","4","1","9",".",".","5"],
>  [".",".",".",".","8",".",".","7","9"]
> ]
> **Output:** true

**Example 2:**

> **Input:**
> [
>  ["8","3",".",".","7",".",".",".","."],
>  ["6",".",".","1","9","5",".",".","."],
>  [".","9","8",".",".",".",".","6","."],
>  ["8",".",".",".","6",".",".",".","3"],
>  ["4",".",".","8",".","3",".",".","1"],
>  ["7",".",".",".","2",".",".",".","6"],
>  [".","6",".",".",".",".","2","8","."],
>  [".",".",".","4","1","9",".",".","5"],
>  [".",".",".",".","8",".",".","7","9"]
> ]
> **Output:** false
> **Explanation:** Same as Example 1, except with the **5** in the top left corner being modified to **8**. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

**Note:**

- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.
- The given board contain only digits  `1-9`  and the character  `'.'`.
- The given board size is always  `9x9`.

**Difficulty**:Medium
**Category**:HashTable  

<!-- more -->

------------

# Analyze

------------

# Solution

```cpp
class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    bool used[9] = {false};

    for (int i = 0; i < 9; ++i) {
      fill(used, used + 9, false);
      // 1.Check each row
      for (int m = 0; m < 9; ++m) {
        if (!isUsed(board[i][m], used)) return false;
      }

      fill(used, used + 9, false);
      // 2.Check each column
      for (int n = 0; n < 9; ++n) {
        if (!isUsed(board[n][i], used)) return false;
      }
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        fill(used, used + 9, false);
        // 3.Check 3*3 size
        for (int m = 3 * i; m < 3 * i + 3; ++m) {
          for (int n = 3 * j; n < 3 * j + 3; ++n) {
            if (!isUsed(board[m][n], used)) return false;
          }
        }
      }
    }

    return true;
  }

  bool isUsed(char ch, bool used[9]) {
    if (ch == '.') return true;
    if (used[ch - '1']) return false;
    used[ch - '1'] = true;
    return true;
  }
};
```
