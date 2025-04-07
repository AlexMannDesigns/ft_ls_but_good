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
    FT_LS_OUTPUT_FILE=$(mktemp)
    EXPECTED_OUTPUT_FILE=$(mktemp)
    TMP_FILES+=("$FT_LS_OUTPUT_FILE" "$EXPECTED_OUTPUT_FILE")
    
    # run ./ft_ls --TEST + commandline args > temp_file
    ./ft_ls --TEST "${ARGS_ARRAY[@]}" > "$FT_LS_OUTPUT_FILE"

    # echo the expected output into another temp file
    echo "$EXPECTED_OUTPUT" > "$EXPECTED_OUTPUT_FILE"
    
    # diff the two temp files, outputting any errors into a test results file
    if diff -u "$EXPECTED_OUTPUT_FILE" "$FT_LS_OUTPUT_FILE" > /dev/null; then
        echo "$TEST_PASS"
    else
        echo "$TEST_FAIL"
        echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG" 
        diff -u "$EXPECTED_OUTPUT_FILE" "$FT_LS_OUTPUT_FILE" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"
    fi
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
        "-la ~ /"
        "-l -a"
        "-l -r -t"
        "-a -rS"
        "-lR -ta -r"
        "-lRtarm"
    )

    # Expected output array
    EXPECTED_OUTPUT_ARRAY=(
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 1\nargv_idx = 3"
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
    echo "//----- OPTION REPETITION TESTS -----//"
    
    # Test cases array
    TEST_CASES=(
        "-ll"
        "-lll"
        "-rrrlrrr"
        "-ll -ll"
        "-ml"
        "-lm"
        "-mmmmmmmmmmml"
    )

    # Expected output array
    EXPECTED_OUTPUT_ARRAY=(
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 1\nall = 0\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 4"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = comma\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
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

# This test handles the double-line (--) edge case
function test_double_line () {
    echo "//----- DOUBLE LINE (--) TESTS -----//"
    
    # Test cases array
    TEST_CASES=(
        "--"
        "-l --"
        "-m -- -l"
    )

    # Expected output array
    EXPECTED_OUTPUT_ARRAY=(
        "display = columns\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 3"
        "display = long\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 4"
        "display = comma\nsort = lexicographical\nrecursive = 0\nreversed = 0\nall = 0\nargv_idx = 4"
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

# This test ensures invalid options are handled correctly
function test_option_errors () {
    echo "//----- OPTION ERROR TESTS -----//"
    
    # Test cases array
    TEST_CASES=(
        "-z"
        "--z"
        "--hello"
        "-l -m -X"
        "-lartYR"
    )

    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    for (( i=0; i<$NUM_TESTS; i++ )); do
        OPTION_STRING="${TEST_CASES[$i]}"
        echo "test case: [ ./ft_ls $OPTION_STRING ]"

        # convert args to array
        ARGS_ARRAY=($OPTION_STRING)
    
        # set up temp files
        FT_LS_OUTPUT=$(mktemp)
        LS_OUTPUT=$(mktemp)
        TMP_FILES+=("$FT_LS_OUTPUT" "$LS_OUTPUT")
        
        # run test and save output to temp file (usage not needed and first
        # 3 chars can be sliced off [i.e. 'ft_'] so the error message matches ls)
        ./ft_ls "${ARGS_ARRAY[@]}" > "$FT_LS_OUTPUT" 2>&1
        FT_LS_ERROR_LINE=$(head -n 1 "$FT_LS_OUTPUT")
        FT_LS_NORMALIZED=${FT_LS_ERROR_LINE:3} 

        # run same args through system ls 
        ls "${ARGS_ARRAY[@]}" > "$LS_OUTPUT" 2>&1 
        LS_ERROR_LINE=$(head -n 1 "$LS_OUTPUT")

        # compare normalized errors
        if [[ "$FT_LS_NORMALIZED" == "$LS_ERROR_LINE" ]]; then
            echo "$TEST_PASS"
        else
            echo "$TEST_FAIL"
            echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG" 
            echo "$LS_ERROR_LINE" >> "$ERROR_LOG"
            echo "$FT_LS_NORMALIZED" >> "$ERROR_LOG"
            echo "" >> "$ERROR_LOG"
        fi
    done
}


##### Test Script starts here #####

# global vars
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

TEST_PASS="${GREEN}PASS${NC} ✅"
TEST_FAIL="${RED}FAIL${NC} ❌"

# setup error log file
ERROR_LOG="test_errors.log"
> "$ERROR_LOG"

# setup temp files array and cleanup 
TMP_FILES=()
cleanup() { rm -f "${TMP_FILES[@]}"; }
trap cleanup EXIT

# call test functions
test_basic_options
test_complex_options
test_option_repetition
test_double_line
test_option_errors

