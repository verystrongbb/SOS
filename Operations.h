/*
TODO：实现以下操作的逻辑
b)	Create a file：createFile fileName fileSize  
i.e.：createFile /dir1/myFile 10 (in KB)
if fileSiz > max file size, print out an error message.
c)	Delete a file：deleteFile filename 
i.e.：deleteFile /dir1/myFile
d)	Create a directory：createDir 
i.e.：createDir /dir1/sub1 (should support nested-directory)
e)	Delete a directory：deleteDir 
i.e.:	deleteDir /dir1/sub1 （The current working directory is not allowed to be deleted）
f)	Change current working direcotry：changeDir 
i.e.: changeDir /dir2
g)	List all the files and sub-directories under current working directory：dir 
You also need to list at least two file attributes. (i.e. file size, time created, etc.)
h)	Copy a file : cp 
i.e.: cp file1 file2
i)	Display the usage of storage space：sum  
Display the usage of the 16MB space. You need to list how many blocks are used and how many blocks are unused. 
j)	Print out the file contents: cat  
Print out the contents of the file on the terminal
i.e:  cat /dir1/file1
k)	You are NOT required to implement the function of Login!
*/