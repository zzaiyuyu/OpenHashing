#include "hash.h"
#include "com.h"

//��ϣͰ��ʼ��
void HashInit(HashBucket* ht, int capacity, PDT _setData)
{
	assert(ht);

	ht->_table = (PNode*)malloc(sizeof(Node)*capacity);
	if (NULL == ht->_table)
		assert(0), exit(1);

	ht->_capacity = capacity;
	ht->_size = 0;
	ht->_setData = _setData;
	for (int i = 0; i < ht->_capacity; ++i)
	{
		ht->_table[i] = NULL;
	}
}

//����Ψһ�Ĳ���
void HashBuctetInsertUnique(HashBucket* ht, DataType data)
{
	int HashAddr = -1;
	assert(ht);

	int Newdata = ht->_setData(data);
	HashAddr = HashFunc(ht, Newdata);

	PNode pCur = ht->_table[HashAddr];

	while (pCur)
	{
		if (pCur->data == data)
			return;
		else
			pCur = pCur->_pNext;
	}

	pCur = BuyNode(data);

	pCur->_pNext = ht->_table[HashAddr];
	ht->_table[HashAddr] = pCur;
	++ht->_size;
}
//����Ψһ��ɾ��
void HashBucketDeleteUnique(HashBucket* ht, DataType data)
{
	assert(ht);
	int HashAddr = -1;
	PNode pPre = NULL;
	PNode pCur = NULL;

	int Newdata = ht->_setData(data);
	HashAddr = HashFunc(ht, Newdata);

	//��Ͱ
	if (NULL == ht->_table[HashAddr])
		return;

	pPre = ht->_table[HashAddr];
	pCur = ht->_table[HashAddr];

	//ͷ����ֵ��data���
	if (pCur->data == data)
	{
		ht->_table[HashAddr] = pCur->_pNext;
		free(pCur);
		--ht->_size;
		return;
	}

	while (pCur)
	{
		if (pCur->data == data)
		{
			break;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}

	//�ж�pCur�Ƿ��ҵ���data���˳��������ҵ��ˣ���pCurΪ��
	if (pCur)
	{
		pPre->_pNext = pCur->_pNext;
		free(pCur);
		--ht->_size;
	}
}

//���ݲ�Ψһ
//������ͬ����
void HashBuctetInsert(HashBucket* ht, DataType data)
{
	int HashAddr = -1;
	assert(ht);

	int Newdata = ht->_setData(data);
	HashAddr = HashFunc(ht, Newdata);

	//ͷ��
	PNode pCur = BuyNode(data);
	pCur->_pNext = ht->_table[HashAddr];
	ht->_table[HashAddr] = pCur;
	ht->_size;
}
//ɾ������ֵΪdata��Ԫ��
void HashBucketDelete(HashBucket* ht, DataType data)
{
	int HashAddr = -1;
	PNode pPre = NULL;
	PNode pCur = NULL;
	assert(ht);

	int Newdata = ht->_setData(data);
	HashAddr = HashFunc(ht, Newdata);

	//��Ͱ
	if (NULL == ht->_table[HashAddr])
		return;

	pPre = ht->_table[HashAddr];
	pCur = ht->_table[HashAddr];

	//dataֵ���ϣ�е�data���
	while (pCur&&pCur->data == data)
	{
		ht->_table[HashAddr] = pCur->_pNext;
		free(pCur);
		--ht->_size;
		pCur = ht->_table[HashAddr];
	}

	//������Ϊ��
	while (pCur)
	{
		if (pCur->data == data)
		{
			pPre->_pNext = pCur->_pNext;
			--ht->_size;
			free(pCur);
			pCur = pPre->_pNext;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}
}

//����
PNode HashBucketFind(HashBucket* ht, DataType data)
{
	int HashAddr = -1;
	assert(ht);

	int Newdata = ht->_setData(data);
	HashAddr = HashFunc(ht, Newdata);

	PNode pCur = ht->_table[HashAddr];
	while (pCur)
	{
		if (pCur->data == data)
			break;
		else
			pCur = pCur->_pNext;
	}

	return pCur;
}

//Ԫ�ظ���
int HashBucketSize(HashBucket* ht)
{
	return ht->_size;
}

//����
void DestroyHashBuctet(HashBucket* ht)
{
	assert(ht);

	PNode pDel = NULL;
	int i = 0;
	for (; i < ht->_capacity; ++i)
	{
		pDel = ht->_table[i];
		while (pDel)
		{
			ht->_table[i] = pDel->_pNext;
			free(pDel);
			pDel = ht->_table[i];
		}
	}

	free(ht->_table);
	ht->_size = 0;
	ht->_capacity = 0;
}

//////////////////////////////////////////////

//��ϣ����
int HashFunc(HashBucket* ht, int data)
{
	assert(ht);

	return data % (ht->_capacity);
}

//�����½��
PNode BuyNode(DataType data)
{
	PNode pNewNode = NULL;
	pNewNode = (PNode)malloc(sizeof(Node));
	if (NULL == pNewNode)
		return NULL;

	pNewNode->data = data;
	pNewNode->_pNext = NULL;

	return pNewNode;
}
//��ӡ
void HashBucketPrint(HashBucket* ht)
{
	PNode pCur = NULL;
	assert(ht);
	int i = 0;

	for (; i < ht->_capacity; ++i)
	{
		printf("Hash Bucket%ld: ", i);
		pCur = ht->_table[i];
		while (pCur)
		{
			if (ht->_setData == IntKeyHash)
			{
				printf("%d\t", pCur->data);
			}
			else
			{
				printf("%s\t", pCur->data);
			}
			pCur = pCur->_pNext;
		}
		printf("\n");
	}
}