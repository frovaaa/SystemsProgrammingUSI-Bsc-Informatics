#include "basic_testing.h"
#include "../rowing.h"

TEST (n_persons_one_repeat) {
    club * c = create_club();
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *pName = (std::string ("person") + std::to_string(j)).c_str();
        CHECK_CMP(add_person(c, pName ),==,1);
    }
    CHECK_CMP(add_person(c, "person405"),==,0);
    destroy_club(c);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();