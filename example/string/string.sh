# Author (Created): Roger "Equah" Hürzeler
# Date (Created): 12020.03.12 HE
# License: apache-2.0

SRC_DIR="`dirname $0`/../../src"
LIB_DIR="`dirname $0`/../../lib"
MAIN_DIR="`dirname $0`"


echo "=== INSTALL DEPENDENCIES ==="
git clone "https://github.com/TheEquah/SBSInt-c" $LIB_DIR/SBSInt-c
git clone "https://github.com/TheEquah/SBLInt-c" $LIB_DIR/SBLInt-c

echo "=== COMPILE ==="
gcc \
-I $LIB_DIR/SBSInt-c/src \
-x c $LIB_DIR/SBSInt-c/src/equah/sbsint.c \
-I $LIB_DIR/SBLInt-c/src \
-x c $LIB_DIR/SBLInt-c/src/equah/sblint.c \
-I $SRC_DIR -x c $SRC_DIR/equah/nuntius.c \
-x c $MAIN_DIR/string.c \
-o $MAIN_DIR/string.o

echo "=== EXECUTE ==="
$MAIN_DIR/string.o

echo "=== END ==="
