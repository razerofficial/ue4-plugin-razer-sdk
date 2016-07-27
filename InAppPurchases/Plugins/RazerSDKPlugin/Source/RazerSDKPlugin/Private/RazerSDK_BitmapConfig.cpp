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

#include "RazerSDK_BitmapConfig.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "android_graphics_Bitmap_Config"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace android_graphics_Bitmap_Config
{
	jfieldID Config::_jfARGB_8888 = 0;
	jclass Config::_jcConfig = 0;

	int Config::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "android/graphics/Bitmap$Config";
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
				_jcConfig = (jclass)env->NewGlobalRef(localRef);
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

	int Config::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strField = "ARGB_8888";
			_jfARGB_8888 = env->GetStaticFieldID(_jcConfig, strField, "Landroid/graphics/Bitmap$Config;");
			if (_jfARGB_8888)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strField);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strField);
				return JNI_ERR;
			}
		}

		return JNI_OK;
	}

	Config::Config(jobject instance)
	{
		_instance = instance;
	}

	jobject Config::GetInstance() const
	{
		return _instance;
	}

	void Config::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	Config Config::ARGB_8888()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_jcConfig) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcConfig is null");
			return Config(0);
		}

		if (!_jfARGB_8888) {
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jfARGB_8888 is null");
			return Config(0);
		}

		jobject localRef = env->GetStaticObjectField(_jcConfig, _jfARGB_8888);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jfARGB_8888 field returned null");
			return Config(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return Config(globalRef);
	}
}

#endif