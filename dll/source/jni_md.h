/*
 * @(#)jni_md.h	1.13 03/01/23
 *
 * Copyright 2003 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

#ifndef _JAVASOFT_JNI_MD_H_
#define _JAVASOFT_JNI_MD_H_

#define JNIEXPORT __declspec(dllexport)
#define JNIIMPORT __declspec(dllimport)
#define JNICALL __stdcall

typedef long jint;
//#ifdef __GNUC__
//typedef long long jlong;
//#else
typedef __int64 jlong;
//#endif

typedef signed char jbyte;

#endif /* !_JAVASOFT_JNI_MD_H_ */
