#!/usr/bin/env python3
"""
创建最简单的测试纹理
"""

def create_basic_xpm(filename, color_name):
    """创建最基本的XPM文件"""
    colors = {
        'red': '#FF0000',
        'green': '#00FF00', 
        'blue': '#0000FF',
        'yellow': '#FFFF00'
    }
    
    color_hex = colors.get(color_name, '#FFFFFF')
    
    xpm_content = f'/* XPM */\n'
    xpm_content += f'static char *{filename.replace(".xpm", "").replace("/", "_")}[] = {{\n'
    xpm_content += f'"/* columns rows colors chars-per-pixel */",\n'
    xpm_content += f'"64 64 1 1",\n'
    xpm_content += f'"  c {color_hex}",\n'
    xpm_content += f'"/* pixels */",\n'
    
    # 创建纯色纹理
    for y in range(64):
        line = '"' + ' ' * 64 + '",'
        xpm_content += line + '\n'
    
    xpm_content += '};\n'
    
    with open(filename, 'w') as f:
        f.write(xpm_content)
    
    print(f"Created {filename} with color {color_name}")

def main():
    """主函数"""
    print("Creating basic test textures...")
    
    # 创建assets目录（如果不存在）
    import os
    if not os.path.exists('assets'):
        os.makedirs('assets')
    
    # 创建纯色纹理
    create_basic_xpm('assets/north.xpm', 'red')
    create_basic_xpm('assets/south.xpm', 'green')
    create_basic_xpm('assets/east.xpm', 'blue')
    create_basic_xpm('assets/west.xpm', 'yellow')
    
    print("Basic textures created successfully!")

if __name__ == "__main__":
    main()
