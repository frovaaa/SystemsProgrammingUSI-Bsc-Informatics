/* Basic Testing is a simple and very basic testing framework.
 *
 * Copyright (C) 2018-2020  Antonio Carzaniga
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BASIC_TESTING_H_INCLUDED
#define BASIC_TESTING_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
#include <iostream>
#endif

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#ifdef __has_include
#if __has_include(<sys/resource.h>)
#include <sys/resource.h>
#define WITH_RUSAGE 1
#endif
#endif

#ifdef __has_include
#if __has_include(<valgrind.h>)
#include <valgrind.h>
#elif __has_include(<valgrind/valgrind.h>)
#include <valgrind/valgrind.h>
#else
#define RUNNING_ON_VALGRIND 0
#endif
#else
#define RUNNING_ON_VALGRIND 0
#endif

/* SUCCESS/FAILURE macros
 */
#define BT_FAILURE 0
#define BT_SUCCESS 1

#define TEST_FAILED do {			\
	if (bt_fork_tests)			\
	    return BT_FAILURE;		\
	else					\
	    abort();				\
    } while(0)

#define TEST_PASSED do { return (BT_SUCCESS); } while(0)

#ifdef __cplusplus
#define BT_POSSIBLY_UNUSED [[maybe_unused]]
#elif defined(__GNUC__) || defined(__clang__)
#define BT_POSSIBLY_UNUSED __attribute__((unused))
#endif
#ifndef BT_POSSIBLY_UNUSED
#define BT_POSSIBLY_UNUSED
#endif

/* Assertion checks
 */

/* Check for generic Boolean expressions
 */
#define CHECK(expr) do {					\
	if (!(expr)) {						\
	    printf("\n%s:%d: Assertion '"#expr"' failed\n",	\
		   __FILE__, __LINE__);				\
	    TEST_FAILED;					\
	}							\
    } while (0)

/* Check for comparison between two C strings based on binary
 * relations/operators (==, >=, <=, !=).
 */
#define CHECK_STRING_CMP(X,OP,Y) do {					\
	const char * x_ = (X);						\
	const char * y_ = (Y);						\
	if (!(strcmp(x_, y_) OP 0)) {					\
	    const char * X_str = #X;					\
	    const char * Y_str = #Y;					\
	    printf("\n%s:%d: Assertion '%s "#OP" %s' failed: %s == %s, %s == %s\n", \
		   __FILE__, __LINE__, X_str, Y_str, X_str, x_, Y_str, y_); \
	    TEST_FAILED;						\
	}								\
    } while (0)

/* Checks for comparisons based on binary relations/operators (==, >=,
 * <=, !=).  We can do this easily with a single generic check in C++.
 * In C we must have specific checks for specific types.
 */
#ifdef __cplusplus

#define CHECK_CMP(X,OP,Y) do {						\
	auto x_ = (X);							\
	decltype (x_) y_ = (Y);						\
	if (!(x_ OP y_)) {						\
	    std::cout << std::endl <<__FILE__ << ":" << __LINE__	\
		      << ": Assertion '"#X" "#OP" "#Y"' failed: "	\
		#X" == " << x_ << ", "#Y" == " << y_ << std::endl;	\
	    TEST_FAILED;						\
	}								\
    } while (0)

#define CHECK_UINT_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

#define CHECK_INT_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

#define CHECK_DOUBLE_CMP(X,OP,Y) CHECK_CMP(X,OP,Y)

#else

#define CHECK_INT_CMP(X,OP,Y) do {					\
	intmax_t x_ = (X);						\
	intmax_t y_ = (Y);						\
	if (!(x_ OP y_)) {						\
	    const char * X_str = #X;					\
	    const char * Y_str = #Y;					\
	    printf("\n%s:%d: Assertion '%s "#OP" %s' failed: %s == %jd, %s == %jd\n", \
		   __FILE__, __LINE__, X_str, Y_str, X_str, x_, Y_str, y_); \
	    TEST_FAILED;						\
	}								\
    } while (0)

#define CHECK_UINT_CMP(X,OP,Y) do {					\
	uintmax_t x_ = (X);						\
	uintmax_t y_ = (Y);						\
	if (!(x_ OP y_)) {						\
	    const char * X_str = #X;					\
	    const char * Y_str = #Y;					\
	    printf("\n%s:%d: Assertion '%s "#OP" %s' failed: %s == %ju, %s == %ju\n", \
		   __FILE__, __LINE__, X_str, Y_str, X_str, x_, Y_str, y_); \
	    TEST_FAILED;						\
	}								\
    } while (0)

