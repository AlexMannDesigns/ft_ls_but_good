#!/bin/sh

### TEST HELPERS ###

# executes the test case and diffs the outputs
function tester () {
    # convert args to array
    ARGS_ARRAY=($1)

    # set up temp files
    FT_LS_OUTPUT=$(mktemp)
    FT_LS_ERROR_OUTPUT=$(mktemp)
    FT_LS_ERROR_NORMALIZED=$(mktemp)
    LS_OUTPUT=$(mktemp)
    LS_OUTPUT_NORMALIZED=$(mktemp)
    LS_ERROR_OUTPUT=$(mktemp)
    TMP_FILES+=("$FT_LS_OUTPUT" "$FT_LS_ERROR_OUTPUT" "$FT_LS_ERROR_NORMALIZED" "$LS_OUTPUT" "$LS_ERROR_OUTPUT" "$LS_OUTPUT_NORMALIZED")

    # run test and save output and error output to temp files
    ./ft_ls "${ARGS_ARRAY[@]}" > "$FT_LS_OUTPUT" 2> "$FT_LS_ERROR_OUTPUT"

    # uncomment the below to see the test output in the terminal
    # echo ""
    # echo "test output:"
    # ./ft_ls "${ARGS_ARRAY[@]}"

    # run same args through system ls
    # NB '-1' option not needed as we are writing onto a file
    ls "${ARGS_ARRAY[@]}" > "$LS_OUTPUT" 2> "$LS_ERROR_OUTPUT"

    # remove the 'ft_' from every line of ft_ls error output
    sed 's/^ft_//' "$FT_LS_ERROR_OUTPUT" > "$FT_LS_ERROR_NORMALIZED"

    # remove any @ or + (i.e. acl stuff) from output as this is not handled
    sed 's/[@+]/ /g' "$LS_OUTPUT" > "$LS_OUTPUT_NORMALIZED"

    # compare errors
    echo "Checking STDOUT..."
    if diff -u -a "$FT_LS_OUTPUT" "$LS_OUTPUT_NORMALIZED" > /dev/null; then
        echo "$TEST_PASS"
    else
        echo "$TEST_FAIL"
        echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG"
        diff -u -a "$FT_LS_OUTPUT" "$LS_OUTPUT_NORMALIZED" >> "$ERROR_LOG"
        echo "$FT_LS_OUTPUT" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"
    fi

    echo "Checking STDERR..."
    if diff -u "$FT_LS_ERROR_NORMALIZED" "$LS_ERROR_OUTPUT" > /dev/null; then
        echo "$TEST_PASS"
    else
        echo "$TEST_FAIL"
        echo "//----- ./ft_ls" "${ARGS_ARRAY[@]}" "-----//" >> "$ERROR_LOG"
        diff -u "$FT_LS_ERROR_NORMALIZED" "$LS_ERROR_OUTPUT" >> "$ERROR_LOG"
        echo "$FT_LS_ERROR_NORMALIZED" >> "$ERROR_LOG"
        echo "" >> "$ERROR_LOG"
    fi
    echo ""
}

### TEST CASES ###

# Tests ./ft_ls with no formatting params
function test_ls () {
    echo "//----- FT_LS OUTPUT TESTS -----//"

    # Test cases array
    TEST_CASES=(
        ""
        "''"
        "${HOME}"
        "libft"
        "${HOME} libft src"
        "Makefile"
        "Makefile src/main.c"
        "Makefile libft ${HOME}"
        "xyz"
        "c b a"
        "${HOME} hello z libft Makefile x src/main.c ../ft_ls / world src"
        "no_permission_soz"
        "no_permission_soz/test_1"
        "libft xyz src no_permission_soz Makefile src/main.c / foobar no_permission_soz/test_1"
    )

    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    for (( i=0; i<$NUM_TESTS; i++ )); do
        ARG_STRING="${TEST_CASES[$i]}"
        echo "test case: [ ./ft_ls $ARG_STRING ]"
        tester "$ARG_STRING"
    done
}

# Tests ./ft_ls -l i.e. the long format display
function test_ls_l () {
    echo "//----- FT_LS -L OUTPUT TESTS -----//"

    # Test cases array
    TEST_CASES=(
        "-l "
        "-l ''"
        "-l ${HOME}"
        "-l libft"
        "-l ${HOME} libft src"
        "-l Makefile"
        "-l Makefile src/main.c"
        "-l Makefile libft ${HOME}"
        "-l xyz"
        "-l c b a"
        "-l ${HOME} hello z libft Makefile x src/main.c ../ft_ls / world src"
        "-l no_permission_soz"
        "-l no_permission_soz/test_1"
        "-l libft xyz src no_permission_soz Makefile src/main.c / foobar no_permission_soz/test_1"
    )

    # Number of tests
    NUM_TESTS=${#TEST_CASES[@]}

    for (( i=0; i<$NUM_TESTS; i++ )); do
        ARG_STRING="${TEST_CASES[$i]}"
        echo "test case: [ ./ft_ls $ARG_STRING ]"
        tester "$ARG_STRING"
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
ERROR_LOG="test_ls_errors.log"
> "$ERROR_LOG"

# setup temp files array and cleanup
TMP_FILES=()
cleanup() { rm -f "${TMP_FILES[@]}"; }
trap cleanup EXIT

test_ls
test_ls_l
