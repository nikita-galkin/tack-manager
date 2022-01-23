#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <locale.h>
#include <stdlib.h>

int MakeProcess(CHAR* c)
{
	if (c == NULL) return 1;
	int Result;
	size_t i;
	PROCESS_INFORMATION ProcessInfo;
	TCHAR Path[MAX_PATH] = TEXT("OnvdqdcaxMhjhs`F`kjhm`mcX`qnrk`uRlhqmnu!");
	STARTUPINFO StartProcess;
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&StartProcess, sizeof(STARTUPINFO));
	GetStartupInfoW(&StartProcess);//Если верить документации Microsoft - функция НИКОГДА не завершается с ошибкой и ничего не возварщает
	if (*c == 'e')
	{
		for (i = 0; i < 45; i++) Path[i]++; Result = _tprintf(TEXT("%s"), Path); if (Result < 0) return 2;
	}
	else
	{
		Result = printf("Введите полный путь к исполняемому файлу: "); 
		if (Result < 0) return 3;
		if (_getts_s(Path, MAX_PATH) == NULL) return 4;
		if ((CreateProcess(NULL, Path, NULL, NULL, FALSE, 0, NULL, NULL, &StartProcess, &ProcessInfo)) == FALSE) return 5;
		if (CloseHandle(ProcessInfo.hProcess) == 0) return 6;
		if (CloseHandle(ProcessInfo.hThread)) return 7;
	}
	return 0;
}

int TerminateProcessEx(DWORD* ProcessId)
{
	if (ProcessId == NULL) return 1;
	DWORD ExitCode = 1;
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle = FALSE;
	int Result;
	HANDLE HandleProcess = OpenProcess(dwDesiredAccess, bInheritHandle, *ProcessId);
	if (HandleProcess == NULL) return 2;
	if (TerminateProcess(HandleProcess, ExitCode))
	{
		Result = printf("The process is terminated!\n");
		if (Result < 0) return 3;
	}
	else return 4;
	if ((CloseHandle(HandleProcess)) == 0) return 5;
	return 0;
}

int PrintPath(DWORD* ProcessID)
{
	if (ProcessID == NULL)	return 1;
	HMODULE Mod;
	int Result;
	DWORD MemoryProcess;
	TCHAR Path[MAX_PATH] = TEXT("ћЅЕіАіІn°Зnњ·№·ВЇn•Їє№·јnЇјІn§ЇАЅБєЇДnЎ»·АјЅД");
	HANDLE HandleProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, *ProcessID);
	if (HandleProcess == NULL) return 2;
	else if (EnumProcessModules(HandleProcess, &Mod, sizeof(Mod), &MemoryProcess) == 0) return 3;
	if ((GetModuleFileNameEx(HandleProcess, Mod, Path, MAX_PATH)) == 0) return 4;
	Result = _tprintf(TEXT("%s"), Path);
	if (Result < 0) return 5;
	if ((CloseHandle(HandleProcess)) == 0) return 6;
	return 0;
}

int Menu(int* Flag)
{
	int a, Result;
	char c;
	DWORD ProcessID;
	if (Flag == NULL)
	{
		printf("Error!\n");
		return 1;
	}
	//return 1
	Result = printf("--------------------------------------------------\nМеню доступных действий:\n--------------------------------------------------\n1. Завершить процесс;\n2. Посмотреть полный путь к процессу;\n3. Создать новый процесс;\n0. Завершение программы.\n--------------------------------------------------\nВведите номер действия, которое вы хотите сделать: ");
	if (Result < 0)
	{
		printf("Error!\n");
		return 2;
	}
	//return 2
	Result = scanf("%d", &a);
	if (Result != 1)
	{
		printf("Error!\n");
		return 3;
	}
	//return 3
	Result = scanf("%c", &c);
	if (Result != 1)
	{
		printf("Error!\n");
		return 4;
	}
	//return 4
	switch (a)
	{
	case 0: *Flag = 0; break;
	case 1: {
		Result = printf("Enter process ID: ");
		if (Result < 0) return 5;
		Result = scanf("%u", &ProcessID);
		if (Result != 1) return 6;
		switch (TerminateProcessEx(&ProcessID))
		{
		case 0: break;
		case 1: return 7; break;//ошибка получения доступа к процессу
		case 2: return 8; break;//ошибка получения кода завершения процесса
		case 3: return 9; break;//ошибка вывода сообщения об успешном завершении процесса
		case 4: return 10; break;//ошибка при завершении процесса
		case 5: return 11; break;//ошибка при закрытии заголовка процесса
		default: return 12; break;//неизвестная ошибка
		}
	}break;
	case 2: {
		Result = printf("Enter process ID: ");
		if (Result < 0) return 13;
		Result = scanf("%u", &ProcessID);
		if (Result != 1) return 14;
		switch (PrintPath(&ProcessID))
		{
		case 0: break;
		case 1: return 15; break;//передан пустой указатель
		case 2: return 16; break;//ошибка получения доступа к процессу
		case 3: return 17; break;//не получен модуль просса
		case 4: return 18; break;//ошибка при получении полного пути к файлу
		case 5: return 19; break;//ошибка при выводе на экран
		case 6: return 20; break;//ошибка при заголовка закрытии процесса
		default: return 21; break;//неизвестная ошибка
		}
	}break;
	case 3: {
		switch (MakeProcess(&c))
		{
		case 0: break;
		case 1: return 22; break;//передан пустой указатель
		case 2: return 23; break;//ошибка вывода на экран
		case 3: return 24; break;//ошибка чтения пути к программе
		case 4: return 25; break;//ошибка при создании процесса
		case 5: return 26; break;//не удалось закрыть заголовочные файлы, возможно произошла утечка памяти
		case 6: return 27; break;//не удалось закрыть заголовочные файлы, возможно произошла утечка памяти
		default: return 28; break;//неизвестная ошибка
		}
	}break;
	default: printf("Incorrect!\n"); break;
	}
	return 0;
}


