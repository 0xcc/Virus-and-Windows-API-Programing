/* sum.c */
int sum(int i) 
{
    __asm {
    // ���㲢���� 1+2+��+i��ֵ
loop:
    cmp dword ptr [i],0
    je RET
    add eax,dword ptr [i]
    dec dword ptr [i]
    jmp loop
RET:
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
    print("%d\n",sum(num))
    
}
