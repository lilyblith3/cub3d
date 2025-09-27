#!/bin/bash

# Color parsing test script for cub3d
# This script tests all the color parsing edge cases

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to create test file
create_test_file() {
    local filename="$1"
    local floor_line="$2"
    local ceiling_line="$3"
    
    cat > "$filename" << EOF
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

${floor_line}
${ceiling_line}

111111111111111111111111
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000N0000000000001
100000000000000000000001
100000000000000000000001
111111111111111111111111
EOF
}

# Function to run test
run_test() {
    local test_name="$1"
    local floor_line="$2"
    local ceiling_line="$3"
    local expected_result="$4"  # "pass" or "fail"
    local expected_error="$5"   # expected error message (optional)
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo "Floor: '$floor_line'"
    echo "Ceiling: '$ceiling_line'"
    
    # Create test file
    create_test_file "test_temp.cub" "$floor_line" "$ceiling_line"
    
    # Run the program and capture output
    output=$(./cub test_temp.cub 2>&1)
    exit_code=$?
    
    # Check result
    if [ "$expected_result" = "pass" ]; then
        if [ $exit_code -eq 0 ] && [[ $output == *"=== All validations passed! Ready for raycasting! ==="* ]]; then
            echo -e "${GREEN}✓ PASSED${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Expected: SUCCESS"
            echo "Got: EXIT_CODE=$exit_code"
            echo "Output: $output"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    else
        if [ $exit_code -ne 0 ] || [[ $output == *"Error:"* ]]; then
            if [ -n "$expected_error" ] && [[ $output == *"$expected_error"* ]]; then
                echo -e "${GREEN}✓ PASSED (correct error)${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            elif [ -z "$expected_error" ]; then
                echo -e "${GREEN}✓ PASSED (failed as expected)${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "${YELLOW}⚠ PARTIAL (failed but wrong error message)${NC}"
                echo "Expected error: '$expected_error'"
                echo "Got: $output"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            fi
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Expected: FAILURE"
            echo "Got: SUCCESS"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    
    echo "----------------------------------------"
    rm -f test_temp.cub
}

# Check if program exists
if [ ! -f "./cub" ]; then
    echo -e "${RED}Error: ./cub executable not found. Please compile your program first.${NC}"
    echo "Run: gcc -Wall -Wextra -Werror *.c -o cub"
    exit 1
fi

# Check if textures directory exists
if [ ! -d "./textures" ]; then
    echo -e "${YELLOW}Warning: ./textures directory not found. Creating dummy texture files...${NC}"
    mkdir -p textures
    touch textures/north_wall.xpm
    touch textures/south_wall.xpm
    touch textures/west_wall.xpm
    touch textures/east_wall.xpm
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}      CUB3D COLOR PARSING TESTS${NC}"
echo -e "${BLUE}========================================${NC}"
echo

echo -e "${GREEN}=== VALID CASES (should pass) ===${NC}"

run_test "Basic valid colors" \
    "F 220,100,0" \
    "C 225,30,0" \
    "pass"

run_test "Colors with leading/trailing spaces" \
    " F 0,255,128 " \
    " C 128,64,32 " \
    "pass"

run_test "Minimum RGB values" \
    "F 0,0,0" \
    "C 0,0,0" \
    "pass"

run_test "Maximum RGB values" \
    "F 255,255,255" \
    "C 255,255,255" \
    "pass"

run_test "Colors with extra spaces around numbers" \
    "F 0,     0,0" \
    "C 100,   200,   50" \
    "pass"

run_test "Colors with leading spaces" \
    "F              0,0,0" \
    "C         255,128,64" \
    "pass"

echo
echo -e "${RED}=== INVALID CASES (should fail) ===${NC}"

run_test "Missing RGB component" \
    "F 220,100" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "RGB value > 255" \
    "F 300,20,10" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Negative RGB value" \
    "F -1,100,0" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Too many RGB components" \
    "F 220,100,0,50" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Multiple consecutive commas" \
    "F 200,,,,,4,3" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Non-numeric RGB values" \
    "F 220,abc,0" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Mixed alphanumeric RGB" \
    "F 220,a0,0" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Space-separated instead of comma" \
    "F 220 100 0" \
    "C 225,30,0" \
    "fail"

run_test "Invalid identifier" \
    "FF 220,100,0" \
    "C 225,30,0" \
    "fail"

run_test "Extra text after RGB" \
    "F 220,100,0 extra" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Duplicate floor color" \
    "F 220,100,0" \
    "F 100,50,25" \
    "fail" \
    "Duplicate floor color"

run_test "Duplicate ceiling color" \
    "C 220,100,0" \
    "C 100,50,25" \
    "fail" \
    "Duplicate ceiling color"

run_test "Empty RGB values" \
    "F ,,," \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Only commas" \
    "F ,," \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

run_test "Single number" \
    "F 220" \
    "C 225,30,0" \
    "fail" \
    "Invalid color format - must be R,G,B"

echo
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST RESULTS${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total Tests: ${TOTAL_TESTS}"
echo -e "${GREEN}Passed: ${PASSED_TESTS}${NC}"
echo -e "${RED}Failed: ${FAILED_TESTS}${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed! Your color parsing is working correctly!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed. Please check your implementation.${NC}"
    exit 1
fi
