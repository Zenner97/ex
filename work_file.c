#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>

HANDLE hmtxW, hmtxR, hout, hmtxW1, hmtxW2, hmtxW3, hmtxR1, hmtxR2, hmtxR3, harr[3];

CRITICAL_SECTION csec;

int N;
char book[] = "123456789012\n";
int arg1, arg2;
char w1book[] = "abcdefghijkl";
char w2book[] = "ABCDEFGHIJKL";
char w3book[] = {'+', '_', '!', '%', '^', '&', '*', '\\', '|', '@', '~', '&'};

void wthread1(void *arg) {

    while (TRUE) {
        WaitForSingleObject(hmtxW, INFINITE);
        for (int i = 0; i < 2; i++) {
            
              for (int i = 6; j < 6 + i * 6; j++){
                 book[j] = w1book[j];}
		 Sleep(100 * (int) arg1);
		
        }
        ReleaseSemaphore(hmtxW, 1, NULL);
        Sleep(100 * (int) arg1);
    }
}

void wthread2(void *arg) {

    while (TRUE) {
        WaitForSingleObject(hmtxW, INFINITE);
        for (int i = 0; i < 2; i++) {
            
		for (int i = 6; j < 6 + i * 6; j++){
		        book[j] = w1book[j];
			}
			Sleep(100 * (int) arg1);
        }
        ReleaseSemaphore(hmtxW, 1, NULL);
        Sleep(100 * (int) arg1);
    }
}

void wthread3(void *arg) {

    while (TRUE) {
        WaitForSingleObject(hmtxW, INFINITE);
        for (int i = 0; i < 2; i++) {
            
		for (int i = 6; j < 6 + i * 6; j++){
			book[j] = w1book[j];}
			Sleep (100 * (int) arg1);
        }
        ReleaseSemaphore(hmtxW, 1, 0);
        Sleep(100 * (int) arg1);
    }
}

void rthread1(void *arg) {
    COORD pos;
    
    for (int i = 0; i < 23; i++) {

        WaitForSingleObject(hmtxR, INFINITE);
        N++;
        if (N == 1) {

            WaitForSingleObject(hmtxW, INFINITE);
        }

        ReleaseMutex(hmtxR);
        pos.X = 40;
        pos.Y = i + 1;

        EnterCriticalSection(&csec);
        SetConsoleCursorPosition(hout, pos);
        printf(book);
        printf("\n");
        LeaveCriticalSection(&csec);
        WaitForSingleObject(hmtxR, INFINITE);
        N--;
        if (N == 0) {
            ReleaseSemaphore(hmtxW, 1, 0);
        }
        ReleaseMutex(hmtxR);
        Sleep(110 * (int) arg2);
    }
}

void rthread2(void *arg) {
    COORD pos;

    for (int i = 0; i < 23; i++) {

        WaitForSingleObject(hmtxR, INFINITE);
        N++;
        if (N == 1) {
            WaitForSingleObject(hmtxW, INFINITE);
        }
        ReleaseMutex(hmtxR);
        pos.X = 60;
        pos.Y = i + 1;

        EnterCriticalSection(&csec);
        SetConsoleCursorPosition(hout, pos);
        printf(book);
        printf("\n");
        LeaveCriticalSection(&csec);
        WaitForSingleObject(hmtxR, INFINITE);
        N--;
        if (N == 0) {
            ReleaseSemaphore(hmtxW, 1, 0);
        }
        ReleaseMutex(hmtxR);
        Sleep(120 * (int) arg2);
    }
}

void rthread3(void *arg) {
    COORD pos;

    for (int i = 0; i < 23; i++) {

        WaitForSingleObject(hmtxR, INFINITE);
        N++;

        if (N == 1) {

            WaitForSingleObject(hmtxW, INFINITE);
        }

        ReleaseMutex(hmtxR);
        pos.X = 80;
        pos.Y = i + 1;

        EnterCriticalSection(&csec);
        SetConsoleCursorPosition(hout, pos);
        printf(book);
        printf("\n");
        LeaveCriticalSection(&csec);
        WaitForSingleObject(hmtxR, INFINITE);
        N--;
        if (N == 0) {
            ReleaseSemaphore(hmtxW, 1, NULL);
        }
        ReleaseMutex(hmtxR);

        Sleep(150 * (int) arg2);
    }
}


void main(int args, char *argv[]) {
    system("cls");
    HANDLE hWthread1, hWthread2, hWthread3, hRthread1, hRthread2, hRthread3;
    unsigned long wthreadid1, wthreadid2, wthreadid3, rthreadid1, rthreadid2, rthreadid3;

    N = 0;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    arg1 = 20;
    arg2 = 3;
    InitializeCriticalSection(&csec);
    if (args >= 3) {
        sscanf(argv[1], "%d", &arg1);
        sscanf(argv[2], "%d", &arg2);
    }
    hmtxW = CreateSemaphore(NULL, 1, 1, "writing");
    hmtxR = CreateMutex(NULL, FALSE, "reading");
	
    if (hmtxW == NULL) {
        printf("Mutex=%d\n", hmtxW);
        getchar();
    }
    if (hmtxR == NULL) {
        printf("Mutex=%d\n", hmtxR);
        getchar();
    }

    hWthread1 = (HANDLE) _beginthreadex(NULL, 4096, wthread1, NULL, 0, &wthreadid1);
    hRthread1 = (HANDLE) _beginthreadex(NULL, 4096, rthread1, (void *) 1, 0, &rthreadid1);
    hWthread2 = (HANDLE) _beginthreadex(NULL, 4096, wthread2, NULL, 0, &wthreadid2);
    hRthread2 = (HANDLE) _beginthreadex(NULL, 4096, rthread2, (void *) 2, 0, &rthreadid2);
    hWthread3 = (HANDLE) _beginthreadex(NULL, 4096, wthread3, NULL, 0, &wthreadid3);
    hRthread3 = (HANDLE) _beginthreadex(NULL, 4096, rthread3, (void *) 3, 0, &rthreadid3);
    getchar();
    DeleteCriticalSection(&csec);
    CloseHandle(hWthread1);
    CloseHandle(hWthread2);
    CloseHandle(hWthread3);
    CloseHandle(hRthread1);
    CloseHandle(hRthread2);
    CloseHandle(hRthread3);
	SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
}
