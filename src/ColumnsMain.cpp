#include "Columns/ColumnsGameController.h"

int main() {
    ColumnsGameController ColumnsCtrl;
   	All2D_init(640, 480, "WinterColumns by hexerei software creations (c) 2000-2003");

    int retval = All2D_main(ColumnsCtrl);
    return retval;
}

