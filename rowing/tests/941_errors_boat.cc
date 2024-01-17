#include "basic_testing.h"
#include "../rowing.h"

TEST (boat_min_cap) {
    club * c = create_club();
    CHECK_CMP(add_boat(c, "boatName1",1000),==,1);
    CHECK_CMP(add_boat(c, "boatName2",0),==,0);
    destroy_club(c);
    TEST_PASSED;
}
MAIN_TEST_DRIVER();
