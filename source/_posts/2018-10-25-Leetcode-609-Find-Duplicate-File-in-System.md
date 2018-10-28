---
title: Leetcode 609. Find Duplicate File in System
date: 2018-10-25 22:09:31
updated: 2018-10-25 22:09:31
categories: Leetcode
tags: Leetcode
notshow: true
top:
---

# Question

Given a list of directory info including directory path, and all the files with contents in this directory, you need to find out all the groups of duplicate files in the file system in terms of their paths.

A group of duplicate files consists of at least  **two**  files that have exactly the same content.

A single directory info string in the  **input**  list has the following format:

`"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"`  

It means there are  **n**  files (`f1.txt`,  `f2.txt`  ...  `fn.txt`  with content  `f1_content`,  `f2_content`  ...  `fn_content`, respectively) in directory  `root/d1/d2/.../dm`. Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.

The  **output**  is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:

`"directory_path/file_name.txt"`

**Example 1:**  

> **Input:**
> ["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
> **Output:**  
> [ ["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"] ]

<!-- more -->

**Note:**  

1. No order is required for the final output.
2. You may assume the directory name, file name and file content only has letters and digits, and the length of file content is in the range of [1,50].
3. The number of files given is in the range of [1,20000].
4. You may assume no files or directories share the same name in the same directory.
5. You may assume each given directory info represents a unique directory. Directory path and file info are separated by a single blank space.

**Follow-up beyond contest:**

1. Imagine you are given a real file system, how will you search files? DFS or BFS?
2. If the file content is very large (GB level), how will you modify your solution?
3. If you can only read the file by 1kb each time, how will you modify your solution?
4. What is the time complexity of your modified solution? What is the most time-consuming part and memory consuming part of it? How to optimize?
5. How to make sure the duplicated files you find are not false positive?

--------------

# Solution

## Solution 1

```cpp
class Solution {
 public:
  vector<vector<string>> findDuplicate(vector<string>& paths) {
    vector<vector<string>> res;
    unordered_set<std::string> contents;
    std::multimap<string, string> mymm;
    int cnt = 0;
    for (string s : paths) {
      string dir_path, content;
      std::size_t file_begin = s.find_first_of(" ");
      if (file_begin != std::string::npos) dir_path = s.substr(0, file_begin);

      bool final_file = false;
      std::size_t file_end = s.find_first_of(" ", file_begin + 1);
      if (file_end == std::string::npos) {
        final_file = true;
        file_end = s.size();
      }

      while (file_end != std::string::npos) {
        string path, file;
        file = s.substr(file_begin + 1, file_end - file_begin - 1);

        std::size_t content_begin = file.find_first_of("(");
        std::size_t content_end = file.find_first_of(")", content_begin + 1);
        path = dir_path + "/" + file.substr(0, content_begin);
        content =
            file.substr(content_begin + 1, content_end - content_begin - 1);
        file_begin = file_end;
        file_end = s.find_first_of(" ", file_begin + 1);
        if (final_file == false && file_end == std::string::npos) {
          final_file = true;
          file_end = s.size();
        }
        contents.emplace(content);
        mymm.insert(std::make_pair(content, path));
      }
    }

    for (const std::string& x : contents) {
      int dup_nums = mymm.count(x);
      if (dup_nums > 1) {
        vector<string> dupfiles;
        dupfiles.reserve(dup_nums);
        for (auto it = mymm.equal_range(x).first;
             it != mymm.equal_range(x).second; ++it) {
          dupfiles.emplace_back((*it).second);
        }
        res.emplace_back(dupfiles);
      }
    }
    return res;
  }
};
```

## Solution 2

```cpp
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
      vector<vector<string>> res;
      unordered_set<std::string> contents;
      std::multimap<string,string> mymm;
      int cnt = 0;
      for(string s : paths) {
        string dir_path, content, file;
        istringstream stream(s);
        stream >> dir_path;
        while(stream >> file){
          string path;
          std::size_t content_begin = file.find_first_of("(");
          std::size_t content_end = file.find_first_of(")", content_begin+1);
          path = dir_path +"/"+ file.substr(0, content_begin);
          content = file.substr(content_begin+1, content_end-content_begin-1);
          contents.emplace(content);
          mymm.insert(std::make_pair(content, path));
        }

      for (const std::string& x: contents) {
        int dup_nums = mymm.count(x);
        if( dup_nums > 1){
          vector<string> dupfiles;
          dupfiles.reserve(dup_nums);
          for (auto it=mymm.equal_range(x).first; it!=mymm.equal_range(x).second; ++it) {
            dupfiles.emplace_back((*it).second);
          }
          res.emplace_back(dupfiles);
        }
      }
      return res;
    }
};
```

## Solution 3

Copy from [Find Duplicate File in System 在系统中寻找重复文件](http://www.cnblogs.com/grandyang/p/7007974.html)

```cpp
class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> m;
        for (string path : paths) {
            istringstream is(path);
            string pre = "", t = "";
            is >> pre;
            while (is >> t) {
                int idx = t.find_last_of('(');
                string dir = pre + "/" + t.substr(0, idx);
                string content = t.substr(idx + 1, t.size() - idx - 2);
                m[content].push_back(dir);
            }
        }
        for (auto a : m) {
            if (a.second.size() > 1)res.push_back(a.second);
        }
        return res;
    }
};
```