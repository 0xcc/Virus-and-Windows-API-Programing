#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    int n,r=0;
    if(argc<2){
               printf("Usage: %s number(<40)\n",argv[0]);
               return -1;
               }
   
    n = atoi(argv[1]);
    //printf("%d %d\n",n,r);
    //printf("fib(%d) = %d\n", n, r);
    __asm{
          mov ebx,dword ptr [n] //���ڼ��� 
          mov edx,0      //����洢�ĵط�
          call fib       //�����ӹ��� 
          jmp FINISH
          
          fib:
              cmp ebx,0 //����ֵΪ0����ת��LO��ֵdxΪ1 
              je L0
              cmp ebx,1 //����ֵΪ1����ת��L1��ֵdxΪ1
              je L1
              dec ebx
              push ebx //����ֵ���ڹ����б��޸ģ�����ѹջ����
              call fib
              pop ebx
              mov eax,edx //�����������ax�����ۼ� 
              push eax //���ۼ����е�ֵѹջ����ֹ���ӹ����б��޸�
              dec ebx
              push ebx
              call fib
              pop ebx 
              pop eax
              add eax,edx
              xchg edx,eax
              jmp fin
          L0:
              mov edx,1
              jmp fin
          L1:
              mov edx,1
          fin:
              ret           
          FINISH:
                 mov dword ptr [r],edx
          }
    printf("fib(%d) = %d\n", n, r);
    return 0;
    }
