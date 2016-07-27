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

#include "RazerSDK_GameMod.h"
#include "RazerSDK_Plugin.h"
#include "RazerSDK_String.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

using namespace java_io_InputStream;
using namespace java_lang_String;
using namespace RazerSDK;
using namespace std;
using namespace com_razerzone_store_sdk_content_GameModEditor;
using namespace com_razerzone_store_sdk_content_GameModScreenshot;

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_content_GameMod"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace com_razerzone_store_sdk_content_GameMod
{
	jclass GameMod::_jcGameMod = 0;
	jmethodID GameMod::_jmEdit = 0;
	jmethodID GameMod::_jmFlag = 0;
	jmethodID GameMod::_jmGetCategory = 0;
	jmethodID GameMod::_jmGetDescription = 0;
	jmethodID GameMod::_jmGetFilenames = 0;
	jmethodID GameMod::_jmGetMetadata = 0;
	jmethodID GameMod::_jmGetRatingAverage = 0;
	jmethodID GameMod::_jmGetRatingCount = 0;
	jmethodID GameMod::_jmGetScreenshots = 0;
	jmethodID GameMod::_jmGetTags = 0;
	jmethodID GameMod::_jmGetTitle = 0;
	jmethodID GameMod::_jmGetUserRating = 0;
	jmethodID GameMod::_jmIsDownloading = 0;
	jmethodID GameMod::_jmIsFlagged = 0;
	jmethodID GameMod::_jmIsInstalled = 0;
	jmethodID GameMod::_jmIsPublished = 0;
	jmethodID GameMod::_jmOpenFile = 0;
	jmethodID GameMod::_jmRate = 0;

	int GameMod::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/content/GameMod";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcGameMod = (jclass)env->NewGlobalRef(localRef);
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

	int GameMod::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strMethod = "edit";
			_jmEdit = env->GetMethodID(_jcGameMod, strMethod, "()Lcom/razerzone/store/sdk/content/GameMod$Editor;");
			if (_jmEdit)
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
			const char* strMethod = "flag";
			_jmFlag = env->GetMethodID(_jcGameMod, strMethod, "()V");
			if (_jmFlag)
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
			const char* strMethod = "getCategory";
			_jmGetCategory = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/lang/String;");
			if (_jmGetCategory)
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
			const char* strMethod = "getDescription";
			_jmGetDescription = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/lang/String;");
			if (_jmGetDescription)
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
			const char* strMethod = "getFilenames";
			_jmGetFilenames = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/util/List;");
			if (_jmGetFilenames)
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
			const char* strMethod = "getMetaData";
			_jmGetMetadata = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/lang/String;");
			if (_jmGetMetadata)
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
			const char* strMethod = "getRatingAverage";
			_jmGetRatingAverage = env->GetMethodID(_jcGameMod, strMethod, "()F");
			if (_jmGetRatingAverage)
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
			const char* strMethod = "getRatingCount";
			_jmGetRatingCount = env->GetMethodID(_jcGameMod, strMethod, "()I");
			if (_jmGetRatingCount)
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
			const char* strMethod = "getTags";
			_jmGetRatingCount = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/util/List;");
			if (_jmGetRatingCount)
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
			const char* strMethod = "getScreenshots";
			_jmGetScreenshots = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/util/List;");
			if (_jmGetScreenshots)
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
			const char* strMethod = "getTitle";
			_jmGetTitle = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/lang/String;");
			if (_jmGetTitle)
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
			const char* strMethod = "getUserRating";
			_jmGetUserRating = env->GetMethodID(_jcGameMod, strMethod, "()Ljava/lang/Float;");
			if (_jmGetUserRating)
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
			const char* strMethod = "isDownloading";
			_jmIsDownloading = env->GetMethodID(_jcGameMod, strMethod, "()Z");
			if (_jmIsDownloading)
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
			const char* strMethod = "isFlagged";
			_jmIsFlagged = env->GetMethodID(_jcGameMod, strMethod, "()Z");
			if (_jmIsFlagged)
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
			const char* strMethod = "isInstalled";
			_jmIsInstalled = env->GetMethodID(_jcGameMod, strMethod, "()Z");
			if (_jmIsInstalled)
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
			const char* strMethod = "isPublished";
			_jmIsPublished = env->GetMethodID(_jcGameMod, strMethod, "()Z");
			if (_jmIsPublished)
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
			const char* strMethod = "openFile";
			_jmOpenFile = env->GetMethodID(_jcGameMod, strMethod, "(Ljava/lang/String;)Ljava/io/InputStream;");
			if (_jmOpenFile)
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
			const char* strMethod = "rate";
			_jmRate = env->GetMethodID(_jcGameMod, strMethod, "()V");
			if (_jmRate)
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

	const GameMod GameMod::CreateObject(jobject instance)
	{
		GameMod gameMod;
		gameMod._instance = instance;
		return gameMod;
	}

	jobject GameMod::GetInstance() const
	{
		return _instance;
	}

	void GameMod::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	GameModEditor GameMod::edit() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return GameModEditor::CreateObject(0);
		}

		if (!_jmEdit)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmEdit is not initialized");
			return GameModEditor::CreateObject(0);
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmEdit);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "edit returned null");
			return GameModEditor::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return GameModEditor::CreateObject(globalRef);
	}

	void GameMod::flag() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmFlag)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmFlag is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Invoke flag");
