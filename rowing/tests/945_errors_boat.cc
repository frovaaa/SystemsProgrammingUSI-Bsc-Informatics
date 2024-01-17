#include "basic_testing.h"
#include "../rowing.h"

TEST (boat_in_use) {
    club * c = create_club();
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *bName = (std::string ("boat") + std::to_string(j)).c_str();
        CHECK_CMP(add_boat(c, bName,1),==,1);
    }
    excursion * e1 = create_excursion(c);
    for (unsigned int j = 0; j < 1; ++j) {
        const char *bName = (std::string ("boat") + std::to_string(j)).c_str();
        CHECK_CMP(use_boat(e1, bName), ==, 1);
    }
    excursion * e2 = create_excursion(c);
    CHECK_CMP(use_boat(e2, "boat0"), ==, 0);
    cancel_excursion(e1);
    cancel_excursion(e2);
    destroy_club(c);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
