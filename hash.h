#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#define size_t unsigned long

typedef char* DataType;

typedef size_t (*PDT)(DataType data);

typedef struct Node
{
	struct  Node* _pNext;
	DataType data;
}Node, *PNode;

//��ϣ��
typedef struct HashBucket
{
	PNode* _table;
	int _capacity;
	int _size;
	PDT _setData;
}HashBucket;

//��ϣͰ��ʼ��
void HashInit(HashBucket* ht, int capacity, PDT _setData);

//����Ψһ�Ĳ�����ɾ��
void HashBuctetInsertUnique(HashBucket* ht, DataType data);
void HashBucketDeleteUnique(HashBucket* ht, DataType data);

//���ݲ�Ψһ
void HashBuctetInsert(HashBucket* ht, DataType data);
void HashBucketDelete(HashBucket* ht, DataType data);

//����
PNode HashBucketFind(HashBucket* ht, DataType data);

//Ԫ�ظ���
int HashBucketSize(HashBucket* ht);

//����
void DestroyHashBuctet(HashBucket* ht);

//////////////////////////////////////////////

//��ϣ����
int HashFunc(HashBucket* ht, int data);

//�����½��
PNode BuyNode(DataType data);
//��ӡ
void HashBucketPrint(HashBucket* ht);

//size_t StrToInt(const char* str);
//
//size_t DataToInt(int data);