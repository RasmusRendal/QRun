#!/usr/bin/env bash
# A shell script that is very specialized to my phone
# But I guess it'll work if you have the same ssh id and userna
set -e
rsync --info=progress2 ../qrun --exclude 'build' phone:/home/mobian/ -r
ssh phone "rm -rf qrun/build && mkdir qrun/build && cd qrun/build && cmake ../ && make"
