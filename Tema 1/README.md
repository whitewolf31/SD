# Welcome to Tema 1.
# Creating a minimal text editor with functionalities from VIM

Link to [Github Pages](https://github.com/whitewolf31/SD/tree/master/Tema%201)
(Ask Permissions to [whitewolf31](https://github.com/whitewolf31) (Laurentiu Ursu))

## Compiling...

`make all`

## Checking Automated Tests...

`./check.sh`

## Creating own tests...

1) `touch editor.in`
2) Add tests inside `editor.in`

## Debugging

1) Change inside `editor.c` the file inputs from `editor.in` and `editor.out` to `PATH_TO_ROOT_FOLDER/editor.in` and `PATH_TO_ROOT_FOLDER/editor.out`

2) Enjoy debugging :D

# Explaining the Project

The program is a minimal text editor which works in the following way. It will take line inputs from a file and put them inside a list. Not unlike vim, you can go into terminal mode via the `::i` command. There you have a multitude of possible commands:

gl line - Move cursor to line <br />
gc char (line) - Move cursor to certain position of the line <br />
b - delete letter before cursor <br />
d (num) - delete num of characters after the cursor. If num misses it is 1 <br />
dl line - delete certain line <br />
dw word - delete first appearance of word after cursor <br />
da word - delete every occurence of the word from the whole text <br />
re word1 word2 - replace first occurence of word1 with word2 after the cursor <br />
ra word1 word2 - replace all occurences of word1 with word2 of the whole text <br />
s - save text to output file <br />
q - quit without saving <br />
u - undo last command (Except save) <br />
r - redo last command <br />

I used lists that stored every character as a separate field. I also used a cursor which held the current node and the first node. For the undo function I used the fact that lists are awesome. Basically, if you wanted to delete something from the list. I would just remove some of the connections, but not all of them, so that when I wanted to undo, I would only have to redo those connections.

[Here](https://imgur.com/a/sqqaujT) is an image.

The same will be done with replacing, except that instead of pointing towards the next node, it will point towards the beginning of the replaced word. When we undo, we will deallocate that word.

To redo, we will just store the command and run it again.

This implementation will save a lot of time, due to not having to create a reverse function for every command.

You will find more info in the comments of the code.

Notes:
This repository has not been shared with any fellow student. It is private and I am totally against copying homeworks. I might make it public after the deadline of the homework, only if the teachers agree.