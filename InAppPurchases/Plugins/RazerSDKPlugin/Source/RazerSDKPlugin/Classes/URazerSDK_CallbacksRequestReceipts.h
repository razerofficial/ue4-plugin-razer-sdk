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

#include "URazerSDK_Types.h"

#if PLATFORM_ANDROID
#include "RazerSDK_CallbacksRequestReceipts.h"
#endif

class URazerSDK_CallbacksRequestReceipts
#if PLATFORM_ANDROID
	: public CallbacksRequestReceipts
#endif
{
public:
#if PLATFORM_ANDROID
	void OnSuccess(const std::vector<RazerSDK::Receipt>& receipts);
	void OnFailure(int errorCode, const std::string& errorMessage);
	void OnCancel();
#endif
	FDelegateRazerSDKOnSuccessRequestReceipts _mOnSuccess;
	FDelegateRazerSDKOnFailure _mOnFailure;
	FDelegateRazerSDKOnCancel _mOnCancel;
};
