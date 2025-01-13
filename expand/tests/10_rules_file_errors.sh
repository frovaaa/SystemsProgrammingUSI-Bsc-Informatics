#!/bin/bash
"$1" tests/non_existent_rules <<EOF
the program must terminate without printing this line.
EOF
# we are expecting the program to fail, so...
test "$!" != 0


    
