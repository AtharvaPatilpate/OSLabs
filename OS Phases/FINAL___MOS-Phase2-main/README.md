### INTERRUPT VALUES

SI = 1 on GD

= 2 on PD

= 3 on H

TI = 2 on Time Limit Exceeded

PI = 1 Operation Error

= 2 Operand Error

= 3 Page Fault

### Error Message Coding:

0 No Error

1 Out of Data

2 Line Limit Exceeded

3 Time Limit Exceeded

4 Operation Code Error

5 Operand Error

6 Invalid Page Fault

### MOS (MASTER MODE)

#### Case TI and SI of

TI SI Action

0 1 READ

0 2 WRITE

0 3 TERMINATE (0)

2 1 TERMINATE (3)

2 2 WRITE, THEN TERMINATE (3)

2 3 TERMINATE (0)

#### Case TI and PI of

TI PI Action

0 1 TERMINATE (4)

0 2 TERMINATE (5)

0 3 If Page Fault Valid, ALLOCATE, update page Table, Adjust IC if necessary,
EXECUTE USER PROGRAM
OTHERWISE TERMINATE (6)

2 1 TERMINATE (3,4)

2 2 TERMINATE (3,5)

2 3 TERMINATE (3)

pi=1 ti=0 opcode ti=2 time and opcode
pi=2 ti=0 operand ti=2 time and operand
pi=3 ti=0 invalid ti=2 time

si=1 ti=0 read ti=2 time
si=2 ti=0 write ti=2 time
si=3 ti=0 no error
