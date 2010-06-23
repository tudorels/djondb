/* 
 * File:   Transaction.cpp
 * Author: cross
 * 
 * Created on May 20, 2010, 1:58 PM
 */

#include <iosfwd>


#include "transaction.h"
#include "transactionentry.h"

#include <sstream>
#include <iostream>
#include <string>

Transaction::Transaction() {
}

Transaction::Transaction(const Transaction& orig) {
}

Transaction::~Transaction() {
    std::map<TransactionKey*, TransactionEntry*, cmp_key >::iterator iter = _entriesMap.begin();
    while (iter != _entriesMap.end()) {
        TransactionKey* key = iter->first;
        TransactionEntry* entry = iter->second;
        delete(key);
        delete(entry);
        iter++;
    }
}

TransactionKey* Transaction::getKey(int idEntity, int idAttrib, int entityKey) {
    TransactionKey* key = new TransactionKey(idEntity, idAttrib, entityKey);
    return key;
}

TransactionKey* Transaction::getKey(const char* globalName) {
    TransactionKey* key = new TransactionKey(globalName);
    return key;
}

void* Transaction::getValue(int idEntity, int idAttrib, int entityKey) {
    TransactionKey* key = getKey(idEntity, idAttrib, entityKey);

    std::map< TransactionKey*, TransactionEntry* >::iterator iter = _entriesMap.find(key);

    delete(key);
    // not found
    if (iter == _entriesMap.end()) {
        return NULL;
    } else {
        TransactionEntry* entry = iter->second;
        return entry->getValue();
    }
}

void Transaction::addEntry(int idEntity, int idAttrib, int entityKey, void* value) {
    TransactionEntry* entry = new TransactionEntry();
    entry->setIdEntity(idEntity);
    entry->setIdAttribute(idAttrib);
    entry->setIdEntityKey(entityKey);
    entry->setValue(value);

    _entries.push_back(entry);
    TransactionKey* key = getKey(idEntity, idAttrib, entityKey);
    std::map<TransactionKey*, TransactionEntry*, cmp_key >::iterator iter = _entriesMap.find(key);
    if (iter != _entriesMap.end()) {
        _entriesMap.erase(iter);
    }
    _entriesMap.insert(std::pair<TransactionKey*, TransactionEntry*>(key, entry));
}

void Transaction::commit() {
    for (std::vector<TransactionEntry*>::iterator iter = _entries.begin();
            iter != _entries.end();
            iter++) {

    }
}