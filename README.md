# Rshell

##About the Program
This is a program that has been designed to run commands like Bash. The program
runs until the user enters the command `exit`, it will not exit until it sees that command.
The program now includes a ls program that works almost like the built in GNU ls command.
It only supports 3 flags `-a    -l      -R`
You can call it on directories and files as well.

##How to Install the Program:
From your terminal run the following:
`$ git clone http://github.com/vgarc018/rshell.git`
`$ cd rshell`
`$ make `
`$ bin/rshell or bin/ls`

and you will be ready to run the program.

##Known Bugs:
Rshell
1. If you type in ;;;;;;;;&&&&&&&||||||||||| you will get a segmentation fault.
2. If you pass in the command true && true || false you will get a memory error

ls
1. The output of the items are not in alphabetical order like the GNU built in command.
    (it does not make the readability bad though)
2. When you can the -R flag on a file name it gives you a Stat error and Segmentation fault.


Any bug you run into would be apprecaited if fixed.


