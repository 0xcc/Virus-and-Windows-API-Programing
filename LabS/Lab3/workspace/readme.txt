test.c�ǵ�һ���͵ڶ�������Ĵ���
hello.c�ǵ������͵��ĸ�����Ҫ�������Ĵ���
inj.c��ע����������Ҫ��ɾ��ʲô��������ϸ�ʵ�������
����ָ��� 
1.2.
cl /c test.c
link /dynamicbase:no test.obj

3.4.
cl /c hello.c
link /dynamicbase:no hello.obj
cl /c inj.c
link /dynamicbase:no inj.obj