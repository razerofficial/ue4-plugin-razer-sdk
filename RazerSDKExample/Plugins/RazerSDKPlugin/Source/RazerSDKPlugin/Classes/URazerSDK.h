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

#pragma once

#include "Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h"

#include "URazerSDK_CallbacksInitPlugin.h"
#include "URazerSDK_CallbacksRequestGamerInfo.h"
#include "URazerSDK_CallbacksRequestProducts.h"
#include "URazerSDK_CallbacksRequestPurchase.h"
#include "URazerSDK_CallbacksRequestReceipts.h"
#include "URazerSDK_CallbacksShutdown.h"
#include "URazerSDK_Types.h"

#include "URazerSDK.generated.h"

UCLASS()
class URazerSDK : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void InitPlugin(FString secretAPiKey, FDelegateRazerSDKOnSuccess onSuccess, FDelegateRazerSDKOnFailure onFailure);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void RequestGamerInfo(FDelegateRazerSDKOnSuccessRequestGamerInfo onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void RequestProducts(const TArray<FString>& products, FDelegateRazerSDKOnSuccessRequestProducts onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void RequestPurchase(const FString& identifier, const FString& productType, FDelegateRazerSDKOnSuccessRequestPurchase onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void RequestReceipts(FDelegateRazerSDKOnSuccessRequestReceipts onSuccess, FDelegateRazerSDKOnFailure onFailure, FDelegateRazerSDKOnCancel onCancel);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void Shutdown(FDelegateRazerSDKOnSuccess onSuccess, FDelegateRazerSDKOnFailure onFailure);

	UFUNCTION(BlueprintCallable, Category = RazerSDK)
	static void Quit();

private:

	static URazerSDK_CallbacksInitPlugin _sCallbacksInitPlugin;
	static URazerSDK_CallbacksRequestGamerInfo _sCallbacksRequestGamerInfo;
	static URazerSDK_CallbacksRequestProducts _sCallbacksRequestProducts;
	static URazerSDK_CallbacksRequestPurchase _sCallbacksRequestPurchase;
	static URazerSDK_CallbacksRequestReceipts _sCallbacksRequestReceipts;
	static URazerSDK_CallbacksShutdown _sCallbacksShutdown;
};
