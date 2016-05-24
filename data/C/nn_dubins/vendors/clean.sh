#!/bin/sh

LIBRARY_PREFIX=../lib
INCLUDE_PREFIX=../include

lst="imr-h.lite imr-h.gui opendubins"
for i in $lst
do
   if [ -f $i/clean.sh ]
   then 
      cd $i; ./clean.sh; cd ..
   fi
done



rm -rf $LIBRARY_PREFIX $INCLUDE_PREFIX
