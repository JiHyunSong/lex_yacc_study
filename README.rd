Mini C Scanner & Parser
-------

Sample test
------
$ lex test.l
$ cc lex.yy.c -o test -ll
$ test < test.dat
 Start of LEX
Begin
identifier : num
Assignment_op
Number : 0
Semicolon
identifier : num
Assignment_op
identifier : num
Add_op
Number : 526
Semicolon
End
Dot
 End of LEX

MyScanner
------
how to compile

$ gcc myScanner.c -o myScanner

Author
-------
Authored by JiHyun Song
