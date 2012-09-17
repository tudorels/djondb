/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ConnectionWrapper */

#ifndef _Included_ConnectionWrapper
#define _Included_ConnectionWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ConnectionWrapper
 * Method:    open
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_open
  (JNIEnv *, jobject, jlong);

/*
 * Class:     ConnectionWrapper
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ConnectionWrapper_close
  (JNIEnv *, jobject, jlong);

/*
 * Class:     ConnectionWrapper
 * Method:    internalClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ConnectionWrapper_internalClose
  (JNIEnv *, jobject, jlong);

/*
 * Class:     ConnectionWrapper
 * Method:    isOpen
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_isOpen
  (JNIEnv *, jobject, jlong);

/*
 * Class:     ConnectionWrapper
 * Method:    insert
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_insert__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring);

/*
 * Class:     ConnectionWrapper
 * Method:    insert
 * Signature: (JLjava/lang/String;Ljava/lang/String;LBSONObjWrapper;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_insert__JLjava_lang_String_2Ljava_lang_String_2LBSONObjWrapper_2
  (JNIEnv *, jobject, jlong, jstring, jstring, jobject);

/*
 * Class:     ConnectionWrapper
 * Method:    findByKey
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)LBSONObjWrapper;
 */
JNIEXPORT jobject JNICALL Java_ConnectionWrapper_findByKey
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring);

/*
 * Class:     ConnectionWrapper
 * Method:    find
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_ConnectionWrapper_find
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring);

/*
 * Class:     ConnectionWrapper
 * Method:    update
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_update__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jlong, jstring, jstring, jstring);

/*
 * Class:     ConnectionWrapper
 * Method:    update
 * Signature: (JLjava/lang/String;Ljava/lang/String;LBSONObjWrapper;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_update__JLjava_lang_String_2Ljava_lang_String_2LBSONObjWrapper_2
  (JNIEnv *, jobject, jlong, jstring, jstring, jobject);

/*
 * Class:     ConnectionWrapper
 * Method:    dropNamespace
 * Signature: (JLjava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_dropNamespace
  (JNIEnv *, jobject, jlong, jstring, jstring);

/*
 * Class:     ConnectionWrapper
 * Method:    host
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ConnectionWrapper_host
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif