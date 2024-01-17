#include "basic_testing.h"
#include "../rowing.h"

TEST (excursion_no_assigned_boat) {
    club * c1 = create_club();
    CHECK_CMP(add_person(c1, "person1"),==,1);
    excursion * e = create_excursion(c1);
    CHECK_CMP(add_crew (e, "person1"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
