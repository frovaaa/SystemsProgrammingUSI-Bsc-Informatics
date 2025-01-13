PROGRAMS=expand

CFLAGS=-Wall -g
CXXFLAGS=-Wall -g

SHELL=/bin/bash

TIMEOUT=8

TESTS_DIR=tests

TESTS_SH:=$(wildcard $(TESTS_DIR)/*.sh)
TESTS_SH_NAMES:=$(sort $(patsubst $(TESTS_DIR)/%.sh, %, $(TESTS_SH)))

TESTS_IO:=$(wildcard $(TESTS_DIR)/*.in)
TESTS_IO_NAMES:=$(sort $(patsubst $(TESTS_DIR)/%.in, %, $(TESTS_IO)))

TESTS_C:=$(wildcard $(TESTS_DIR)/*.c)
TESTS_CXX:=$(wildcard $(TESTS_DIR)/*.cc)
TESTS_BIN:=$(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%, $(TESTS_C)) \
	   $(patsubst $(TESTS_DIR)/%.cc, $(TESTS_DIR)/%, $(TESTS_CXX))
TESTS_BIN_NAMES:=$(sort $(patsubst $(TESTS_DIR)/%.c, %, $(TESTS_C)) $(patsubst $(TESTS_DIR)/%.cc, %, $(TESTS_CXX)))

.PHONY: all
all: compile check

.PHONY: compile-program

compile: $(PROGRAMS) $(OBJECTS)

.PHONY: check
check: check-bin check-io-sh

WITH_VALGRIND :=

PROGRAMS_DRIVERS := $(foreach prog,$(PROGRAMS),$(prog)$(if $(WITH_VALGRIND),-valgrind,))
PROGRAMS_CWD := $(shell pwd)

%-valgrind: %
	echo -e '#!/bin/sh\nexec valgrind -q "./$*" $$@' > $@
	chmod 755 $@

TEST_DIAGNOSTICS=yes
ifeq ($(TEST_DIAGNOSTICS),no)
SUPPRESS_DIAGNOSTICS=yes
else
SUPPRESS_DIAGNOSTICS=
endif
TEST_COLORS=yes
ifeq ($(TEST_COLORS),no)
COLOR_RED :=
COLOR_GREEN :=
COLOR_NORMAL :=
else
COLOR_RED := $(shell tput setaf 1; tput bold)
COLOR_GREEN := $(shell tput setaf 2; tput bold)
COLOR_NORMAL := $(shell tput sgr0 ; tput oc )
endif

SCRIPT_UTILS := \
	echo_ko () { echo "$(COLOR_RED)$$@$(COLOR_NORMAL)"; }; \
	echo_ok () { echo "$(COLOR_GREEN)$$@$(COLOR_NORMAL)"; }; \
	echo_diag () { $(if $(SUPPRESS_DIAGNOSTICS),return,echo "$$@"); }

SCRIPT_GET_TEST_RESULT := \
	prog_pid=$$!; \
	( sleep $(TIMEOUT); kill -9 $$prog_pid > /dev/null 2>&1 ) & \
	killer_pid=$$!; \
	wait $$prog_pid; \
	res=$$?; \
	if test $$res -gt 128; \
	then \
		sig=`kill -l $$(($$res - 128))`; \
		case "$$sig" in \
			ABRT ) echo_ko FAIL; ;; \
			TERM | KILL ) echo_ko TIME OUT; ;; \
			* ) echo_ko ERROR "($$sig)"; ;; \
		esac ; \
		res=KO; \
	else \
		kill $$killer_pid > /dev/null 2>&1 ;\
		wait $$killer_pid; \
		if test "$$res" = 0; \
		then \
			res=OK; \
		else \
			echo_ko FAIL; \
			res=KO; \
		fi; \
	fi

SCRIPT_CHECK_ERR_FILE := \
	if test -s "$$t.err"; \
	then \
		echo_diag "there were also errors ($$t.err):"; \
		cat "$$t.err"; \
	fi

OUTPUT_LIMIT := 10M
# SCRIPT_HANDLE_OUT_ERR_TEST := | head -c $(OUTPUT_LIMIT) > "$$t.out" |& tee "$$t.err"
SCRIPT_HANDLE_OUT_ERR_TEST := > "$$t.out" 2>&1

.PHONY: check-io-sh
check-io-sh: compile $(TESTS_IO) $(TESTS_SH) $(PROGRAMS_DRIVERS)
	@exec 2> /dev/null; \
	$(SCRIPT_UTILS); \
	for p in $(PROGRAMS_DRIVERS); do \
	echo "Testing $${p}:" ; \
	for t in $(TESTS_IO_NAMES); do \
		echo -n "Running test $$t... " ; \
		"$(PROGRAMS_CWD)/$$p" < "$(TESTS_DIR)/$$t.in" $(SCRIPT_HANDLE_OUT_ERR_TEST) &\
		$(SCRIPT_GET_TEST_RESULT); \
		if test "$$res" = KO; \
		then \
			echo_diag "see $(TESTS_DIR)/$$t.in" ;\
			echo_diag "you may run $$p < $(TESTS_DIR)/$$t.in" ;\
			echo_diag "to see what went wrong";\
			rm -f "$$t.out" ;\
		else \
			if cmp -s "$$t.out" "$(TESTS_DIR)/$$t.expected"; \
			then \
				echo_ok PASS; \
				rm -f "$$t.out" ;\
			else \
				echo_ko FAIL ;\
				echo_diag "see $(TESTS_DIR)/$$t.in" ;\
				echo_diag "run diff $$t.out $(TESTS_DIR)/$$t.expected";\
				echo_diag "to see the difference between the actual and expected output";\
			fi; \
		fi; \
		$(SCRIPT_CHECK_ERR_FILE); \
	done; \
	for t in $(TESTS_SH_NAMES); do \
		echo -n "Running test $$t... " ; \
		$(SHELL) "$(TESTS_DIR)/$$t.sh" "$(PROGRAMS_CWD)/$$p"  $(SCRIPT_HANDLE_OUT_ERR_TEST) &\
		$(SCRIPT_GET_TEST_RESULT); \
		if test "$$res" = KO; \
		then \
			echo_diag "see $(TESTS_DIR)/$$t.sh" ;\
			echo_diag "you may run $(TESTS_DIR)/$$t.sh $$p" ;\
			echo_diag "to see what went wrong";\
			rm -f "$$t.out";\
		else \
			if test ! -r "$(TESTS_DIR)/$$t.expected" || cmp -s "$$t.out" "$(TESTS_DIR)/$$t.expected"; \
			then \
				echo_ok PASS; \
				rm -f "$$t.out" ;\
			else \
				echo_ko FAIL ;\
				echo_diag "see $(TESTS_DIR)/$$t.sh" ;\
				echo_diag "run diff $$t.out $(TESTS_DIR)/$$t.expected";\
				echo_diag "to see the difference between the actual and expected output";\
			fi; \
		fi; \
		$(SCRIPT_CHECK_ERR_FILE); \
	done; \
	done

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.c $(OBJECTS) -o $@

$(TESTS_DIR)/%: $(TESTS_DIR)/%.cc $(OBJECTS)
	$(CXX) -std=c++11 $(CXXFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.cc $(OBJECTS) -o $@

.PHONY: check-bin
check-bin: $(TESTS_BIN)
	@exec 2> /dev/null; \
	$(SCRIPT_UTILS); \
	for t in $(TESTS_BIN_NAMES); do \
		echo -n "Running test $$t... " ; \
		if test -n "$(WITH_VALGRIND)"; then \
			echo ;\
			valgrind -q "$(TESTS_DIR)/$$t" 2>&1 &\
		else \
			"$(TESTS_DIR)/$$t" -q &\
		fi; \
		$(SCRIPT_GET_TEST_RESULT); \
		if test $$res = KO; then \
			echo_diag "run '$(TESTS_DIR)/$$t' to see what went wrong" ; \
			echo_diag "run '$(TESTS_DIR)/$$t -d' with a debugger" ; \
		else \
			echo_ok PASS; \
		fi; \
	done


.PHONY: clean
clean:
	rm -f $(PROGRAMS) *-valgrind $(OBJECTS) tests/*.o $(TESTS_BIN)
