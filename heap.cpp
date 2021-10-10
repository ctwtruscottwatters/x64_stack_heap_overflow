#include <stdio.h>
#include <Windows.h>
#include <iostream>

int return_function(void);

int return_function(void);

int main(void) {
	SetProcessDEPPolicy(1);
	HLOCAL h1 = 0;
	HLOCAL h2 = 0;
	void * oldprotect;
	HANDLE hp;
	char array_of_chars[2000];
	
	hp = HeapCreate(0, 1000, 5000);
	if (!hp) {
		std::cout << "Failed to create heap.\n";
	}
	h1 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 1000);
	BOOL np;
	np = VirtualProtect((LPVOID) hp, (SIZE_T) 0x666,(DWORD) 0x40, (PDWORD) oldprotect);
	if(!np) {
		printf("VirtualProtect failed\n");
	}
	printf("\t%p\t%p\n", hp, h1);
	np = VirtualProtect((LPVOID) h1, (SIZE_T) 0x666,(DWORD) 0x40, (PDWORD) oldprotect);
	if(!np) {
		printf("VirtualProtect failed\n");
	}
	std::cout << "ENTER: ";
	std::cin >> array_of_chars;
	strcpy((char*)h1, (char*)array_of_chars);
	void* heap_overflow = *return_function;
	void* two_overflow = &return_function;
	return_function();
	h2 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 1000);
	printf("\nFIN\n");
	return 0;
}

int return_function(void) {
	return 0;
}