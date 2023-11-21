#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <jni.h>
#include <jni_md.h>

#include "iowkit2jni.h"
#include "iowkit2.h"

#include <string.h>

static jlong handleToJLong(IOWKIT2_HANDLE handle)
 {
  if(sizeof(IOWKIT2_HANDLE) == sizeof(jlong))
    return (jlong) handle;
  else
    return (jlong) ((int) handle);
 }

static IOWKIT2_HANDLE jlongToHandle(jlong handle)
 {
  if(sizeof(IOWKIT2_HANDLE) == sizeof(jlong))
    return (IOWKIT2_HANDLE) handle;
  else
    return (IOWKIT2_HANDLE) ((int) handle);
 }

/* The JVM */
static JavaVM *cached_jvm = NULL;

/** 
 * A static reference for the jmethodID of libraryDeviceChangeCallback() .
 * This jmethodID is initialized in the initialize() method. 
 * Once we have the id for the method, there is no need for a dynamic lookup of the methodID.
 */
static jmethodID javaDeviceCallMethodId;

/** 
 * A static reference for the jmethodID of libraryDataCallback() .
 * This jmethodID is initialized in the initialize() method. 
 * Once we have the id for the method, there is no need for a dynamic lookup of the methodID.
 */
static jmethodID javaDataCallMethodId;

/**
 * The callback function for data-callbacks from the lib
 */
BOOL IOWKIT2_API dataCallback(IOWKIT2_HANDLE handle, ULONG pipe, IOWKIT2_REPORT *rep, ULONG size, PVOID context)
 {
  int i;
  int retval = FALSE;
  JNIEnv *env;
  jclass cls = NULL;
  int buffer[IOWKIT2_REPORT_SIZE];
  jintArray data = NULL;

  if((*cached_jvm)->AttachCurrentThread(cached_jvm, (void **) &env, NULL))
   {
    //Unable to call into the JVM.
    //No workaround possible and no way we could signal that to Java
    return retval;
   }
  cls = (*env)->FindClass(env, "com/codemercs/iow/IowKit2");
  if (cls == NULL)
   {
    //Unable to locate our main-class.
    //could happen if it was NOT loaded by the Default.ClassLoder
    //FIXME : Document this, there is no workaround
    return retval; 
   }
  data = (*env)->NewIntArray(env, IOWKIT2_REPORT_SIZE);
  if (data == NULL)
    return FALSE;

  buffer[0] = rep->ReportID;
  for(i = 0; i < IOWKIT2_REPORT_PAYLOAD_SIZE; i++)
    buffer[i+1] = rep->Bytes[i];
  (*env)->SetIntArrayRegion(env, data ,0, IOWKIT2_REPORT_SIZE, buffer);
  retval = (*env)->CallStaticIntMethod(env, cls, javaDataCallMethodId, 
     handleToJLong(handle), (jint) pipe, data, (jint) size, (jint) context); 
  (*env)->DeleteLocalRef(env, data);
  (*cached_jvm)->DetachCurrentThread(cached_jvm);
  return retval;
 }

/**
 * The callback function for device-callbacks from the lib
 */
