#include "basic_testing.h"
#include "../rowing.h"
#include <cstdio>

TEST(create_two_boats) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c,"boat 1", 3),==,1);
    CHECK_CMP(add_boat(c,"boat 2", 3),==,1);
    CHECK_CMP(add_boat(c,"boat 1", 3),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST(close_excursion_without_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    excursion *e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(close_excursion(e, 10),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST(use_one_boat_in_excursion) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c,"boat 1", 3),==,1);
    CHECK_CMP(add_boat(c,"boat 2", 3),==,1);

    excursion *e1 = create_excursion(c);
    CHECK(e1 != nullptr);

    excursion *e2 = create_excursion(c);
    CHECK(e2 != nullptr);

    CHECK_CMP(use_boat(e1, "not existing boat"),==,0);
    CHECK_CMP(use_boat(e1, "boat 1"),==,1);
    CHECK_CMP(use_boat(e1, "boat 1"),==,0);
    CHECK_CMP(use_boat(e1, "boat 2"),==,0);
    CHECK_CMP(use_boat(e2, "boat 1"),==,0);

    cancel_excursion(e1);
    CHECK_CMP(boat_available(c, "boat 1"),==,1);
    CHECK_CMP(use_boat(e1, "boat 2"),==,0);
    CHECK_CMP(use_boat(e2, "boat 2"),==,1);
    cancel_excursion(e2);
    destroy_club(c);
    TEST_PASSED;
}

TEST(excursion_having_a_boat_already) {
    club * c = create_club();
    CHECK(c != nullptr);

    CHECK_CMP(add_boat(c,"boat 1", 2),==,1);

    excursion *e = create_excursion(c);
    CHECK(e != nullptr);

    CHECK_CMP(use_boat(e, "boat 1"),==,1);
    CHECK_CMP(add_boat(c,"boat 2", 2),==,1);
    CHECK_CMP(use_boat(e, "boat 2"),==,0);

    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST(excursion_with_boat_in_another_excursion) {
    club * c = create_club();
    CHECK(c != nullptr);

    CHECK_CMP(add_boat(c,"boat 1", 2),==,1);
    CHECK_CMP(add_boat(c,"boat 2", 2),==,1);

    excursion *e1 = create_excursion(c);
    CHECK(e1 != nullptr);


    excursion *e2 = create_excursion(c);
    CHECK(e2 != nullptr);


    CHECK_CMP(use_boat(e1, "boat 1"),==,1);
    CHECK_CMP(use_boat(e2, "boat 1"),==,0);

    CHECK_CMP(use_boat(e2, "boat 2"),==,1);

    cancel_excursion(e1);
    cancel_excursion(e2);
    destroy_club(c);
    TEST_PASSED;
}

TEST(excursion_with_non_existent_boat) {
    club * c = create_club();
    CHECK(c != nullptr);

    CHECK_CMP(add_boat(c,"boat 1", 2),==,1);

    excursion *e = create_excursion(c);
    CHECK(e != nullptr);

    CHECK_CMP(use_boat(e, "not a boat"),==,0);
    CHECK_CMP(use_boat(e, "boat 1"),==,1);

    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST(boat_with_multiple_excursions) {
    club * c = create_club();
    CHECK(c != nullptr);
    unsigned int n = 3;
    CHECK_CMP(add_boat(c,"boat 1", n),==,1);
    char people[n][15] = {
        "person 1",
        "person 2",
        "person 3",
    };

    for (unsigned int i = 0; i < n; ++i)
        CHECK_CMP(add_person(c, people[i]),==,1);

    for (unsigned int i = 1; i <= 10; ++i) {
        excursion *e = create_excursion(c);
        CHECK(e != nullptr);

        CHECK_CMP(use_boat(e, "boat 1"),==,1);

        for (unsigned int j = 0; j < n; ++j)
            CHECK_CMP(add_crew(e, people[j]),==,1);

        close_excursion(e, 10);

        for (unsigned int j = 0; j < n; ++j) {
            CHECK_CMP(get_crew_excursions(c, people[j]),==,i);
            CHECK_CMP(get_crew_kilometers(c, people[j]),==,10*i);
        }

        CHECK_CMP(get_boat_excursions(c, "boat 1"),==,i);
        CHECK_CMP(boat_available(c, "boat 1"),==,1);
        CHECK_CMP(get_boat_kilometers(c, "boat 1"),==,10*i);

    }

    destroy_club(c);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
