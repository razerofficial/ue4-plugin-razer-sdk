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

#include "RazerSDK_Bitmap.h"
#include "RazerSDK_BitmapConfig.h"
#include "RazerSDK_Bundle.h"
#include "RazerSDK_CallbackSingleton.h"
#include "RazerSDK_Color.h"
#include "RazerSDK_InputStream.h"
#include "RazerSDK_JSONArray.h"
#include "RazerSDK_JSONObject.h"
#include "RazerSDK_GameModManager.h"
#include "RazerSDK_GameMod.h"
#include "RazerSDK_GameModEditor.h"
#include "RazerSDK_GameModScreenshot.h"
#include "RazerSDK_OutputStream.h"
#include "RazerSDK_Plugin.h"
#include "RazerSDK_String.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <jni.h>
#include <android/log.h>

#include <string>
#include <vector>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_engine_unreal_Plugin"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

using namespace android_graphics_Bitmap;
using namespace android_graphics_Bitmap_Config;
using namespace android_graphics_Color;
using namespace android_os_Bundle;
using namespace java_io_InputStream;
using namespace java_io_OutputStream;
using namespace org_json_JSONArray;
using namespace org_json_JSONObject;
using namespace std;
using namespace com_razerzone_store_sdk_content_GameModManager;
using namespace com_razerzone_store_sdk_content_GameMod;
using namespace com_razerzone_store_sdk_content_GameModEditor;
using namespace com_razerzone_store_sdk_content_GameModScreenshot;

// If we cause an exception in JNI, we print the exception info to
// the log, we clear the exception to avoid a pending-exception
// crash, and we force the function to return.
#define EXCEPTION_RETURN(env) \
	if (env->ExceptionOccurred()) { \
		env->ExceptionDescribe(); \
		env->ExceptionClear(); \
		return; \
	}

namespace RazerSDK
{
	jclass Plugin::jc_Plugin = 0;

	int Plugin::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/engine/unreal/Plugin";
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for %s", strClass);
#endif
			jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strClass);
#endif
				jc_Plugin = (jclass)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strClass);
				return JNI_ERR;
			}
		}

		if (Bitmap::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (Bundle::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (CallbackSingleton::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (Color::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (Config::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (InputStream::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (JSONArray::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (JSONObject::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (OutputStream::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (GameModManager::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (GameMod::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (GameModEditor::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (GameModScreenshot::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		if (java_lang_String::String::InitJNI() == JNI_ERR)
		{
			return JNI_ERR;
		}

		return JNI_OK;
	}

	void Plugin::initPlugin(const string& secretApiKey, CallbacksInitPlugin* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "initPlugin");
#endif

		CallbackSingleton::GetInstance()->m_callbacksInitPlugin = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the initPlugin method");
#endif
		jmethodID method = env->GetStaticMethodID(jc_Plugin, "initPlugin", "(Ljava/lang/String;)V");
		EXCEPTION_RETURN(env);

		jstring arg1 = env->NewStringUTF(secretApiKey.c_str());
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the initPlugin method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, method, arg1);
		EXCEPTION_RETURN(env);

		//TODO: clean memory
	}

	void Plugin::requestLogin(CallbacksRequestLogin* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "requestLogin");
#endif

		CallbackSingleton::GetInstance()->m_callbacksRequestLogin = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the requestLogin method");
#endif
		jmethodID method = env->GetStaticMethodID(jc_Plugin, "requestLogin", "()V");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the requestLogin method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, method);
		EXCEPTION_RETURN(env);

		//TODO: clean memory
	}

	void Plugin::requestGamerInfo(CallbacksRequestGamerInfo* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "requestGamerInfo");
#endif

		CallbackSingleton::GetInstance()->m_callbacksRequestGamerInfo = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the requestGamerInfo method");
#endif
		jmethodID method = env->GetStaticMethodID(jc_Plugin, "requestGamerInfo", "()V");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the requestGamerInfo method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, method);
		EXCEPTION_RETURN(env);

		//TODO: clean memory
	}

	void Plugin::requestProducts(const vector<string>& productIds, CallbacksRequestProducts* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "requestProducts");
#endif

		CallbackSingleton::GetInstance()->m_callbacksRequestProducts = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get string class");
#endif

		// Get a class reference for java.lang.String
		// for whatever reason env->FindClass has to be used instead of FAndroidApplication::FindJavaClass
		jclass classString = env->FindClass("java/lang/String");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "create array");
#endif
		jobjectArray products = env->NewObjectArray(productIds.size(), classString, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "populate items");
#endif
		for (unsigned int i = 0; i < productIds.size(); ++i) {
			jstring identifierString = env->NewStringUTF(productIds[i].c_str());
			// need to clean up
			EXCEPTION_RETURN(env);
			env->SetObjectArrayElement(products, i, identifierString);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the requestProducts method");
#endif
		jmethodID method = env->GetStaticMethodID(jc_Plugin, "requestProducts", "([Ljava/lang/String;)V");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the requestProducts method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, method, products);
		EXCEPTION_RETURN(env);

		//TODO: clean memory
	}

	void Plugin::requestPurchase(const string& purchasable, const string& productType, CallbacksRequestPurchase* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "requestPurchase");
#endif

		CallbackSingleton::GetInstance()->m_callbacksRequestPurchase = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Allocate purchasable String");
#endif
		jstring purchasableString = env->NewStringUTF(purchasable.c_str());
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Allocate productType String");
#endif
		jstring productTypeString = env->NewStringUTF(productType.c_str());
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the invoke method");
#endif
		jmethodID method = env->GetStaticMethodID(jc_Plugin, "requestPurchase", "(Ljava/lang/String;Ljava/lang/String;)V");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the requestPurchase method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, method, purchasableString, productTypeString);
		EXCEPTION_RETURN(env);

		//TODO: clean memory
	}

	void Plugin::requestReceipts(CallbacksRequestReceipts* callbacks)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "requestReceipts");
#endif

		CallbackSingleton::GetInstance()->m_callbacksRequestReceipts = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "get the requestReceipts method");
