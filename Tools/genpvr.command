#!/bin/bash
 
BASEDIR=$(dirname $0)
cd $BASEDIR
echo
ls
echo $BASEDIR
echo

read -p “輸入總頁數:” pageCount
echo

 rm -f _PVR_Out/*.pvr.ccz
 rm -f _PVR_Out/*.plist

for ((i=0; i<=$pageCount; i++)); do
echo - $i -
if [ -f p$i.png ]; then

  TexturePacker p$i.png p$i\_cn.png p$i\_tw.png p$i\_tw2.png \
      --data _PVR_Out/Page$i.plist \
      --sheet _PVR_Out/Page$i.pvr.ccz \
      --allow-free-size \
      --opt RGBA4444 \
      --enable-rotation \
      --premultiply-alpha \
      --dither-fs-alpha \
      --border-padding 0 \
      --max-width 2048 \
      --max-height 2048 \

else
 echo ====
 echo Error : p$i.png No Find
 echo ====
fi



done