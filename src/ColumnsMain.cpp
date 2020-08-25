
#include "Columns/ColumnsGameController.h"

int main() {
    ColumnsGameController ColumnsCtrl;
    Image icon;
    icon.loadImage("data/icon.png");
   	All2D_init(640, 480, "WinterColumns by hexerei software creations (c) 2000-2003",&icon);

    int retval = All2D_main(ColumnsCtrl);
    return retval;
}
