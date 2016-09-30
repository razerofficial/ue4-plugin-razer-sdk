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

#include "URazerSDK.h"

#include "RazerSDK_Plugin.h"

#if PLATFORM_ANDROID
using namespace RazerSDK;
#endif

URazerSDK_CallbacksInitPlugin URazerSDK::_sCallbacksInitPlugin = URazerSDK_CallbacksInitPlugin();
URazerSDK_CallbacksRequestLogin URazerSDK::_sCallbacksRequestLogin = URazerSDK_CallbacksRequestLogin();
URazerSDK_CallbacksRequestGamerInfo URazerSDK::_sCallbacksRequestGamerInfo = URazerSDK_CallbacksRequestGamerInfo();
URazerSDK_CallbacksRequestProducts URazerSDK::_sCallbacksRequestProducts = URazerSDK_CallbacksRequestProducts();
URazerSDK_CallbacksRequestPurchase URazerSDK::_sCallbacksRequestPurchase = URazerSDK_CallbacksRequestPurchase();
URazerSDK_CallbacksRequestReceipts URazerSDK::_sCallbacksRequestReceipts = URazerSDK_CallbacksRequestReceipts();
URazerSDK_CallbacksShutdown URazerSDK::_sCallbacksShutdown = URazerSDK_CallbacksShutdown();

URazerSDK::URazerSDK(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URazerSDK::InitPlugin(FString secretAPiKey, FDelegateRazerSDKOnSuccess onSuccess, FDelegateRazerSDKOnFailure onFailure)
{
	_sCallbacksInitPlugin._mOnSuccess = onSuccess;
	_sCallbacksInitPlugin._mOnFailure = onFailure;
#if PLATFORM_ANDROID
	string strSecretApiKey = TCHAR_TO_ANSI(*secretAPiKey);
	Plugin::initPlugin(strSecretApiKey, &_sCallbacksInitPlugin);
#else
	_sCallbacksInitPlugin._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::RequestLogin(FDelegateRazerSDKOnSuccess onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel)
{
	_sCallbacksRequestLogin._mOnSuccess = onSuccess;
	_sCallbacksRequestLogin._mOnFailure = onFailure;
	_sCallbacksRequestLogin._mOnCancel = onCancel;
#if PLATFORM_ANDROID
	Plugin::requestLogin(&_sCallbacksRequestLogin);
#else
	_sCallbacksRequestLogin._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::RequestGamerInfo(FDelegateRazerSDKOnSuccessRequestGamerInfo onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel)
{
	_sCallbacksRequestGamerInfo._mOnSuccess = onSuccess;
	_sCallbacksRequestGamerInfo._mOnFailure = onFailure;
	_sCallbacksRequestGamerInfo._mOnCancel = onCancel;
#if PLATFORM_ANDROID
	Plugin::requestGamerInfo(&_sCallbacksRequestGamerInfo);
#else
	_sCallbacksRequestGamerInfo._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::RequestProducts(const TArray<FString>& products, FDelegateRazerSDKOnSuccessRequestProducts onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel)
{
	_sCallbacksRequestProducts._mOnSuccess = onSuccess;
	_sCallbacksRequestProducts._mOnFailure = onFailure;
	_sCallbacksRequestProducts._mOnCancel = onCancel;
#if PLATFORM_ANDROID
	std::vector<std::string> newProducts;
	for (const FString& identifier : products)
	{
		string strIdentifier = TCHAR_TO_ANSI(*identifier);
		newProducts.push_back(strIdentifier);
	}
	Plugin::requestProducts(newProducts, &_sCallbacksRequestProducts);
#else
	_sCallbacksRequestProducts._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::RequestPurchase(const FString& identifier, const FString& productType, FDelegateRazerSDKOnSuccessRequestPurchase onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel)
{
	_sCallbacksRequestPurchase._mOnSuccess = onSuccess;
	_sCallbacksRequestPurchase._mOnFailure = onFailure;
	_sCallbacksRequestPurchase._mOnCancel = onCancel;
#if PLATFORM_ANDROID
	string strIdentifier = TCHAR_TO_ANSI(*identifier);
	string strProductType = TCHAR_TO_ANSI(*productType);
	Plugin::requestPurchase(strIdentifier, strProductType, &_sCallbacksRequestPurchase);
#else
	_sCallbacksRequestPurchase._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::RequestReceipts(FDelegateRazerSDKOnSuccessRequestReceipts onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel)
{
	_sCallbacksRequestReceipts._mOnSuccess = onSuccess;
	_sCallbacksRequestReceipts._mOnFailure = onFailure;
	_sCallbacksRequestReceipts._mOnCancel = onCancel;
#if PLATFORM_ANDROID
	Plugin::requestReceipts(&_sCallbacksRequestReceipts);
#else
	_sCallbacksRequestReceipts._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::Shutdown(FDelegateRazerSDKOnSuccess onSuccess, FDelegateRazerSDKOnFailure onFailure)
{
	_sCallbacksShutdown._mOnSuccess = onSuccess;
	_sCallbacksShutdown._mOnFailure = onFailure;
#if PLATFORM_ANDROID
	Plugin::shutdown(&_sCallbacksShutdown);
#else
	_sCallbacksShutdown._mOnFailure.ExecuteIfBound(0, "Platform not supported!");
#endif
}

void URazerSDK::Quit()
{
#if PLATFORM_ANDROID
	Plugin::quit();
#else
#endif
}