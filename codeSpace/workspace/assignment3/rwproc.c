#include <windows.h>

int main(int argc, char *argv[])
{
    int pid = 0;
    HANDLE hproc = 0;
    int buf;
    int nRead, nWrite;
    char *s = "I'm hacked";

    //PBYTE pRemote = (PBYTE)0x00401000;//��0x00401000 λ�õ����� 
    PBYTE pRemote = (PBYTE)0x00409af9;//�����ݡ� 
    //PBYTE pRemote = (PBYTE)0x6b0c8000;//�ı����� 

    if (argc < 2) {
        printf("Usage: %s pid\n", argv[0]);
        return -1;
    }
    pid = atoi(argv[1]);
    if (pid <= 0) {
        printf("[E]: pid must be positive (pid>0)!\n"); 
        return -2;
    }

    hproc = OpenProcess(PROCESS_QUERY_INFORMATION 
        | PROCESS_VM_READ
        | PROCESS_VM_WRITE
        | PROCESS_VM_OPERATION, 0, pid);

    if (hproc == 0) {
        printf("[E]: Process (%d) cannot be opened !\n", pid);
        return -2;
    }
    printf("[I]: Process (%d) is opened --> 0x%08x\n", pid, hproc);

    if (!ReadProcessMemory(hproc, 
        pRemote, &buf, 4, &nRead)) {
        printf("[E]: Read DWORD from remote process failed at 0x%08x!\n", pRemote);
    }
    else {
        printf("[I]: Read DWORD from remote process (%d) from 0x%08x --> 0x%08x \n", pid, pRemote, buf);
    }
    printf("nRead:%08x\n",nRead);

    if (!WriteProcessMemory(hproc, 
        pRemote, s, strlen(s)+1, &nWrite)) {
        printf("[E]: Write string to remote process failed at 0x%08x!\n", pRemote);
    } else {
        printf("[I]: Write string (size: %d) to remote process at 0x%08x.\n", nWrite, pRemote);
    }

    if (!CloseHandle(hproc)) {
        printf("[E]: Process (%d) cannot be closed !\n", pid);
        return 2;
    };
    printf("[I]: Process (%d) is closed. \n", pid);
    return 0;
}
//����ollydbg
//���г�����while����ϵ㣬�ܵ�while����
//����ʾ�򣬿�ѹ�������ַ��Ȼ���Ҷ�Ӧ �ڴ������ֵ��
//�ҵ���Ӧ����󣬴�ƫ�Ƶ�ַ���ҵ��ַ���buf��helloworld���ڵĵ�ַ�������ʵ��ַ��Ȼ���޸Ĵ˵�ַ���� 
