#!/bin/sh


# runs ft_ls with the --TEST option, which prints the state of the options struct
# after the options handling is complete. This is piped to a temp file and diffed
# with the expected output
# Param 1: commandline args
# Param 2: expected output
function options_tester () {
    echo hello world
    # run ./ft_ls --TEST + commandline args > temp_file

    # echo the expected output into another temp file

    # diff the two temp files, outputting any errors into a test results file
    
    # echo pass or fail depending on output

    # delete the two temp files

}

# This test covers the most basic option handling (e.g. ./ft_ls -l)
function test_basic_options () {
    # echo basic tests start

    # Test cases arrary

    # call options_tester() with each test case in a loop, echoing each test case
}

# This test covers some more convoluted (but valid) option sequences (e.g. ./ft_ls -lR -ta -r)
function test_complex_options () {

}

# i.e. ./ftls
function test_no_options () {

}

# repeating an option should not change anything
function test_option_repetition () {

}

# This test handles the double-line (--) edge case
function test_double_line () {

}

# This test ensures invalid options are handled correctly
function test_option_errors () {

}


test_basic_options


