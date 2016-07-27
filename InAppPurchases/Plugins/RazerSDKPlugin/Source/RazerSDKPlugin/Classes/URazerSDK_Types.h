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

#include "Runtime/CoreUObject/Public/UObject/UObject.h"

#include "URazerSDK_Types.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDelegateRazerSDKOnSuccess);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateRazerSDKOnFailure, int32, errorCode, FString, errorMessage);

DECLARE_DYNAMIC_DELEGATE(FDelegateRazerSDKOnCancel);

UCLASS()
class URazerSDK_Types : public UObject
{
	GENERATED_UCLASS_BODY()
};

USTRUCT(BlueprintType)
struct FRazerSDK_GamerInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Uuid;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateRazerSDKOnSuccessRequestGamerInfo, FRazerSDK_GamerInfo, gamerInfo);

USTRUCT(BlueprintType)
struct FRazerSDK_Product
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString CurrencyCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString DeveloperName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Identifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	float LocalPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	float OriginalPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	float PercentOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	int PriceInCents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString ProductType;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateRazerSDKOnSuccessRequestProducts, const TArray<FRazerSDK_Product>&, products);

USTRUCT(BlueprintType)
struct FRazerSDK_PurchaseResult
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Identifier;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateRazerSDKOnSuccessRequestPurchase, FRazerSDK_PurchaseResult, purchaseResult);

USTRUCT(BlueprintType)
struct FRazerSDK_Receipt
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Currency;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString GamerUuid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString GeneratedDate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Identifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	float LocalPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	int PriceInCents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString PurchaseDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RazerSDK")
	FString Uuid;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateRazerSDKOnSuccessRequestReceipts, const TArray<FRazerSDK_Receipt>&, receipts);
