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

#include "RazerSDK_GameModScreenshot.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_content_GameModScreenshot"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

using namespace android_graphics_Bitmap;

namespace com_razerzone_store_sdk_content_GameModScreenshot
{
	jclass GameModScreenshot::_jcGameModScreenshot = 0;

	int GameModScreenshot::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/content/GameModScreenshot";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcGameModScreenshot = (jclass)env->NewGlobalRef(localRef);
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

	int GameModScreenshot::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		return JNI_OK;
	}

	const GameModScreenshot GameModScreenshot::CreateObject(jobject instance)
	{
		GameModScreenshot gameModScreenshot;
		gameModScreenshot._instance = instance;
		return gameModScreenshot;
	}

	jobject GameModScreenshot::GetInstance() const
	{
		return _instance;
	}

	void GameModScreenshot::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	Bitmap GameModScreenshot::getImage() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is null!");
			return Bitmap(0);
		}

		jmethodID method;
		{
			const char* strMethod = "getImage";
			method = env->GetMethodID(_jcGameModScreenshot, strMethod, "()Landroid/graphics/Bitmap;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return Bitmap(0);
			}
		}

		jobject localRef = env->CallObjectMethod(_instance, method);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getImage returned null");
			return Bitmap(0);
		}
		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getImage returned Bitmap");
#endif
		return Bitmap(globalRef);
	}

	Bitmap GameModScreenshot::getThumbnail() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is null!");
			return Bitmap(0);
		}

		jmethodID method;
		{
			const char* strMethod = "getThumbnail";
			method = env->GetMethodID(_jcGameModScreenshot, strMethod, "()Landroid/graphics/Bitmap;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return Bitmap(0);
			}
		}

		jobject localRef = env->CallObjectMethod(_instance, method);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getThumbnail returned null");
			return Bitmap(0);
		}
		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getThumbnail returned Bitmap");
#endif
		return Bitmap(globalRef);
	}
}

#endif
