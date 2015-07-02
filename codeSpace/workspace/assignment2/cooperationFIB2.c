#include <stdio.h>
struct ctx {
  int eip, esp, ebx, ebp;
} M, A, B;

__declspec(naked) void swtch(struct ctx *from, struct ctx *to)
{
 __asm{
        cmp ecx,0
        je EQU
        dec ecx
        
        
        
        mov eax, [esp+4] //��M�ĵ�ֵַ����ax  eax=&from
        pop dword ptr [eax] //from.eip=ret
        mov [eax+4], esp //from.esp=esp
        mov [eax+8], ebx//from.ebx=ebx
        mov [eax+12], ebp//from.ebp=ebp
        
        //push ecx
        //mov ecx,ebx
        
        mov eax, [esp+8] //eax=&lastFrom
        mov edx, [esp+4] //ecx=&to
        mov ebp, [edx+12] //ebp=to.ebp
        
        add [edx+8] , ebx
        mov ebx, [edx+8] //ebx=to.ebx
        
        mov esp, [edx+4] //esp=to.esp
        push [edx] //push to.eip
        ret //esp=esp+4;return to to.eip
        
        EQU:
            
            jmp dword ptr [M]
    }
}

void A_proc()
{
    /*
    printf("A: 1\n");
    swtch(&A, &B); //�Ӻ���A�л�������B
    printf("A: 2\n");
    swtch(&A, &B);
    printf("A: 3\n");
    swtch(&A, &M);
    */
    while(1){
                swtch(&A, &B);
                }
}

void B_proc()
{
     /*
    printf("B: 1\n");
    swtch(&B, &A); //�Ӻ���B�л�������A
    printf("B: 2\n");
    swtch(&B, &A);
    */
    while(1){
                swtch(&B, &A);
                }
}

int main(int argc,char *argv[])
{
  int Astack[1024];
  int Bstack[1024];
  int n,r=0;
  if(argc<2){
             printf("Usage: %s number(<40)\n",argv[0]);
             return -1;
               }
   
  n = atoi(argv[1]);
  A.eip = (int)A_proc;//A���̵ĳ�ʼ��ַ 
  A.esp = (int)(&Astack[1023]);//A��ջ�� 
  A.ebx = 1;
  B.eip = (int)B_proc;//B���̵ĳ�ʼ��ַ 
  B.esp = (int)(&Bstack[1023]);//B��ջ�� 
  B.ebx = 1;
  
  //printf("fib(%d)=%d\n",n,r);
  __asm{
        mov ecx , dword ptr [n]
        mov ebx , 0
        
        }
  
  //printf("fib(%d)=%d\n",n,r);
  
  swtch(&M, &A);//��main�����л���A����
  
  //printf("fib(%d)=%d\n",n,r);
  __asm{
        mov dword ptr [r] , ebx
        }
  printf("fib(%d)=%d\n",n,r);
  return 0;
}
