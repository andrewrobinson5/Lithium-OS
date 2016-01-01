.set ALIGN,   1<<0
.set MEMINFO,   1<<1
.set GRAPH,     1<<2
.set FLAGS,   ALIGN | MEMINFO | GRAPH
.set MAGIC,   0x1BADB002
.set CHECKSUM,    -(MAGIC + FLAGS)
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0, 0, 0, 0, 0
.long 0 # 0 = set graphics mode
.long 1024, 768, 32 # Width, height, depth
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
.section .text
.global _start
.type _start, @function
_start:
cli
movl $stack_top, %esp
push %ebx
call kernel_main #Replace with your kernel main function.
hlt

.Lhang:
jmp .Lhang
.size _start, . - _start
