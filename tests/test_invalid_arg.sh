#!/bin/sh

function test_invalid_args () {
    echo "//----- INVALID ARG TESTS -----//"
    
    # Test cases array
    TEST_CASES=(
        "hello"
        "a b c d e f g"
        "g f e d c b a"
        "1 c b a M - #"
        "wow these are a lot of words I wonder what order they will be printed"
        "-l foo"
        "-l -r hello world"
        "-l foo -x"
        "-m foo"
        "-"
    )

    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    for (( i=0; i<$NUM_TESTS; i++ )); do
        ARG_STRING="${TEST_CASES[$i]}"
        echo "test case: [ ./ft_ls $ARG_STRING ]"

        # convert args to array
        ARGS_ARRAY=($ARG_STRING)
    
        # set up temp files
        FT_LS_OUTPUT=$(mktemp)
        FT_LS_NORMALIZED=$(mktemp)
        LS_OUTPUT=$(mktemp)
        TMP_FILES+=("$FT_LS_OUTPUT" "$FT_LS_NORMALIZED" "$LS_OUTPUT")
        
        # run test and save output to temp file
        ./ft_ls "${ARGS_ARRAY[@]}" > "$FT_LS_OUTPUT" 2>&1

        # run same args through system ls 
        ls "${ARGS_ARRAY[@]}" > "$LS_OUTPUT" 2>&1 
       
        # remove the 'ft_' from every line of ft_ls error output
        sed 's/^ft_//' "$FT_LS_OUTPUT" > "$FT_LS_NORMALIZED"
        
        # compare errors 
        if diff -u "$FT_LS_NORMALIZED" "$LS_OUTPUT" > /dev/null; then
            echo "$TEST_PASS"
        else
            echo "$TEST_FAIL"
            echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG" 
            diff -u "$FT_LS_NORMALIZED" "$LS_OUTPUT" >> "$ERROR_LOG"
            echo "$FT_LS_NORMALIZED" >> "$ERROR_LOG"
            echo "" >> "$ERROR_LOG"
        fi
    done
}


##### Test Script starts here #####

# global vars
RED="$(printf '\033[0;31m')"
GREEN="$(printf '\033[0;32m')"
NC="$(printf '\033[0m')" # No Color

TEST_PASS="${GREEN}PASS${NC} ✅"
TEST_FAIL="${RED}FAIL${NC} ❌"

# setup error log file
ERROR_LOG="test_arg_errors.log"
> "$ERROR_LOG"

# setup temp files array and cleanup 
TMP_FILES=()
cleanup() { rm -f "${TMP_FILES[@]}"; }
trap cleanup EXIT

test_invalid_args
