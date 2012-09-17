/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class BSONObjWrapper */

#ifndef _Included_BSONObjWrapper
#define _Included_BSONObjWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2I
  (JNIEnv *, jobject, jlong, jstring, jint);

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2D
  (JNIEnv *, jobject, jlong, jstring, jdouble);

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2J
  (JNIEnv *, jobject, jlong, jstring, jlong);

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;LBSONObjWrapper;)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2LBSONObjWrapper_2
  (JNIEnv *, jobject, jlong, jstring, jobject);

/*
 * Class:     BSONObjWrapper
 * Method:    has
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_BSONObjWrapper_has
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getInt
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_BSONObjWrapper_getInt
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getDouble
 * Signature: (JLjava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_BSONObjWrapper_getDouble
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getLong
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_BSONObjWrapper_getLong
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getStrings
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_BSONObjWrapper_getStrings
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getString
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_BSONObjWrapper_getString
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    get
 * Signature: (JLjava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_get
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getBSON
 * Signature: (JLjava/lang/String;)LBSONObjWrapper;
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_getBSON
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    getXpath
 * Signature: (JLjava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_getXpath
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     BSONObjWrapper
 * Method:    toString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_BSONObjWrapper_toString
  (JNIEnv *, jobject, jlong);

/*
 * Class:     BSONObjWrapper
 * Method:    iterator
 * Signature: (J)Ljava/util/Iterator;
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_iterator
  (JNIEnv *, jobject, jlong);

/*
 * Class:     BSONObjWrapper
 * Method:    length
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_BSONObjWrapper_length
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif