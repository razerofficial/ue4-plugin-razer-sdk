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

#include "RazerSDK_Bundle.h"
#include "RazerSDK_CallbackSingleton.h"
#include "RazerSDK_CallbacksContentDelete.h"
#include "RazerSDK_CallbacksContentDownload.h"
#include "RazerSDK_CallbacksContentInit.h"
#include "RazerSDK_CallbacksContentPublish.h"
#include "RazerSDK_CallbacksContentSave.h"
#include "RazerSDK_CallbacksContentSearchInstalled.h"
#include "RazerSDK_CallbacksContentSearchPublished.h"
#include "RazerSDK_CallbacksContentUnpublish.h"
#include "RazerSDK_CallbacksRequestLogin.h"
#include "RazerSDK_CallbacksRequestGamerInfo.h"
#include "RazerSDK_CallbacksInitPlugin.h"
#include "RazerSDK_CallbacksRequestProducts.h"
#include "RazerSDK_CallbacksRequestPurchase.h"
#include "RazerSDK_CallbacksRequestReceipts.h"
#include "RazerSDK_CallbacksShutdown.h"
#include "RazerSDK_GamerInfo.h"
#include "RazerSDK_Product.h"
#include "RazerSDK_Receipt.h"
#include "RazerSDK_JSONArray.h"
#include "RazerSDK_JSONObject.h"
#include "RazerSDK_GameMod.h"

#include <android/log.h>
#include <jni.h>
#include <stdio.h>
#include <string>

