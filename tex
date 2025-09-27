#!/bin/bash

# Texture parsing test script for cub3d
# This script tests all the texture parsing edge cases

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
    local north_line="$2"
    local south_line="$3"
    local west_line="$4"
    local east_line="$5"
    
    cat > "$filename" << EOF
${north_line}
${south_line}
${west_line}
${east_line}

F 220,100,0
C 225,30,0

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

# Function to setup test textures
setup_test_textures() {
    mkdir -p textures
    mkdir -p test_textures
    mkdir -p "path with spaces"
    
    # Create valid texture files
    touch textures/north_wall.xpm
    touch textures/south_wall.xpm
    touch textures/west_wall.xpm
    touch textures/east_wall.xpm
    touch textures/valid_texture.xpm
    touch test_textures/texture1.xpm
    touch test_textures/texture2.xpm
    touch "path with spaces/texture.xpm"
    
    # Create some invalid files (non-texture)
    echo "not a texture" > textures/invalid.txt
    
    # Create a directory with same name as texture
    mkdir -p textures/directory_texture.xpm 2>/dev/null || true
}

# Function to cleanup test textures
cleanup_test_textures() {
    rm -rf test_textures
    rm -rf "path with spaces"
    rm -f textures/invalid.txt
    rm -rf textures/directory_texture.xpm 2>/dev/null || true
    rm -f textures/nonexistent.xpm
}

# Function to run test
run_test() {
    local test_name="$1"
    local north_line="$2"
    local south_line="$3"
    local west_line="$4"
    local east_line="$5"
    local expected_result="$6"  # "pass" or "fail"
    local expected_error="$7"   # expected error message (optional)
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo "NO: '$north_line'"
    echo "SO: '$south_line'"
    echo "WE: '$west_line'"
    echo "EA: '$east_line'"
    
    # Create test file
    create_test_file "test_temp.cub" "$north_line" "$south_line" "$west_line" "$east_line"
    
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
    echo "Run: make"
    exit 1
fi

# Setup test environment
setup_test_textures

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}      CUB3D TEXTURE PARSING TESTS${NC}"
echo -e "${BLUE}========================================${NC}"
echo

echo -e "${GREEN}=== VALID CASES (should pass) ===${NC}"

run_test "Basic valid textures" \
    "NO ./textures/north_wall.xpm" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "pass"

run_test "Textures with leading/trailing spaces" \
    " NO ./textures/north_wall.xpm " \
    " SO ./textures/south_wall.xpm " \
    " WE ./textures/west_wall.xpm " \
    " EA ./textures/east_wall.xpm " \
    "pass"

run_test "Textures with extra spaces" \
    "NO     ./textures/north_wall.xpm" \
    "SO     ./textures/south_wall.xpm" \
    "WE     ./textures/west_wall.xpm" \
    "EA     ./textures/east_wall.xpm" \
    "pass"

run_test "Different valid texture paths" \
    "NO ./test_textures/texture1.xpm" \
    "SO ./test_textures/texture2.xpm" \
    "WE ./textures/valid_texture.xpm" \
    "EA ./textures/north_wall.xpm" \
    "pass"

echo
echo -e "${RED}=== INVALID CASES (should fail) ===${NC}"

run_test "Missing texture file" \
    "NO ./textures/nonexistent.xpm" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail" \
    "Texture file not found"

run_test "Empty texture path" \
    "NO " \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Invalid texture identifier" \
    "NN ./textures/north_wall.xpm" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Duplicate north texture" \
    "NO ./textures/north_wall.xpm" \
    "NO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Missing texture path" \
    "NO" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Extra text after texture path" \
    "NO ./textures/north_wall.xpm extra text" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Wrong texture format (not .xpm)" \
    "NO ./textures/invalid.txt" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Directory instead of file" \
    "NO ./textures" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "fail"

run_test "Missing north texture" \
    "SO ./textures/south_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "F 220,100,0" \
    "fail"

run_test "Missing south texture" \
    "NO ./textures/north_wall.xpm" \
    "WE ./textures/west_wall.xpm" \
    "EA ./textures/east_wall.xpm" \
    "F 220,100,0" \
    "fail"

run_test "All textures missing" \
    "F 220,100,0" \
    "C 225,30,0" \
    "" \
    "" \
    "fail"

# Test with paths containing spaces (if your system supports it)
if [ -f "path with spaces/texture.xpm" ]; then
    run_test "Path with spaces (quoted)" \
        "NO \"path with spaces/texture.xpm\"" \
        "SO ./textures/south_wall.xpm" \
        "WE ./textures/west_wall.xpm" \
        "EA ./textures/east_wall.xpm" \
        "fail"  # Most parsers don't handle quotes
fi

echo
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST RESULTS${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total Tests: ${TOTAL_TESTS}"
echo -e "${GREEN}Passed: ${PASSED_TESTS}${NC}"
echo -e "${RED}Failed: ${FAILED_TESTS}${NC}"

# Cleanup
cleanup_test_textures

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed! Your texture parsing is working correctly!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed. Please check your implementation.${NC}"
    exit 1
fi
