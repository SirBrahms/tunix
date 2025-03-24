# 03 - KIS
KIS, which stands for Kernel Integrated Shell, is a barebones kernelmode shell program, which serves to interactively test OS-Functionality in absence of usermode. It interfaces directly with the FAT32 and TTY drivers to deliver output. 
## Members
KIS.h exposes the following Members:<br>
### char current_cmd[128]
```c
char current_cmd[128];
```
- Purpose: Stores the current command
### size_t cmd_index
```c
size_t cmd_index;
```
- Purpose: Stores the index of the next writable slot in current_cmd

### KIS()
```c
void KIS();
```
- Purpose: Starts the shell Main Loop and stores commands (which it takes in via serial) in current_cmd
- Parameters: None
- Return Value: Void
### interpret()
```c
int interpret()
```
- Purpose: Interprets the command stored in ```current_cmd```
- Parameters: None
- Return Value: 0 if the Main Loop should continue, 1 if a break has been requested<br>
### ls()
```c
void ls()
```
- Purpose: Gets the directory listing for the Current Cluster 
- Parameters: None
- Return Value: Void
### isysr()
```c
void isysr();
```
- Purpose: Calls interrupt 0x80, handing control to the Syscall Handler 
- Parameters: None
- Return Value: Void
### void cd()
```c
void cd();
```
- Purpose: Changes the Current Cluster based on User input 
- Parameters: None
- Return Value: Void
### void cat()
```c
void cat();
```
- Purpose: Prints the text content of the Current Cluster 
- Parameters: None
- Return Value: Void

## Commands
The KIS allows input via Serial. It is capable of executing the following commands:
- cd [DIR]: changes the directory to [DIR]
- ls: lists the contents of the current directory
- cat: lists the text contents of the current directory
    - To read a file: cd [FILE] then cat
- isr: calls the System interrupt handler
- clear: clears the terminal
- exit: exits the system
