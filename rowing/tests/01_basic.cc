#include "basic_testing.h"
#include "../rowing.h"

TEST (club_create_destroy) {
    club * c = create_club();
    CHECK (c != nullptr);
    destroy_club(c);
    TEST_PASSED;
}

TEST (club_create_destroy_two) {
    club * c1 = create_club();
    CHECK (c1 != nullptr);
    club * c2 = create_club();
    CHECK (c2 != nullptr);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (club_create_destroy_1000) {
    club * C[1000];
    for (unsigned int i = 0; i < 1000; ++i) {
	C[i] = create_club();
	CHECK (C[i] != nullptr);
    }
    for (unsigned int i = 0; i < 1000; ++i)
	destroy_club(C[i]);
    TEST_PASSED;
}

TEST (excursion_create_cancel) {
    club * c = create_club();
    excursion * e = create_excursion(c);
    CHECK (e != nullptr);
    cancel_excursion(e);
    destroy_club(c);
    TEST_PASSED;
}

TEST (excursion_create_cancel_two_clubs) {
    club * c1 = create_club();
    CHECK (c1 != nullptr);
    club * c2 = create_club();
    CHECK (c2 != nullptr);
    excursion * e1 = create_excursion(c1);
    CHECK (e1 != nullptr);
    cancel_excursion(e1);
    excursion * e2 = create_excursion(c2);
    CHECK (e2 != nullptr);
    cancel_excursion(e2);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (excursion_create_cancel_1000_1000) {
    club * C[1000];
    excursion * E[1000][1000];
    for (unsigned int i = 0; i < 1000; ++i) {
	C[i] = create_club();
        for (unsigned int j = 0; j < 1000; ++j) {
	    E[i][j] = create_excursion(C[i]);
	    CHECK (E[i][j] != nullptr);
	}
    }
    for (unsigned int i = 0; i < 1000; ++i) {
        for (unsigned int j = 0; j < 1000; ++j)
	    cancel_excursion (E[i][j]);
	destroy_club(C[i]);
    }
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
