// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include "bplusindex.h"

#include "bson.h"
#include "util.h"
#include <string.h>
#include <boost/crc.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

BPlusIndex::BPlusIndex()
{

    _head = new Bucket();
    initializeBucket(_head);
}



void cascadeDelete(Bucket* bucket) {
    BucketElement* element = bucket->root;
    while (element != NULL) {
        BucketElement* next = element->next;
        if (next != NULL)
            next->previous = NULL;
        if (element->index != NULL) {
            if (element->index->key != NULL) {
                delete (element->index->key);
                element->index->key = 0;
            }
            delete element->index;
            element->index = 0;
        }
        if (element->key != NULL) {
            free(element->key);
            element->key = 0;
        }
        delete element;
        element = next;
    }
    bucket->root = NULL;
    bucket->tail = NULL;
    if (bucket->left != NULL) {
        cascadeDelete(bucket->left);
    }
    if (bucket->right != NULL) {
        cascadeDelete(bucket->right);
    }
    delete bucket;
}

BPlusIndex::~BPlusIndex()
{
    if (_head)
    {
        cascadeDelete(_head);
    }
}

Index* BPlusIndex::add(const BSONObj& elem, long filePos)
{
    Index* index = new Index();
    index->key = new BSONObj(elem);
    index->posData = filePos;

    if (!insertElement(index)) {
        // If the index was not inserted then drop the index
        delete index;
        index = 0;
    };
    return index;
}

Index* BPlusIndex::find(const BSONObj& elem)
{
//    char* key = elem->toChar();
//    boost::crc_32_type crc32;
//    crc32.process_bytes(key, strlen(key));
//    long value = crc32.checksum();

    Index* index = new Index();
    index->key = new BSONObj(elem);
    BucketElement* element = findBucketElement(_head, index, false);
    Index* result = NULL;
    if (element != NULL) {
        result = element->index;
    }
    if (index) {
        if (index->key) {
            delete index->key;
            index->key = NULL;
        }
        delete index;
        index = NULL;
    }
    return result;
}

void BPlusIndex::remove(const BSONObj& elem)
{
}

void BPlusIndex::initializeBucketElement(BucketElement* const elem)
{
//    elem->index = NULL;
    elem->next = NULL;
    elem->previous = NULL;
}

void BPlusIndex::initializeBucket(Bucket* const bucket)
{
    bucket->minKey = NULL;
    bucket->maxKey = NULL;
    bucket->root = NULL;
    bucket->size = 0;
    bucket->tail = NULL;
    bucket->parentBucket = NULL;
}

void BPlusIndex::checkBucket(Bucket* const bucket)
{
    if (bucket->size == BUCKET_MAX_ELEMENTS) {
        std::auto_ptr<Logger> log(getLogger(NULL));
        // The bucked will be split
        Bucket* leftBucket = new Bucket();
        leftBucket->parentBucket = bucket;
        initializeBucket(leftBucket);
        bucket->left = leftBucket;

        BucketElement* leftElement = bucket->root;
        BucketElement* rightElement = bucket->tail;

        // Move 2nd element
        bucket->root = leftElement->next;
        bucket->minKey = bucket->root->key;
        // Disconnects last element
        bucket->tail = rightElement->previous;
        bucket->tail->next = NULL;
        bucket->maxKey = bucket->tail->key;

        // Disconnects the leaf
        leftElement->next = NULL;
        leftElement->previous = NULL;
        rightElement->next = NULL;
        rightElement->previous = NULL;

        // Creates buckets
        Bucket* rightBucket = new Bucket();
        rightBucket->parentBucket = bucket;
        initializeBucket(rightBucket);
        bucket->right = rightBucket;

        insertBucketElement(leftBucket, leftElement);
        insertBucketElement(rightBucket, rightElement);

        bucket->size -= 2;
    #ifdef DEBUG
        log->debug("Sucessful split of the bucket. min: %s, max: %s, size: %d. Left: %s, Right: %s", bucket->minKey, bucket->maxKey, bucket->size, leftBucket->minKey, rightBucket->minKey);
    #endif
    }
}

