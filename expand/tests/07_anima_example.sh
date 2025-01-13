#!/bin/bash
exec "$1" tests/anima_rules.txt <<EOF
ANIMA
SANITY
ANIMA SANITY
SANITY ANIMA
EOF
