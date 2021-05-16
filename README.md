# File_Encryption_System
This is a file encryption system that utilizes AES and RSA algorithm. It is meant to help us transfer files security over the internet.

Cuurently, this is a windows only program. 

If you want to run the program, the compiled program is in the Compiled_Program Folder.
The progross of using this system involve both sender and receiver.

First:
Run the first option of sender program. It will generate a RSA key pair Public.txt and Private.txt. Send the Public.txt to the receiver.

Second:
When receiver end recevied the public.txt put it in the same folder of Receiver.exe. Then run the first option of receiver program. It will generated a serial_num.txt. Send it back to sender end.

Thrid:
When receiver end recevied the serial_num.txt put it in the same folder of Sender.exe. Meanwhile put the file that you wanted to encrypte to the same folder. Run the second Option of the file. It will generate a .Rkey file. Send it to the receiver end.

Final Step:
Put the .Rkey file in the same folder of Receiver.exe. Run the sencond of option it can decrypte the file. 