#endif
		jmethodID invokeMethod = env->GetStaticMethodID(jc_Plugin, "requestReceipts", "()V");
		EXCEPTION_RETURN(env);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "execute the requestReceipts method");
#endif
		env->CallStaticVoidMethod(jc_Plugin, invokeMethod);
		EXCEPTION_RETURN(env);
	}

	void Plugin::updateSafeArea(float amount)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		const char* strMethod = "updateSafeArea";
		jmethodID method = env->GetStaticMethodID(jc_Plugin, strMethod, "(F)V");
		if (method)
		{
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
		}
		else
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			return;
		}

		env->CallStaticVoidMethod(jc_Plugin, method, amount);
	}

	void Plugin::shutdown(CallbacksShutdown* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksShutdown = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

		const char* strMethod = "shutdown";
		jmethodID method = env->GetStaticMethodID(jc_Plugin, strMethod, "()V");
		if (method)
		{
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
		}
		else
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			return;
		}

		env->CallStaticVoidMethod(jc_Plugin, method);
	}

	void Plugin::quit()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return;
		}

		const char* strMethod = "quit";
		jmethodID method = env->GetStaticMethodID(jc_Plugin, strMethod, "()V");
		if (method)
		{
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
		}
		else
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			return;
		}

		env->CallStaticVoidMethod(jc_Plugin, method);
	}

	void Plugin::contentDelete(const GameMod& gameMod, CallbacksContentDelete* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentDelete = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "contentDelete";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Lcom/razerzone/store/sdk/content/GameMod;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method, gameMod.GetInstance());
	}

	void Plugin::contentDownload(const GameMod& gameMod, CallbacksContentDownload* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentDownload = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "contentDownload";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Lcom/razerzone/store/sdk/content/GameMod;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method, gameMod.GetInstance());
	}

	void Plugin::contentPublish(const GameMod& gameMod, CallbacksContentPublish* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentPublish = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "contentPublish";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Lcom/razerzone/store/sdk/content/GameMod;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method, gameMod.GetInstance());
	}

	void Plugin::contentUnpublish(const GameMod& gameMod, CallbacksContentUnpublish* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentUnpublish = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "contentUnpublish";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Lcom/razerzone/store/sdk/content/GameMod;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method, gameMod.GetInstance());
	}

	void Plugin::saveGameMod(const com_razerzone_store_sdk_content_GameModEditor::GameModEditor& gameModEditor,
		const GameMod& gameMod,
		CallbacksContentSave* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentSave = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "saveGameMod";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Lcom/razerzone/store/sdk/content/GameMod$Editor;Lcom/razerzone/store/sdk/content/GameMod;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method, gameModEditor.GetInstance(), gameMod.GetInstance());
	}

	void Plugin::getOuyaContentInstalled(CallbacksContentSearchInstalled* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentSearchInstalled = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "getOuyaContentInstalled";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "()V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		env->CallStaticVoidMethod(jc_Plugin, method);
	}

	void Plugin::getOuyaContentPublished(string sortMethod, CallbacksContentSearchPublished* callbacks)
	{
		CallbackSingleton::GetInstance()->m_callbacksContentSearchPublished = callbacks;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		jmethodID method;

		{
			const char* strMethod = "getOuyaContentPublished";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Ljava/lang/String;)V");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		jstring arg1 = env->NewStringUTF(sortMethod.c_str());
		env->CallStaticVoidMethod(jc_Plugin, method, arg1);
		env->DeleteLocalRef(arg1);
	}

	float Plugin::getFloat(jobject fFloat)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return 0;
		}

		if (!fFloat)
		{
			return 0;
		}

		jmethodID method;
		{
			const char* strMethod = "getFloat";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Ljava/lang/Float;)F");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return 0;
			}
		}

		jobject arg1 = fFloat;
		float result = env->CallStaticFloatMethod(jc_Plugin, method, arg1);
		return result;
	}

	vector<Bitmap> Plugin::getBitmapArray(jobject listBitmaps)
	{
		vector<Bitmap> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return results;
		}

		if (!listBitmaps)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "listBitmaps reference is null");
			return results;
		}

		jmethodID method;
		{
			const char* strMethod = "getBitmapArray";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Ljava/util/List;)[Landroid/graphics/Bitmap;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return results;
			}
		}

		jobject arg1 = listBitmaps;
		jobject result = (jarray)env->CallStaticObjectMethod(jc_Plugin, method, arg1);
		if (!result)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getBitmapArray returned null");
			return results;
		}

		jsize length = env->GetArrayLength((jarray)result);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getBitmapArray returned %d elements", length);
