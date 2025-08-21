#!/bin/bash

# Detailed test script for cub3d map parsing
# This script provides more detailed information about test failures

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Function to run a specific test and show details
run_detailed_test() {
    local map_file="$1"
    local map_name=$(basename "$map_file")

    echo -e "${CYAN}Testing: $map_name${NC}"
    echo "File: $map_file"

    # Show first few lines of the map file
    echo -e "${YELLOW}Content preview:${NC}"
    head -10 "$map_file" | sed 's/^/  /'

    # Run the test
    echo -e "${YELLOW}Running test...${NC}"
    output=$(./cub3d "$map_file" 2>&1)
    exit_code=$?

    echo -e "${YELLOW}Exit code: $exit_code${NC}"
    echo -e "${YELLOW}Output:${NC}"
    echo "$output" | sed 's/^/  /'
    echo "----------------------------------------"
    echo
}

# Make sure we have an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <map_file>"
    echo "       $0 all_bad     # Test all bad maps"
    echo "       $0 all_good    # Test all good maps"
    exit 1
fi

# Compile cub3d
echo -e "${BLUE}Compiling cub3d...${NC}"
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Failed to compile cub3d${NC}"
    exit 1
fi

if [ "$1" = "all_bad" ]; then
    echo -e "${BLUE}Testing all BAD maps:${NC}"
    echo "===================="
    for map_file in maps/bad/*; do
        if [ -f "$map_file" ]; then
            run_detailed_test "$map_file"
        fi
    done
elif [ "$1" = "all_good" ]; then
    echo -e "${BLUE}Testing all GOOD maps:${NC}"
    echo "====================="
    for map_file in maps/good/*.cub; do
        if [ -f "$map_file" ]; then
            run_detailed_test "$map_file"
        fi
    done
elif [ -f "$1" ]; then
    run_detailed_test "$1"
else
    echo -e "${RED}File not found: $1${NC}"
    exit 1
fi
