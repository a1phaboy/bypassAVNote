BOOL InjectDll(DWORD dwPID, LPCTSTR szDllPath) {

	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	HMODULE hMod = NULL;
	LPVOID pRemoteBuf = NULL;
	DWORD dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE pThreadProc;

	//使用dwPID获取目标进程句柄
	//得到PROCESS_ALL_ACCESS权限后便可以使用获取的句柄控制对应的进程
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID))) {
		_tprintf(L"[-]OpenProcess(%d) failed!!! [%d]\n", dwPID, GetLastError());
		return FALSE;
	}

	//在目标进程hProcess内存中分配dwBufSize大小的内存空间
	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);

	//将DLL文件路径写入内存
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllPath, dwBufSize, NULL);

	//先获取模块句柄，再从句柄中获取LoadLibraryW() API的地址
	//LoadLibraryW()是LoadLibrary()的Unicode字符串版本
	//Win OS中，kernel32.dll在每个进程中的加载地址是一致的，故不用特意获取加载到目标进程的kernel32.dll的LoadLibraryW() API地址而直接加载本身的即可
	hMod = GetModuleHandle(L"kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");

	//令目标进程hProcessd调用CreateRemoteThread()从而调用LoadLibrary()
	//其中线程函数ThreadProc()与LoadLibrary()两者形态结构一致，即LoadLibrary()可当做线程函数来执行
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	//关闭线程和句柄
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}