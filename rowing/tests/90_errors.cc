#include "basic_testing.h"
#include "../rowing.h"

TEST (unknown_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "titanic"),==,0);
    CHECK_CMP(get_boat_excursions (c, "titanic"),==,-1);
    CHECK_CMP(get_boat_kilometers (c, "titanic"),==,-1);
    CHECK_CMP(boat_available (c, "titanic"),==,-1);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}


TEST (boat_with_zero_capacity) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c, "boat", 0),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (two_boat_same_name) {
    club * c = create_club();
    CHECK_CMP(add_boat(c, "abcdefghijklmnopqrstuvwz",1),==,1);
    CHECK_CMP(add_boat(c, "abcdefghijklmnopqrstuvwz",1),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (unknown_boat_similar_name) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c, "abcdefghijklmnopqrstuvwz 1",1),==,1);
    CHECK_CMP(add_boat(c, "abcdefghijklmnopqrstuvwz 3",1),==,1);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "abcdefghijklmnopqrstuvwz 2"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (unknown_boat_same_name_other_club) {
    club * c1 = create_club();
    club * c2 = create_club();
    CHECK(c1 != nullptr);
    CHECK(c2 != nullptr);
    CHECK_CMP(add_boat(c1, "abcdefghijklmnopqrstuvwz 1",1),==,1);
    CHECK_CMP(add_boat(c2, "abcdefghijklmnopqrstuvwz 2",1),==,1);
    excursion * e = create_excursion(c1);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "abcdefghijklmnopqrstuvwz 2"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (unknown_club_member) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c, "titanic",1),==,1);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "titanic"),==,1);
    CHECK_CMP(add_crew(e, "unknown"),==,0);
    CHECK_CMP(get_crew_excursions(c, "unknown"),==,-1);
    CHECK_CMP(get_crew_kilometers(c, "unknown"),==,-1);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (two_club_members_same_name) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_person(c, "abcdefghijklmnopqrstuvwz"),==,1);
    CHECK_CMP(add_person(c, "abcdefghijklmnopqrstuvwz"),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (two_crew_members_same_name) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c, "titanic",1),==,1);
    CHECK_CMP(add_person(c, "person 1"),==,1);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "titanic"),==,1);
    CHECK_CMP(add_crew(e, "person 1"),==,1);
    CHECK_CMP(add_crew(e, "person 1"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (unknown_club_members_similar_name) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_person(c, "abcdefghijklmnopqrstuvwz 1"),==,1);
    CHECK_CMP(add_person(c, "abcdefghijklmnopqrstuvwz 3"),==,1);
    CHECK_CMP(add_boat(c, "boat", 2),==,1);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "boat"),==,1);
    CHECK_CMP(add_crew (e, "abcdefghijklmnopqrstuvwz 2"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (unknown_club_members_same_name_other_club) {
    club * c1 = create_club();
    club * c2 = create_club();
    CHECK(c1 != nullptr);
    CHECK(c2 != nullptr);
    CHECK_CMP(add_boat(c1, "abcdefghijklmnopqrstuvwz 1",1),==,1);
    CHECK_CMP(add_boat(c2, "abcdefghijklmnopqrstuvwz 2",1),==,1);
    CHECK_CMP(add_person(c1, "abcdefghijklmnopqrstuvwz 1"),==,1);
    CHECK_CMP(add_person(c2, "abcdefghijklmnopqrstuvwz 2"),==,1);
    excursion * e = create_excursion(c1);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "abcdefghijklmnopqrstuvwz 1"),==,1);
    CHECK_CMP(use_boat (e, "abcdefghijklmnopqrstuvwz 2"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (close_excursion_without_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    excursion *e  = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(close_excursion(e, 10),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_crew_members_to_excursion_without_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_person(c, "person"),==,1);
    excursion *e  = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(add_crew(e, "person"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (create_excursion_with_boat_of_other_club) {
    club * c1 = create_club();
    club * c2 = create_club();
    CHECK(c1 != nullptr);
    CHECK(c2 != nullptr);
    CHECK_CMP(add_boat(c1, "boat 1",1),==,1);
    CHECK_CMP(add_boat(c2, "boat 2",1),==,1);
    CHECK_CMP(add_person(c1, "abcdefghijklmnopqrstuvwz 1"),==,1);
    CHECK_CMP(add_person(c2, "abcdefghijklmnopqrstuvwz 2"),==,1);
    excursion * e = create_excursion(c1);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "boat 2"),==,0);
    cancel_excursion(e);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (use_boat_for_excursion_that_already_has_a_boat) {
    club * c = create_club();
    CHECK(c != nullptr);
    CHECK_CMP(add_boat(c, "boat 1",1),==,1);
    CHECK_CMP(add_boat(c, "boat 2",1),==,1);
    excursion * e = create_excursion(c);
    CHECK(e != nullptr);
    CHECK_CMP(use_boat (e, "boat 1"),==,1);
    CHECK_CMP(use_boat (e, "boat 2"),==,0);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
