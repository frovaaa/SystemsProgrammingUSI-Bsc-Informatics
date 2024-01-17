#include "basic_testing.h"
#include "../rowing.h"


TEST (boat_unavailable) {
    club * c = create_club();
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *bName = (std::string ("boat") + std::to_string(j)).c_str();
        CHECK_CMP(add_boat(c, bName,1),==,1);
    }
    excursion * e = create_excursion(c);
    CHECK_CMP(use_boat(e, "boat1000"), ==, 0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
