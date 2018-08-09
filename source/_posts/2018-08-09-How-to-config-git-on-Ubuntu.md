---
title: How to config git on Ubuntu
date: 2018-08-09 13:42:10
categories: Git Linux
tags: Linux
---
## Git command

### Branch operation
1. Background: We often want the copy the `master` branch(or other branch) to develop a new function. 

```bash
$git checkout master  //Change to the master branch or which branch you want to copy
$git pull                   //从远端拉取最新版本
$git checkout -b NewBranch  //Switched to a new branch 'NewBranch'
$git push origin NewBranch  //新建分支NewBranch到远端
```

## Issues
### git pull error

```sh
$git pull

There is no tracking information for the current branch.
Please specify which branch you want to merge with.
See git-pull(1) for details.

git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

git branch --set-upstream-to=origin/<branch> NewBranch
```

**solution**
`$git branch --set-upstream-to=origin/NewBranch`
`$git pull`
`$git push origin test:test`


## Git configure on Ubuntu
### Add git branch name if its present
Open `~/.bashrc` file, add the code followed this paragraph after the default prompt definition and  `unset color_prompt force_color_prompt`. You also can replace the the default prompt definition with the snippet or leave your  `~/.bashrc`  as it is and comment the default prompt definition along with  `unset color_prompt force_color_prompt`.

```bash
# Add git branch if its present to PS1

parse_git_branch() {
 git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}
if [ "$color_prompt" = yes ]; then
 PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '
else
 PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w$(parse_git_branch)\$ '
fi
```

replace

```bash
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
```

Which ends with:

```bash
unset color_prompt force_color_prompt
```