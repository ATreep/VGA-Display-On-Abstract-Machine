# VGA Display on Abstract Machine
## 效果图
![Screenshot](./screenshot.png)

## 启动示例
编辑根目录的 [Makefile](./Makefile)，根据你的环境修改 AM_HOME 与 CROSS_COMPILE。

在根目录打开终端运行：
```sh
make log
make run
```

调试 `boot.o`:
```sh
make debug  # 默认为 LLDB，如果使用 GDB 请修改根目录 Makefile 与 debug.py
```

## 说明
此项目 fork 于 [ProjectN/abstract-machine](https://github.com/NJU-ProjectN/abstract-machine)，对原有项目进行微小的改进，使之支持串行打印 `print` 与在 VGA 文本模式下显示文本 `print_vga`。
具体实现参见 [klib/src/stdio.c](abstract-machine/klib/src/stdio.c)。

另外，本人使用的环境是 Musl Cross Toolchain，其对应的 GCC 工具名称为 `x86_64-linux-musl-gcc`，因此对项目的部分 Makefile 与部分不兼容代码做了相应适配（gnu gcc 下应该照样可用，但是没有测试，仅猜测！如果 gnu gcc 下出现问题欢迎告诉我！）。

仅实验了 x86 架构，其他架构没有做修改。

## 原理
因为本项目旨在 VGA 文本模式下显示内容，因此在汇编层面做了修改，参见：[am/src/x86/qemu/boot/start.S](abstract-machine/am/src/x86/qemu/boot/start.S)。在 CPU 保护模式下，程序无法直接修改 0xB8000 处的数据，因此通过 GDT 映射到 GS 寄存器，后续只需要操作寄存器数据即可控制 VGA 显示的内容。

## 文件修改记录
对比原项目（[abstract-machine](https://github.com/NJU-ProjectN/abstract-machine)），此项目修改了如下文件：
| File  | Comment |
|-------|-----|
| am/src/x86/x86.h | 333 行的 rdtsc 函数中修改了左移逻辑以适配 MUSL GCC  |
| am/src/x86/qemu/boot/genboot.py   | 本人测试时，由于原先使用 python 生成 bootblock.o 的方法无法正确拷贝 MBR 数据，因此改为使用 Makefile 生成 |
| am/src/x86/qemu/boot/Makefile   | 见上一条  |
| am/src/x86/qemu/boot/start.S | 进入 VGA 文本模式并设置 GDT 映射 |
| klib/include/klib.h | 添加 `print` 与 `print_vga` 函数签名 |
| klib/src/stdio.c | `print` 与 `print_vga` 函数实现|
| scripts/isa/x86_64.mk | 删除指定的 CROSS_COMPILE 变量|
| scripts/isa/x86.mk | 删除 CROSS_COMPILE 变量与 --param=min-pagesize=0 (MUSL GCC 不支持此参数) |
