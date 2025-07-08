# Word-Swap
This program takes in three arguments:
* File of readable/writable text
* Word 1
* Word 2

The contents of the file are scanned line by line and copied over to another file made by the program. If there is no instance of Word 1, then the line is copied over as is. If there is an instance of Word 1, it's replaced with Word 2 then copied over.

## Example  
Ex Input:
```
./wswap shrekScript.txt Farquaad "Homeboy David"
```
Ex Output:
```
File "shrekScript.txt" opened for reading...
File "shrekScriptWS.txt" created...
File "shrekScriptWS.txt" opened for writing...
"Shrek" was found 72 times.
The word "Shrek" was replaced by the word "Homeboy David" and written to "shrekScriptWS.txt"
```

## How to Run Program
1. Clone repository
2. Execute the makefile command
```
make
```
3. Run the executable
```
./wswap [Filename.extension] [Word 1] [Word 2]
```
