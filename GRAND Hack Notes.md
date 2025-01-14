 # Links
- [Debugging Guide Stanford](https://web.stanford.edu/class/archive/cs/cs107/cs107.1252/resources/debugging.html)
- [GDB Guide Stanford](https://web.stanford.edu/class/archive/cs/cs107/cs107.1252/resources/gdb)
- 


# Tools

- pwntools
	- extract int (decimal) from raw bytes
		- int.from_bytes(thing_of_raw_bytes, byteorder="little")
			- little endian vs big endian: 2 ways to store bytes
				- take the number 0x12345678, let's represent them in bytes (hex rep)
				- in little endian: (the least significant byte is put first in little format)
					- 78 56 34 12
				- in big endian: (the most significant byte is put first in big format)
					- 12 34 56 78
				- <b>x86 CPUs work in little endian byte order</b>
				- ARM machines support both big and little endian (hence called "bi-endian")
				- Fun fact: ethernet uses big endian at the byte level, but little endian at the bit level
					- binary 10100110 00110101 --> bit-reverse(10100100) bit-reverse(00110101)  --> send over in the order: 00100101 10101100 
			- 
	- BEWARE! sending raw bytes != hex in byte string
		- hex in byte string: "0x123abc"
			- a string, encoded with 0s and 1s, that spells out hex, including the 0x at the start
			- hex(num).encode()
				- num can be in hex or decimal or whatever
		- raw bytes
			- 0s and 1s that represent the number itself
			- no "0x" is encoded
			- 
		- be mindful of what they ask for: address in hex or address in raw bytes?
- (cmd) objdump -d
	- see the assembly code of a compiled binary



# Exploits
Goal: we have the compiled binary of a program. We want to exploit this binary somehow. e.g. to get protected info through digging through the binary

## Big-Pic, Mental Models
- Function calls: stack
Let's say we're within main(), and main() calls another function called A()
At first, this is handled by the `call` assembly instruction.
On the stack:
- `call` the current instruction ptr gets pushed onto the stack. This is the return addr (original next instruction to be executed after we return to main from A
- `call` updates instruction ptr to be the entry point of A()
- A: push the current rbp onto stack. This is the base ptr of main's stack frame. Done such that we know where main's stack frame is when we return to main
- A: update rbp <-- rsp; set stack base ptr to equal to current top of stack. Base of A's stack frame is now defined correctly
- B: decrement rsp to grow A's stack frame, allowing enough space to house local variables and passed-in arguments (already in )



## Stack Overflow
- you have buffers on the stack
- buffers are just arrays
- maybe that buffer is where you will store user input
- imagine the user inputs more than the buffer's capacity
- if we don't check this "overflow"(i.e. no runtime bounds checking) and allow it to happen, user input will overwrite data in memory regions outside this 
	- things they write might be malicious code

- only langs that don't do runtime bounds checking are vulnerable to stack overflow
	- e.g. C, C++
	- Python and Java have runtime checking, so CANNOT be attacked with stack overflow. 
	- 