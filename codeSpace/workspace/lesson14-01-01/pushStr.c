#include <stdio.h>//����
int main(){
__asm{
	call _func//push eip����ת
	_emit 'h'
	_emit '0'
	_emit 0x0
_func:
	call printf//������push��eip���ɲ�������printf
	add esp,0x4

}

}