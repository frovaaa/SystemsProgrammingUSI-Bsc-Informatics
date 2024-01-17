#include "basic_testing.h"
#include "../rowing.h"

TEST (unknown_boat_similar_name_n) {
    club * c = create_club();
    for (unsigned int j = 0; j < 1000; ++j) {
        const char *bName = (std::string ("boat") + std::to_string(j)).c_str();
        CHECK_CMP(add_boat(c, bName,1),==,1);
    }
    CHECK_CMP(add_boat(c, "boat486",1),==,0);
    destroy_club(c);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
