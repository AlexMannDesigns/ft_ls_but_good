#!/bin/sh

# runs ft_ls with the --TEST option, which prints the state of the options struct
# after the options handling is complete. This is piped to a temp file and diffed
# with the expected output
# Param 1: commandline args
# Param 2: expected output
function options_tester () {
    # rename params
    ARGS_STRING=$1
    EXPECTED_OUTPUT=$2

    # convert args to array
    ARGS_ARRAY=($ARGS_STRING)

    # set up temp files
    FT_LS_TEST_OPTIONS_OUTPUT=$(mktemp)
    EXPECTED_TEST_OPTIONS_OUTPUT=$(mktemp)
    
    # run ./ft_ls --TEST + commandline args > temp_file
    ./ft_ls --TEST "${ARGS_ARRAY[@]}" > "$FT_LS_TEST_OPTIONS_OUTPUT"

    # echo the expected output into another temp file
    echo "$EXPECTED_OUTPUT" > "$EXPECTED_TEST_OPTIONS_OUTPUT"
    
    # diff the two temp files, outputting any errors into a test results file
    if diff -u "$EXPECTED_TEST_OPTIONS_OUTPUT" "$FT_LS_TEST_OPTIONS_OUTPUT" > /dev/null; then
        echo "$TEST_PASS"
    else
        echo "$TEST_FAIL"
        echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG" 
        diff -u "$EXPECTED_TEST_OPTIONS_OUTPUT" "$FT_LS_TEST_OPTIONS_OUTPUT" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"
    fi

    # delete the two temp files
    rm "$FT_LS_TEST_OPTIONS_OUTPUT" "$EXPECTED_TEST_OPTIONS_OUTPUT"
}

# This test covers the most basic option handling (e.g. ./ft_ls -l)
function test_basic_options () {
    # echo basic tests start
    echo "//----- BASIC OPTIONS TESTS -----//"

    # Test cases array
    TEST_CASES=(
        ""
        "-l"
        "-m"
        "-1"
        "-t"
        "-S"
        "-R"
        "-r"
        "-a"
    )

    # Expected output array
    EXPECTED_OUTPUT_ARRAY=(
        "display = columns\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 2"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = comma\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = one\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = columns\nsort = time\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = columns\nsort = size\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = columns\nsort = lexicographical\nrecursive = 1\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = columns\nsort = lexicographical\nrecursive = 0\nreversed = 1\nall = 0\nargv_idx = 3"
        "display = columns\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 1\nargv_idx = 3"
    )

    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    # Run tests
    # call options_tester() with each test case in a loop, echoing each test case
    for (( i=0; i<$NUM_TESTS; i++ )); do
        OPTION_STRING="${TEST_CASES[$i]}"
        EXPECTED_OUTPUT="${EXPECTED_OUTPUT_ARRAY[$i]}"

        echo "test case: [ ./ft_ls" $OPTION_STRING " ]"
        options_tester "$OPTION_STRING" "$EXPECTED_OUTPUT"
    done
    echo ""
}

# This test covers some more convoluted (but valid) option sequences (e.g. ./ft_ls -lR -ta -r)
function test_complex_options () {
    echo "//----- COMPLEX OPTIONS TESTS -----//"
    
    # Test cases array
    TEST_CASES=(
        "-la"
        "-l -a"
        "-l -r -t"
        "-a -rS"
        "-lR -ta -r"
        "-lRtarm"
    )

    # Expected output array
    EXPECTED_OUTPUT_ARRAY=(
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 1\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 1\nargv_idx = 4"
        "display = long\nsort = time\nrecursive = 0\nreversed = 1\nall = 0\nargv_idx = 5"
        "display = columns\nsort = size\nrecursive = 0\nreversed = 1\nall = 1\nargv_idx = 4"
        "display = long\nsort = time\nrecursive = 1\nreversed = 1\nall = 1\nargv_idx = 5"
        "display = comma\nsort = time\nrecursive = 1\nreversed = 1\nall = 1\nargv_idx = 3"
    )
    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    # Run tests
    # call options_tester() with each test case in a loop, echoing each test case
    for (( i=0; i<$NUM_TESTS; i++ )); do
        OPTION_STRING="${TEST_CASES[$i]}"
        EXPECTED_OUTPUT="${EXPECTED_OUTPUT_ARRAY[$i]}"

        echo "test case: [ ./ft_ls" $OPTION_STRING " ]"
        options_tester "$OPTION_STRING" "$EXPECTED_OUTPUT"
    done
    echo ""
}

# repeating an option should not change anything
function test_option_repetition () {
    echo NOT YET IMPLEMENTED
}

# This test handles the double-line (--) edge case
function test_double_line () {
    echo NOT YET IMPLEMENTED
}

# This test ensures invalid options are handled correctly
function test_option_errors () {
    echo NOT YET IMPLEMENTED
}



# Test Script starts here

# global vars
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

TEST_PASS="${GREEN}PASS${NC} ✅"
TEST_FAIL="${RED}FAIL${NC} ❌"

# setup error log file
ERROR_LOG="test_errors.log"
> "$ERROR_LOG"

test_basic_options
test_complex_options


