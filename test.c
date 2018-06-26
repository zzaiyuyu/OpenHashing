#include "hash.h"
#include "com.h"
int main()
{
	HashBucket hb;
	HashInit(&hb, 10, IntKeyHash);
	HashBuctetInsertUnique(&hb, 2);
	HashBuctetInsertUnique(&hb, 4);
	HashBuctetInsertUnique(&hb, 14);
	HashBuctetInsertUnique(&hb, 24);

	HashBuctetInsertUnique(&hb, 34);
	HashBucketFind(&hb, 14);
	HashBucketDelete(&hb, 14);
	HashBucketPrint(&hb);

}