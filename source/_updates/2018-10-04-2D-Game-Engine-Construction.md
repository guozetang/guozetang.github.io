---
title: 2D游戏设计课程学习目录(CU CPSC6160)
date: 2018-10-05 13:04:27
updated: 2018-10-05 13:04:27
categories: Game, 2D, Engine, Construction
tags: Game
---

![](/images/in-post/2018-10-04-2D-Game-Engine-Construction/2018-10-07-20-02-19.png)

2D游戏引擎设计这门课程是我在CU的2018 Fall选修的一门专业核心课程，老师是Clemson CS系比较受欢迎的[Brian Malloy教授](https://people.cs.clemson.edu/~malloy/)。

---

# 课程内容

### Week1

**Aug 28, Tue:**
- Office hour: Wed 10-11:30 AM
- Quiz on Tue or Thu
- Answer Ques about Basics or Classes:
  - ternery operator
  - namespaces
  - if (0)
- Do the Rule of 3

**Aug 30, Thu:**
- refs vs ptrs
- r-value references
- Introduce SDL draw functions
- Review Rule of 3 -- how to reproduce no crash?
- Illustrate the functions that are called: whatcalls
- Trace the Rule of 3 example from cppreference
- Rule of 0
- Introduce vectors:
  - size vs capacity
  - push_back vs emplace_back

### Week2

**Sep 11, Tue:**
- Review the quiz
- Why no vector.push_front() ???
- When to use emplace_back()?
- A temp is always an r-value reference
- review Rule of 3, Rule of 0, Rule of 5

**Sep 13, Thu:**
- Your game: can definitely be a "cover"
  - Keep the scope manageable -- one level, etc.
- Terminology:
  - move assignment vs copy assignment
  - copy constructor vs move constructor
- Questions about move semantics
- ranged for loops: 
  - ints: size vs cap
  - C++ strings
  - why no push_front for vector?
- Drawing a texture: GPU
  - Makefile
- Drawing a Surface: CPU

### Week3

**Oct 4, Thu:**
- Jacob Wood
- IoMod: overload writeText
  - put in Engine::draw, which is const!
  - Engine::update is NOT const!
  - draw and update called every iteration of the event list
- Why Singleton:
  - Gamedata -- yes
  - Clock -- no!
- Clock and fps
- string streams
- Two-way sprites?
- SpriteSheet
- projects from last year
- project #4
- sorting:
  - vectors
  - lists


Oct 2, Tue:
  -- maps
  -- sorting:
    -- vectors
    -- lists
  -- emplace_back: how to use?
  -- Why Singleton:
    -- Gamedata?
    -- Clock?
  -- Two-way sprites?
  -- SpriteSheet
  -- Project #2 -- CANDY

Sep 27, Thu:
  -- Quiz #2

Sep 25, Tue:
  -- Last time: Many spinning stars -- tweak velocity
     using XML velocity as base!
  -- Parallax Scrolling is easy -- it's already in the code
  -- string streams
  -- making a video

Sep 20, Thu:
  -- Sammy's dilemma
  -- Project #2 -- let's look at my solution.
  -- The Meyer's Singleton
  -- Polymorphism: 
    -- see poly example
    -- shapes example
  -- Use g++ not clang++ for effc++ warnings

  -- Project #3 and the tracker framework
    -- default vs delete for constructors/destructors
    -- ranged for vs while
    -- when to use auto
    -- function overload
    -- transparency vs alpha channel
    -- Parallax Scrolling
    -- Getting images vs "rolling your own"
    -- Making videos
    -- why use g++ vs clang++
    -- XML

Sep 18, Tue:
  -- static variables
  -- Design Patterns
  -- The Singleton Design Pattern
  -- Animations with SDL:
    -- cpu clock vs game clock
    -- Why clear the screen
  -- Inheritance:





Sep 4, Tue:
  -- Review what get's called:
    -- why prefer init vs assign
  -- Introduce vectors:
    -- size vs capacity
    -- value semantics
    -- emplace_back
  -- Marcus Painting
  -- Project #2
  -- Quiz #1 review
