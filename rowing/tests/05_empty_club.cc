#include "basic_testing.h"
#include "../rowing.h"

TEST (no_boats_queries) {
    club * c = create_club();
    CHECK_CMP(boat_available(c,""),==,-1);
    CHECK_CMP(get_boat_excursions(c,""),==,-1);
    CHECK_CMP(get_boat_kilometers(c,""),==,-1);
    destroy_club(c);
    TEST_PASSED;
}

TEST (no_persons_queries) {
    club * c = create_club();
    CHECK_CMP(get_crew_excursions(c,""),==,-1);
    CHECK_CMP(get_crew_kilometers(c,""),==,-1);
    destroy_club(c);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
