#include "basic_testing.h"
#include "../rowing.h"
#include <cstdio>

TEST (club_add_boat_person) {
    club * c = create_club();
    CHECK (c != nullptr);
    CHECK_CMP (add_boat(c,"boat 1", 3),==,1);
    CHECK_CMP (add_person(c,"person 1"),==,1);
    destroy_club(c);
    TEST_PASSED;
}

TEST (query_club_no_excursions) {
    club * c = create_club();
    CHECK(c != nullptr);
    char boat[] = "boat 1";
    char person[] = "person 1";

    CHECK_CMP(add_boat(c, boat, 3),==,1);
    CHECK_CMP(add_person(c, person),==,1);

    CHECK_CMP(get_crew_excursions(c, person),==,0);
    CHECK_CMP(get_crew_kilometers(c, person),==,0);

    CHECK_CMP(boat_available(c, boat),==,1);
    CHECK_CMP(get_boat_excursions(c, boat),==,0);
    CHECK_CMP(get_boat_kilometers(c, boat),==,0);

    destroy_club(c);
    TEST_PASSED;
}

TEST (close_excursion_without_crew) {
    club * c = create_club();
    CHECK(c != nullptr);
    char boat[] = "boat 1";
    CHECK_CMP(add_boat(c, boat, 3),==,1);
    CHECK_CMP(add_person(c, "person 1"),==,1);
    excursion *e = create_excursion(c);
    CHECK_CMP(close_excursion(e, 10),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}


TEST (add_twice_person_in_club) {
    club * c = create_club();
    CHECK(c != nullptr);
    char person[] = "person 1";

    CHECK_CMP(add_person(c, person),==,1);
    CHECK_CMP(add_person(c, person),==,0);

    destroy_club(c);
    TEST_PASSED;
}

TEST (add_not_in_club_to_excursion) {
    club * c = create_club();
    CHECK(c != nullptr);
    char person[] = "person 1";
    CHECK_CMP(add_person(c, person),==,1);
    excursion *e = create_excursion(c);
    CHECK_CMP(add_crew(e, "person 2"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_person_already_in_excursion) {
    club * c = create_club();
    CHECK(c != nullptr);
    char person[] = "person 1";
    CHECK_CMP(add_person(c, person),==,1);
    CHECK_CMP(add_boat(c, "boat 1",1),==,1);
    excursion *e = create_excursion(c);
    CHECK_CMP(use_boat(e,"boat 1"),==,1);
    CHECK_CMP(add_crew(e, person),==,1);

    excursion *e2 = create_excursion(c);
    CHECK_CMP(add_crew(e2, person),==,0);
    cancel_excursion(e2);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_crew_to_excursion_without_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    char person[] = "person 1";
    CHECK_CMP(add_person(c, person),==,1);
    CHECK_CMP(add_boat(c, "boat 1",1),==,1);
    excursion *e = create_excursion(c);
    CHECK_CMP(add_crew(e, person),==,0);

    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_person_twice_to_excursion) {
    club * c = create_club();
    CHECK(c != nullptr);
    char person[] = "person 1";
    CHECK_CMP(add_person(c, person),==,1);
    CHECK_CMP(add_boat(c, "boat 1",10),==,1);
    excursion *e = create_excursion(c);
    CHECK_CMP(use_boat(e,"boat 1"),==,1);
    CHECK_CMP(add_crew(e, person),==,1);
    CHECK_CMP(add_crew(e, person),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_and_cancel_excursion) {
    club *c = create_club();
    CHECK(c != nullptr);
    char boat[] = "boat 1";
    char person[] = "person 1";

    CHECK_CMP(add_boat(c, boat, 3),==,1);
    CHECK_CMP(add_person(c, person),==,1);

    excursion *e = create_excursion(c);

    CHECK(e != nullptr);
    CHECK_CMP(use_boat(e, boat),==,1);
    CHECK_CMP(add_crew(e, person),==,1);

    CHECK_CMP(get_crew_excursions(c, person),==,0);
    CHECK_CMP(get_crew_kilometers(c, person),==,0);
    CHECK_CMP(boat_available(c, boat),==,0);
    CHECK_CMP(get_boat_excursions(c, boat),==,0);
    CHECK_CMP(get_boat_kilometers(c, boat),==,0);

    cancel_excursion(e);

    CHECK_CMP(get_crew_excursions(c, person),==,0);
    CHECK_CMP(get_crew_kilometers(c, person),==,0);
    CHECK_CMP(boat_available(c, boat),==,1);
    CHECK_CMP(get_boat_excursions(c, boat),==,0);
    CHECK_CMP(get_boat_kilometers(c, boat),==,0);
    TEST_PASSED;
}

TEST (add_and_close_excursion) {
    club *c = create_club();
    CHECK(c != nullptr);
    char boat[] = "boat 1";
    char person[] = "person 1";

    CHECK_CMP(add_boat(c, boat, 3),==,1);
    CHECK_CMP(add_person(c, person),==,1);

    excursion *e = create_excursion(c);

    CHECK(e != nullptr);
    CHECK_CMP(use_boat(e, boat),==,1);
    CHECK_CMP(add_crew(e, person),==,1);

    CHECK_CMP(get_crew_excursions(c, person),==,0);
    CHECK_CMP(get_crew_kilometers(c, person),==,0);
    CHECK_CMP(boat_available(c, boat),==,0);
    CHECK_CMP(get_boat_excursions(c, boat),==,0);
    CHECK_CMP(get_boat_kilometers(c, boat),==,0);

    CHECK_CMP(close_excursion(e, 10),==,1);

    CHECK_CMP(get_crew_excursions(c, person),==,1);
    CHECK_CMP(get_crew_kilometers(c, person),==,10);
    CHECK_CMP(boat_available(c, boat),==,1);
    CHECK_CMP(get_boat_excursions(c, boat),==,1);
    CHECK_CMP(get_boat_kilometers(c, boat),==,10);
    TEST_PASSED;
}

TEST (add_and_cancel_full_boat_excursion) {
    club *c = create_club();
    CHECK(c != nullptr);

    excursion *e = create_excursion(c);
    CHECK(e != nullptr);

    char boat[] = "boat 1";
    unsigned int n = 50;
    char people[n][15];
    char not_in_excursion_person[] = "not in excursion";

    CHECK_CMP(add_boat(c, boat, n),==,1);
    CHECK_CMP(use_boat(e, boat),==,1);

    for (unsigned i = 0; i < n; ++i) {
        sprintf(people[i], "person %u", i);
        CHECK_CMP(add_person(c, people[i]),==,1);
        CHECK_CMP(add_crew(e, people[i]),==,1);
    }

    CHECK_CMP(add_person(c, not_in_excursion_person),==,1);
    CHECK_CMP(add_crew(e,not_in_excursion_person),==,0);

    for (unsigned i = 0; i < n; ++i) {
        CHECK_CMP(get_crew_excursions(c, people[i]),==,0);
        CHECK_CMP(get_crew_kilometers(c, people[i]),==,0);
    }

    cancel_excursion(e);

    for (unsigned i = 0; i < n; ++i) {
        CHECK_CMP(get_crew_excursions(c, people[i]),==,0);
        CHECK_CMP(get_crew_kilometers(c, people[i]),==,0);
    }

    CHECK_CMP(boat_available(c, boat),==,1);
    CHECK_CMP(get_boat_excursions(c, boat),==,0);
    CHECK_CMP(get_boat_kilometers(c, boat),==,0);
    TEST_PASSED;
}


TEST (add_and_close_full_boat_excursion) {
    club *c = create_club();
    CHECK(c != nullptr);

    excursion *e = create_excursion(c);
    CHECK(e != nullptr);

    char boat[] = "boat 1";
    unsigned int n = 50;
    char people[n][15];
    char not_in_excursion_person[] = "not in excursion";

    CHECK_CMP(add_boat(c, boat, n),==,1);
    CHECK_CMP(use_boat(e, boat),==,1);

    for (unsigned i = 0; i < n; ++i) {
        sprintf(people[i], "person %u", i);
        CHECK_CMP(add_person(c, people[i]),==,1);
        CHECK_CMP(add_crew(e, people[i]),==,1);
    }

    CHECK_CMP(add_person(c, not_in_excursion_person),==,1);
    CHECK_CMP(add_crew(e,not_in_excursion_person),==,0);

    for (unsigned i = 0; i < n; ++i) {
        CHECK_CMP(get_crew_excursions(c, people[i]),==,0);
        CHECK_CMP(get_crew_kilometers(c, people[i]),==,0);
    }

    close_excursion(e, 10);

    CHECK_CMP(boat_available(c, boat),==,1);
    CHECK_CMP(get_boat_excursions(c, boat),==,1);
    CHECK_CMP(get_boat_kilometers(c, boat),==,10);

    for (unsigned i = 0; i < n; ++i) {
        CHECK_CMP(get_crew_kilometers(c, people[i]),==,10);
        CHECK_CMP(get_crew_excursions(c, people[i]),==,1);
    }
    TEST_PASSED;
}



MAIN_TEST_DRIVER();
