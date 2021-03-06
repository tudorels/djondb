/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.10
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#ifndef PHP_DJONWRAPPER_H
#define PHP_DJONWRAPPER_H

extern zend_module_entry djonwrapper_module_entry;
#define phpext_djonwrapper_ptr &djonwrapper_module_entry

#ifdef PHP_WIN32
# define PHP_DJONWRAPPER_API __declspec(dllexport)
#else
# define PHP_DJONWRAPPER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(djonwrapper);
PHP_MSHUTDOWN_FUNCTION(djonwrapper);
PHP_RINIT_FUNCTION(djonwrapper);
PHP_RSHUTDOWN_FUNCTION(djonwrapper);
PHP_MINFO_FUNCTION(djonwrapper);

ZEND_NAMED_FUNCTION(_wrap_new_BSONObjVectorPtr);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_size);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_capacity);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_reserve);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_clear);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_push);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_is_empty);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_pop);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_get);
ZEND_NAMED_FUNCTION(_wrap_BSONObjVectorPtr_set);
ZEND_NAMED_FUNCTION(_wrap_new_StringVector);
ZEND_NAMED_FUNCTION(_wrap_StringVector_size);
ZEND_NAMED_FUNCTION(_wrap_StringVector_capacity);
ZEND_NAMED_FUNCTION(_wrap_StringVector_reserve);
ZEND_NAMED_FUNCTION(_wrap_StringVector_clear);
ZEND_NAMED_FUNCTION(_wrap_StringVector_push);
ZEND_NAMED_FUNCTION(_wrap_StringVector_is_empty);
ZEND_NAMED_FUNCTION(_wrap_StringVector_pop);
ZEND_NAMED_FUNCTION(_wrap_StringVector_get);
ZEND_NAMED_FUNCTION(_wrap_StringVector_set);
ZEND_NAMED_FUNCTION(_wrap_new_BSONArrayObj);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_length);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_add);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_get);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_toChar);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_select);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_begin);
ZEND_NAMED_FUNCTION(_wrap_BSONArrayObj_end);
ZEND_NAMED_FUNCTION(_wrap_new_BSONObj);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_add);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_has);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getBoolean);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getInt);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getDouble);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getLong);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getString);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getBSON);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getBSONArray);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_get);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getContent);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_getXpath);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_select);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_type);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_toChar);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_begin);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_end);
ZEND_NAMED_FUNCTION(_wrap_BSONObj_length);
ZEND_NAMED_FUNCTION(_wrap_new_BSONParser);
ZEND_NAMED_FUNCTION(_wrap_BSONParser_parse);
ZEND_NAMED_FUNCTION(_wrap_BSONParser_parseArray);
ZEND_NAMED_FUNCTION(_wrap_parseFilterOperator);
ZEND_NAMED_FUNCTION(_wrap_new_ParseException);
ZEND_NAMED_FUNCTION(_wrap_ParseException_what);
ZEND_NAMED_FUNCTION(_wrap_ParseException_errorCode);
ZEND_NAMED_FUNCTION(_wrap_bson_splitSelect);
ZEND_NAMED_FUNCTION(_wrap_bson_subselect);
ZEND_NAMED_FUNCTION(_wrap_convert);
ZEND_NAMED_FUNCTION(_wrap_new_DjondbConnection);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_beginTransaction);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_commitTransaction);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_rollbackTransaction);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_open);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_close);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_internalClose);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_isOpen);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_shutdown);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_insert);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_findByKey);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_find);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_update);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_remove);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_executeQuery);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_executeUpdate);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_dropNamespace);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_dbs);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_namespaces);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnection_host);
ZEND_NAMED_FUNCTION(_wrap_ConnectionReference__connection_set);
ZEND_NAMED_FUNCTION(_wrap_ConnectionReference__connection_get);
ZEND_NAMED_FUNCTION(_wrap_ConnectionReference__references_set);
ZEND_NAMED_FUNCTION(_wrap_ConnectionReference__references_get);
ZEND_NAMED_FUNCTION(_wrap_new_ConnectionReference);
ZEND_NAMED_FUNCTION(_wrap_new_DjondbConnectionManager);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnectionManager_getConnection);
ZEND_NAMED_FUNCTION(_wrap_DjondbConnectionManager_releaseConnection);
#endif /* PHP_DJONWRAPPER_H */
