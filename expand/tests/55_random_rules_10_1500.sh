#!/bin/bash
# crazy eh... applying random rules to the random rules themselves!
exec "$1" tests/random_rules_10_1500.txt < tests/random_rules_10_1500.txt
