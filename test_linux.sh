#!/bin/bash

echo "=== Linux Compatibility Test ==="
echo "Current OS: $(uname -s)"
echo "Architecture: $(uname -m)"
echo ""

# Test if we can detect Linux
if [ "$(uname -s)" = "Linux" ]; then
    echo "✅ Running on Linux"
    echo "Expected minilibx directory: library/minilibx-linux"
    echo "Expected flags: -lmlx -lXext -lX11"
else
    echo "✅ Running on macOS"
    echo "Expected minilibx directory: library/minilibx_opengl_20191021"
    echo "Expected flags: -framework OpenGL -framework AppKit"
fi

echo ""
echo "=== Compilation Test ==="
make clean
make

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "✅ Binary created: ./cub3D"
else
    echo "❌ Compilation failed!"
    exit 1
fi

echo ""
echo "=== Dependencies Check ==="
if [ "$(uname -s)" = "Linux" ]; then
    echo "Checking Linux dependencies..."
    if command -v x11-apps >/dev/null 2>&1; then
        echo "✅ X11 development libraries available"
    else
        echo "⚠️  X11 development libraries not found"
        echo "   Install with: sudo apt-get install libx11-dev libxext-dev"
    fi
fi

echo ""
echo "=== Test Complete ==="
