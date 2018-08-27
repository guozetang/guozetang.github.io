#!/bin/bash
#
#===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== 
# Filename:     leetcode_update.sh
# Revision:     1.0
# Author:       Guoze Tang
# Date:         2018-08-30
# Description:      finding quotes how to affect regex evaluation
#===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== 

export PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
clear
CURRENT_DIR=$(pwd)
WORK_DIR=$(dirname $(pwd))
POST_DIR=$WORK_DIR/source/_posts
re_num="~ ^[[:digit:]]+$ ]]"
echo "[INFO]Post dir name: $POST_DIR"


cd $POST_DIR
POSTS=$(ls $POST_DIR | grep .md | grep Leetcode)
for file in $POSTS; do
    if [ -d $file ]; then
        continue
    fi
    
    if [ -f $file ]; then
        # file_name=$(echo $file | sed 's/\.[^.]*$//' | sed)
        # leetcode
        num=$(echo $file | grep -Eo 'Leetcode-[0-9]+' | grep -Eo '[0-9]+')
        linkname=$(echo $file | grep -Eo 'Leetcode-[0-9]+.+[^.md$]')
        name=$(echo $linkname | cut -d'-' -f3-)
        difficulty=$(grep -Eo '**Difficulty.+' $file | cut -d':' -f2-)
        category=$(grep -Eo '**Category.+' $file | cut -d':' -f2-)
        if [ ! $difficulty ]; then
            difficulty="Null"
        fi
        
        if [ ! $category ]; then
            category="Null"
        fi

        if [ $num ] ; then
            echo "| $num | [$name](../$linkname/) | $difficulty | $category"
        fi
    fi
done