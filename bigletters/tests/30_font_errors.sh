"$1" tests/duplicate_font <<EOF
test
EOF
echo "$?"

"$1" tests/font_wrong_size <<EOF
test
EOF
echo "$?"

"$1" tests/font_wrong_depth <<EOF
test
EOF
echo "$?"

"$1" tests/font_wrong_format <<EOF
test
EOF
echo "$?"

