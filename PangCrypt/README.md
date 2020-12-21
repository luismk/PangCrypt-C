# PangCrypt C++

### About PangCrypt

this is a C++ version based on Csharp/GO
parts of the codes are not authorized by the owner,
all credits were highlighted within the codes
I thought of creating it not to say "mine" but to raise my level as a programmer, maybe in the future other programmers will try to do better

### Build

how about testing PangCrypt with your own pangya server?
this is possible, try to compile it!

### Release 

https://github.com/luismk/PangCrypt-C/releases

### DLL_EXPORT

The Pang.dll shares some functions with the server you will be able to understand.
    
     int pangya_client_decrypt (unsigned char *buffin, int size, unsigned char **buffout, int * buffoutSize, unsigned char key);//decrypt packet of client
     int pangya_server_encrypt (unsigned char *buffin, size int, unsigned char **buffout, int * buffoutSize, unsigned char key);//encrypt server packets that are sent to for the client
     int pangya_client_encrypt (unsigned char *buffin, int size, unsigned char **buffout, int * buffoutSize, unsigned char key, unsigned char packetid);//encrypt client packets that are sent to for the server
     int pangya_server_decrypt (unsigned char *buffin, internal size, unsigned char ** buffout, int * buffoutSize, char key);//decrypt packets of server
     UInt32 pangya_deserialize (UInt32 desserialize);//decrypt build_date by client
     UInt32 pangya_encrypt_deserialize (UInt32 desserialize);//encrypt build_date by client
     void pangya_free (char ** buffout);//clear buffer

### ShowCase

![pangya_001](https://cdn.discordapp.com/attachments/521180240542826498/789565764599808080/unknown.png)
