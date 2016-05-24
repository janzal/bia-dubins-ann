#!/bin/sh

INCLUDE_PREFIX=../include
LIBRARY_PREFIX=../lib

OPENDUBINS_INCLUDE=opendubins/include
OPENDUBINS_LIB=opendubins/lib

lst="imr-h.lite imr-h.gui opendubins"
for i in $lst
do
   cd $i; ./install.sh; cd -
done

if [ -d $OPENDUBINS_INCLUDE ]
then
   mv $OPENDUBINS_INCLUDE/* $INCLUDE_PREFIX
   rm -rf $OPENDUBINS_INCLUDE
fi

if [ -d $OPENDUBINS_LIB ]
then
   mv $OPENDUBINS_LIB/* $LIBRARY_PREFIX
   rm -rf $OPENDUBINS_LIB
fi
