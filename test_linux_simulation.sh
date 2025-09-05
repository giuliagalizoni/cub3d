#!/bin/bash

echo "=== Linux Compilation Simulation ==="
echo "This script shows what would happen on Linux"
echo ""

# Simulate Linux environment
echo "Simulating Linux environment..."
echo "UNAME_S would be: Linux"
echo "MLX_DIR would be: library/minilibx-linux"
echo "MLX_FLAGS would be: -lmlx -lXext -lX11"
echo ""

# Check if Linux minilibx exists
if [ -f "library/minilibx-linux.tgz" ]; then
    echo "✅ Linux minilibx archive found"
else
    echo "❌ Linux minilibx archive missing"
    exit 1
fi

# Show what the Makefile would do on Linux
echo ""
echo "=== What Makefile would do on Linux ==="
echo "1. Detect OS: Linux"
echo "2. Set MLX_DIR = library/minilibx-linux"
echo "3. Set MLX_FLAGS = -lmlx -lXext -lX11"
echo "4. Extract minilibx-linux.tgz if needed"
echo "5. Compile with Linux flags"
echo ""

# Show the compilation command that would be used
echo "=== Compilation command on Linux ==="
echo "cc obj/*.o -Llibrary/minilibx-linux -lmlx -lmlx -lXext -lX11 -Llibft -lft -lm -o cub3D"
echo ""

# Check for potential issues
echo "=== Potential Linux Issues ==="
echo "1. Missing X11 libraries: sudo apt-get install libx11-dev libxext-dev"
echo "2. Display issues: export DISPLAY=:0"
echo "3. Permission issues: Check X11 forwarding"
echo ""

echo "=== Solution ==="
echo "The fixed Makefile now:"
echo "✅ Uses dynamic INCLUDES path based on OS"
echo "✅ Automatically extracts correct minilibx version"
echo "✅ Uses correct compilation flags for each OS"
echo ""

echo "=== Test on Linux ==="
echo "Run these commands on Linux:"
echo "1. sudo apt-get install libx11-dev libxext-dev"
echo "2. make clean"
echo "3. make"
echo "4. ./cub3D maps/test.cub"
echo ""

echo "=== Expected Output ==="
echo "On Linux, you should see:"
echo "- Setting up Linux minilibx..."
echo "- Compilation with -lmlx -lXext -lX11 flags"
echo "- Successful binary creation"
echo ""
