# Cub3D Linux 兼容性说明

## 概述
这个项目现在支持Linux和macOS系统，会自动检测操作系统并使用相应的minilibx版本。

## 系统要求

### Linux
- X11开发库
- 安装命令：`sudo apt-get install libx11-dev libxext-dev`

### macOS
- 系统自带的OpenGL和AppKit框架

## 编译

### 自动编译（推荐）
```bash
make re
```
系统会自动检测操作系统并使用相应的配置。

### 手动编译
- Linux: `make -f Makefile.linux`
- macOS: `make -f Makefile.macos`

## 运行
```bash
./cub3D maps/simplemap.cub
```

## 主要修改

### Makefile
- 添加了操作系统检测
- Linux使用 `library/minilibx-linux`
- macOS使用 `library/minilibx_opengl_20191021`
- 自动配置相应的链接库

### 头文件 (include/cub3d.h)
- 动态包含相应系统的mlx.h
- Linux和macOS的按键代码定义
- 自动系统检测和配置

### 窗口管理 (src/render/window.c)
- Linux使用 `mlx_key_hook` 函数
- macOS使用 `mlx_hook` 函数
- 不同系统的事件处理方式

### 兼容性特性
- Linux: 使用X11和Xext库
- macOS: 使用OpenGL和AppKit框架
- 自动头文件路径配置
- 统一的编译流程
- **按键支持**: WASD移动，方向键旋转，ESC退出

## 按键控制

### 移动控制
- **W**: 向前移动
- **S**: 向后移动
- **A**: 向左移动
- **D**: 向右移动

### 视角控制
- **左方向键**: 向左旋转
- **右方向键**: 向右旋转

### 其他
- **ESC**: 退出程序

## 故障排除

### Linux编译错误
如果遇到X11相关错误，请确保安装了开发库：
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

### 按键不响应
如果按键不响应，请确保：
1. 程序窗口处于焦点状态
2. 使用的是Linux版本的minilibx
3. 编译时没有错误

### 权限问题
确保可执行文件有执行权限：
```bash
chmod +x cub3D
```

## 测试
项目包含一个简单的测试地图：`maps/simplemap.cub`

运行测试：
```bash
./cub3D maps/simplemap.cub
```

程序应该会打开一个窗口显示3D迷宫，并且按键应该正常工作。

## 技术细节

### 按键代码映射
- Linux使用X11按键代码
- macOS使用系统按键代码
- 自动检测和映射

### 事件处理
- Linux: `mlx_key_hook` + X11事件
- macOS: `mlx_hook` + 系统事件
- 统一的回调函数接口

## OS Detection
The Makefile uses:
```makefile
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS settings
    MLX_FLAGS = -framework OpenGL -framework AppKit
else
    # Linux settings
    MLX_FLAGS = -lXext -lX11 -lm
endif
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

## Notes
- The project automatically handles OS detection
- No manual configuration required
- Both versions of minilibx are included
- Clean compilation on both platforms
