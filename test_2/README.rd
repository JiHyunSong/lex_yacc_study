test2
------------

ref : http://isilab.kaist.ac.kr/files/File/public_html/guide/lexyacc/lex_ex.htm



COMPILE
------------
flex test.l
vagrant@precise64:~/test_2$ ls -al
total 52
drwxr-xr-x 1 vagrant vagrant   136 Dec 19 16:41 .
drwxr-xr-x 1 vagrant vagrant   680 Dec 19 16:41 ..
-rw-r--r-- 1 vagrant vagrant 47635 Dec 19 16:41 lex.yy.c
-rw-r--r-- 1 vagrant vagrant  1406 Dec 19 16:41 test.l
vagrant@precise64:~/test_2$ gcc -o test lex.yy.c -lfl



HOW TO
------------
$ ./test
jfkdsla
An identifier: jfkdsla
123.456
A float: 123.456 (123.456)
55555
An integer: 55555 (55555)
if
A keyword: if
then
A keyword: then
else
An identifier: else
123&*(
An integer: 123 (123)
Unrecognized character: &
An operator: *
Unrecognized character: (
