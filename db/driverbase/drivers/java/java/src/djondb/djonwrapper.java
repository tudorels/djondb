/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package djondb;

public class djonwrapper implements djonwrapperConstants {
  public static FILTER_OPERATORS parseFilterOperator(String text) {
    return FILTER_OPERATORS.swigToEnum(djonwrapperJNI.parseFilterOperator(text));
  }

  public static SWIGTYPE_p_std__setT_std__string_t bson_splitSelect(String select) {
    return new SWIGTYPE_p_std__setT_std__string_t(djonwrapperJNI.bson_splitSelect(select), true);
  }

  public static String bson_subselect(String select, String elment) {
    return djonwrapperJNI.bson_subselect(select, elment);
  }

}
