#include <sstream>
#include "basic_testing.h"
#include "../rowing.h"

TEST (add_one_person) {
    club * c = create_club();
    CHECK_CMP(add_person (c,"person"),==,1);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_persons_same_name) {
    club * c = create_club();
    CHECK_CMP(add_person (c, "person"),==,1);
    CHECK_CMP(add_person (c, "person"),==,0);
    destroy_club(c);
    TEST_PASSED;
}

TEST (add_persons_same_name_two_clubs) {
    club * c1 = create_club();
    club * c2 = create_club();
    CHECK_CMP(add_person (c1, "person"),==,1);
    CHECK_CMP(add_person (c2, "person"),==,1);
    destroy_club(c1);
    destroy_club(c2);
    TEST_PASSED;
}

TEST (many_persons) {
    club * c = create_club();
    for (unsigned i = 0; i < 1000; ++i) {
	std::ostringstream s;
	s << "person" << i;
	std::string name = s.str();
	CHECK_CMP(add_person (c, name.c_str()),==,1);
    }
    destroy_club(c);
    TEST_PASSED;
}

TEST (many_persons_many_clubs) {
    club * C[1000];
    for (unsigned j = 0; j < 1000; ++j) {
	C[j] = create_club();
	CHECK_CMP(C[j],!=,nullptr);
	for (unsigned i = 0; i < 1000; ++i) {
	    std::ostringstream s;
	    s << "person" << i;
	    std::string name = s.str();
	    CHECK_CMP(add_person (C[j], name.c_str()),==,1);
	}
    }
    for (unsigned j = 0; j < 1000; ++j)
	destroy_club(C[j]);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