// This method will insert the element into the currentBucket
void BPlusIndex::insertBucketElement(Bucket* bucket, BucketElement* element)
{
    std::auto_ptr<Logger> log(getLogger(NULL));
    #ifdef DEBUG
        log->debug("inserting element. key: %s", element->key);
        log->debug("current bucket. min: %s, max: %s, size: %d", bucket->minKey, bucket->maxKey, bucket->size);
    #endif
    INDEXPOINTERTYPE key = element->key;
    BucketElement* currentElement = bucket->root;
    if (currentElement == NULL) {
        bucket->root = element;
        bucket->tail = element;
        bucket->size++;
        bucket->minKey = element->key;
        bucket->maxKey = element->key;
        return;
    }
    INDEXPOINTERTYPE testKey = currentElement->key;
    int compMinKey = strcmp(bucket->minKey, testKey);
    // the element should be inserted on the parent, because it's lesser than the
    // root element
    if ((compMinKey < 0) && (bucket->parentBucket != NULL)) {
        insertBucketElement(bucket->parentBucket, element);
        return;
    }

    // Insert in the current bucket
    while (true) {
        INDEXPOINTERTYPE testKey = currentElement->key;
        int comp = strcmp(key, testKey);
        if (comp == 0)
        {
            return;
        }
        else
        {
            // The value is lesser than the current, should be inserted in front
            // if there's enough space
            if (comp < 0)
            {
                if (currentElement == bucket->root)
                {
                    element->next = currentElement;
                    currentElement->previous = element;
                    bucket->root = element;
                    bucket->minKey = element->key;
                }
                else
                {
                    currentElement->previous->next = element;
                    currentElement->previous = element;
                }
                bucket->size++;
                break;
            }
            else
            {
                // the value is greater and should be added to the next
                if (currentElement == bucket->tail)
                {
                    currentElement->next = element;
                    element->previous = currentElement;
                    bucket->maxKey = element->key;
                    bucket->tail = element;
                    bucket->size++;
                    break;
                } else {
                    // Moves to the next node
                    currentElement = currentElement->next;
                }
            }
        }
    }
    checkBucket(bucket);
    #ifdef DEBUG
        log->debug("bucket after insert. min: %s, max: %s, size: %d", bucket->minKey, bucket->maxKey, bucket->size);
    #endif
}

int compKey(BucketElement* element, INDEXPOINTERTYPE key) {
    INDEXPOINTERTYPE testKey = element->key;
    return strcmp(testKey, key);
}

/***
This will find the bucket in which the key should be in
*/
BucketElement* BPlusIndex::findBucketElement(Bucket* start, Index* idx, bool create)
{
    Index* index = new Index();
    index->key = new BSONObj(*idx->key);
    index->indexPos = idx->indexPos;
    index->posData = idx->posData;

    BSONObj* bkey = idx->key;
    Bucket* currentBucket = start;
    INDEXPOINTERTYPE key = bkey->toChar();
    BucketElement* result = NULL;
    bool created = false;
    if (currentBucket->size == 0)
    {
        if (!create) {
            result = result;
        } else {
            BucketElement* element = new BucketElement();
            initializeBucketElement(element);
            element->index = index;
            element->key = key;
            insertBucketElement(currentBucket, element);
            result = element;
            created = true;
        }
    } else {
        while (true)
        {
            int comp = strcmp(key, currentBucket->minKey);

            // Lucky the min is the one we're looking for
            if (comp == 0)
            {
                result = currentBucket->root;
                break;
            }
            else if (comp < 0)
            {
                // If the value is less than current left element in bucket and there's leaf then should test on that
                if (currentBucket->left != NULL)
                {
                    currentBucket = currentBucket->left;
                    continue;
                }
            }

            comp = strcmp(key, currentBucket->maxKey);
            if (comp == 0) {
                result = currentBucket->tail;
                break;
            } else if (comp > 0) {
                if (currentBucket->right != NULL) {
                    currentBucket = currentBucket->right;
                    continue;
                }
            }
            if (create) {
                BucketElement* element = new BucketElement();
                initializeBucketElement(element);
                element->index = index;
                element->key = key;
                insertBucketElement(currentBucket, element);
                result = element;
                created = true;
                break;
            } else {
                result = NULL;
                break;
            }
        }
    }
    if (!created) {
        free(key);
        delete index->key;
        delete index;
    }

    return result;
}

bool BPlusIndex::insertElement(Index* elem)
{
    BucketElement* res = findBucketElement(_head, elem, true);

    return (res != NULL);
}
