Date: Nov 23, 2024
Username: arcticBleu

# reverse engineering
### packed (100)
- Given: a stripped binary called "a.out"
	- no debugging symbols - can't run GDB on this
- Test run:
	- Prompted for flag
	- User enters something
	- "Wrong." > Exit program
- Brainstorm:
	- Use binja. I rmb one class was on statically debugging stripped binaries. 
	- 