using namespace android_os_Bundle;
using namespace org_json_JSONObject;
using namespace org_json_JSONArray;
using namespace com_razerzone_store_sdk_content_GameMod;

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "RazerSDK_CallbackSingleton"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace RazerSDK
{
CallbackSingleton* CallbackSingleton::m_instance = NULL;

CallbackSingleton::CallbackSingleton() {
	CallbackSingleton::m_instance = this;

	m_callbacksContentDelete = NULL;
	m_callbacksContentDownload = NULL;
	m_callbacksContentInit = NULL;
	m_callbacksContentPublish = NULL;
	m_callbacksContentSave = NULL;
	m_callbacksContentSearchInstalled = NULL;
	m_callbacksContentSearchPublished = NULL;
	m_callbacksContentUnpublish = NULL;
	m_callbacksInitPlugin = NULL;
	m_callbacksRequestLogin = NULL;
	m_callbacksRequestGamerInfo = NULL;
	m_callbacksRequestProducts = NULL;
	m_callbacksRequestPurchase = NULL;
	m_callbacksRequestReceipts = NULL;
	m_callbacksShutdown = NULL;
}

CallbackSingleton::~CallbackSingleton() {
}

CallbackSingleton* CallbackSingleton::GetInstance() {
	if (!CallbackSingleton::m_instance) {
		CallbackSingleton::m_instance = new CallbackSingleton();
	}

	return CallbackSingleton::m_instance;
}

extern "C" {
	/// CallbacksInitPlugin

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnSuccess(JNIEnv* env, jobject thiz)
	{
	#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnSuccess***********");
	#endif

		CallbacksInitPlugin* callback = CallbackSingleton::GetInstance()->m_callbacksInitPlugin;
		if (callback)
		{
			callback->OnSuccess();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksInitPlugin is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksInitPlugin* callback = CallbackSingleton::GetInstance()->m_callbacksInitPlugin;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksInitPlugin is not set");
		}
#endif
	}

	/// CallbacksRequestLogin

	//com.ODK.CallbacksRequestLogin.CallbacksRequestLoginOnSuccess
	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnSuccess(JNIEnv* env, jobject thiz)
	{
	#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnSuccess***********");
	#endif

		CallbacksRequestLogin* callback = CallbackSingleton::GetInstance()->m_callbacksRequestLogin;
		if (callback)
		{
			callback->OnSuccess();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestLogin is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksRequestLogin* callback = CallbackSingleton::GetInstance()->m_callbacksRequestLogin;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestLogin is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnCancel(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnCancel***********");
#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnCancel: Returned to C");
#endif

		CallbacksRequestLogin* callback = CallbackSingleton::GetInstance()->m_callbacksRequestLogin;
		if (callback)
		{
			callback->OnCancel();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestLogin is not set");
		}
#endif
	}

	/// CallbacksRequestGamerInfo

	//com.ODK.CallbacksRequestGamerInfo.CallbacksRequestGamerInfoOnSuccess
	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnSuccess(JNIEnv* env, jobject thiz, jstring jsonData)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnSuccess***********");
#endif

		std::string strJsonData = env->GetStringUTFChars(jsonData, NULL);

		//char buffer[256];
		//sprintf(buffer, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnSuccess: Returned to C: %s", strJsonData.c_str());
		//LOGI(buffer);

		JSONObject jsonObject = JSONObject(strJsonData.c_str());

		// Parse example data
		RazerSDK::GamerInfo newGamerInfo;
		newGamerInfo.ParseJSON(jsonObject);

		CallbacksRequestGamerInfo* callback = CallbackSingleton::GetInstance()->m_callbacksRequestGamerInfo;
		if (callback)
		{
			callback->OnSuccess(newGamerInfo);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestGamerInfo is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksRequestGamerInfo* callback = CallbackSingleton::GetInstance()->m_callbacksRequestGamerInfo;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestGamerInfo is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnCancel(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnCancel***********");
#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnCancel: Returned to C");
#endif

		CallbacksRequestGamerInfo* callback = CallbackSingleton::GetInstance()->m_callbacksRequestGamerInfo;
		if (callback)
		{
			callback->OnCancel();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestGamerInfo is not set");
		}
#endif
	}

	/// CallbacksRequestProducts

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnSuccess(JNIEnv* env, jobject thiz, jstring jsonData)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnSuccess***********");
#endif

		std::string strJsonData = env->GetStringUTFChars(jsonData, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnSuccess: Returned to C: %s", strJsonData.c_str());
#endif

		JSONArray jsonArray = JSONArray(strJsonData.c_str());

		std::vector<Product> products;

		for (int i = 0; i < jsonArray.length(); i++)
		{
			RazerSDK::Product newProduct;
			JSONObject jsonObject = jsonArray.getJSONObject(i);
			newProduct.ParseJSON(jsonObject);

			products.push_back(newProduct);
		}

		CallbacksRequestProducts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestProducts;
		if (callback)
		{
			callback->OnSuccess(products);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestProducts is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksRequestProducts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestProducts;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestProducts is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnCancel(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnCancel***********");
#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnCancel: Returned to C");
#endif

		CallbacksRequestProducts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestProducts;
		if (callback)
		{
			callback->OnCancel();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestProducts is not set");
		}
#endif
	}

	/// CallbacksRequestPurchase

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnSuccess(JNIEnv* env, jobject thiz, jstring jsonData)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnSuccess***********");
#endif

		std::string strJsonData = env->GetStringUTFChars(jsonData, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnSuccess: Returned to C: %s", strJsonData.c_str());
#endif

		JSONObject jsonObject = JSONObject(strJsonData.c_str());

		RazerSDK::PurchaseResult purchaseResult;
		purchaseResult.ParseJSON(jsonObject);

		CallbacksRequestPurchase* callback = CallbackSingleton::GetInstance()->m_callbacksRequestPurchase;
		if (callback)
		{
			callback->OnSuccess(purchaseResult);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestPurchase is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksRequestPurchase* callback = CallbackSingleton::GetInstance()->m_callbacksRequestPurchase;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestPurchase is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnCancel(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnCancel***********");
#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnCancel: Returned to C");
#endif

		CallbacksRequestPurchase* callback = CallbackSingleton::GetInstance()->m_callbacksRequestPurchase;
		if (callback)
		{
			callback->OnCancel();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestPurchase is not set");
		}
#endif
	}

	/// CallbacksRequestReceipts

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnSuccess(JNIEnv* env, jobject thiz, jstring jsonData)
	{
	#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnSuccess***********");
	#endif

		std::string strJsonData = env->GetStringUTFChars(jsonData, NULL);

	#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnSuccess: Returned to C: %s", strJsonData.c_str());
	#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parsing JSON Data");
#endif

		JSONArray jsonArray = JSONArray(strJsonData.c_str());

		std::vector<Receipt> receipts;

		for (int i = 0; i < jsonArray.length(); i++)
		{
			RazerSDK::Receipt newReceipt;
			JSONObject jsonObject = jsonArray.getJSONObject(i);
			newReceipt.ParseJSON(jsonObject);

			receipts.push_back(newReceipt);
		}

		CallbacksRequestReceipts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestReceipts;
		if (callback)
		{
			callback->OnSuccess(receipts);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestReceipts is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksRequestReceipts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestReceipts;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestReceipts is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnCancel(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnCancel***********");
#endif

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnCancel: Returned to C");
#endif

		CallbacksRequestReceipts* callback = CallbackSingleton::GetInstance()->m_callbacksRequestReceipts;
		if (callback)
		{
			callback->OnCancel();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksRequestReceipts is not set");
		}
#endif
	}

	/// CallbacksShutdown

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnSuccess(JNIEnv* env, jobject thiz)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnSuccess***********");
#endif

		CallbacksShutdown* callback = CallbackSingleton::GetInstance()->m_callbacksShutdown;
		if (callback)
		{
			callback->OnSuccess();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksShutdown is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnFailure(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "***********Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnFailure***********");
#endif

		std::string strErrorMessage = env->GetStringUTFChars(errorMessage, NULL);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnFailure: Returned to C: %d %s", errorCode, strErrorMessage.c_str());
#endif

		CallbacksShutdown* callback = CallbackSingleton::GetInstance()->m_callbacksShutdown;
		if (callback)
		{
			callback->OnFailure(errorCode, strErrorMessage);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksShutdown is not set");
		}
#endif
	}

	/// CallbacksContentDelete

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDelete_CallbacksContentDeleteOnDeleteFailed(JNIEnv* env, jobject thiz, jobject gameMod, jint code, jstring reason)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentDelete* callback = CallbackSingleton::GetInstance()->m_callbacksContentDelete;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnDeleteFailed(newGameMod, code, strReason);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentDelete is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDelete_CallbacksContentDeleteOnDeleted(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentDelete* callback = CallbackSingleton::GetInstance()->m_callbacksContentDelete;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnDeleted(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentDelete is not set");
		}
#endif
	}

	/// CallbacksContentDownload

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnProgress(JNIEnv* env, jobject thiz, jobject gameMod, jint progress)
	{
		CallbacksContentDownload* callback = CallbackSingleton::GetInstance()->m_callbacksContentDownload;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnProgress(newGameMod, progress);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentDownload is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnFailed(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentDownload* callback = CallbackSingleton::GetInstance()->m_callbacksContentDownload;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnFailed(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentDownload is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnComplete(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentDownload* callback = CallbackSingleton::GetInstance()->m_callbacksContentDownload;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnComplete(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentDownload is not set");
		}
#endif
	}

	/// CallbacksContentInit

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentInit_CallbacksContentInitOnInitialized(JNIEnv* env, jobject thiz)
	{
		CallbacksContentInit* callback = CallbackSingleton::GetInstance()->m_callbacksContentInit;
		if (callback)
		{
			callback->OnInitialized();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentInit is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentInit_CallbacksContentInitOnDestroyed(JNIEnv* env, jobject thiz)
	{
		CallbacksContentInit* callback = CallbackSingleton::GetInstance()->m_callbacksContentInit;
		if (callback)
		{
			callback->OnDestroyed();
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentInit is not set");
		}
#endif
	}

	/// CallbacksContentSave

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSave_CallbacksContentSaveOnError(JNIEnv* env, jobject thiz, jobject gameMod, jint code, jstring reason)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentSave* callback = CallbackSingleton::GetInstance()->m_callbacksContentSave;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnError(newGameMod, code, strReason);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSave is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSave_CallbacksContentSaveOnSuccess(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentSave* callback = CallbackSingleton::GetInstance()->m_callbacksContentSave;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnSuccess(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSave is not set");
		}
#endif
	}

	/// CallbacksContentPublish

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentPublish_CallbacksContentPublishOnError(JNIEnv* env, jobject thiz, jobject gameMod, jint code, jstring reason, jobject bundle)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentPublish* callback = CallbackSingleton::GetInstance()->m_callbacksContentPublish;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			Bundle newBundle = Bundle(bundle);
			callback->OnError(newGameMod, code, strReason, newBundle);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentPublish is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentPublish_CallbacksContentPublishOnSuccess(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentPublish* callback = CallbackSingleton::GetInstance()->m_callbacksContentPublish;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnSuccess(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentPublish is not set");
		}
#endif
	}

	/// CallbacksContentSearchInstalled

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchInstalled_CallbacksContentSearchInstalledOnError(JNIEnv* env, jobject thiz, jint code, jstring reason)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentSearchInstalled* callback = CallbackSingleton::GetInstance()->m_callbacksContentSearchInstalled;
		if (callback)
		{
			callback->OnError(code, strReason);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSearchInstalled is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchInstalled_CallbacksContentSearchInstalledOnResults(JNIEnv* env, jobject thiz, jobjectArray gameMods, jint count)
	{
		CallbacksContentSearchInstalled* callback = CallbackSingleton::GetInstance()->m_callbacksContentSearchInstalled;
		if (callback)
		{
			std::vector<GameMod> newGameMods;
			jsize length = env->GetArrayLength(gameMods);
			for (jsize index(0); index < length; ++index)
			{
				jobject localRef = (jobject)env->GetObjectArrayElement(gameMods, index);
				jobject globalRef = (jobject)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
				GameMod newGameMod = GameMod::CreateObject(globalRef);
				newGameMods.push_back(newGameMod);

			}
			callback->OnResults(newGameMods, count);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSearchInstalled is not set");
		}
#endif
	}

	/// CallbacksContentSearchPublished

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchPublished_CallbacksContentSearchPublishedOnError(JNIEnv* env, jobject thiz, jint code, jstring reason)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentSearchPublished* callback = CallbackSingleton::GetInstance()->m_callbacksContentSearchPublished;
		if (callback)
		{
			callback->OnError(code, strReason);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSearchPublished is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchPublished_CallbacksContentSearchPublishedOnResults(JNIEnv* env, jobject thiz, jobjectArray gameMods, jint count)
	{
		CallbacksContentSearchPublished* callback = CallbackSingleton::GetInstance()->m_callbacksContentSearchPublished;
		if (callback)
		{
			std::vector<GameMod> newGameMods;
			jsize length = env->GetArrayLength(gameMods);
			for (jsize index(0); index < length; ++index)
			{
				jobject localRef = (jobject)env->GetObjectArrayElement(gameMods, index);
				jobject globalRef = (jobject)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
				GameMod newGameMod = GameMod::CreateObject(globalRef);
				newGameMods.push_back(newGameMod);

			}
			callback->OnResults(newGameMods, count);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentSearchPublished is not set");
		}
#endif
	}

	/// CallbacksContentUnpublish

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentUnpublish_CallbacksContentUnpublishOnError(JNIEnv* env, jobject thiz, jobject gameMod, jint code, jstring reason)
	{
		std::string strReason = env->GetStringUTFChars(reason, NULL);

		CallbacksContentUnpublish* callback = CallbackSingleton::GetInstance()->m_callbacksContentUnpublish;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnError(newGameMod, code, strReason);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentUnpublish is not set");
		}
#endif
	}

	JNIEXPORT void JNICALL Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentUnpublish_CallbacksContentUnpublishOnSuccess(JNIEnv* env, jobject thiz, jobject gameMod)
	{
		CallbacksContentUnpublish* callback = CallbackSingleton::GetInstance()->m_callbacksContentUnpublish;
		if (callback)
		{
			GameMod newGameMod = GameMod::CreateObject(gameMod);
			callback->OnSuccess(newGameMod);
		}
#if ENABLE_VERBOSE_LOGGING
		else
		{
			__android_log_print(ANDROID_LOG_WARN, LOG_TAG, "CallbacksContentUnpublish is not set");
		}
#endif
	}
}

void RegisterNativeMethod(JNIEnv* env, std::string methodName,
	std::string className, std::string signature, void* method,
	JNINativeMethod* savedNativeMethod) {
///*
#if ENABLE_VERBOSE_LOGGING
__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,
		"Registering Native Method: %s className=%s signature=%s",
		methodName.c_str(), className.c_str(), signature.c_str());
#endif
//*/

//Register the Native method on the object
*savedNativeMethod = {methodName.c_str(), signature.c_str(), method};

// Find the class using the native
jclass CallerJavaClass = FAndroidApplication::FindJavaClass(className.c_str());
if (env->RegisterNatives(CallerJavaClass, savedNativeMethod, 1)) {
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG,
			"Could not register native method: %s", methodName.c_str());
#endif
}
}

//
// Native Callbacks for InitPlugin
//

JNINativeMethod g_nativeCallbacksInitPluginOnSuccess;
JNINativeMethod g_nativeCallbacksInitPluginOnFailure;

//
// Native Callbacks for RequestLogin
//

JNINativeMethod g_nativeCallbacksRequestLoginOnSuccess;
JNINativeMethod g_nativeCallbacksRequestLoginOnFailure;
JNINativeMethod g_nativeCallbacksRequestLoginOnCancel;

//
// Native Callbacks for RequestGamerInfo
//

JNINativeMethod g_nativeCallbacksRequestGamerInfoOnSuccess;
JNINativeMethod g_nativeCallbacksRequestGamerInfoOnFailure;
JNINativeMethod g_nativeCallbacksRequestGamerInfoOnCancel;

//
// Native Callbacks for RequestProducts
//

JNINativeMethod g_nativeCallbacksRequestProductsOnSuccess;
JNINativeMethod g_nativeCallbacksRequestProductsOnFailure;
JNINativeMethod g_nativeCallbacksRequestProductsOnCancel;

//
// Native Callbacks for RequestPurchase
//

JNINativeMethod g_nativeCallbacksRequestPurchaseOnSuccess;
JNINativeMethod g_nativeCallbacksRequestPurchaseOnFailure;
JNINativeMethod g_nativeCallbacksRequestPurchaseOnCancel;

//
// Native Callbacks for RequestReceipts
//

JNINativeMethod g_nativeCallbacksRequestReceiptsOnSuccess;
JNINativeMethod g_nativeCallbacksRequestReceiptsOnFailure;
JNINativeMethod g_nativeCallbacksRequestReceiptsOnCancel;

//
// Native Callbacks for Shutdown
//

JNINativeMethod g_nativeCallbacksShutdownOnSuccess;
JNINativeMethod g_nativeCallbacksShutdownOnFailure;

//
// Native Callbacks for ContentDelete
//

JNINativeMethod g_nativeCallbacksContentDeleteOnDeleteFailed;
JNINativeMethod g_nativeCallbacksContentDeleteOnDeleted;

//
// Native Callbacks for ContentDownload
//

JNINativeMethod g_nativeCallbacksContentDownloadOnProgress;
JNINativeMethod g_nativeCallbacksContentDownloadOnFailed;
JNINativeMethod g_nativeCallbacksContentDownloadOnComplete;

//
// Native Callbacks for ContentInit
//

JNINativeMethod g_nativeCallbacksContentInitOnInitialized;
JNINativeMethod g_nativeCallbacksContentInitOnDestroyed;

//
// Native Callbacks for ContentSave
//

JNINativeMethod g_nativeCallbacksContentSaveOnError;
JNINativeMethod g_nativeCallbacksContentSaveOnSuccess;

//
// Native Callbacks for ContentPublish
//

JNINativeMethod g_nativeCallbacksContentPublishOnError;
JNINativeMethod g_nativeCallbacksContentPublishOnSuccess;

//
// Native Callbacks for ContentSearchInstalled
//

JNINativeMethod g_nativeCallbacksContentSearchInstalledOnError;
JNINativeMethod g_nativeCallbacksContentSearchInstalledOnResults;

//
// Native Callbacks for ContentSearchPublished
//

JNINativeMethod g_nativeCallbacksContentSearchPublishedOnError;
JNINativeMethod g_nativeCallbacksContentSearchPublishedOnResults;

//
// Native Callbacks for ContentUnpublish
//

JNINativeMethod g_nativeCallbacksContentUnpublishOnError;
JNINativeMethod g_nativeCallbacksContentUnpublishOnSuccess;

int CallbackSingleton::InitJNI() {
	JNIEnv* env = FAndroidApplication::GetJavaEnv();

//
// Register Native Callbacks for InitPlugin
//

RegisterNativeMethod(env, "CallbacksInitPluginOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksInitPlugin", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnSuccess,
		&g_nativeCallbacksInitPluginOnSuccess);

RegisterNativeMethod(env, "CallbacksInitPluginOnFailure",
		"com/razerzone/store/sdk/engine/unreal/CallbacksInitPlugin", "(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksInitPlugin_CallbacksInitPluginOnFailure,
		&g_nativeCallbacksInitPluginOnFailure);

//
// Register Native Callbacks for RequestLogin
//

RegisterNativeMethod(env, "CallbacksRequestLoginOnSuccess",
	"com/razerzone/store/sdk/engine/unreal/CallbacksRequestLogin", "()V",
	(void*)&Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnSuccess,
	&g_nativeCallbacksRequestLoginOnSuccess);

RegisterNativeMethod(env, "CallbacksRequestLoginOnFailure",
	"com/razerzone/store/sdk/engine/unreal/CallbacksRequestLogin",
	"(ILjava/lang/String;)V",
	(void*)&Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnFailure,
	&g_nativeCallbacksRequestLoginOnFailure);

RegisterNativeMethod(env, "CallbacksRequestLoginOnCancel",
	"com/razerzone/store/sdk/engine/unreal/CallbacksRequestLogin", "()V",
	(void*)&Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestLogin_CallbacksRequestLoginOnCancel,
	&g_nativeCallbacksRequestLoginOnCancel);

//
// Register Native Callbacks for RequestGamerInfo
//

RegisterNativeMethod(env, "CallbacksRequestGamerInfoOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestGamerInfo", "(Ljava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnSuccess,
		&g_nativeCallbacksRequestGamerInfoOnSuccess);

RegisterNativeMethod(env, "CallbacksRequestGamerInfoOnFailure",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestGamerInfo",
		"(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnFailure,
		&g_nativeCallbacksRequestGamerInfoOnFailure);

RegisterNativeMethod(env, "CallbacksRequestGamerInfoOnCancel",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestGamerInfo", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestGamerInfo_CallbacksRequestGamerInfoOnCancel,
		&g_nativeCallbacksRequestGamerInfoOnCancel);

//
// Register Native Callbacks for RequestProducts
//

RegisterNativeMethod(env, "CallbacksRequestProductsOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestProducts", "(Ljava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnSuccess,
		&g_nativeCallbacksRequestProductsOnSuccess);

RegisterNativeMethod(env, "CallbacksRequestProductsOnFailure",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestProducts", "(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnFailure,
		&g_nativeCallbacksRequestProductsOnFailure);

RegisterNativeMethod(env, "CallbacksRequestProductsOnCancel",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestProducts", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestProducts_CallbacksRequestProductsOnCancel,
		&g_nativeCallbacksRequestProductsOnCancel);

//
// Register Native Callbacks for RequestPurchase
//

RegisterNativeMethod(env, "CallbacksRequestPurchaseOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestPurchase", "(Ljava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnSuccess,
		&g_nativeCallbacksRequestPurchaseOnSuccess);

RegisterNativeMethod(env, "CallbacksRequestPurchaseOnFailure",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestPurchase", "(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnFailure,
		&g_nativeCallbacksRequestPurchaseOnFailure);

RegisterNativeMethod(env, "CallbacksRequestPurchaseOnCancel",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestPurchase", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestPurchase_CallbacksRequestPurchaseOnCancel,
		&g_nativeCallbacksRequestPurchaseOnCancel);

//
// Register Native Callbacks for RequestReceipts
//

RegisterNativeMethod(env, "CallbacksRequestReceiptsOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestReceipts", "(Ljava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnSuccess,
		&g_nativeCallbacksRequestReceiptsOnSuccess);

RegisterNativeMethod(env, "CallbacksRequestReceiptsOnFailure",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestReceipts", "(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnFailure,
		&g_nativeCallbacksRequestReceiptsOnFailure);

RegisterNativeMethod(env, "CallbacksRequestReceiptsOnCancel",
		"com/razerzone/store/sdk/engine/unreal/CallbacksRequestReceipts", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksRequestReceipts_CallbacksRequestReceiptsOnCancel,
		&g_nativeCallbacksRequestReceiptsOnCancel);

//
// Register Native Callbacks for Shutdown
//

RegisterNativeMethod(env, "CallbacksShutdownOnSuccess",
	"com/razerzone/store/sdk/engine/unreal/CallbacksShutdown", "()V",
	(void*)&Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnSuccess,
	&g_nativeCallbacksShutdownOnSuccess);

RegisterNativeMethod(env, "CallbacksShutdownOnFailure",
	"com/razerzone/store/sdk/engine/unreal/CallbacksShutdown", "(ILjava/lang/String;)V",
	(void*)&Java_com_razerzone_store_sdk_engine_unreal_CallbacksShutdown_CallbacksShutdownOnFailure,
	&g_nativeCallbacksShutdownOnFailure);

//
// Register Native Callbacks for ContentDelete
//

RegisterNativeMethod(env, "CallbacksContentDeleteOnDeleteFailed",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentDelete",
		"(Lcom/razerzone/store/sdk/content/GameMod;ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDelete_CallbacksContentDeleteOnDeleteFailed,
		&g_nativeCallbacksContentDeleteOnDeleteFailed);

RegisterNativeMethod(env, "CallbacksContentDeleteOnDeleted",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentDelete",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDelete_CallbacksContentDeleteOnDeleted,
		&g_nativeCallbacksContentDeleteOnDeleted);

//
// Register Native Callbacks for ContentDownload
//

RegisterNativeMethod(env, "CallbacksContentDownloadOnProgress",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentDownload",
		"(Lcom/razerzone/store/sdk/content/GameMod;I)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnProgress,
		&g_nativeCallbacksContentDownloadOnProgress);

RegisterNativeMethod(env, "CallbacksContentDownloadOnFailed",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentDownload",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnFailed,
		&g_nativeCallbacksContentDownloadOnFailed);

RegisterNativeMethod(env, "CallbacksContentDownloadOnComplete",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentDownload",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentDownload_CallbacksContentDownloadOnComplete,
		&g_nativeCallbacksContentDownloadOnComplete);

//
// Register Native Callbacks for ContentInit
//

RegisterNativeMethod(env, "CallbacksContentInitOnInitialized",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentInit", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentInit_CallbacksContentInitOnInitialized,
		&g_nativeCallbacksContentInitOnInitialized);

RegisterNativeMethod(env, "CallbacksContentInitOnDestroyed",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentInit", "()V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentInit_CallbacksContentInitOnDestroyed,
		&g_nativeCallbacksContentInitOnDestroyed);

//
// Register Native Callbacks for ContentPublish
//

RegisterNativeMethod(env, "CallbacksContentPublishOnError",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentPublish",
		"(Lcom/razerzone/store/sdk/content/GameMod;ILjava/lang/String;Landroid/os/Bundle;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentPublish_CallbacksContentPublishOnError,
		&g_nativeCallbacksContentPublishOnError);

RegisterNativeMethod(env, "CallbacksContentPublishOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentPublish",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentPublish_CallbacksContentPublishOnSuccess,
		&g_nativeCallbacksContentPublishOnSuccess);

//
// Register Native Callbacks for ContentSave
//

RegisterNativeMethod(env, "CallbacksContentSaveOnError",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSave",
		"(Lcom/razerzone/store/sdk/content/GameMod;ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSave_CallbacksContentSaveOnError,
		&g_nativeCallbacksContentSaveOnError);

RegisterNativeMethod(env, "CallbacksContentSaveOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSave",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSave_CallbacksContentSaveOnSuccess,
		&g_nativeCallbacksContentSaveOnSuccess);

//
// Register Native Callbacks for ContentSearchInstalled
//

RegisterNativeMethod(env, "CallbacksContentSearchInstalledOnError",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSearchInstalled",
		"(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchInstalled_CallbacksContentSearchInstalledOnError,
		&g_nativeCallbacksContentSearchInstalledOnError);

RegisterNativeMethod(env, "CallbacksContentSearchInstalledOnResults",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSearchInstalled",
		"([Lcom/razerzone/store/sdk/content/GameMod;I)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchInstalled_CallbacksContentSearchInstalledOnResults,
		&g_nativeCallbacksContentSearchInstalledOnResults);

//
// Register Native Callbacks for ContentSearchPublished
//

RegisterNativeMethod(env, "CallbacksContentSearchPublishedOnError",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSearchPublished",
		"(ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchPublished_CallbacksContentSearchPublishedOnError,
		&g_nativeCallbacksContentSearchPublishedOnError);

RegisterNativeMethod(env, "CallbacksContentSearchPublishedOnResults",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentSearchPublished",
		"([Lcom/razerzone/store/sdk/content/GameMod;I)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentSearchPublished_CallbacksContentSearchPublishedOnResults,
		&g_nativeCallbacksContentSearchPublishedOnResults);

//
// Register Native Callbacks for ContentUnpublish
//

RegisterNativeMethod(env, "CallbacksContentUnpublishOnError",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentUnpublish",
		"(Lcom/razerzone/store/sdk/content/GameMod;ILjava/lang/String;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentUnpublish_CallbacksContentUnpublishOnError,
		&g_nativeCallbacksContentUnpublishOnError);

RegisterNativeMethod(env, "CallbacksContentUnpublishOnSuccess",
		"com/razerzone/store/sdk/engine/unreal/CallbacksContentUnpublish",
		"(Lcom/razerzone/store/sdk/content/GameMod;)V",
		(void*) &Java_com_razerzone_store_sdk_engine_unreal_CallbacksContentUnpublish_CallbacksContentUnpublishOnSuccess,
		&g_nativeCallbacksContentUnpublishOnSuccess);

//
// DONE
//

return JNI_OK;
}
}

#endif
