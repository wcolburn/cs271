// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@2
M=0
@1
D=M
@3
M=D
(Multiplication)
    @3
    D=M
    @End    
    D;JEQ              // If i == 0, End
    @0
    D=M
    @2                 // Add R0 to result
    M=M+D
    @3                 // i-1
    M=M-1
    @Multiplication   // Repeat
    0;JMP
(End)
    @End
    0;JMP