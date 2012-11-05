/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package djondb;

public class Connection {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Connection(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Connection obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        djonwrapperJNI.delete_Connection(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Connection(String host) {
    this(djonwrapperJNI.new_Connection__SWIG_0(host), true);
  }

  public Connection(String host, int port) {
    this(djonwrapperJNI.new_Connection__SWIG_1(host, port), true);
  }

  public Connection(Connection orig) {
    this(djonwrapperJNI.new_Connection__SWIG_2(Connection.getCPtr(orig), orig), true);
  }

  public boolean open() {
    return djonwrapperJNI.Connection_open(swigCPtr, this);
  }

  public void close() {
    djonwrapperJNI.Connection_close(swigCPtr, this);
  }

  public void internalClose() {
    djonwrapperJNI.Connection_internalClose(swigCPtr, this);
  }

  public boolean isOpen() {
    return djonwrapperJNI.Connection_isOpen(swigCPtr, this);
  }

  public boolean shutdown() {
    return djonwrapperJNI.Connection_shutdown(swigCPtr, this);
  }

  public boolean insert(String db, String ns, String json) {
    return djonwrapperJNI.Connection_insert__SWIG_0(swigCPtr, this, db, ns, json);
  }

  public boolean insert(String db, String ns, BSONObj obj) {
    return djonwrapperJNI.Connection_insert__SWIG_1(swigCPtr, this, db, ns, BSONObj.getCPtr(obj), obj);
  }

  public BSONObj findByKey(String db, String ns, String select, String id) {
    long cPtr = djonwrapperJNI.Connection_findByKey__SWIG_0(swigCPtr, this, db, ns, select, id);
    return (cPtr == 0) ? null : new BSONObj(cPtr, false);
  }

  public BSONObj findByKey(String db, String ns, String id) {
    long cPtr = djonwrapperJNI.Connection_findByKey__SWIG_1(swigCPtr, this, db, ns, id);
    return (cPtr == 0) ? null : new BSONObj(cPtr, false);
  }

  public BSONObjVectorPtr find(String db, String ns, String select, String filter) {
    long cPtr = djonwrapperJNI.Connection_find__SWIG_0(swigCPtr, this, db, ns, select, filter);
    return (cPtr == 0) ? null : new BSONObjVectorPtr(cPtr, false);
  }

  public BSONObjVectorPtr find(String db, String ns, String filter) {
    long cPtr = djonwrapperJNI.Connection_find__SWIG_1(swigCPtr, this, db, ns, filter);
    return (cPtr == 0) ? null : new BSONObjVectorPtr(cPtr, false);
  }

  public boolean update(String db, String ns, String json) {
    return djonwrapperJNI.Connection_update__SWIG_0(swigCPtr, this, db, ns, json);
  }

  public boolean update(String db, String ns, BSONObj bson) {
    return djonwrapperJNI.Connection_update__SWIG_1(swigCPtr, this, db, ns, BSONObj.getCPtr(bson), bson);
  }

  public boolean dropNamespace(String db, String ns) {
    return djonwrapperJNI.Connection_dropNamespace(swigCPtr, this, db, ns);
  }

  public StringVector dbs() {
    long cPtr = djonwrapperJNI.Connection_dbs(swigCPtr, this);
    return (cPtr == 0) ? null : new StringVector(cPtr, false);
  }

  public StringVector namespaces(String db) {
    long cPtr = djonwrapperJNI.Connection_namespaces(swigCPtr, this, db);
    return (cPtr == 0) ? null : new StringVector(cPtr, false);
  }

  public String host() {
    return djonwrapperJNI.Connection_host(swigCPtr, this);
  }

}