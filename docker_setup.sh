#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== cub3D Linux Docker Setup ===${NC}"

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo -e "${RED}❌ Docker is not installed. Please install Docker Desktop first.${NC}"
    echo "Visit: https://www.docker.com/products/docker-desktop"
    exit 1
fi

# Check if Docker is running
if ! docker info &> /dev/null; then
    echo -e "${RED}❌ Docker is not running. Please start Docker Desktop.${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Docker is available and running${NC}"

# Build the Docker image
echo -e "${YELLOW}🔨 Building Docker image...${NC}"
docker build -t cub3d-linux .

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Docker image built successfully${NC}"
else
    echo -e "${RED}❌ Failed to build Docker image${NC}"
    exit 1
fi

echo ""
echo -e "${BLUE}=== Usage Instructions ===${NC}"
echo ""
echo -e "${YELLOW}1. Basic Linux compatibility test (no GUI):${NC}"
echo "   docker run -it --rm cub3d-linux"
echo ""
echo -e "${YELLOW}2. With GUI support (requires XQuartz on macOS):${NC}"
echo "   docker run -it --rm -e DISPLAY=host.docker.internal:0 cub3d-linux"
echo ""
echo -e "${YELLOW}3. Interactive shell:${NC}"
echo "   docker run -it --rm cub3d-linux bash"
echo ""
echo -e "${YELLOW}4. Run specific test:${NC}"
echo "   docker run -it --rm cub3d-linux ./test_linux_compatibility.sh"
echo ""
echo -e "${BLUE}=== GUI Setup for macOS ===${NC}"
echo ""
echo "For GUI testing, you need to install XQuartz:"
echo "1. Install XQuartz: brew install --cask xquartz"
echo "2. Start XQuartz: open -a XQuartz"
echo "3. Allow connections from network clients in XQuartz preferences"
echo "4. Run: xhost +localhost"
echo "5. Then use the GUI command above"
echo ""
echo -e "${GREEN}✅ Setup complete!${NC}"
