int sum(int i) 
{
    __asm {
    // ���㲢���� 1+2+��+i��ֵ
    mov eax,0 //eax���ڱ��淵��ֵ 
    mov ecx ,dword ptr [i] 
comeBack:
    add eax,ecx
    loop comeBack
    //mov [i] , eax
   
    }
    //return i;
}
