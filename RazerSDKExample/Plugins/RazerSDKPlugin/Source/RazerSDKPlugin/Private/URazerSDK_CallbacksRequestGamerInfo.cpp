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

#include "URazerSDK_CallbacksRequestGamerInfo.h"

#if PLATFORM_ANDROID

void URazerSDK_CallbacksRequestGamerInfo::OnSuccess(const RazerSDK::GamerInfo& gamerInfo)
{
	FRazerSDK_GamerInfo fGamerInfo;
	fGamerInfo.Username = gamerInfo.Username.c_str();
	fGamerInfo.Uuid = gamerInfo.Uuid.c_str();
	_mOnSuccess.ExecuteIfBound(fGamerInfo);
}

void URazerSDK_CallbacksRequestGamerInfo::OnFailure(int errorCode, const std::string& errorMessage)
{
	_mOnFailure.ExecuteIfBound(errorCode, errorMessage.c_str());
}

void URazerSDK_CallbacksRequestGamerInfo::OnCancel()
{
	_mOnCancel.ExecuteIfBound();
}

#endif
