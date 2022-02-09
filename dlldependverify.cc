#include <windows.h>
#include <stdio.h>
#include <string>

typedef int (*pfn)(int a, int b);


std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

int main(int argc, char* argv[])
{
    SetErrorMode(0);
	
	if(argc<2){
		fprintf(stdout,"usage %s some.dll [somefunname]\n", argv[0]);
		return 0;
	}

    HMODULE hmod = LoadLibraryA(argv[1]);

    if(!hmod)
    {
        std::string errStr = GetLastErrorAsString();
        fprintf(stderr, "error loading library:%s,err: %s\n", argv[1], errStr.c_str());
        return 1;
    }
	
	fprintf(stdout,"load %s ok\n", argv[1]);

	if(argc<3){
		FreeLibrary(hmod);
		return 0;
	}
	
    pfn bar = (pfn)GetProcAddress(hmod, argv[2]);
    if(bar)
    {
        fprintf(stdout, "get addr %s ok\n", argv[1]);
    }
    else
    {
        fprintf(stderr, "can't load bar foonction: %d\n", GetLastError());
    }

    FreeLibrary(hmod);
    return 0;
}