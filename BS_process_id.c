#ifdef _WIN32
	#include <stdio.h>
	#include <windows.h>
	#include <winternl.h>
	#include <conio.h>


	__declspec(noinline)
    __declspec(naked)
	NTSTATUS CallNtQueryInformationProcess(
		__in HANDLE ProcessHandle,
		__in PROCESS_INFORMATION_CLASS ProcessInformationClass,
		__out_bcount(ProcessInformationLength) PVOID ProcessInformation,
		__in ULONG ProcessInformationLength,
		__out_opt PULONG ReturnLength)
		{
			__asm {
                mov eax, 0x00a1
                mov edx, 0x7FFE0300
                call dword ptr [edx]

                ret
		}

	int main(int argc, char** argv)
	{
		DWORD usermodeProcessID = GetCurrentProcessId();

		PROCESS_BASIC_INFORMATION basicProcessInfos;
    	unsigned long buffersize = sizeof(basicProcessInfos);
    	unsigned long outputsize = 0;
    	NTSTATUS kernelspaceStatus = CallNtQueryInformationProcess(GetCurrentProcess(), 0, &output, buffersize, &outputsize);

    	DWORD systemCallProcessID = output.UniqueProcessId;

		return 0;
	}
#endif

#ifdef linux
	#include <stdio.h>
	#include <unistd.h>
	#include <syscall.h>


	int main()
	{
		int usermodeProcessID = getpid();
		int systemCallProcessID = syscall(__NR_getpid);
		printf("%d\n", usermodeProcessID);

		if (systemCallProcessID == -1){
    		printf("Something went wrong \n");
    	}

		printf("%d\n", systemCallProcessID);

		return 0;
	}
#endif
