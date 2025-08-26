# Use Ubuntu 22.04 as base image
FROM ubuntu:22.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV DISPLAY=:0

# Install system dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    gdb \
    libx11-dev \
    libxext-dev \
    x11-apps \
    xvfb \
    git \
    vim \
    curl \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m -s /bin/bash developer
RUN echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set working directory
WORKDIR /workspace

# Copy the project files
COPY . /workspace/

# Change ownership to developer
RUN chown -R developer:developer /workspace

# Switch to developer user
USER developer

# Set up environment for X11 forwarding (for GUI applications)
ENV DISPLAY=host.docker.internal:0

# Create a startup script
RUN echo '#!/bin/bash\n\
echo "=== Linux Docker Environment for cub3D ==="\n\
echo "OS: $(uname -s)"\n\
echo "Architecture: $(uname -m)"\n\
echo "Working directory: $(pwd)"\n\
echo ""\n\
echo "Available commands:"\n\
echo "  make clean && make    - Compile the project"\n\
echo "  ./cub3D maps/simplemap.cub  - Run the program"\n\
echo "  ./test_linux_compatibility.sh  - Run compatibility test"\n\
echo "  bash                  - Start a new shell"\n\
echo ""\n\
echo "Note: For GUI testing, run with X11 forwarding:"\n\
echo "  docker run -it --rm -e DISPLAY=host.docker.internal:0 cub3d-linux"\n\
echo ""\n\
bash' > /workspace/start.sh && chmod +x /workspace/start.sh

# Default command
CMD ["/workspace/start.sh"]
