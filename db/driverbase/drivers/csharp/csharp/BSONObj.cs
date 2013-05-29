/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace djondb {

using System;
using System.Runtime.InteropServices;

public class BSONObj : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal BSONObj(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(BSONObj obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~BSONObj() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          djonwrapperPINVOKE.delete_BSONObj(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public BSONObj() : this(djonwrapperPINVOKE.new_BSONObj__SWIG_0(), true) {
  }

  public BSONObj(BSONObj orig) : this(djonwrapperPINVOKE.new_BSONObj__SWIG_1(BSONObj.getCPtr(orig)), true) {
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, int arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_0(swigCPtr, arg0, arg1);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, double arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_1(swigCPtr, arg0, arg1);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, long arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_2(swigCPtr, arg0, arg1);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, string arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_3(swigCPtr, arg0, arg1);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, string arg1, int arg2) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_4(swigCPtr, arg0, arg1, arg2);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, BSONObj arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_5(swigCPtr, arg0, BSONObj.getCPtr(arg1));
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, BSONArrayObj arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_6(swigCPtr, arg0, BSONArrayObj.getCPtr(arg1));
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public void add(string arg0, SWIGTYPE_p_BSONContent arg1) {
    djonwrapperPINVOKE.BSONObj_add__SWIG_7(swigCPtr, arg0, SWIGTYPE_p_BSONContent.getCPtr(arg1));
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual bool has(string arg0) {
    bool ret = djonwrapperPINVOKE.BSONObj_has(swigCPtr, arg0);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual int getInt(string arg0) {
    int ret = djonwrapperPINVOKE.BSONObj_getInt(swigCPtr, arg0);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual double getDouble(string arg0) {
    double ret = djonwrapperPINVOKE.BSONObj_getDouble(swigCPtr, arg0);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual long getLong(string arg0) {
    long ret = djonwrapperPINVOKE.BSONObj_getLong(swigCPtr, arg0);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getString(string arg0) {
    string ret = djonwrapperPINVOKE.BSONObj_getString(swigCPtr, arg0);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual BSONObj getBSON(string arg0) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_getBSON(swigCPtr, arg0);
    BSONObj ret = (cPtr == IntPtr.Zero) ? null : new BSONObj(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual BSONArrayObj getBSONArray(string arg0) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_getBSONArray(swigCPtr, arg0);
    BSONArrayObj ret = (cPtr == IntPtr.Zero) ? null : new BSONArrayObj(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual SWIGTYPE_p_BSONContent get(string arg0) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_get(swigCPtr, arg0);
    SWIGTYPE_p_BSONContent ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_BSONContent(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual SWIGTYPE_p_BSONContent getContent(string arg0) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_getContent__SWIG_0(swigCPtr, arg0);
    SWIGTYPE_p_BSONContent ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_BSONContent(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual SWIGTYPE_p_BSONContent getContent(string arg0, SWIGTYPE_p_BSONTYPE arg1) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_getContent__SWIG_1(swigCPtr, arg0, SWIGTYPE_p_BSONTYPE.getCPtr(arg1));
    SWIGTYPE_p_BSONContent ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_BSONContent(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual SWIGTYPE_p_BSONContent getXpath(string xpath) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_getXpath(swigCPtr, xpath);
    SWIGTYPE_p_BSONContent ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_BSONContent(cPtr, false);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual BSONObj select(string sel) {
    IntPtr cPtr = djonwrapperPINVOKE.BSONObj_select(swigCPtr, sel);
    BSONObj ret = (cPtr == IntPtr.Zero) ? null : new BSONObj(cPtr, false);
    return ret;
  }

  public virtual SWIGTYPE_p_BSONTYPE type(string arg0) {
    SWIGTYPE_p_BSONTYPE ret = new SWIGTYPE_p_BSONTYPE(djonwrapperPINVOKE.BSONObj_type(swigCPtr, arg0), true);
    if (djonwrapperPINVOKE.SWIGPendingException.Pending) throw djonwrapperPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual string toChar() {
    string ret = djonwrapperPINVOKE.BSONObj_toChar(swigCPtr);
    return ret;
  }

  public virtual SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator begin() {
    SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator ret = new SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator(djonwrapperPINVOKE.BSONObj_begin(swigCPtr), true);
    return ret;
  }

  public virtual SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator end() {
    SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator ret = new SWIGTYPE_p_std__mapT_std__string_BSONContent_p_t__const_iterator(djonwrapperPINVOKE.BSONObj_end(swigCPtr), true);
    return ret;
  }

  public virtual int length() {
    int ret = djonwrapperPINVOKE.BSONObj_length(swigCPtr);
    return ret;
  }

}

}
