#include "stdafx.h"
#include "tree.h"
#include <stdio.h>
#include <iostream>


void createBiTree(BiTree &t)
{
	TreeEleType ch;
	scanf_s("%c", &ch);
	if ('#' == ch)
	{
		t = nullptr;
		return;
	}
	else
	{
		t = (BiTree)malloc(sizeof(BiNode));
		if (nullptr == t)
		{
			return;
		}
		t->data = ch;
		createBiTree(t->lChild);
		createBiTree(t->rChild);
	}
}

void destroyBiTree(BiTree & t)
{
	if (nullptr == t)
	{
		return;
	}
	if (nullptr != t->lChild)
	{
		destroyBiTree(t->lChild);
	}
	if (nullptr != t->rChild)
	{
		destroyBiTree(t->rChild);
	}
	free(t);
	t = nullptr;
}

void preOrderTraverse(BiTree t)
{
	if (nullptr == t)
	{
		return;
	}
	//¸ù¡¢×ó¡¢ÓÒ
	printf("%c ", t->data);
	preOrderTraverse(t->lChild);
	preOrderTraverse(t->rChild);
}

void inOrderTraverse(BiTree t)
{
	if (nullptr == t)
	{
		return;
	}
	//×ó¡¢¸ù¡¢ÓÒ
	inOrderTraverse(t->lChild);
	printf("%c ", t->data);
	inOrderTraverse(t->rChild);
}

void postOrderTraverse(BiTree t)
{
	if (nullptr == t)
	{
		return;
	}
	//×ó¡¢ÓÒ¡¢¸ù
	postOrderTraverse(t->lChild);
	postOrderTraverse(t->rChild);
	printf("%c ", t->data);
}

void inThreadingTree(BiThrTree t)
{
	static BiThrTree pre = nullptr;
	
}

void inThreadingTree(BiThrTree t, BiThrTree pre /*= nullptr*/)
{
	if (nullptr == t)
	{
		return;
	}
	//×ó¡¢¸ù¡¢ÓÒ
	inThreadingTree(t->lChild, pre);
	if (nullptr == t->lChild)
	{
		t->lTag = Thread;
		t->lChild = pre;
	}
	if (nullptr != pre && nullptr == pre->rChild)
	{
		pre->rTag = Thread;
		pre->rChild = t;
	}
	pre = t;
	inThreadingTree(t->rChild, pre);
}
