##########################
#Working Code - No GDT
##########################
#.set ALIGN,   1<<0
#.set MEMINFO,   1<<1
#.set GRAPH,     1<<2
#.set FLAGS,   ALIGN | MEMINFO | GRAPH
#.set MAGIC,   0x1BADB002
#.set CHECKSUM,    -(MAGIC + FLAGS)
#.align 4
#.long MAGIC
#.long FLAGS
#.long CHECKSUM
#.long 0, 0, 0, 0, 0
#.long 0 # 0 = set graphics mode
#.long 1024, 768, 4 # Width, height, depth
#.section .bootstrap_stack, "aw", @nobits
#stack_bottom:
#.skip 16384 # 16 KiB
#stack_top:
#.section .text
#.global _start
#.type _start, @function
#_start:
#cli
#movl $stack_top, %esp
#push %ebx
#call kernel_main #Replace with your kernel main function.
#hlt
#
#.Lhang:
#jmp .Lhang
#.size _start, . - _start

##########################
#Bad Code - GDT should work
##########################
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
movl $stack_top, %esp
# Finish installing the Task Switch Segment into the Global Descriptor Table.
movl $tss, %ecx
movw %cx, gdt + 0x28 + 2
shrl $16, %ecx
movb %cl, gdt + 0x28 + 4
shrl $8, %ecx
movb %cl, gdt + 0x28 + 7
# Load the Global Descriptor Table pointer register.
subl $6, %esp
movw gdt_size_minus_one, %cx
movw %cx, 0(%esp)
movl $gdt, %ecx
movl %ecx, 2(%esp)
lgdt 0(%esp)
addl $6, %esp
# Switch cs to the kernel code segment (0x08).
push $0x08
push $1f
retf
1:
# Switch ds, es, fs, gs, ss to the kernel data segment (0x10).
movw $0x10, %cx
movw %cx, %ds
movw %cx, %es
movw %cx, %fs
movw %cx, %gs
movw %cx, %ss
# Switch the task switch segment register to the task switch segment (0x28).
movw $(0x28 /* TSS */ | 0x3 /* RPL */), %cx
ltr %cx
# Call the global constructors.
call _init	
# Transfer control to the main kernel.
call kernel_main
# Hang if kernel_main unexpectedly returns.
cli

.Lhang:
jmp .Lhang
.size _start, . - _start
