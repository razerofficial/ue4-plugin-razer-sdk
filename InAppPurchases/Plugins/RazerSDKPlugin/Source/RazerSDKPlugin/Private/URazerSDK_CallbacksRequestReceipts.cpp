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

#include "URazerSDK_CallbacksRequestReceipts.h"

#if PLATFORM_ANDROID

using namespace RazerSDK;

void URazerSDK_CallbacksRequestReceipts::OnSuccess(const std::vector<Receipt>& receipts)
{
	TArray<FRazerSDK_Receipt> newReceipts;
	for (const Receipt& receipt : receipts)
	{
		FRazerSDK_Receipt fReceipt;
		fReceipt.Currency = receipt.Currency.c_str();
		fReceipt.GamerUuid = receipt.GamerUuid.c_str();
		fReceipt.GeneratedDate = receipt.GeneratedDate.c_str();
		fReceipt.Identifier = receipt.Identifier.c_str();
		fReceipt.LocalPrice = receipt.LocalPrice;
		fReceipt.PriceInCents = receipt.PriceInCents;
		fReceipt.PurchaseDate = receipt.PurchaseDate.c_str();
		fReceipt.Uuid = receipt.Uuid.c_str();
		
		newReceipts.Add(fReceipt);
	}
	_mOnSuccess.ExecuteIfBound(newReceipts);
}

void URazerSDK_CallbacksRequestReceipts::OnFailure(int errorCode, const std::string& errorMessage)
{
	_mOnFailure.ExecuteIfBound(errorCode, errorMessage.c_str());
}

void URazerSDK_CallbacksRequestReceipts::OnCancel()
{
	_mOnCancel.ExecuteIfBound();
}

#endif
