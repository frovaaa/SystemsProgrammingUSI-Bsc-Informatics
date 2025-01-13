#!/bin/bash
exec "$1" tests/poem_rules.txt <<EOF
Ciao darkness, my old friend... should be: ciao darkness, my old friend...

Here is a poem by Blake.

Notice the expansion.

And here's another example of an expansion of empty text that you
should not see.  Well, you should see two consecutive spaces...
EOF
