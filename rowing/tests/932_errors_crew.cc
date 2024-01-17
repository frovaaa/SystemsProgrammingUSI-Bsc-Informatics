#include "basic_testing.h"
#include "../rowing.h"


TEST (max_limit_reached_boat) {
    club * c1 = create_club();
    CHECK_CMP(add_boat(c1, "boat1", 1),==,1);
    CHECK_CMP(add_person(c1, "person1"),==,1);
    CHECK_CMP(add_person(c1, "person2"),==,1);
    excursion * e = create_excursion(c1);
    CHECK_CMP(use_boat(e, "boat1"), ==, 1);
    CHECK_CMP(add_crew (e, "person1"),==,1);
    CHECK_CMP(add_crew (e, "person2"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
