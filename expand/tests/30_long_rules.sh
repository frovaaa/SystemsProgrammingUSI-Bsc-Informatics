#!/bin/bash
exec "$1" tests/long_rules.txt  tests/anima_rules.txt <<EOF
This one of the most inspiring speeches by Martin Luther King.  It is entitled "Beyond Vietnam: A Time to Break Silence"
EOF
