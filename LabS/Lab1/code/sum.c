/* sum.c */
#include <stdio.h>
int sum(int i) 
{
    __asm {
    // ���㲢���� 1+2+��+i��ֵ
    mov eax,0
comeBack:
    cmp dword ptr [i],0
    je finish
    add eax,dword ptr [i]
    dec dword ptr [i]
    jmp comeBack
finish:
    mov dword ptr [i],eax
    
    }
    return i;
}
int main()
{
    // ���sum(100)��ֵ
    int num=100;
    //int res;
    //res=sum(num);
    printf("%d\n",sum(num));
    
}
