Lesson Flow
1. fave-100 go through
	1. need to consider offsets (from hint's leaked addr, use that to calculate the base offset)
2. tools/techniques
	1. remote VMs can git clone Ian repo directly and git pull
		1. removes need to scp files to VM
	2. pointers are 8 bytes (64 bits) - because pointers hold memory addr (8 bytes), so the pointer needs to have 8 byte capacity 
3. structure
	1. in decompiled code, tends to look complicated
		1. shift bits, add address of sth, deref the whole thing...
			1. ^ actually it's indexing an array containing a bunch of these structs
			2. That's the decompiler attempting to translate the block of memory that contains the entire structure
	2. in disassembly
	3. consider these factors
		1. is the struct storing the data itself? or a pointer to the data?
			1. this affects how much memory the struct occupies
		2. how to figure out size
			1. every time you add a new instance of the struct to some array (say you are storing all your instances of this struct in an array), notice how much more memory the array takes up - the difference is the # bytes of the struct 
	4. example
		1. struct student
			1. name
			2. age 
			3. grade
4. SAT solvers
	1. purpose: you need to give certain inputs s.t. the inputs fulfil a condition, past which we pass a gated condition
		1. give SAT solver conditions that need to be fulfilled to output TRUE
		2. SAT solver will work out what inputs need to be used
	2. SAT solvers we use 
		1. 


## Recitation
Rec 3.0
- structure character (video game)
	- name
	- total hit pts
	- total attack
	- total defense
	- total mana
- size of character
	- 0x44 
	- how do we know? malloc heap is allocating 0x44 bytes on the heap when a new character is created
		- 0000159e      create_character(new_character: malloc(bytes: 0x44))
- as user creates new character, get_num() is being called to receive user input

