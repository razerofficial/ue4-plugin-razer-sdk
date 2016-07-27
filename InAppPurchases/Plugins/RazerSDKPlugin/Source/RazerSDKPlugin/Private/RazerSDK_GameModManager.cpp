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

#include "RazerSDK_GameModManager.h"
#include "RazerSDK_GameMod.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

using namespace com_razerzone_store_sdk_content_GameMod;

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_content_GameModManager"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace com_razerzone_store_sdk_content_GameModManager
{
	jclass GameModManager::_jcGameModManager = 0;
	jmethodID GameModManager::_jmCreate = 0;
	jmethodID GameModManager::_jmGetInstance = 0;
	jmethodID GameModManager::_jmIsInitialized = 0;

	int GameModManager::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/content/GameModManager";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcGameModManager = (jclass)env->NewGlobalRef(localRef);
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

	int GameModManager::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strMethod = "create";
			_jmCreate = env->GetMethodID(_jcGameModManager, strMethod, "()Lcom/razerzone/store/sdk/content/GameMod;");
			if (_jmCreate)
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

		{
			const char* strMethod = "getInstance";
			_jmGetInstance = env->GetStaticMethodID(_jcGameModManager, strMethod, "()Lcom/razerzone/store/sdk/content/GameModManager;");
			if (_jmGetInstance)
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

		{
			const char* strMethod = "isInitialized";
			_jmIsInitialized = env->GetMethodID(_jcGameModManager, strMethod, "()Z");
			if (_jmIsInitialized)
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

	GameModManager GameModManager::CreateObject(jobject instance)
	{
		GameModManager gameModManager;
		gameModManager._instance = instance;
		return gameModManager;
	}

	jobject GameModManager::GetInstance() const
	{
		return _instance;
	}

	void GameModManager::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	GameModManager GameModManager::getInstance()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_jcGameModManager)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcGameModManager is not initialized");
			return GameModManager::CreateObject(0);
		}

		if (!_jmGetInstance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetInstance is not initialized");
			return GameModManager::CreateObject(0);
		}

		jobject localRef = (jobject)env->CallStaticObjectMethod(_jcGameModManager, _jmGetInstance);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getInstance returned null");
			return GameModManager::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return GameModManager::CreateObject(globalRef);
	}

	GameMod GameModManager::create()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return GameMod::CreateObject(0);
		}

		if (!_jmCreate)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmCreate is not initialized");
			return GameMod::CreateObject(0);
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmCreate);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "create returned null");
			return GameMod::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return GameMod::CreateObject(globalRef);
	}

	bool GameModManager::isInitialized() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsInitialized)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsInitialized is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsInitialized);
		return result;
	}
}

#endif