int PrintList(int* ErrorCount)
{
	if (ErrorCount == NULL) return 1;
	DWORD Processes[1024], MemoryProcesses, i, j = 0, NumberProcess;//DWORD <=> unsigned long int,nProcess - number(количество)
	if (!EnumProcesses(Processes, sizeof(Processes), &MemoryProcesses)) return 2;
	NumberProcess = MemoryProcesses / sizeof(DWORD);
	for (i = 1; i < NumberProcess; i++)
		if (Processes[i] != 0)
		{
			TCHAR ProcessName[40] = TEXT("<unknown>");
			HANDLE ProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Processes[i]);//Объявление и инициализация Handle
			if (ProcessHandle == NULL) (*ErrorCount)++;// проверка удачности выполнения функции OpenProcess
			else {
				j++;
				HMODULE HandleMod;
				DWORD MemProcess;
				size_t k;
				if (EnumProcessModules(ProcessHandle, &HandleMod, sizeof(HandleMod), &MemProcess) == 0) return 4;//получение модуля процесса
				if (GetModuleBaseName(ProcessHandle, HandleMod, ProcessName, sizeof(ProcessName) / sizeof(TCHAR)) == 0) return 5;//получение имени процесса из модуля
				for (k = _tcslen(ProcessName); k < 39; k++) ProcessName[k] = '.';
				ProcessName[39] = '\0';
				if (j % 2) _tprintf(TEXT("%s...(PID: %-5u)    "), ProcessName, Processes[i]);
				else _tprintf(TEXT("%s...(PID: %-5u)\n"), ProcessName, Processes[i]);
				if (CloseHandle(ProcessHandle) == 0) return 7;
			}
		}
	if ((*ErrorCount) != 0) return 3;
	return 0;
}

