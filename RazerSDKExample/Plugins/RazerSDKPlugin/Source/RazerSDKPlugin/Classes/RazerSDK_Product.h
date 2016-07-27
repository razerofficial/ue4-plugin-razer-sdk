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

// this code is Android specific
#if PLATFORM_ANDROID

#include "RazerSDK_JsonObject.h"

#include <string>

namespace RazerSDK
{
	class Product
	{
	public:
		// String developerName, Product.Type type

		std::string CurrencyCode;
		std::string Description;
		std::string DeveloperName;
		std::string Identifier;
		float LocalPrice;
		std::string Name;
		float OriginalPrice;
		float PercentOff;
		int PriceInCents;
		std::string ProductType;

		void Init();
		void ParseJSON(const org_json_JSONObject::JSONObject& jsonObject);
	};
}

#endif
