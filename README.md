# Monitor File Activities of Dynamically Linked Programs

## Requirements
### Program Arguments
Your program should work with the following arguments:
```
usage: ./logger [-o file] [-p sopath] [--] cmd [cmd args ...]       
    -p: set the path to logger.so, default = ./logger.so            
    -o: print output to file, print to "stderr" if no file specified
    --: separate the arguments for logger and for the command       
```
The message should be displayed if an invalid argument is passed to the logger.
### Monitored file access activities
The list of monitored library calls is shown below.
||||||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|chmod|chown|close|creat|fclose|fopen|fread|
|fwrite|open|read|remove|rename|tmpfile|write|
