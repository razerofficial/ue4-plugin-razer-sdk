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

#include "RazerSDK_CallbacksContentSave.h"
#include "RazerSDK_CallbackSingleton.h"

#include <stdio.h>

using namespace com_razerzone_store_sdk_content_GameMod;

void CallbacksContentSave::OnError(GameMod gameMod, int code, const std::string& reason)
{
}

void CallbacksContentSave::OnSuccess(GameMod gameMod)
{
}

#endif