void IOWKIT2_API deviceCallback(ULONG action, IOWKIT2_HANDLE handle, PVOID context)
 {
  JNIEnv *env;
  jclass cls = NULL;
  jint jaction;
  jlong productId;
  jlong serial;
  jlong revision;

  if((*cached_jvm)->AttachCurrentThread(cached_jvm, (void **) &env, NULL))
   {
    //Unable to call into the JVM.
    //No workaround possible and no way we could signal that to Java
    return;
   }

  cls = (*env)->FindClass(env, "com/codemercs/iow/IowKit2");
  if(cls == NULL)
   {
    //Unable to locate our main-class.
    //could happen if it was NOT loaded by the Default.ClassLoder
    //FIXME : Document this, there is no workaround
    return;	
   }

  jaction = (jint) action;
  productId = (jlong) IowKit2GetProductId(handle);
  serial = (jlong) IowKit2GetSerialNumber(handle);
  revision = (jlong) IowKit2GetRevision(handle);
  (*env)->CallStaticVoidMethod(env, cls, javaDeviceCallMethodId,
    jaction, handleToJLong(handle), productId, serial, revision, (jint) context);
  (*cached_jvm)->DetachCurrentThread(cached_jvm);
 }

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
 {
  cached_jvm = jvm;  /* cache the JavaVM pointer */
  return JNI_VERSION_1_2;
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    libraryInitialize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_libraryInitialize(JNIEnv *env, jclass cls,
  jint context)
 {
  //lookup the callbacks into the JVM
  javaDeviceCallMethodId = (*env)->GetStaticMethodID(env, cls,
    "libraryDeviceChangeCallback", "(IJJJJI)V"); 	
  if(javaDeviceCallMethodId == NULL)
   {
    //printf("java devicechange lookup failed\n");
    return -1;	//throws an IOWarriorRuntimeException because we can't go on without this method
   }

  javaDataCallMethodId = (*env)->GetStaticMethodID(env, cls, 
    "libraryDataCallback", "(JI[III)Z"); 	
  if(javaDataCallMethodId == NULL)
   {
    //printf("java datachange lookup failed\n");
    return -1;	//throws an IOWarriorRuntimeException because we can't go on without this method
   }
  //install our callback for devices from the lib
  return (jint) IowKit2Initialize(deviceCallback, (PVOID) context);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    libraryFinalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_codemercs_iow_IowKit2_libraryFinalize(JNIEnv *env, jclass cls)
 {
  IowKit2Finalize();
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    setDeviceUse
 * Signature: (JZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_setDeviceUse(JNIEnv *env, jclass cls, 
  jlong handle, jboolean use)
 {
  return (jboolean) IowKit2SetDeviceUse(jlongToHandle(handle), (BOOL) use);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getDeviceUse
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_getDeviceUse(JNIEnv *env, jclass cls, 
  jlong handle)
 {
  return (jboolean) IowKit2GetDeviceUse(jlongToHandle(handle));
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getNumDevs
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_codemercs_iow_IowKit2_getNumDevs(JNIEnv *env, jclass cls)
 {
  return (jlong) IowKit2GetNumDevs();
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    enumerate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_codemercs_iow_IowKit2_enumerate(JNIEnv *env, jclass cls)
 {
  IowKit2Enumerate();
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_codemercs_iow_IowKit2_getVersion(JNIEnv *env, jclass cls)
 {
  return (*env)->NewStringUTF(env, IowKit2Version());
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    libraryRegister
 * Signature: (JJI)Z
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_libraryRegister(JNIEnv *env, jclass cls, 
  jlong handle, jlong pipe, jint action, jint context) 
 {
  BOOL retval = FALSE;

  if(action == 1)
    retval = IowKit2Register(jlongToHandle(handle), (ULONG) pipe, dataCallback, (PVOID) context);
  else
    retval = IowKit2Register(jlongToHandle(handle), (ULONG) pipe, NULL, 0);
  return (jboolean) retval;
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    isConnected
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_isConnected(JNIEnv *env, jclass cls,
  jlong handle) 
 {
  return (jboolean) IowKit2IsConnected(jlongToHandle(handle));
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    write
 * Signature: (JB[B)J
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_write(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe, jintArray data)
 {
  int i;
  int len;
  IOWKIT2_REPORT report;
  jint *ia;

  len=(*env)->GetArrayLength(env, data);
  if(len == 0)
   {
    // no elements in array
    return -1;
   }
  ia = (*env)->GetIntArrayElements(env, data, NULL);
  if(ia == NULL)
   {
    // array is null
    return -1;
   }
  memset(&report, 0, IOWKIT2_REPORT_SIZE);
  report.ReportID = (BYTE) ia[0];
  for(i = 0; i < len; i++)
    report.Bytes[i] = (BYTE) ia[i+1];
  (*env)->ReleaseIntArrayElements(env, data, ia, JNI_ABORT);
  return (jint) IowKit2Write(jlongToHandle(handle), (ULONG) pipe, &report);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    read
 * Signature: (JB[B)J
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_read(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe, jintArray data)
 {
  jint retval;
  int i;
  int len;
  IOWKIT2_REPORT report;
  jint *ia;

  memset(&report, 0, IOWKIT2_REPORT_SIZE);
  retval = IowKit2Read(jlongToHandle(handle), (ULONG) pipe, &report);
  if(retval <= 0)
    return retval;
  len=(*env)->GetArrayLength(env, data);
  if(len == 0 || len < retval)
   {
    // Array is too small
    return -1;
   }
  ia = (*env)->GetIntArrayElements(env, data, NULL);
  if(ia == NULL)
   {
    // array is null
    return -1;
   }
  ia[0] = report.ReportID;
  for(i = 0; i < len; i++)
    ia[i+1] = (jint) report.Bytes[i];
  (*env)->ReleaseIntArrayElements(env, data, ia, 0);
  return retval;
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    readNonBlocking
 * Signature: (JJ[I)I
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_readNonBlocking(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe, jintArray data)
 {
  jint retval;
  int i;
  int len;
  IOWKIT2_REPORT report;
  jint *ia;

  memset(&report, 0, IOWKIT2_REPORT_SIZE);
  retval = IowKit2ReadNonBlocking(jlongToHandle(handle), (ULONG) pipe, &report);
  if(retval <= 0)
    return retval;
  len = (*env)->GetArrayLength(env, data);
  if(len == 0 || len < retval)
   {
    // Array is too small
    return -1;
   }
  ia = (*env)->GetIntArrayElements(env, data, NULL);
  if(ia == NULL)
   {
    // array is null
    return -1;
   }
  ia[0] = report.ReportID;
  for(i = 0; i < len; i++)
    ia[i+1] = (jint) report.Bytes[i];
  (*env)->ReleaseIntArrayElements(env, data, ia, 0);
  return retval;
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    readImmediate
 * Signature: (JB[B)J
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_readImmediate(JNIEnv *env, jclass cls, 
  jlong handle, jintArray data)
 {
  jint retval;
  int i;
  int len;
  IOWKIT2_REPORT report;
  jint *ia;

  memset(&report, 0, IOWKIT2_REPORT_SIZE);
  retval = IowKit2ReadImmediate(jlongToHandle(handle), &report);
  if(retval <= 0)
    return retval;
  len = (*env)->GetArrayLength(env, data);
  if(len == 0 || len < retval)
   {
    // Array is too small
    return -1;
   }
  ia = (*env)->GetIntArrayElements(env, data, NULL);
  if(ia == NULL)
   {
    // array is null
    return -1;
   }
  *ia = report.ReportID;
  for(i = 0; i < len; i++)
    ia[i+1] = (jint) report.Bytes[i];
  (*env)->ReleaseIntArrayElements(env, data, ia, 0);
  return retval;
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    pendingReports
 * Signature: (JB)J
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_pendingReports(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe)
 {
  return (jint) IowKit2PendingReports(jlongToHandle(handle), (ULONG) pipe);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    flush
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_codemercs_iow_IowKit2_flush(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe)
 {
  return IowKit2Flush(jlongToHandle(handle), (ULONG) pipe);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getProductId
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_codemercs_iow_IowKit2_getProductId(JNIEnv *env, jclass cls, 
  jlong handle)
 {
  return (jlong) IowKit2GetProductId(jlongToHandle(handle));
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getSerialNumber
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_codemercs_iow_IowKit2_getSerialNumber(JNIEnv *env, jclass cls, 
  jlong handle)
 {
  return (jlong) IowKit2GetSerialNumber(jlongToHandle(handle));
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getRevision
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_codemercs_iow_IowKit2_getRevision(JNIEnv *env, jclass cls, 
  jlong handle)
 {
  return (jlong) IowKit2GetRevision(jlongToHandle(handle));
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    setTimeout
 * Signature: (JI)J
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_setTimeout(JNIEnv *env, jclass cls, 
  jlong handle, jint timeout)
 {
  return (jboolean) IowKit2SetTimeout(jlongToHandle(handle), (ULONG) timeout);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    setWriteTimeout
 * Signature: (JI)J
 */
JNIEXPORT jboolean JNICALL Java_com_codemercs_iow_IowKit2_setWriteTimeout(JNIEnv *env, jclass cls, 
  jlong handle, jint timeout)
 {
  return (jboolean) IowKit2SetWriteTimeout(jlongToHandle(handle), (ULONG) timeout);
 }

/*
 * Class:     com_codemercs_iow_IowKit2
 * Method:    getThreadHandle
 * Signature: (JI)I
 */
JNIEXPORT jlong JNICALL Java_com_codemercs_iow_IowKit2_getThreadHandle(JNIEnv *env, jclass cls, 
  jlong handle, jint pipe)
 {
  return (jlong) IowKit2GetThreadHandle(jlongToHandle(handle), (ULONG) pipe);
 }