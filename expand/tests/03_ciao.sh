#!/bin/bash
exec "$1" tests/rules1.txt <<EOF
ciao mamma
EOF
