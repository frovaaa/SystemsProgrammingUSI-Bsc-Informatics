#include "basic_testing.h"
#include "../rowing.h"
#include <cstdio>


TEST (create_c1_c2) {
    club *c1 = create_club();
    CHECK(c1 != nullptr);
    club *c2 = create_club();
    CHECK(c2 != nullptr);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (create_c1_c2_many) {
    club *c1 = create_club();
    CHECK(c1 != nullptr);
    club *c2 = create_club();
    CHECK(c2 != nullptr);

    for (unsigned int i = 1; i <= 1000; ++i) {
        char person[20], boat[20];

        sprintf(person, "person %u", i);
        sprintf(boat, "boat %u", i);

        CHECK_CMP(add_boat(c1, boat, i),==,1);
        CHECK_CMP(add_boat(c2, boat, i),==,1);

        CHECK_CMP(add_person(c1, person),==,1);
        CHECK_CMP(add_person(c2, person),==,1);
    }

    for (unsigned int i = 1; i <= 1000; ++i) {
        char boat[20];
        excursion * e1 = create_excursion(c1);
        excursion * e2 = create_excursion(c2);
        CHECK(e1 != nullptr);
        CHECK(e2 != nullptr);

        sprintf(boat, "boat %u", i);

        CHECK_CMP(use_boat(e1, boat),==,1);
        CHECK_CMP(use_boat(e2, boat),==,1);

        for (unsigned int j = 1; j <= i; ++j) {
            char person[20];
            sprintf(person, "person %u", j);

            CHECK_CMP(add_crew(e1, person),==,1);
            CHECK_CMP(add_crew(e2, person),==,1);
        }

        CHECK_CMP(close_excursion(e1, 10),==,1);
        CHECK_CMP(close_excursion(e2, 10),==,1);
    }

    for (unsigned int i = 1; i <= 1000; ++i) {
        char person[20], boat[20];

        sprintf(person, "person %u", i);
        sprintf(boat, "boat %u", i);

        CHECK_CMP(boat_available(c1, boat),==,1);
        CHECK_CMP(boat_available(c2, boat),==,1);

        CHECK_CMP(get_boat_excursions(c1, boat),==,1);
        CHECK_CMP(get_boat_excursions(c2, boat),==,1);

        CHECK_CMP(get_boat_kilometers(c1, boat),==,10);
        CHECK_CMP(get_boat_kilometers(c2, boat),==,10);

        CHECK_CMP(get_crew_excursions(c1, person),==,1001-i);
        CHECK_CMP(get_crew_excursions(c2, person),==,1001-i);

        CHECK_CMP(get_crew_kilometers(c1, person),==,(1001-i)*10);
        CHECK_CMP(get_crew_kilometers(c2, person),==,(1001-i)*10);
    }

    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
