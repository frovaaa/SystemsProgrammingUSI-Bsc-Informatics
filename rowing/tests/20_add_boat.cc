#include <sstream>
#include "basic_testing.h"
#include "../rowing.h"

TEST (add_one_boat) {
    club * c = create_club();
    CHECK_CMP(add_boat (c,"boat1",4),==,1);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_boat_zero_crew) {
    club * c = create_club();
    CHECK_CMP(add_boat (c,"boat1",0),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_boats_same_name) {
    club * c = create_club();
    CHECK_CMP(add_boat (c,"boat1",1),==,1);
    CHECK_CMP(add_boat (c,"boat1",1),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_boats_same_name_two_clubs) {
    club * c1 = create_club();
    club * c2 = create_club();
    CHECK_CMP(add_boat (c1,"boat1",1),==,1);
    CHECK_CMP(add_boat (c2,"boat1",1),==,1);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (many_boats) {
    club * c = create_club();
    for (unsigned i = 0; i < 1000; ++i) {
	std::ostringstream s;
	s << "boat" << i;
	std::string name = s.str();
	CHECK_CMP(add_boat (c, name.c_str(), 1),==,1);
    }
    destroy_club(c);
    TEST_PASSED;
}

TEST (many_boats_many_clubs) {
    club * C[1000];
    for (unsigned j = 0; j < 1000; ++j) {
	C[j] = create_club();
	CHECK_CMP(C[j],!=,nullptr);
	for (unsigned i = 0; i < 1000; ++i) {
	    std::ostringstream s;
	    s << "boat" << i;
	    std::string name = s.str();
	    CHECK_CMP(add_boat (C[j], name.c_str(), 1),==,1);
	}
    }
    for (unsigned j = 0; j < 1000; ++j)
	destroy_club(C[j]);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
