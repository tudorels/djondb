%module pydjondb

%include "std_string.i"
%include "std_vector.i"

%{
#define SWIG_FILE_WITH_INIT
#include "bsonarrayobj.h"
#include "bson.h"
#include "bsonobj.h"
#include "bsonparser.h"
#include "filterdefs.h"
#include "bsonutil.h"
#include "djondbconnection.h"
#include "djondbconnectionmanager.h"
#include "djondb_client.h"
%}

namespace std {
   %template(BSONObjVectorPtr) vector<BSONObj*>;
   %template(StringVector) vector<std::string>;
}

%ignore getDJString;

/* Let's just grab the original header file here */
%include "bsonarrayobj.h"
%include "bson.h"
%include "bsonobj.h"
%include "bsonparser.h"
%include "filterdefs.h"
%include "bsonutil.h"
%include "djondbconnection.h"
%include "djondbconnectionmanager.h"
%include "djondb_client.h"