#endif

		for (jsize index(0); index < length; ++index)
		{
			jobject localRef = (jobject)env->GetObjectArrayElement((jobjectArray)result, index);
			jobject globalRef = (jobject)env->NewGlobalRef(localRef);
			env->DeleteLocalRef(localRef);
			Bitmap bitmap = Bitmap(globalRef);
			results.push_back(bitmap);
		}

		env->DeleteLocalRef(result);

		return results;
	}

	vector<GameModScreenshot> Plugin::getGameModScreenshotArray(jobject listGameModScreenshots)
	{
		vector<GameModScreenshot> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return results;
		}

		if (!listGameModScreenshots)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "listGameModScreenshots reference is null");
			return results;
		}

		jmethodID method;
		{
			const char* strMethod = "getGameModScreenshotArray";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Ljava/util/List;)[Lcom/razerzone/store/sdk/content/GameModScreenshot;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return results;
			}
		}

		jobject arg1 = listGameModScreenshots;
		jobject result = (jarray)env->CallStaticObjectMethod(jc_Plugin, method, arg1);
		if (!result)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getGameModScreenshotArray returned null");
			return results;
		}

		jsize length = env->GetArrayLength((jarray)result);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getBitmapArray returned %d elements", length);
#endif

		for (jsize index(0); index < length; ++index)
		{
			jobject localRef = (jobject)env->GetObjectArrayElement((jobjectArray)result, index);
			jobject globalRef = (jobject)env->NewGlobalRef(localRef);
			env->DeleteLocalRef(localRef);
			GameModScreenshot gameModScreenshot = GameModScreenshot::CreateObject(globalRef);
			results.push_back(gameModScreenshot);
		}

		env->DeleteLocalRef(result);

		return results;
	}

	vector<string> Plugin::getStringArray(jobject listStrings)
	{
		vector<string> results;

		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!jc_Plugin)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "jc_Plugin is not initialized");
			return results;
		}

		jmethodID method;
		{
			const char* strMethod = "getStringArray";
			method = env->GetStaticMethodID(jc_Plugin, strMethod, "(Ljava/util/List;)[Ljava/lang/String;");
			if (method)
			{
#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return results;
			}
		}

		jobject arg1 = listStrings;
		jobject result = (jarray)env->CallStaticObjectMethod(jc_Plugin, method, arg1);
		if (!result)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getStringArray returned null");
			return results;
		}

		jsize length = env->GetArrayLength((jarray)result);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "getStringArray returned %d elements", length);
#endif

		for (jsize index(0); index < length; ++index)
		{
			jstring localRef = (jstring)env->GetObjectArrayElement((jobjectArray)result, index);
			const char* nativeString = env->GetStringUTFChars(localRef, 0);
			std::string element = nativeString;
			env->ReleaseStringUTFChars(localRef, nativeString);
			env->DeleteLocalRef(localRef);
			results.push_back(element);
		}

		env->DeleteLocalRef(result);

		return results;
	}
}

#endif
