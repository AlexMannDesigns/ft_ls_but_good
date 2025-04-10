#!/bin/sh

TEST_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "🧪 Running all tests in $TEST_DIR"
echo ""

"$TEST_DIR"/test_options_handling.sh
echo ""
"$TEST_DIR"/test_invalid_arg.sh