#endif

		env->CallVoidMethod(_instance, _jmFlag);
	}

	string GameMod::getCategory() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return "";
		}

		if (!_jmGetCategory)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetCategory is not initialized");
			return "";
		}

		jstring localRef = (jstring)env->CallObjectMethod(_instance, _jmGetCategory);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getCategory returned null");
			return "";
		}

		const char* nativeString = env->GetStringUTFChars(localRef, 0);
		std::string result = nativeString;
		env->ReleaseStringUTFChars(localRef, nativeString);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getCategory=%s", result.c_str());
#endif

		return result;
	}

	string GameMod::getDescription() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return "";
		}

		if (!_jmGetDescription)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetDescription is not initialized");
			return "";
		}

		jstring localRef = (jstring)env->CallObjectMethod(_instance, _jmGetDescription);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getDescription returned null");
			return "";
		}

		const char* nativeString = env->GetStringUTFChars(localRef, 0);
		std::string result = nativeString;
		env->ReleaseStringUTFChars(localRef, nativeString);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getDescription=%s", result.c_str());
#endif

		return result;
	}

	vector<string> GameMod::getFilenames() const
	{
		vector<string> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return results;
		}

		if (!_jmGetFilenames)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetFilenames is not initialized");
			return results;
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmGetFilenames);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getFilenames returned null");
			return results;
		}

		results = Plugin::getStringArray(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getFilenames count=%d", results.size());
#endif

		return results;
	}

	string GameMod::getMetadata() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return "";
		}

		if (!_jmGetMetadata)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetMetadata is not initialized");
			return "";
		}

		jstring localRef = (jstring)env->CallObjectMethod(_instance, _jmGetMetadata);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getMetadata returned null");
			return "";
		}

		const char* nativeString = env->GetStringUTFChars(localRef, 0);
		std::string result = nativeString;
		env->ReleaseStringUTFChars(localRef, nativeString);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getMetadata=%s", result.c_str());
#endif

		return result;
	}

	float GameMod::getRatingAverage() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return 0;
		}

		if (!_jmGetRatingAverage)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetRatingAverage is not initialized");
			return 0;
		}

		float result = env->CallFloatMethod(_instance, _jmGetRatingAverage);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getRatingAverage=%f", result);
#endif

		return result;
	}

	float GameMod::getRatingCount() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return 0;
		}

		if (!_jmGetRatingCount)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetRatingCount is not initialized");
			return 0;
		}

		int result = env->CallIntMethod(_instance, _jmGetRatingCount);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getRatingCount=%d", result);
#endif

		return result;
	}

	vector<GameModScreenshot> GameMod::getScreenshots() const
	{
		vector<GameModScreenshot> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return results;
		}

		if (!_jmGetScreenshots)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetScreenshots is not initialized");
			return results;
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmGetScreenshots);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getScreenshots returned null");
			return results;
		}

		results = Plugin::getGameModScreenshotArray(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getScreenshots count=%d", results.size());
#endif

		return results;
	}

	vector<string> GameMod::getTags() const
	{
		vector<string> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return results;
		}

		if (!_jmGetTags)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetTags is not initialized");
			return results;
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmGetTags);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getTags returned null");
			return results;
		}

		results = Plugin::getStringArray(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getTags count=%d", results.size());
#endif

		return results;
	}

	string GameMod::getTitle() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return "";
		}

		if (!_jmGetTitle)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetTitle is not initialized");
			return "";
		}

		jstring localRef = (jstring)env->CallObjectMethod(_instance, _jmGetTitle);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getTitle returned null");
			return "";
		}

		const char* nativeString = env->GetStringUTFChars(localRef, 0);
		std::string result = nativeString;
		env->ReleaseStringUTFChars(localRef, nativeString);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getTitle=%s", result.c_str());
#endif

		return result;
	}

	float GameMod::getUserRating() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return 0;
		}

		if (!_jmGetUserRating)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetUserRating is not initialized");
			return 0;
		}

		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmGetUserRating);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getUserRating returned null");
			return 0;
		}

		float result = Plugin::getFloat(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getUserRating=%f", result);
#endif

		return result;
	}

	bool GameMod::isDownloading() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsDownloading)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsDownloading is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsDownloading);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "isDownloading=%s", result ? "true" : "false");
#endif

		return result;
	}

	bool GameMod::isFlagged() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsFlagged)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsFlagged is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsFlagged);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "isFlagged=%s", result ? "true" : "false");
#endif

		return result;
	}

	bool GameMod::isInstalled() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsInstalled)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsInstalled is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsInstalled);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "isInstalled=%s", result ? "true" : "false");
#endif

		return result;
	}

	bool GameMod::isPublished() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return false;
		}

		if (!_jmIsPublished)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmIsPublished is not initialized");
			return false;
		}

		bool result = env->CallBooleanMethod(_instance, _jmIsPublished);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "isPublished=%s", result ? "true" : "false");
#endif

		return result;
	}

	InputStream GameMod::openFile(const string& filename) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return InputStream(0);
		}

		if (!_jmOpenFile)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmOpenFile is not initialized");
			return InputStream(0);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "invoke openFile on %s", filename.c_str());
#endif

		jstring arg1 = env->NewStringUTF(filename.c_str());
		jobject localRef = env->CallObjectMethod(_instance, _jmOpenFile, arg1);
		env->DeleteLocalRef(arg1);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "openFile returned null");
			return InputStream(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Opened file with openFile on %s", filename.c_str());
#endif

		return InputStream(globalRef);
	}

	void GameMod::rate() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmRate)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmRate is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "invoke rate");
#endif

		env->CallVoidMethod(_instance, _jmRate);
	}
}

#endif
