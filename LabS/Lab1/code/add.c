#include <stdio.h>
int add(int x, int y) 
{
    //int z;
    __asm {
        //����x+y��ֵ
        mov eax,dword ptr [y]
        add eax,dword ptr [x]
        //mov dword ptr [z],eax
    }
    //return z;
}
int main()
{
    //��� add(2,4)��ֵ
    printf("%d\n",add(2,4));
}
