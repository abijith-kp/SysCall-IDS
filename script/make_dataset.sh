#!/bin/bash

function convert() {
    cd $DIR
    touch .tmp.list
    awk '{ IFS = " "; }{ print $1; }' "$@" | uniq > .tmp.list

    while read line
    do
        grep $line "$@" > .tmp.call
        touch $line
        awk '{ IFS = " "; }{ print $2; }' .tmp.call > $line
    done < .tmp.list

    rm .tmp.list .tmp.call
    cd -
}

ROOT=~/abijith/dataset
DIR=

find $ROOT -name "*" -type f > .list

while read line
do
    DIR="$line.dir"
    mkdir $DIR
    convert $line
done < .list
