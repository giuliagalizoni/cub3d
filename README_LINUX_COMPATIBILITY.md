# Linux Compatibility Guide for cub3D

## Overview
This project now supports both macOS and Linux automatically. The Makefile detects the operating system and uses the appropriate minilibx version and compilation flags.

## Current Status ✅
- **✅ Automatic OS Detection** - Makefile detects macOS vs Linux
- **✅ Correct Library Selection** - Uses appropriate minilibx version
- **✅ Proper Compilation Flags** - X11 for Linux, OpenGL for macOS
- **✅ Library Extraction** - Automatic extraction of minilibx archives
- **✅ Cross-platform Testing** - Test script validates setup

## Automatic Setup

### What Happens Automatically
1. **OS Detection**: `uname -s` determines if you're on Darwin (macOS) or Linux
2. **Library Selection**: 
   - macOS: `minilibx_opengl_20191021`
   - Linux: `minilibx-linux`
3. **Compilation Flags**:
   - macOS: `-framework OpenGL -framework AppKit`
   - Linux: `-lmlx -lXext -lX11`
4. **Library Extraction**: Automatically extracts the correct minilibx archive

### Compilation Commands
```bash
# Clean and compile (recommended)
make clean && make

# Or just compile
make
```

## Linux Requirements

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libx11-dev libxext-dev gcc make
```

### CentOS/RHEL/Fedora
```bash
sudo yum install libX11-devel libXext-devel gcc make
# or for newer versions:
sudo dnf install libX11-devel libXext-devel gcc make
```

### Arch Linux
```bash
sudo pacman -S libx11 libxext gcc make
```

## File Structure
```
library/
├── minilibx_opengl_20191021/  # macOS version (OpenGL)
├── minilibx-linux/            # Linux version (X11)
├── minilibx_macos_opengl.tgz  # macOS archive
├── minilibx_macos_metal.tgz   # macOS Metal archive
└── minilibx-linux.tgz         # Linux archive
```

## Makefile Configuration

### OS Detection
```makefile
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS settings
    MLX_DIR = library/minilibx_opengl_20191021
    MLX_FLAGS = -framework OpenGL -framework AppKit
else
    # Linux settings
    MLX_DIR = library/minilibx-linux
    MLX_FLAGS = -lmlx -lXext -lX11
endif
```

### Automatic Library Setup
```makefile
setup_mlx:
ifeq ($(UNAME_S),Darwin)
    @if [ ! -d "$(MLX_DIR)" ]; then \
        echo "Setting up macOS minilibx..."; \
        cd library && tar -xzf minilibx_macos_opengl.tgz; \
    fi
else
    @if [ ! -d "$(MLX_DIR)" ]; then \
        echo "Setting up Linux minilibx..."; \
        cd library && tar -xzf minilibx-linux.tgz; \
    fi
endif
    @make -C $(MLX_DIR) 2>/dev/null || echo "minilibx already compiled"
```

## Testing

### Run Compatibility Test
```bash
./test_linux_compatibility.sh
```

### Manual Testing
```bash
# Test compilation
make clean && make

# Test execution
./cub3D maps/simplemap.cub

# Test with different map files
./cub3D your_map.cub
```

## Troubleshooting

### Common Linux Issues

#### 1. Missing X11 Libraries
```
/usr/bin/ld: cannot find -lX11
```
**Solution**: Install X11 development libraries
```bash
sudo apt-get install libx11-dev libxext-dev
```

#### 2. Permission Issues
```
X11 connection rejected
```
**Solution**: 
- For remote connections: `ssh -X user@server`
- For local display: `export DISPLAY=:0`

#### 3. Minilibx Not Found
```
cannot find -lmlx
```
**Solution**: Ensure minilibx is compiled
```bash
make clean && make
```

#### 4. Compilation Warnings
Linux minilibx may show warnings about deprecated function declarations. These are normal and don't affect functionality.

### Debugging Steps

1. **Check OS Detection**:
   ```bash
   uname -s
   ```

2. **Verify Library Presence**:
   ```bash
   ls -la library/
   ```

3. **Test Minilibx Compilation**:
   ```bash
   cd library/minilibx-linux
   make clean && make
   cd ../..
   ```

4. **Check Compilation Flags**:
   ```bash
   make clean
   make V=1  # Verbose output
   ```

## Performance Notes

### Linux vs macOS
- **Linux**: Uses X11 window system, generally good performance
- **macOS**: Uses native OpenGL, optimized for Apple hardware

### Memory Usage
- Both versions use similar memory footprints
- Linux version may have slightly higher initial overhead due to X11

## Development Workflow

### For Linux Development
1. Ensure X11 libraries are installed
2. Use `make clean && make` for fresh compilation
3. Test with `./test_linux_compatibility.sh`
4. Run with `./cub3D your_map.cub`

### For Cross-platform Development
1. Test on both macOS and Linux
2. Use the compatibility test script
3. Ensure both minilibx versions are available
4. Check that OS detection works correctly

## Future Improvements

### Potential Enhancements
- [ ] Add Wayland support for modern Linux systems
- [ ] Implement Metal backend for macOS
- [ ] Add Vulkan support for cross-platform graphics
- [ ] Improve error handling for missing libraries

### Monitoring
- Watch for minilibx updates
- Monitor X11 deprecation in favor of Wayland
- Track macOS OpenGL deprecation in favor of Metal

## Support

If you encounter issues:
1. Run the compatibility test script
2. Check the troubleshooting section
3. Verify your system meets the requirements
4. Ensure all dependencies are installed

## Version History

- **v1.0**: Initial Linux compatibility
- **v1.1**: Automatic OS detection
- **v1.2**: Improved error handling
- **v1.3**: Added compatibility test script
