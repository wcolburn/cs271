// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/06/pong/Pong.asm

// The Pong game program was originally written in the high-level Jack language.
// The Jack code was then translated by the Jack compiler into VM code.
// The VM code was then translated by the VM translator into the Hack
// assembly code shown here.

@256
D=A
@SP
M=D
@133
0;JMP
@R15
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
M=0
@END_EQ
D;JNE
@SP
A=M-1
M=-1
(END_EQ)
@R15
A=M
0;JMP
@R15
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
M=0
@END_GT
D;JLE
@SP
A=M-1
M=-1
(END_GT)
@R15
A=M
0;JMP
@R15
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
M=0
@END_LT
D;JGE
@SP
A=M-1
M=-1
(END_LT)
@R15
A=M
0;JMP
@5
D=A
@LCL
A=M-D
D=M
@R13
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
D=A
@SP
M=D+1
@LCL
D=M
@R14
AM=D-1
D=M
@THAT
M=D
@R14
AM=M-1
D=M
@THIS
M=D
@R14
AM=M-1
D=M
@ARG
M=D
@R14
AM=M-1
D=M
@LCL
M=D
@R13
A=M
0;JMP
@SP
A=M
M=D
@LCL
D=M
@SP
AM=M+1
M=D
@ARG
D=M
@SP
AM=M+1
M=D
@THIS
D=M
@SP
AM=M+1
M=D
@THAT
D=M
@SP
AM=M+1
M=D
@4
D=A
@R13
D=D+M
@SP
D=M-D
@ARG
M=D
@SP
MD=M+1
@LCL
M=D
@R14
A=M
0;JMP
@0
D=A
@R13
M=D
@sys.init
D=A
@R14
M=D
@RET_ADDRESS_CALL0
D=A
@95
0;JMP
(RET_ADDRESS_CALL0)
(ball.new)
@15
D=A
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@R13
M=D
@memory.alloc
D=A
@R14
M=D
@RET_ADDRESS_CALL1
D=A
@95
0;JMP
(RET_ADDRESS_CALL1)
@SP
AM=M-1
D=M
@THIS
M=D
@ARG
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
A=M
M=D
@ARG
A=M+1
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
A=M+1
M=D
@ARG
A=M+1
A=A+1
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@10
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M
@3
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
@6
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@THIS
D=M
@11
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M
@4
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
D=M
@12
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M
@5
A=D+A
D=M
@SP
AM=M+1
A=A-1
M=D
@6
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@THIS
D=M
@13
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@SP
M=M+1
A=M-1
M=0
@THIS
D=M
@14
D=D+A
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@R13
M=D
@ball.show
D=A
@R14
M=D
@RET_ADDRESS_CALL2
D=A
@95
0;JMP
(RET_ADDRESS_CALL2)
@SP
AM=M-1
D=M
@R5
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@54
0;JMP
(ball.dispose)
@ARG
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@R13
M=D
@memory.dealloc
D=A
@R14
M=D
@RET_ADDRESS_CALL3
D=A
@95
0;JMP
(RET_ADDRESS_CALL3)
@SP
AM=M-1
D=M
@R5
M=D
@SP
M=M+1
A=M-1
M=0
@54
0;JMP
(ball.show)
@ARG
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
M=D
@SP
M=M+1
A=M-1
M=0
@SP
A=M-1
M=!M
@1
D=A
@R13
M=D
@screen.setcolor
D=A
@R14
M=D
@RET_ADDRESS_CALL4
D=A
@95
0;JMP
(RET_ADDRESS_CALL4)
@SP
AM=M-1
D=M
@R5
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@R13
M=D
@ball.draw
D=A
@R14
M=D
@RET_ADDRESS_CALL5
D=A
@95
0;JMP
(RET_ADDRESS_CALL5)
@SP
AM=M-1
D=M
@R5
M=D
@SP
M=M+1
A=M-1
M=0
@54
0;JMP
(ball.hide)
@ARG
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
M=D
@SP
M=M+1
A=M-1
M=0
@1
D=A
@R13
M=D
@screen.setcolor
D=A
@R14
M=D
@RET_ADDRESS_CALL6
D=A
@95
0;JMP
(RET_ADDRESS_CALL6)
@SP
AM=M-1
D=M
@R5
M=D
@THIS
D=M
@SP
AM=M+1
A=A-1
M=D
@1
D=A
@R13
M=D
@ball.draw
D=A
@R14
M=D
@RET_ADDRESS_CALL7
D=A
@95
0;JMP
(RET_ADDRESS_CALL7)
@SP
AM=M-1
D=M
@R5
M=D
@SP
M=M+1
A=M-1
M=0
@54
0;JMP
(ball.draw)
@ARG
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
@THIS
M=D
@THIS
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
A=M+1
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS
A=M
D=M
@SP
AM=M+1
A=A-1
M=D
@5
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D+M
@THIS
A=M+1
D=M
@SP
AM=M+1
A=A-1
M=D
@5
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D+M
@4
D=A
@R13
M=D
@screen.drawrectangle
D=A
@R14
M=D
@RET_ADDRESS_CALL8
D=A
@95
0;JMP
(RET_ADDRESS_CALL8)
@SP
