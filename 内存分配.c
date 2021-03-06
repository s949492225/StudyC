#define _CRT_SECURE_NO_WARNINGS //宏定义
//动态内存分布 ,java里面没有动态内存分配的问题,所以java有很多内存的问题
//javaweb的底层有时候也会用c/c++实现,很多时候也是效率和内存之间的原因

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>


//动态内存分配
/*
void main(){
//40M

//静态内存分配
//stack overflow 错误,栈溢出
//栈内存
int a[1024 * 1024 * 10];


//C语言内存分配:
//1 栈区(stack)
//	windows下,栈内存分配2M(确定的常量),超出就会 栈溢出
//	自动分配,释放

//2 堆区(heap)
//	程序员手动分配和释放,操作系统80%的内存

//3 全局区或静态区
//4 字符常量区
//5 程序代码区
getchar();
}*/

//栈内存,自动释放, 局部变量(用完就释放)
/*void stackFun(){
	//1kb  
	int a[1024];
}

//堆内存
void  heapFuun(){
	//在堆内存上,分配40M的内存
	//字节
	//malloc --> void *返回任意类型的指针
	int* p = malloc(1024 * 1024 * 10 * sizeof(int));

	//释放
	free(p);
}*/
//创建一个数组,动态指定数组的大小
//在程序运行过程中,可以随意的开辟制定大小的内存,以供使用
//相当于java中的集合

//静态内存分配,分配内存大小是固定的,
//问题1 很容易超出栈内存的最大值  2 往往为了防止内存不够用会开辟更多的内存,容易浪费内存

//动态内存分配,在程序运行过程中,动态制定需要制定的内存大小,可以手动释放,释放之后这些内存还可以被重新使用

/*void main(){
	// int i=10;   int a[i] 编译报错
	//静态内存分配创建数组,数组的大小是固定的

	int len;
	printf("输入数组的长度:");
	scanf("%d", &len);

	//开辟内存,  大小len *4字节
	//数组的名称就是数组的首地址
	//int* p = malloc(len * sizeof(int));
	int *p = calloc(len, sizeof(int));
	//p,数组的首地址 ,p 就是数组的名称
	//给数组元素赋值(使用这一块刚刚开辟出来的内存区域)
	int i = 0;
	for (; i < len; i++){
		p[i] = rand() % 100;
		printf("%d,%#x\n", p, &p[i]);
	}
	printf("输入数组增加的长度:");
	int addlen;
	scanf("%d", &addlen);
	//扩大刚刚分配的内存空间
	//1 原来内存的指针  2 内存扩大之后的 总大小
	//realloc 重新分配内存 
	//分配内存两种情况
	//缩小 ,缩小的一部分数据会丢失
	//扩大,(连续的)
	//1 .如果当前内存段后面有需要的内存空间,直接扩展这段内存空间,realloc返回原指针
	//2 .如果当前内存段后面的空闲字节不够,那么就是用队中的第一个能够满足这一要求的内存块,将目前的数据复制到新的位置，并将原来的数据库释放掉，返回新的内存地址
	//3 .如果申请失败,返回null,原来的指针仍然有效
	int *p2 = realloc(p, sizeof(int)* (len + addlen));
	if (p2 == NULL){
		printf("重新分配失败,世界那么大,却容不下我");
	}
	int x = 0;
	for (; x < len + addlen; x++){
		p2[x] = rand() % 100;
		printf("%d,%#x\n", p2, &p2[x]);
	}
	//p ,p2
	//手动释放内存,,p不需要手动释放内存,在扩容的时候要么扩容要么就已经被回收了
	if (p != NULL){
		free(p);
		p = NULL;
	}
	if (p2 != NULL){
		free(p2);
		p2 = NULL;
	}
	getchar();
}*/

//内存分配的几个注意细节
//1  不能多次释放
//2  释放完之后,给指针置NULL,标志释放完成,仅仅是free的话,p1是不为空的
//3  内存泄漏 (p重新赋值之后,再free,并没有真正的释放内存),要先释放内存,然后再重新赋值
void msg2(){
	//40M
	int* p1 = malloc(1024 * 1024 * 10 * sizeof(int));
	free(p1);//如果没有这次free的话,这40M 系统是不会回收的,
	p1 = NULL;
	printf("%#x\n", p1);

	//80M
	p1 = malloc(1024 * 1024 * 10 * sizeof(int)* 2);

	free(p1);
	p1 = NULL;

	getchar();
}