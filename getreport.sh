#!/bin/bash

git --no-pager log --graph --date-order --all --pretty=format: '%h %Cred%d %Cgreen%ad %Cblue%cn %Creset%s' --date=short
echo "Hello"
git status
ls -la
rm *.o
make
