TARGEDIR="/home/usr/src"
SRCIMG="u-boot.img MLO"

make distclean

make am335x_evm_nor_config

make CROSS_COMPILE=arm-linux-

echo "Info: COPY $SRCIMG -> $TARGEDIR"
cp -rf $SRCIMG $TARGEDIR

make distclean

SRCIMG="u-boot.bin"
DESTIMG="u-boot-nor.img"
make am335x_evm_norboot_config

make CROSS_COMPILE=arm-linux-

echo "Info: COPY $SRCIMG -> $TARGEDIR/$DESTIMG"
cp -rf $SRCIMG $TARGEDIR/$DESTIMG

