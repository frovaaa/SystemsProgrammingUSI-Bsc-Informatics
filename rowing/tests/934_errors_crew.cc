#include "basic_testing.h"
#include "../rowing.h"


TEST (max_limit_reached_boat_n_crew_m) {
    club * c1 = create_club();

    CHECK_CMP(add_boat(c1, "boat1", 1000),==,1);
    for (unsigned int j = 0; j < 1001; ++j) {
        const char *pName = (std::string ("person") + std::to_string(j)).c_str();
        CHECK_CMP(add_person(c1, pName ),==,1);
    }
    excursion * e = create_excursion(c1);
    CHECK_CMP(use_boat(e, "boat1"), ==, 1);
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *pName = (std::string ("person") + std::to_string(j)).c_str();
        CHECK_CMP(add_crew (e, pName),==,1);
    }
    CHECK_CMP(add_crew (e, "person1000"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
