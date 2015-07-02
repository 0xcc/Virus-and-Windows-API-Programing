#include <stdio.h>
struct ctx {
  int eip, esp, ebx, ebp;
} M, A, B;

int n;
int r=0;

__declspec(naked) void swtch(struct ctx *from, struct ctx *to)
{
 __asm{
        mov eax, [esp+4] //��M�ĵ�ֵַ����ax  eax=&from
        pop dword ptr [eax] //from.eip=ret
        mov [eax+4], esp //from.esp=esp
        mov [eax+8], ebx//from.ebx=ebx
        mov [eax+12], ebp//from.ebp=ebp
        
        //mov eax, [esp+8] //eax=&lastFrom
        mov eax , [esp] //eax=&from
        
        mov ecx, [esp+4] //ecx=&to
        mov ebp, [ecx+12] //ebp=to.ebp
        mov ebx, [ecx+8] //ebx=to.ebx
        mov esp, [ecx+4] //esp=to.esp ջ����ַ�ı䣬������һ������ 
        push [ecx] //push to.eip
        ret //esp=esp+4;return to to.eip
    }
}

void A_proc()
{ 
    //while(count<n){             
//                   r=B.ebx;//��B�ļ�����ȡ�� 
//                   __asm{
//                         add ebx,dword ptr [r]//��A�ļ�������B�ļ�������� 
//                         }
//                   count++;
//                   swtch(&A,&B);//��A�ļ���������ṹ��A�У��������ṹ��B�еļ����������л� 
//                   }
//                   swtch(&A,&M); //�����������������M���� 
 __asm{
             
        WHILE:
              
              cmp edx , 0
              je Final
              //push ebp
              mov eax , [eax+8]//r=B.ebx
              //mov eax , [eax+8]//r=B.ebx
              mov dword ptr [r] , eax//r=B.ebx 
              //pop eax
              //pop ebp
              
              add ebx,dword ptr [r]
              dec edx
//            xor eax,eax
//            }
//            //printf("A:%d\n",r);
//            swtch(&A,&B);
//            //printf("A:%d\n",r);
// __asm{
              lea eax,dword ptr [B]
              push eax
              push ecx //ecx=&from
              call swtch
              add esp,8
         
              jmp WHILE
        Final:
              mov dword ptr [r],ebx
              lea eax , dword ptr [M]
              lea ecx , dword ptr [A]
              push eax
              push ecx
              call swtch 
        }
        //swtch(&A,&M);


}

void B_proc()
{
    /*
    printf("B: 1\n");
    swtch(&B, &A); //�Ӻ���B�л�������A
    printf("B: 2\n");
    swtch(&B, &A);
    */ 
    //while(count<n){
//                   r=A.ebx;//��A�ļ�����ȡ��
//                   __asm{
//                         add ebx,dword ptr [r]//��B�ļ�������A�ļ�������� 
//                         }
//                   count++;
//                   swtch(&B,&A);//��B�ļ���������ṹ��B�У��������ṹ��A�еļ����������л�
//                   }
//                   swtch(&B,&M); //�����������������M���� 
        
        __asm{
              
        WHILE:
              cmp edx , 0
              je Final
              //push edx
              //push eax
             // mov eax , [eax+8]//r=A.ebx
              mov eax , [eax+8]//r=A.ebx
              mov dword ptr [r] , eax//r=A.ebx
              
              //pop eax
              //pop edx
              
              add ebx,dword ptr [r]
              dec edx
              //xor eax,eax
             // }
//           //printf("B:%d\n",r);
//           swtch(&B,&A);
//           //printf("B:%d\n",r);
//           __asm{
             lea eax,dword ptr [A]
             push eax
             push ecx
             call swtch
             add esp,8
             jmp WHILE
        Final:
              mov dword ptr [r],ebx
              lea eax , dword ptr [M]
              lea ecx , dword ptr [B]
              push eax
              push ecx
              call swtch 
              }
        //swtch(&B,&M);
              
              
                         
}

int main(int argc,char *argv[])
{
  int Astack[1024];
  int Bstack[1024];
  
  
 if(argc<2){
           printf("Usage: %s number(<40)\n",argv[0]);
           return -1;
           }
   
   n = atoi(argv[1]);
  //n=3;
  
  A.eip = (int)A_proc;//A���̵ĳ�ʼ��ַ 
  A.esp = (int)(&Astack[1023]);//A��ջ��
  A.ebx = 1; 
  B.eip = (int)B_proc;//B���̵ĳ�ʼ��ַ 
  B.esp = (int)(&Bstack[1023]);//B��ջ�� 
  B.ebx = 1;
  __asm{
        mov ebx , 1
        mov edx , dword ptr [n]
        }
  //printf("fib(%d)=%d\n",n,r);
  swtch(&M, &A);//��main�����л���A���� 
  //printf("fib(%d)=%d\n",n,r);
  /*__asm{
        mov dword ptr [r] , ebx
        }*/
  //r=tmp;
  printf("fib(%d)=%d\n",n,r);
  return 0;
}
