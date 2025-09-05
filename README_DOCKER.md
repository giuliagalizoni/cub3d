# Docker Linux Environment for cub3D

## Overview
This Docker setup allows you to test the cub3D project in a Linux environment on macOS, ensuring cross-platform compatibility.

## Quick Start

### 1. Setup Docker Environment
```bash
# Build the Docker image
./docker_setup.sh
```

### 2. Run Linux Tests
```bash
# Run comprehensive Linux compatibility tests
./test_docker_linux.sh
```

## Docker Commands

### Basic Usage
```bash
# Start Linux environment with welcome message
docker run -it --rm cub3d-linux

# Start interactive shell
docker run -it --rm cub3d-linux bash

# Run specific test
docker run -it --rm cub3d-linux ./test_linux_compatibility.sh

# Compile and test
docker run -it --rm cub3d-linux bash -c "make clean && make && ./cub3D maps/simplemap.cub"
```

### GUI Testing (macOS)
For GUI testing, you need XQuartz:

1. **Install XQuartz**:
   ```bash
   brew install --cask xquartz
   ```

2. **Start XQuartz**:
   ```bash
   open -a XQuartz
   ```

3. **Allow network connections**:
   - Open XQuartz preferences
   - Go to Security tab
   - Check "Allow connections from network clients"

4. **Allow local connections**:
   ```bash
   xhost +localhost
   ```

5. **Run with GUI support**:
   ```bash
   docker run -it --rm -e DISPLAY=host.docker.internal:0 cub3d-linux
   ```

## Docker Image Details

### Base Image
- **OS**: Ubuntu 22.04 LTS
- **Architecture**: x86_64 (will run on Apple Silicon via emulation)

### Installed Packages
- `gcc` - C compiler
- `make` - Build tool
- `libx11-dev` - X11 development libraries
- `libxext-dev` - X11 extension libraries
- `x11-apps` - X11 applications
- `xvfb` - Virtual framebuffer
- `valgrind` - Memory debugging
- `gdb` - Debugger
- `git` - Version control
- `vim` - Text editor

### Environment
- **User**: `developer` (non-root)
- **Working Directory**: `/workspace`
- **Display**: Configured for X11 forwarding

## Testing Scenarios

### 1. Compilation Test
```bash
docker run -it --rm cub3d-linux bash -c "
    cd /workspace
    make clean && make
    echo 'Compilation successful!'
"
```

### 2. Compatibility Test
```bash
docker run -it --rm cub3d-linux bash -c "
    cd /workspace
    ./test_linux_compatibility.sh
"
```

### 3. Program Execution Test
```bash
docker run -it --rm cub3d-linux bash -c "
    cd /workspace
    make clean && make
    timeout 10s ./cub3D maps/simplemap.cub
"
```

### 4. Interactive Development
```bash
docker run -it --rm cub3d-linux bash
# Now you're in a Linux shell with all tools available
```

## Troubleshooting

### Common Issues

#### 1. Docker Not Running
```bash
# Start Docker Desktop
open -a Docker
```

#### 2. Permission Issues
```bash
# If you get permission errors, ensure Docker is running
docker info
```

#### 3. GUI Not Working
- Ensure XQuartz is installed and running
- Check XQuartz security settings
- Run `xhost +localhost` before starting Docker

#### 4. Build Failures
```bash
# Clean and rebuild Docker image
docker rmi cub3d-linux
./docker_setup.sh
```

#### 5. Network Issues
```bash
# If you can't download packages, check your internet connection
docker run --rm ubuntu:22.04 ping -c 3 google.com
```

### Debugging

#### Check Docker Image
```bash
# List images
docker images

# Inspect image
docker inspect cub3d-linux
```

#### Check Container
```bash
# Run container with verbose output
docker run -it --rm cub3d-linux bash -c "uname -a && gcc --version"
```

#### Check File System
```bash
# Verify project files are copied
docker run -it --rm cub3d-linux bash -c "ls -la /workspace/"
```

## Performance Notes

### Apple Silicon (M1/M2) Macs
- Docker runs via emulation on Apple Silicon
- Compilation may be slower than native
- GUI performance may be reduced

### Intel Macs
- Native performance
- Full compatibility with Linux binaries

## Development Workflow

### Daily Testing
1. Make changes to your code
2. Run `./test_docker_linux.sh` to test Linux compatibility
3. Fix any Linux-specific issues
4. Commit changes

### Continuous Integration
```bash
# Automated testing script
#!/bin/bash
./test_docker_linux.sh
if [ $? -eq 0 ]; then
    echo "Linux compatibility tests passed"
    exit 0
else
    echo "Linux compatibility tests failed"
    exit 1
fi
```

## Advanced Usage

### Custom Docker Commands
```bash
# Mount current directory for development
docker run -it --rm -v $(pwd):/workspace cub3d-linux bash

# Run with specific environment variables
docker run -it --rm -e CC=gcc -e CFLAGS="-O2" cub3d-linux bash

# Run with memory limits
docker run -it --rm --memory=2g cub3d-linux bash
```

### Building Custom Images
```bash
# Build with different base image
docker build -t cub3d-linux:custom -f Dockerfile.custom .

# Build with additional packages
docker build -t cub3d-linux:dev --build-arg EXTRA_PACKAGES="clang llvm" .
```

## Cleanup

### Remove Docker Image
```bash
docker rmi cub3d-linux
```

### Remove All Unused Images
```bash
docker image prune -a
```

### Clean Docker System
```bash
docker system prune -a
```

## Support

If you encounter issues:
1. Check the troubleshooting section
2. Verify Docker is running
3. Ensure you have sufficient disk space
4. Check your internet connection
5. Try rebuilding the Docker image

## Version History

- **v1.0**: Initial Docker setup
- **v1.1**: Added GUI support
- **v1.2**: Improved testing scripts
- **v1.3**: Added comprehensive documentation
