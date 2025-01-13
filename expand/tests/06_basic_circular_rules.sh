#!/bin/bash
exec "$1" tests/circular_rules.txt <<EOF
hello my friend!
"ciao" means "hello"
"ciao" also means "goodbye"
EOF
