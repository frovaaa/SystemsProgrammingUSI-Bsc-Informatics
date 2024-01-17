#include "basic_testing.h"
#include "../rowing.h"

TEST (person__already_assigned_n) {
    club * c1 = create_club();
    CHECK_CMP(add_boat(c1, "boat1", 1001),==,1);
    for (unsigned int j = 0; j < 1001; ++j) {
        const char *pName = (std::string ("person") + std::to_string(j)).c_str();
        CHECK_CMP(add_person(c1, pName ),==,1);
    }
    excursion * e1 = create_excursion(c1);
    excursion * e2 = create_excursion(c1);
    CHECK_CMP(use_boat(e1, "boat1"), ==, 1);
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *pName = (std::string ("person") + std::to_string(j)).c_str();
        CHECK_CMP(add_crew (e1, pName),==,1);
    }
    CHECK_CMP(add_crew (e2, "person999"),==,0);
    cancel_excursion(e1);
    cancel_excursion(e2);
    destroy_club(c1);
    TEST_PASSED;
}
MAIN_TEST_DRIVER();
