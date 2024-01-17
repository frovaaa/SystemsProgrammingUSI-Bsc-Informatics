#include "basic_testing.h"
#include "../rowing.h"


TEST (unknown_boat_same_name_other_club_n) {
    club * c1 = create_club();
    club * c2 = create_club();
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *bName = (std::string ("boat") + std::to_string(j)).c_str();
        CHECK_CMP(add_boat(c1, bName,1),==,1);
    }
    CHECK_CMP(add_boat(c2, "boat5000",1),==,1);
    excursion * e = create_excursion(c1);
    CHECK_CMP(use_boat (e, "boat5000"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
