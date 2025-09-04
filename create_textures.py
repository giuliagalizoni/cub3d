#!/usr/bin/env python3
"""
创建简单的测试纹理用于cub3D项目
"""

from PIL import Image, ImageDraw
import os

def create_simple_texture(size, color, pattern=None, filename=None):
    """创建简单的纹理"""
    img = Image.new('RGB', (size, size), color)
    draw = ImageDraw.Draw(img)
    
    if pattern == 'stripes':
        # 创建条纹图案
        for i in range(0, size, 20):
            draw.rectangle([0, i, size, i+10], fill=(255, 255, 255))
    elif pattern == 'checker':
        # 创建棋盘图案
        for y in range(0, size, 40):
            for x in range(0, size, 40):
                if (x // 40 + y // 40) % 2 == 0:
                    draw.rectangle([x, y, x+40, y+40], fill=(255, 255, 255))
    elif pattern == 'gradient':
        # 创建渐变图案
        for y in range(size):
            intensity = int(255 * y / size)
            draw.line([(0, y), (size, y)], fill=(intensity, intensity, intensity))
    
    return img

def create_directional_textures():
    """创建方向性纹理"""
    textures = {}
    
    # North texture - 红色，带白色条纹
    north = create_simple_texture(64, (200, 50, 50), 'stripes')
    textures['north'] = north
    
    # South texture - 绿色，带白色条纹
    south = create_simple_texture(64, (50, 200, 50), 'stripes')
    textures['south'] = south
    
    # East texture - 蓝色，带白色条纹
    east = create_simple_texture(64, (50, 50, 200), 'stripes')
    textures['east'] = east
    
    # West texture - 黄色，带白色条纹
    west = create_simple_texture(64, (200, 200, 50), 'stripes')
    textures['west'] = west
    
    return textures

def create_test_textures():
    """创建测试纹理"""
    textures = {}
    
    # 创建不同图案的纹理用于测试
    textures['north'] = create_simple_texture(64, (255, 100, 100), 'stripes')
    textures['south'] = create_simple_texture(64, (100, 255, 100), 'checker')
    textures['east'] = create_simple_texture(64, (100, 100, 255), 'gradient')
    textures['west'] = create_simple_texture(64, (255, 255, 100), 'stripes')
    
    return textures

def save_as_xpm(img, filename):
    """将PIL图像保存为XPM格式"""
    # 转换为PPM格式然后转换为XPM
    temp_ppm = filename.replace('.xpm', '_temp.ppm')
    img.save(temp_ppm, 'PPM')
    
    # 使用ImageMagick转换（如果可用）
    try:
        os.system(f'convert {temp_ppm} {filename}')
        os.remove(temp_ppm)
        print(f"Created {filename}")
    except:
        print(f"Failed to create {filename}, keeping PPM format")
        os.rename(temp_ppm, filename.replace('.xpm', '.ppm'))

def create_simple_xpm(size, color, pattern, filename):
    """直接创建简单的XPM文件"""
    # 创建简单的XPM内容
    xpm_content = f'/* XPM */\n'
    xpm_content += f'static char *{filename.replace(".xpm", "").replace("/", "_")}[] = {{\n'
    xpm_content += f'"/* columns rows colors chars-per-pixel */",\n'
    xpm_content += f'"{size} {size} 2 1",\n'
    xpm_content += f'"  c #000000",\n'
    xpm_content += f'". c #FFFFFF",\n'
    xpm_content += f'"/* pixels */",\n'
    
    # 根据图案生成像素数据
    for y in range(size):
        line = '"'
        for x in range(size):
            if pattern == 'stripes':
                if (x // 8) % 2 == 0:
                    line += '.'
                else:
                    line += ' '
            elif pattern == 'checker':
                if (x // 8 + y // 8) % 2 == 0:
                    line += '.'
                else:
                    line += ' '
            else:
                line += '.'
        line += '",'
        xpm_content += line + '\n'
    
    xpm_content += '};\n'
    
    with open(filename, 'w') as f:
        f.write(xpm_content)
    
    print(f"Created {filename}")

def create_colored_xpm(size, color_name, pattern, filename):
    """创建带颜色的XPM文件"""
    colors = {
        'red': '#FF0000',
        'green': '#00FF00', 
        'blue': '#0000FF',
        'yellow': '#FFFF00',
        'white': '#FFFFFF',
        'black': '#000000'
    }
    
    color_hex = colors.get(color_name, '#FFFFFF')
    
    # 创建简单的XPM内容
    xpm_content = f'/* XPM */\n'
    xpm_content += f'static char *{filename.replace(".xpm", "").replace("/", "_")}[] = {{\n'
    xpm_content += f'"/* columns rows colors chars-per-pixel */",\n'
    xpm_content += f'"{size} {size} 2 1",\n'
    xpm_content += f'"  c #000000",\n'
    xpm_content += f'". c {color_hex}",\n'
    xpm_content += f'"/* pixels */",\n'
    
    # 根据图案生成像素数据
    for y in range(size):
        line = '"'
        for x in range(size):
            if pattern == 'stripes':
                if (x // 8) % 2 == 0:
                    line += '.'
                else:
                    line += ' '
            elif pattern == 'checker':
                if (x // 8 + y // 8) % 2 == 0:
                    line += '.'
                else:
                    line += ' '
            else:
                line += '.'
        line += '",'
        xpm_content += line + '\n'
    
    xpm_content += '};\n'
    
    with open(filename, 'w') as f:
        f.write(xpm_content)
    
    print(f"Created {filename}")

def main():
    """主函数"""
    print("Creating test textures for cub3D...")
    
    # 创建assets目录（如果不存在）
    if not os.path.exists('assets'):
        os.makedirs('assets')
    
    # 创建带颜色的测试纹理
    create_colored_xpm(64, 'red', 'stripes', 'assets/north.xpm')
    create_colored_xpm(64, 'green', 'checker', 'assets/south.xpm')
    create_colored_xpm(64, 'blue', 'stripes', 'assets/east.xpm')
    create_colored_xpm(64, 'yellow', 'checker', 'assets/west.xpm')
    
    print("Test textures created successfully!")
    print("North: Red with horizontal stripes")
    print("South: Green with checker pattern")
    print("East: Blue with horizontal stripes")
    print("West: Yellow with checker pattern")

if __name__ == "__main__":
    main()
