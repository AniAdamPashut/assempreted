# this pure evil project should be left unnamed
> This is a simple interpreter that runs assembly like language

yes, this is shit af. but hey, first time writing cpp so i'll take it as a win. <br>

This language has 4 registers (yeah only 4) <br>
Those are the ax, bx, cx and dx registers <br>

This is not an emulator (although I might implement one later) <br>

**I made this in one day (like 3-4 hours). It doesnt have inline arithmetic support (or pointers). this just moves some integers around. yes i know it's trash but i made it so shush** <br>

## To run:
- `make init`
- `make`
- `./assembler ./examples/xxx.bass`

## opcodes implemented:
- push, pop
- add, sub
- inc, dec
- jmp, je, cmp
- syscall - (exit, write) (only writes one char at a time)
- call, ret 


## comments

comments are inserted using `;`


it never fails to amaze me how like 7 hours ago i thought it was undoable. look at this now <br>