#define CHECK_DOUBLE_CMP(X,OP,Y) do {					\
	double x_ = (X);						\
	double y_ = (Y);						\
	if (!(x_ OP y_)) {						\
	    const char * X_str = #X;					\
	    const char * Y_str = #Y;					\
	    printf("\n%s:%d: Assertion '%s "#OP" %s' failed: %s == %lf, %s == %lf\n", \
		   __FILE__, __LINE__, X_str, Y_str, X_str, x_, Y_str, y_); \
	    TEST_FAILED;						\
	}								\
    } while (0)

#endif	/* C++/C */

BT_POSSIBLY_UNUSED
static int bt_fork_tests = 1;

BT_POSSIBLY_UNUSED
static unsigned int bt_timeout = 3; /* three seconds */

BT_POSSIBLY_UNUSED
static int bt_verbose = 1;

struct bt_test_descriptor {
    const char * name;
    int (*test_function)();
    const char * file;
    int line;
    struct bt_test_descriptor * next;
};

static struct bt_test_descriptor * bt_main_test_suite = 0;
static struct bt_test_descriptor ** bt_last_test_p = &bt_main_test_suite;

BT_POSSIBLY_UNUSED
static int bt_add_test(struct bt_test_descriptor * t) {
    t->next = 0;
    *bt_last_test_p = t;
    bt_last_test_p = &(t->next);
    return 1;
}

#ifdef __cplusplus
#define TEST(test_name)							\
BT_POSSIBLY_UNUSED static int test_name ## _fn ();					\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _fn, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static const int test_name ## _init = bt_add_test(test_name);	\
BT_POSSIBLY_UNUSED static int test_name ## _fn ()
#else
#define  TEST(test_name)						\
BT_POSSIBLY_UNUSED static int test_name ## _fn ();					\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor test_name ## _descr		\
    = { # test_name, test_name ## _fn, __FILE__, __LINE__, 0};		\
BT_POSSIBLY_UNUSED static struct bt_test_descriptor * test_name = & test_name ## _descr; \
BT_POSSIBLY_UNUSED static int test_name ## _fn ()
#endif

BT_POSSIBLY_UNUSED static unsigned int bt_fail_count = 0;
BT_POSSIBLY_UNUSED static unsigned int bt_pass_count = 0;

BT_POSSIBLY_UNUSED
static int bt_run_test(const struct bt_test_descriptor * t) {
    if (RUNNING_ON_VALGRIND || !bt_fork_tests)
	return t->test_function();
    pid_t pid;
    /* Make sure the child starts with empty I/O buffers. */
    fflush(stdout);
    fflush(stderr);
#ifdef WITH_RUSAGE
    struct rusage usage_before;
    struct rusage usage_after;
    getrusage(RUSAGE_CHILDREN, &usage_before);
#endif
    pid = fork();

    if (pid == (pid_t)-1) {
	printf("Cannot fork test %s. %s [%d]\n", t->name, strerror(errno), errno);
	return BT_FAILURE;
    } else if (pid == 0) {
	/* Child: Do the test. */
	if (bt_timeout > 0)
	    alarm(bt_timeout);
	exit(t->test_function());
    } else {
	/* Parent: Wait until child terminates and analyze its exit code. */
	int exit_code;
	waitpid(pid, &exit_code, 0);
#ifdef WITH_RUSAGE
	getrusage(RUSAGE_CHILDREN, &usage_after);
#endif
	if (WIFEXITED(exit_code)) {
	    switch (WEXITSTATUS(exit_code)) {
	    case BT_SUCCESS: return BT_SUCCESS;
	    case BT_FAILURE: break;
	    default:  printf("Unexpected exit code [%d]", WEXITSTATUS(exit_code));
	    }
	} else if (WIFSIGNALED(exit_code)) {
	    const char* signame;
	    int sig = WTERMSIG(exit_code);
	    switch (sig) {
	    case SIGINT:  signame = "SIGINT"; break;
	    case SIGHUP:  signame = "SIGHUP"; break;
	    case SIGQUIT: signame = "SIGQUIT"; break;
	    case SIGABRT: signame = "SIGABRT"; break;
	    case SIGKILL: signame = "SIGKILL"; break;
	    case SIGSEGV: signame = "SIGSEGV"; break;
	    case SIGILL:  signame = "SIGILL"; break;
	    case SIGTERM: signame = "SIGTERM"; break;
	    case SIGALRM:
#ifdef WITH_RUSAGE
		if (usage_after.ru_utime.tv_sec - usage_before.ru_utime.tv_sec >= bt_timeout - 1)
		    signame = "SIGALARM (timeout), infinite loop?";
		else
		    signame = "SIGALARM (timeout), stuck on input?";
#else
		signame = "SIGALARM (timeout)";
#endif
		break;
	    default: signame = 0;
	    }
	    if (bt_verbose) {
		if (signame)
		    printf("interrupted by %s\n", signame);
		else
		    printf("interrupted by signal %d\n", sig);
	    }
	} else {
	    if (bt_verbose)
		printf("Test ended in an unexpected way [%d]\n", exit_code);
	}
	return BT_FAILURE;
    }
}

BT_POSSIBLY_UNUSED
static void bt_run_and_record_test(const struct bt_test_descriptor * t) {
    if (bt_verbose)
	printf("test %-40s  ", t->name);
    switch (bt_run_test(t)) {
    case BT_FAILURE:
	bt_fail_count += 1;
	if (bt_verbose)
	    printf("test %-40s  FAIL\n", t->name);
	break;
    case BT_SUCCESS:
	bt_pass_count += 1;
	if (bt_verbose)
	    printf("PASS\n");
	break;
    }
}

#define RUN_TEST(name) do { bt_run_and_record_test(name); } while (0);

#define RUN_TESTS(...) do {						\
	struct bt_test_descriptor * T_[] = { __VA_ARGS__, 0 };		\
	for (struct bt_test_descriptor ** ti = T_; *ti != 0; ++ti) {	\
	    bt_run_and_record_test(*ti);				\
	}								\
    } while (0)

