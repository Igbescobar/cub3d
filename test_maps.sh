#!/bin/bash

# Test script for cub3d map parsing
# This script tests all maps in the good and bad directories
# Good maps should pass (exit code 0), bad maps should fail (exit code 1)

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Make sure cub3d is compiled
echo -e "${BLUE}Compiling cub3d...${NC}"
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Failed to compile cub3d${NC}"
    exit 1
fi
echo -e "${GREEN}✅ cub3d compiled successfully${NC}"
echo

# Function to test a single map
test_map() {
    local map_file="$1"
    local expected_result="$2"  # 0 for good maps, 1 for bad maps
    local map_name=$(basename "$map_file")

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Run cub3d with the map file, capture output and exit code
    output=$(./cub3d "$map_file" 2>&1)
    exit_code=$?

    # Check if the result matches expectation
    if [ $exit_code -eq $expected_result ]; then
        echo -e "${GREEN}✅ PASS${NC} - $map_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        return 0
    else
        echo -e "${RED}❌ FAIL${NC} - $map_name (expected exit code $expected_result, got $exit_code)"
        echo -e "${YELLOW}   Output: $output${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return 1
    fi
}

# Test good maps (should pass - exit code 0)
echo -e "${BLUE}Testing GOOD maps (should pass):${NC}"
echo "=================================="
for map_file in maps/good/*.cub; do
    if [ -f "$map_file" ]; then
        test_map "$map_file" 0
    fi
done
echo

# Test bad maps (should fail - exit code 1)
echo -e "${BLUE}Testing BAD maps (should fail):${NC}"
echo "================================="
for map_file in maps/bad/*; do
    if [ -f "$map_file" ]; then
        test_map "$map_file" 1
    fi
done
echo

# Print summary
echo -e "${BLUE}Test Summary:${NC}"
echo "============="
echo -e "Total tests: ${YELLOW}$TOTAL_TESTS${NC}"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}💥 $FAILED_TESTS test(s) failed!${NC}"
    exit 1
fi
