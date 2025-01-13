#!/bin/bash
exec "$1" tests/random_rules_10_1500.txt < tests/random_text_100_1000.txt
