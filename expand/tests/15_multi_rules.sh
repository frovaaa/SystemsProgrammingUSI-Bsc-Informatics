#!/bin/bash
exec "$1" tests/anima_rules.txt tests/poem_rules.txt <<EOF
ANIMA poem SANITY
SANII empty textciaoSANIAIAI
EOF
