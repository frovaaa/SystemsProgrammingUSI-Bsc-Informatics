#include "basic_testing.h"
#include "../rowing.h"

TEST (two_person_same_name) {
    club * c = create_club();
    CHECK_CMP(add_person(c, "person1"),==,1);
    CHECK_CMP(add_person(c, "person1"),==,0);
    destroy_club(c);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();