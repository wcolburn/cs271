// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@SCREEN
D=A
@0
M=D               // A[0] == @SCREEN
@24576
D=A
@1
M=D               // A[1] == 24576
@2
M=0               // A[2] == Screen is White (0) or Black (1)
(WhitenScreen)
	@2
	D=M
	@MainLoop
	D;JEQ		  // If screen already white, skip

	@0
	D=M
	A=D           // Load D to be memory location
	M=0           // Set memory location to be white
	@0
	M=M+1         // Increment memory location

	D=M
	@1
	D=M-D         // Keyboard - Memory Address
	@WhitenScreen
    D;JGT
    @2
    M=0
(MainLoop)
	@SCREEN
	D=A
	@0
	M=D 

	@24576
	D=M
	@WhitenScreen
	D;JEQ				// If keyboard input is 0, repeat
	@2
	D=M
	@MainLoop
	M;JGT				// If A[2] == 1 (screen is black) keep waiting until change

	@SCREEN
	D=A
	@0
	M=D                 // Set A[0] back to @SCREEN
(BlackenScreen)
	@2
	M=1

	@0
	D=M
	A=D
	M=-1				// -1 = 1111111111111111
	@0
	M=M+1

	D=M
	@1
	D=M-D
	@MainLoop
	D;JEQ
	@BlackenScreen
	0;JMP
(End)
	@End
	0;JMP