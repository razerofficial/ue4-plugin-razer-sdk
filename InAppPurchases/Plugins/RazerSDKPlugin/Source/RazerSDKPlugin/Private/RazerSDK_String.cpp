/*
* Copyright (C) 2012-2016 Razer, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "RazerSDKPluginPrivatePCH.h"

// this test is Android specific
#if PLATFORM_ANDROID

#include "RazerSDK_String.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "java_lang_String"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace java_lang_String
{
	jclass String::_jcString = 0;
	jmethodID String::_jmGetBytes = 0;

	int String::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "java/lang/String";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			// system classes don't use `FAndroidApplication`
			jclass localRef = env->FindClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcString = (jclass)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strClass);
				return JNI_ERR;
			}
		}

		return FindJNI();
	}

	int String::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strMethod = "getBytes";
			_jmGetBytes = env->GetMethodID(_jcString, strMethod, "()[B");
			if (_jmGetBytes)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return JNI_ERR;
			}
		}

		return JNI_OK;
	}

	String::String(const std::string& val)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jstring localRef = env->NewStringUTF(val.c_str());
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to convert to jstring");
			return;
		}

		_instance = (jstring)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);
	}

	String::String(jstring instance)
	{
		_instance = instance;
	}

	jstring String::GetInstance() const
	{
		return _instance;
	}

	void String::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	int* String::getBytes(int& length) const
	{
		length = 0;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is null");
			return 0;
		}

		if (!_jmGetBytes) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetBytes is null");
			return 0;
		}

		jintArray localRef = (jintArray)env->CallObjectMethod(_instance, _jmGetBytes);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getBytes returned null");
			return 0;
		}

		length = env->GetArrayLength(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Bytes length=%d", length);
#endif

		if (length <= 0)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "length is zero");
			return 0;
		}

		jint* body = env->GetIntArrayElements(localRef, 0);
		int* buffer = new int[length];
		for (int index = 0; index < length; ++index)
		{
			buffer[index] = body[index];
		}
		env->ReleaseIntArrayElements(localRef, body, 0);
		return buffer;
	}
}

#endif
