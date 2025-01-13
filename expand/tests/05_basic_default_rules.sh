#!/bin/bash
exec "$1" <<EOF
hello my friend!
"ciao" means "hello"
"ciao" also means "goodbye"
EOF
