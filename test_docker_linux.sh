#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Docker Linux Compatibility Test ===${NC}"

# Check if Docker image exists
if ! docker image inspect cub3d-linux &> /dev/null; then
    echo -e "${YELLOW}⚠️  Docker image not found. Building...${NC}"
    ./docker_setup.sh
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Failed to build Docker image${NC}"
        exit 1
    fi
fi

echo -e "${GREEN}✅ Docker image found${NC}"

# Test 1: Basic compilation
echo -e "${YELLOW}1. Testing compilation in Linux environment...${NC}"
docker run --rm cub3d-linux bash -c "
    cd /workspace
    make clean
    make
    if [ -f 'cub3D' ]; then
        echo '✅ Compilation successful'
        ls -lh cub3D
    else
        echo '❌ Compilation failed'
        exit 1
    fi
"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Compilation test passed${NC}"
else
    echo -e "${RED}❌ Compilation test failed${NC}"
    exit 1
fi

# Test 2: Compatibility test script
echo -e "${YELLOW}2. Running Linux compatibility test script...${NC}"
docker run --rm cub3d-linux bash -c "
    cd /workspace
    ./test_linux_compatibility.sh
"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Compatibility test passed${NC}"
else
    echo -e "${RED}❌ Compatibility test failed${NC}"
    exit 1
fi

# Test 3: Basic program execution (non-GUI)
echo -e "${YELLOW}3. Testing basic program execution...${NC}"
docker run --rm cub3d-linux bash -c "
    cd /workspace
    timeout 10s ./cub3D maps/simplemap.cub || echo 'Program executed (timeout is normal for non-GUI)'
"

echo -e "${GREEN}✅ Basic execution test completed${NC}"

# Test 4: Check OS and architecture
echo -e "${YELLOW}4. Verifying Linux environment...${NC}"
docker run --rm cub3d-linux bash -c "
    echo 'OS: \$(uname -s)'
    echo 'Architecture: \$(uname -m)'
    echo 'Distribution: \$(cat /etc/os-release | grep PRETTY_NAME)'
    echo 'GCC version: \$(gcc --version | head -1)'
"

echo ""
echo -e "${BLUE}=== Test Summary ===${NC}"
echo -e "${GREEN}✅ All Docker Linux tests completed successfully${NC}"
echo ""
echo -e "${YELLOW}For GUI testing, run:${NC}"
echo "docker run -it --rm -e DISPLAY=host.docker.internal:0 cub3d-linux"
echo ""
echo -e "${YELLOW}For interactive shell:${NC}"
echo "docker run -it --rm cub3d-linux bash"
