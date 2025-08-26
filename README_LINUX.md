# Linux Compatibility Setup for cub3D

## Overview
This project now supports both macOS and Linux automatically. The Makefile detects the operating system and uses the appropriate minilibx version and compilation flags.

## Automatic Setup
The Makefile automatically:
1. Detects your operating system (`uname -s`)
2. Extracts the appropriate minilibx version
3. Uses the correct compilation flags
4. Links the necessary libraries

## Linux Requirements

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libx11-dev libxext-dev
```

### CentOS/RHEL/Fedora
```bash
sudo yum install libX11-devel libXext-devel
# or for newer versions:
sudo dnf install libX11-devel libXext-devel
```

### Arch Linux
```bash
sudo pacman -S libx11 libxext
```

## Compilation

### Automatic (Recommended)
```bash
make clean
make
```

### Manual Linux Setup
If automatic detection fails:
```bash
# Extract Linux minilibx
cd library
tar -xzf minilibx-linux.tgz
cd ..

# Compile with Linux flags
make clean
make
```

## OS Detection
The Makefile uses:
```makefile
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS settings
    MLX_FLAGS = -framework OpenGL -framework AppKit
else
    # Linux settings
    MLX_FLAGS = -lmlx -lXext -lX11
endif
```

## Troubleshooting

### Common Linux Issues

1. **OpenGL headers not found**
   ```
   fatal error: OpenGL/gl3.h: No such file or directory
   ```
   **Solution**: This happens when macOS minilibx is used on Linux. The fixed Makefile now automatically uses the correct version.
   ```bash
   make clean
   make
   ```

2. **Missing X11 libraries**
   ```
   /usr/bin/ld: cannot find -lX11
   ```
   **Solution**: Install X11 development libraries
   ```bash
   sudo apt-get install libx11-dev libxext-dev
   ```

2. **Permission denied**
   ```
   X11 connection rejected
   ```
   **Solution**: Run with X11 forwarding or use a local display
   ```bash
   # For remote connections
   ssh -X user@server
   
   # For local display
   export DISPLAY=:0
   ```

3. **Minilibx not found**
   ```
   cannot find -lmlx
   ```
   **Solution**: Ensure minilibx is compiled
   ```bash
   make clean
   make
   ```

### Testing
Run the test script to verify compatibility:
```bash
./test_linux.sh
```

## File Structure
```
library/
├── minilibx_opengl_20191021/  # macOS version
├── minilibx-linux/            # Linux version (auto-extracted)
├── minilibx_macos_opengl.tgz  # macOS archive
├── minilibx_macos_metal.tgz   # macOS Metal archive
└── minilibx-linux.tgz         # Linux archive
```

## Compilation Flags by OS

### macOS
- `-framework OpenGL -framework AppKit`
- Uses OpenGL framework
- Native macOS graphics

### Linux
- `-lmlx -lXext -lX11`
- Uses X11 window system
- Cross-platform compatibility

## Notes
- The project automatically handles OS detection
- No manual configuration required
- Both versions of minilibx are included
- Clean compilation on both platforms
