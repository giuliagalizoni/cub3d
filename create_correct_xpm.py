#!/usr/bin/env python3
"""
创建正确格式的XPM文件
"""

def create_correct_xpm(filename, color_name):
    """创建正确格式的XPM文件"""
    colors = {
        'red': '#FF0000',
        'green': '#00FF00', 
        'blue': '#0000FF',
        'yellow': '#FFFF00'
    }
    
    color_hex = colors.get(color_name, '#FFFFFF')
    
    # 创建正确格式的XPM内容
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

def create_striped_xpm(filename, color_name):
    """创建条纹纹理"""
    colors = {
        'red': '#FF0000',
        'green': '#00FF00', 
        'blue': '#0000FF',
        'yellow': '#FFFF00'
    }
    
    color_hex = colors.get(color_name, '#FFFFFF')
    
    # 创建正确格式的XPM内容
    xpm_content = f'/* XPM */\n'
    xpm_content += f'static char *{filename.replace(".xpm", "").replace("/", "_")}[] = {{\n'
    xpm_content += f'"/* columns rows colors chars-per-pixel */",\n'
    xpm_content += f'"64 64 2 1",\n'
    xpm_content += f'"  c #000000",\n'
    xpm_content += f'". c {color_hex}",\n'
    xpm_content += f'"/* pixels */",\n'
    
    # 创建条纹纹理
    for y in range(64):
        line = '"'
        for x in range(64):
            if (x // 8) % 2 == 0:
                line += '.'
            else:
                line += ' '
        line += '",'
        xpm_content += line + '\n'
    
    xpm_content += '};\n'
    
    with open(filename, 'w') as f:
        f.write(xpm_content)
    
    print(f"Created {filename} with {color_name} stripes")

def main():
    """主函数"""
    print("Creating correct XPM textures...")
    
    # 创建assets目录（如果不存在）
    import os
    if not os.path.exists('assets'):
        os.makedirs('assets')
    
    # 创建条纹纹理
    create_striped_xpm('assets/north.xpm', 'red')
    create_striped_xpm('assets/south.xpm', 'green')
    create_striped_xpm('assets/east.xpm', 'blue')
    create_striped_xpm('assets/west.xpm', 'yellow')
    
    print("XPM textures created successfully!")

if __name__ == "__main__":
    main()