int main()
{
	if ((setlocale(LC_ALL, "")) == NULL)
	{
		printf("ERROR! Сannot set locate\n");
		return 40;
	}
	int Result, ErrorCount, Flag = 1;//переменная, отвечающая за инициацию выхода из программы
	char c;
	while (Flag)
	{
		ErrorCount = 0;
		switch (PrintList(&ErrorCount)) {
		case 0:break;
		case 1: {
			printf("\033[0;31mERROR! Incorrect pointer in PrintList!\033[m\n");
			return 1;
		}break;
		case 2: {
			printf("\033[0;31mERROR! Cannot get list of processID!\033[m\n");
			return 2;
		}break;
		case 3: {
			printf("%d ERRORS! Cannot get Handle of process!\n", ErrorCount);
		}break;
		case 4: {
			printf("\033[0;31mERROR! Cannot get the Module of the process! Maybe you run x86 version on x64 system!\033[m\n");
			return 4;
		}break;
		case 5: {
			printf("\033[0;31mERROR! Cannot get the Name of process from module!\033[m\n");
			return 5;
		}break;
		case 6: {
			printf("\033[0;31mERROR! printf failed!\033[m\n");
			return 6;
		}break;
		case 7: {
			printf("\033[0;31mERROR! Cannot close Handle!\033[m\n");
			return 7;
		}break;
		default: {
			printf("\033[0;31mUNKNOWN ERROR in function PrintList!\033[m\n");
			return 8;
		}break;
		}
		switch (Menu(&Flag)) {
		case 0:break;
		case 1: {
			printf("\033[0;31mERROR! *Flag=NULL!\033[m\n");
			return 9;
		}break;
		case 2: {
			printf("\033[0;31mERROR! printf in Menu failed!\033[m\n");
			return 10;
		}break;
		case 3: {
			printf("\033[0;31mERROR! scanf in Menu failed!\033[m\n");
			return 11;
		}break;
		case 4: {
			printf("\033[0;31mERROR! scanf in Menu failed!\033[m\n");
			return 12;
		}break;
		case 5: {
			printf("\033[0;31mERROR! printf in Menu failed!\033[m\n");
			return 13;
		}break;
		case 6: {
			printf("\033[0;31mERROR! scanf in Menu failed!\033[m\n");
			return 14;
		}break;
		case 7: {
			printf("\033[0;31mERROR! Cannot open process in function TerminateProcessEx!\033[m\n");
			return 15;
		}break;
		case 8: {
			printf("\033[0;31mERROR! Cannot get ExitCode in function TerminateProcessEx!\033[m\n");
			return 16;
		}break;
		case 9: {
			printf("\033[0;31mERROR! printf failed in function TerminateProcessEx!\033[m\n");
			return 17;
		}break;
		case 10: {
			printf("\033[0;31mERROR! Cannot terminate process with function TerminateProcessEx!\033[m\n");
			return 18;
		}break;
		case 11: {
			printf("\033[0;31mERROR! Cannot close handle of process in function TerminateProcessEx!\033[m\n");
			return 19;
		}break;
		case 12: {
			printf("\033[0;31mERROR! UNKNOWN ERROR in function TerminateProcessEx!\033[m\n");
			return 20;
		}break;
		case 13: {
			printf("\033[0;31mERROR! printf failed in Menu!\033[m\n");
			return 21;
		}break;
		case 14: {
			printf("\033[0;31mERROR! scanf failed in Menu!\033[m\n");
			return 22;
		}break;
		case 15: {
			printf("\033[0;31mERROR! ProcessID=NULL in function PrintPath!\033[m\n");
			return 23;
		}break;
		case 16: {
			printf("\033[0;31mERROR! Cannot open process in function PrintPath!\033[m\n");
			return 24;
		}break;
		case 17: {
			printf("\033[0;31mERROR! Cannot get the Module in function PrintPath!\033[m\n");
			return 25;
		}break;
		case 18: {
			printf("\033[0;31mERROR! Cannot get the full path of the process in function PrintPath!\033[m\n");
			return 26;
		}break;
		case 19: {
			printf("\033[0;31mERROR! printf failed in function PrintPath!\033[m\n");
			return 27;
		}break;
		case 20: {
			printf("\033[0;31mERROR! CloseHandle failed in function PrintPath!\033[m\n");
			return 28;
		}break;
		case 21: {
			printf("\033[0;31mERROR! UNKNOWN ERROR in function PrintPath!\033[m\n");
			return 29;
		}break;
		case 22: {
			printf("\033[0;31mERROR! *c=NULL!\033[m\n");
			return 30;
		}break;
		case 23: {
			printf("\033[0;31mERROR! printf failed in function MakeProcess!\033[m\n");
			return 31;
		}break;
		case 24: {
			printf("\033[0;31mERROR! _getts_s failed in function MakeProcess!\033[m\n");
			return 32;
		}break;
		case 25: {
			printf("\033[0;31mERROR! Cannot create the process!\033[m\n");
			return 33;
		}break;
		case 26: {
			printf("\033[0;31mERROR! Cannot CloseHandle, возможна утечка памяти!\033[m\n");
			return 34;
		}break;
		case 27: {
			printf("\033[0;31mERROR! Cannot CloseHandle, возможна утечка памяти!\033[m\n");
			//return 35;
		}break;
		case 28: {
			printf("\033[0;31mERROR! UNKNOWN ERROR in create process!\033[m\n");
			return 36;
		}break;
		default: {
			printf("\033[0;31mUNKNOWN ERROR in function menu!\033[m\n");
			return 37;
		}break;
		}
		if (Flag == 0) return 0;
		Result = scanf("%c%c", &c, &c);
		if (Result != 2)
		{
			printf("\033[0;31mERROR! scanf failed!\033[m\n");
			return 37;
		}
		if (system(NULL))
		{
			if (system("cls") != 0)
			{
				printf("\033[0;31mERROR! system(""clz"") failed!\033[m\n");
				return 38;
			}
		}
		else
		{
			printf("\033[0;31mERROR! Недоступен исполнитель команды system!\033[m\n");
			return 39;
		}
	}
	return 0;
}