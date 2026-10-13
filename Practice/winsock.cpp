//FOR PRACTICE 

#include <iostream> 
#include <winsock2.h> //includes primary winsock 2 header file , contains definatons for almost all windows specfific networking functions, constants 
using namespace std;
#include <ws2tcpip.h>  //provides newer ip helper with tcp/ip protocol works alongside winsock 2 for better ip handling
#pragma comment(lib, "ws2_32.lib") //pragma stands for pragmatic information that means deal with things sensibiliy, comment means unlike // ignored by compiler, "comment" tells the compiler to pass this specific instruction, lib stands for library of winsock, ws2_32.lib means windows socket library files, this library brings the  actual compiled code of winsock from OS 
// winsock2.h = the text guide/blueprint ,
//it tells the compiler the names and rules of networking functions
//EX: tells compiler that there is a function named WSAstartup that requires 2 inputs and stuff like that

//ws2_32.lib = The linker library/helper file
//An import file that gets used during compilation
//Helps compiler undersdtand that when program runs look inside ws2_32.dll to find actual code for WSAstartup

//ws_32.dll = The actual engine /dynamic link library
//used during runtime, pre installed in windows sytem folder C:\windows\System32, 
//It is a pre compiler binary file containing machine code written by microsoft that physically talks to the computer's wifi card, ethernet port and windows Kernel to send and receive data over the internet
/* File Name       | File Type                    | When Is It Used? | What Is Inside It?
----------------|------------------------------|------------------|---------------------------------------------------------------
winsock2.h      | Header File (.h)             | Coding Time      | Human-readable function names, structures, and definitions.
ws2_32.lib      | Library File (.lib)          | Compile Time     | Instructions telling the linker how to connect your app to the DLL.
ws2_32.dll      | Dynamic Link Library (.dll)  | Run Time         | Actual compiled machine code that provides Winsock networking functionality. */

int main(){
    WSADATA wsaData; //structure to hold winsock details filled by WSAstartup
    WORD wVersionRequested =MAKEWORD(2,2); //here we are asking for windows version 2.2 
    int result = WSAStartup(wVersionRequested, &wsaData); //initlasze winsock
    if (result != 0){
        cout << "winsock initlaization failed" << endl;
        return 1;
    }
 cout << "winsock successfull";
 cout << "status code" << wsaData.szSystemStatus;

 /* Socket CODE 

 ***************************************************************************
 */

 WSACleanup();
 cout << "winsock cleanup done " ;
 return 0;

}