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

#include "RazerSDK_GameModEditor.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_content_GameModEditor"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

using namespace android_graphics_Bitmap;
using namespace java_io_OutputStream;
using namespace std;
using namespace com_razerzone_store_sdk_content_GameModScreenshot;

namespace com_razerzone_store_sdk_content_GameModEditor
{
	jclass GameModEditor::_jcGameModEditor = 0;
	jmethodID GameModEditor::_jmAddScreenshot = 0;
	jmethodID GameModEditor::_jmAddTag = 0;
	jmethodID GameModEditor::_jmDeleteFile = 0;
	jmethodID GameModEditor::_jmNewFile = 0;
	jmethodID GameModEditor::_jmRemoveScreenshot = 0;
	jmethodID GameModEditor::_jmRemoveTag = 0;
	jmethodID GameModEditor::_jmSetCategory = 0;
	jmethodID GameModEditor::_jmSetDescription = 0;
	jmethodID GameModEditor::_jmSetMetadata = 0;
	jmethodID GameModEditor::_jmSetTitle = 0;

	int GameModEditor::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/content/GameMod$Editor";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "Found %s", strClass);
#endif
				_jcGameModEditor = (jclass)env->NewGlobalRef(localRef);
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

	int GameModEditor::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strMethod = "addScreenshot";
			_jmAddScreenshot = env->GetMethodID(_jcGameModEditor, strMethod, "(Landroid/graphics/Bitmap;)Lcom/razerzone/store/sdk/content/GameModScreenshot;");
			if (_jmAddScreenshot)
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
			const char* strMethod = "addTag";
			_jmAddTag = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmAddTag)
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
			const char* strMethod = "deleteFile";
			_jmDeleteFile = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmDeleteFile)
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
			const char* strMethod = "newFile";
			_jmNewFile = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)Ljava/io/OutputStream;");
			if (_jmNewFile)
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
			const char* strMethod = "removeScreenshot";
			_jmRemoveScreenshot = env->GetMethodID(_jcGameModEditor, strMethod, "(Lcom/razerzone/store/sdk/content/GameModScreenshot;)V");
			if (_jmRemoveScreenshot)
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
			const char* strMethod = "removeTag";
			_jmRemoveTag = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmRemoveTag)
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
			const char* strMethod = "setCategory";
			_jmSetCategory = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmSetCategory)
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
			const char* strMethod = "setDescription";
			_jmSetDescription = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmSetDescription)
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
			const char* strMethod = "setMetadata";
			_jmSetMetadata = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmSetMetadata)
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
			const char* strMethod = "setTitle";
			_jmSetTitle = env->GetMethodID(_jcGameModEditor, strMethod, "(Ljava/lang/String;)V");
			if (_jmSetTitle)
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

	const GameModEditor GameModEditor::CreateObject(jobject instance)
	{
		GameModEditor gameModEditor;
		gameModEditor._instance = instance;
		return gameModEditor;
	}

	jobject GameModEditor::GetInstance() const
	{
		return _instance;
	}

	void GameModEditor::Dispose() const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteGlobalRef(_instance);
		}
	}

	GameModScreenshot GameModEditor::addScreenshot(const Bitmap& bitmap) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return GameModScreenshot::CreateObject(0);
		}

		if (!_jmAddScreenshot)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmAddScreenshot is not initialized");
			return GameModScreenshot::CreateObject(0);
		}

		if (!bitmap.GetInstance())
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "bitmap is not initialized");
			return GameModScreenshot::CreateObject(0);
		}

		jobject arg1 = bitmap.GetInstance();
		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmAddScreenshot, arg1);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "addScreenshot returned null");
			return GameModScreenshot::CreateObject(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return GameModScreenshot::CreateObject(globalRef);
	}

	void GameModEditor::addTag(const string& tag) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmAddTag)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmAddScreenshot is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(tag.c_str());
		env->CallVoidMethod(_instance, _jmAddTag, arg1);
		env->DeleteLocalRef(arg1);
	}

	void GameModEditor::deleteFile(const string& filename) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmDeleteFile)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmDeleteFile is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(filename.c_str());
		env->CallVoidMethod(_instance, _jmDeleteFile, arg1);
		env->DeleteLocalRef(arg1);
	}

	OutputStream GameModEditor::newFile(const string& filename) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return OutputStream(0);
		}

		if (!_jmNewFile)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmNewFile is not initialized");
			return OutputStream(0);
		}

		jstring arg1 = env->NewStringUTF(filename.c_str());
		jobject localRef = (jobject)env->CallObjectMethod(_instance, _jmNewFile, arg1);
		env->DeleteLocalRef(arg1);
		if (!localRef)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "newFile returned null");
			return OutputStream(0);
		}

		jobject globalRef = (jobject)env->NewGlobalRef(localRef);
		env->DeleteLocalRef(localRef);

		return OutputStream(globalRef);
	}

	void GameModEditor::removeScreenshot(const GameModScreenshot& gameModScreenshot) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmRemoveScreenshot)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmRemoveScreenshot is not initialized");
			return;
		}

		if (!gameModScreenshot.GetInstance())
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "gameModScreenshot is not initialized");
			return;
		}

		jobject arg1 = gameModScreenshot.GetInstance();
		env->CallVoidMethod(_instance, _jmRemoveScreenshot, arg1);
	}

	void GameModEditor::removeTag(const string& tag) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmRemoveTag)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmRemoveTag is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(tag.c_str());
		env->CallVoidMethod(_instance, _jmRemoveTag, arg1);
		env->DeleteLocalRef(arg1);
	}

	void GameModEditor::setCategory(const string& category) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmSetCategory)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmSetCategory is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(category.c_str());
		env->CallVoidMethod(_instance, _jmSetCategory, arg1);
		env->DeleteLocalRef(arg1);
	}

	void GameModEditor::setDescription(const string& description) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmSetDescription)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmSetDescription is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(description.c_str());
		env->CallVoidMethod(_instance, _jmSetDescription, arg1);
		env->DeleteLocalRef(arg1);

#if ENABLE_VERBOSE_LOGGING
		if (description.c_str())
		{
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "setDescription=%s", description.c_str());
		}
		else
		{
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "setDescription=null");
		}
#endif
	}

	void GameModEditor::setMetadata(const string& metadata) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmSetMetadata)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmSetMetadata is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(metadata.c_str());
		env->CallVoidMethod(_instance, _jmSetMetadata, arg1);
		env->DeleteLocalRef(arg1);
	}

	void GameModEditor::setTitle(const string& title) const
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return;
		}

		if (!_jmSetTitle)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmSetTitle is not initialized");
			return;
		}

		jstring arg1 = env->NewStringUTF(title.c_str());
		env->CallVoidMethod(_instance, _jmSetTitle, arg1);
		env->DeleteLocalRef(arg1);
	}
}

#endif