#define PRINT_TEST_RESULTS						\
    do {								\
	if (bt_verbose)							\
	    printf("Summary: %u/%u test passed\n",			\
		   bt_pass_count, bt_pass_count + bt_fail_count);	\
    } while (0)

#define ALL_TESTS_PASSED (bt_fail_count == 0)

#define EXIT_ALL_TESTS_PASSED ((bt_fail_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE)

BT_POSSIBLY_UNUSED
const char * bt_test_usage
  = "usage: %s [-d] [-v] [-n] [-t <seconds>]  [-- <test_name> ...]\n"
    "\t-d            :: run tests in debug mode (no fork, no timeout)\n"
    "\t-q            :: quiet: minimal output\n"
    "\t-n            :: simple output without a new-line\n"
    "\t-t <seconds>  :: set timeout for each test (default 3s)\n"
    "\t-- <names>... :: run the specified tests only\n"
    ;

BT_POSSIBLY_UNUSED
int bt_test_names_argc = -1;

BT_POSSIBLY_UNUSED
void bt_parse_args(int argc, char * argv []) {
    for (int i = 1; i < argc; ++i) {
	if (strcmp(argv[i], "-d")==0) {
	    bt_fork_tests = 0;
	} else if (strcmp(argv[i], "-q")==0) {
	    bt_verbose = 0;
	} else if (strcmp(argv[i], "-v")==0) {
	    bt_verbose = 1;
	} else if (strcmp(argv[i], "-t")==0 && i + 1 < argc) {
	    i += 1;
	    bt_timeout = atoi(argv[i]);
	} else if (strcmp(argv[i], "--")==0) {
	    bt_test_names_argc = i + 1;
	    return;
	} else {
	    printf(bt_test_usage, argv[0]);
	    exit(EXIT_FAILURE);
	}
    }
}

#define INIT_TESTING(argc,argv) bt_parse_args(argc,argv)

int bt_test_driver(int argc, char * argv[]) {
    bt_parse_args(argc, argv);
    if (bt_test_names_argc == -1) {
	for (struct bt_test_descriptor * t = bt_main_test_suite; t != 0; t = t->next)
	    bt_run_and_record_test(t);
    } else {
	for (int i = bt_test_names_argc; i < argc; ++i)
	    for (struct bt_test_descriptor * t = bt_main_test_suite; t != 0; t = t->next)
		if (strcmp(argv[i], t->name) == 0)
		    bt_run_and_record_test(t);
    }
    PRINT_TEST_RESULTS;
    return EXIT_ALL_TESTS_PASSED;
}

#ifdef __cplusplus
#define MAIN_TEST_DRIVER(...)						\
    int main(int argc, char * argv[]) {					\
	return bt_test_driver(argc, argv);				\
    }
#else
#define MAIN_TEST_DRIVER(...)						\
    int main(int argc, char * argv[]) {					\
	struct bt_test_descriptor * suite [] = { __VA_ARGS__ };		\
	const unsigned n = sizeof(suite)/sizeof(struct bt_test_descriptor *); \
	for (unsigned i = 0; i < n; ++i)				\
	    bt_add_test(suite[i]);					\
	return bt_test_driver(argc, argv);				\
    }
#endif

#endif /* BASIC_TESTING_H_INCLUDED */
