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

#include "RazerSDK_Product.h"
#include "RazerSDK_JSONObject.h"

#include <string>

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

namespace RazerSDK
{
	void Product::Init()
	{
		CurrencyCode = "";
		Description = "";
		DeveloperName = "";
		Identifier = "";
		LocalPrice = 0;
		Name = "";
		OriginalPrice = 0;
		PercentOff = 0;
		PriceInCents = 0;
		ProductType = "";
	}

	void Product::ParseJSON(const org_json_JSONObject::JSONObject& jsonObject)
	{
		Init();

		std::string field;

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse currencyCode");
#endif
		field = "currencyCode";
		if (jsonObject.has(field))
		{
			CurrencyCode = jsonObject.getString(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse description");
#endif
		field = "description";
		if (jsonObject.has(field))
		{
			Description = jsonObject.getString(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse developerName");
#endif
		field = "developerName";
		if (jsonObject.has(field))
		{
			DeveloperName = jsonObject.getString(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse identifier");
#endif
		field = "identifier";
		if (jsonObject.has(field))
		{
			Identifier = jsonObject.getString(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse localPrice");
#endif
		field = "localPrice";
		if (jsonObject.has(field))
		{
			LocalPrice = jsonObject.getDouble(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse name");
#endif
		field = "name";
		if (jsonObject.has(field))
		{
			Name = jsonObject.getString(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse originalPrice");
#endif
		field = "originalPrice";
		if (jsonObject.has(field))
		{
			OriginalPrice = jsonObject.getDouble(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse percentOff");
#endif
		field = "percentOff";
		if (jsonObject.has(field))
		{
			PercentOff = jsonObject.getDouble(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse priceInCents");
#endif
		field = "priceInCents";
		if (jsonObject.has(field))
		{
			PriceInCents = jsonObject.getInt(field);
		}

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Parse productType");
#endif
		field = "productType";
		if (jsonObject.has(field))
		{
			ProductType = jsonObject.getString(field);
		}
	}
}

#endif
