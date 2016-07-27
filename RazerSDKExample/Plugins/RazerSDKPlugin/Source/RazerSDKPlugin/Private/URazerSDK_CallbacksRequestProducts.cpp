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

#include "URazerSDK_CallbacksRequestProducts.h"

#if PLATFORM_ANDROID

using namespace RazerSDK;
using namespace std;

void URazerSDK_CallbacksRequestProducts::OnSuccess(const vector<Product>& products)
{
	TArray<FRazerSDK_Product> newProducts;
	for (int index = 0; index < products.size(); ++index)
	{
		Product product = products[index];
		FRazerSDK_Product fProduct;
		fProduct.CurrencyCode = product.CurrencyCode.c_str();
		fProduct.Description = product.Description.c_str();
		fProduct.DeveloperName = product.DeveloperName.c_str();
		fProduct.Identifier = product.Identifier.c_str();
		fProduct.LocalPrice = product.LocalPrice;
		fProduct.Name = product.Name.c_str();
		fProduct.OriginalPrice = product.OriginalPrice;
		fProduct.PercentOff = product.PercentOff;
		fProduct.PriceInCents = product.PriceInCents;
		fProduct.ProductType = product.ProductType.c_str();
		newProducts.Add(fProduct);
	}
	_mOnSuccess.ExecuteIfBound(newProducts);
}

void URazerSDK_CallbacksRequestProducts::OnFailure(int errorCode, const string& errorMessage)
{
	_mOnFailure.ExecuteIfBound(errorCode, errorMessage.c_str());
}

void URazerSDK_CallbacksRequestProducts::OnCancel()
{
	_mOnCancel.ExecuteIfBound();
}

#endif
