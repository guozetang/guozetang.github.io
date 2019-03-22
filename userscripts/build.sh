#!/bin/bash
#-------------User Config-------

GITHUB_EMAIL=269831714@qq.com
GITHUB_USER=guozet
GITHUB_REPO=guozet/guozet.github.io.git

CV_LINK=https://github.com/guozetang/Resume/raw/master/_build/resume.pdf
RESUME_LINK=https://github.com/guozetang/Resume/raw/master/_build/resume.pdf
LEETCODE_LINK=https://github.com/guozetang/leetcode.git

################################
WORK_DIR=$(pwd)

leetcode_generate() {
  # mv ./source/_updates/* ./source/_posts/
  # mv ./source/leetcode/* ./source/_posts/
  chmod +x ./userscripts/leetcode.sh
  ./userscripts/leetcode.sh
}

hexo_set() {
  hexo generate
  cd ./public
  mv ./index.html ./post/
  cp ./about/index.html .
}

get_cv(){
  wget -O ./about/cv.pdf $CV_LINK
  wget -O ./about/resume.pdf $RESUME_LINK
}

get_leetcode_questions(){
  git clone $LEETCODE_LINK
  mv ./leetcode/leetcode ./source/
}

setup_git() {
  git init
  git config --global push.default matching
  git config --global user.email "$GITHUB_EMAIL"
  git config --global user.name "$GITHUB_USER"
}

git_push() {
  git add --all .
  git commit -m "Travis CI Auto Builder"
  git push --quiet --force https://${REPO_TAKEN}@github.com/$GITHUB_REPO master > /dev/null 2>&1
}


# get_leetcode_questions
# leetcode_generate
hexo_set
get_cv
setup_git
git_push
