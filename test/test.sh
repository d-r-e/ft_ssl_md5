#!/bin/bash

# Color functions for pretty output
function echo_green {
    echo -e "\033[32m$1\033[0m"
}

function echo_red {
    echo -e "\033[31m$1\033[0m"
}

function echo_yellow {
    echo -e "\033[33m$1\033[0m"
}

# Compile the program
make all

# Failing arguments
./ft_ssl 2>/dev/null || echo_green "[OK] no arguments"
./ft_ssl md4 2>/dev/null || echo_green "[OK] invalid command \"md4\""
./ft_ssl "" 2>/dev/null || echo_green "[OK] invalid command \"\""
./ft_ssl md5 2>/dev/null || echo_green "[OK] md5 without arguments"

# Function to compare expected and actual outputs
function check_output {
    local command="$1"
    local expected="$2"
    local result
    result=$(eval "$command")
    if [[ "$result" == "$expected" ]]; then
        echo_green "[OK] $command"
    else
        echo_red "[FAIL] $command - Expected: \"$expected\", Got: \"$result\""
    fi
}

function check_valgrind {
    local command="$1"
    valgrind --leak-check=full --error-exitcode=1 $command &> /dev/null
    if [[ $? -eq 0 ]]; then
        echo_green "[OK] No memory leaks detected in: $command"
    else
        echo_red "[FAIL] Memory leaks detected in: $command"
    fi
}

# Tests with expected output
check_output 'echo -n "42 is nice" | ./ft_ssl md5' "(stdin)= 35f1d6de0302e2086a4e472266efb3a9"
check_output 'echo "42 is nice" | ./ft_ssl md5 -p' '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'
check_output 'echo "Pity the living." | ./ft_ssl md5 -q -r' 'e20c3b973f63482a778f3fd1869b7f25'

# File based tests
echo "And above all," > file
check_output './ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
check_output './ft_ssl md5 -r file' '53d53ea94217b259c11a5a2d104ec58a file'

# String input with -s flag
check_output './ft_ssl md5 -s "pity those that aren'\''t following baerista on spotify."' 'MD5 ("pity those that aren'\''t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'

# Edge cases
check_output 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file' '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

check_output 'echo "some of this will not make sense at first" | ./ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

# Combined flags
check_output 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file' '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file'

check_output 'echo "GL HF let'\''s go" | ./ft_ssl md5 -p -s "foo" file' '("GL HF let'\''s go")= d1e3cc342b6da09480b27ec57ff243e2
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

check_output 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"' '("one more thing")= a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 "foo"
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory'

check_output 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file' 'just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a'

# Additional edge cases
echo "another edge case" > edge_case_file
check_output './ft_ssl md5 edge_case_file' 'MD5 (edge_case_file) = d73a5bbbd40ef1c05c0b5a59f91fccc1'
check_output './ft_ssl md5 -s ""' 'MD5 ("") = d41d8cd98f00b204e9800998ecf8427e'
check_output 'echo -n "" | ./ft_ssl md5' '(stdin)= d41d8cd98f00b204e9800998ecf8427e'

check_valgrind "./ft_ssl md5"
check_valgrind "./ft_ssl md5 -s 'test'"
check_valgrind "./ft_ssl md5 file"
check_valgrind "./ft_ssl md5 edge_case_file"

# Clean up
rm -f file edge_case_file

# Summary
echo_green "All tests completed."
