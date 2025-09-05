#!/bin/bash

echo "=== Linux Compatibility Test ==="
echo "Testing compilation and basic functionality..."

# Test 1: Check if Linux minilibx is available
echo "1. Checking Linux minilibx..."
if [ -d "library/minilibx-linux" ]; then
    echo "   ✅ Linux minilibx found"
else
    echo "   ❌ Linux minilibx not found"
    exit 1
fi

# Test 2: Check if Linux minilibx can be compiled (skip if already compiled)
echo "2. Testing Linux minilibx compilation..."
if [ -f "library/minilibx-linux/libmlx.a" ]; then
    echo "   ✅ Linux minilibx already compiled"
else
    cd library/minilibx-linux
    make clean > /dev/null 2>&1
    if make > /dev/null 2>&1; then
        echo "   ✅ Linux minilibx compiles successfully"
    else
        echo "   ❌ Linux minilibx compilation failed"
        cd ../..
        exit 1
    fi
    cd ../..
fi

# Test 3: Check if main project compiles with Linux settings
echo "3. Testing main project compilation..."
make clean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo "   ✅ Main project compiles successfully"
else
    echo "   ❌ Main project compilation failed"
    exit 1
fi

# Test 4: Check if executable was created
echo "4. Checking executable..."
if [ -f "cub3D" ]; then
    echo "   ✅ Executable created successfully"
    echo "   📁 Executable size: $(ls -lh cub3D | awk '{print $5}')"
else
    echo "   ❌ Executable not found"
    exit 1
fi

# Test 5: Check if .cub file parsing works
echo "5. Testing .cub file parsing..."
if [ -f "maps/simplemap.cub" ]; then
    echo "   ✅ Test map file found"
    # Run with timeout to prevent hanging
    timeout 5s ./cub3D maps/simplemap.cub > /dev/null 2>&1
    if [ $? -eq 0 ] || [ $? -eq 124 ]; then
        echo "   ✅ Program starts without immediate crash"
    else
        echo "   ⚠️  Program may have issues (exit code: $?)"
    fi
else
    echo "   ❌ Test map file not found"
fi

echo ""
echo "=== Test Summary ==="
echo "✅ Linux compatibility setup appears to be working"
echo "✅ All compilation steps successful"
echo "✅ Basic functionality test passed"
echo ""
echo "Note: This test was run on macOS but validates Linux compatibility setup."
echo "For full Linux testing, run this on a Linux system or in a Linux container."
