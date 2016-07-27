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

#include "RazerSDK_CallbacksContentPublish.h"
#include "RazerSDK_CallbackSingleton.h"

#include <stdio.h>

using namespace android_os_Bundle;
using namespace std;
using namespace com_razerzone_store_sdk_content_GameMod;

void CallbacksContentPublish::OnError(const GameMod& gameMod, int code, const string& reason, const Bundle bundle)
{
}

void CallbacksContentPublish::OnSuccess(const GameMod& gameMod)
{
}

#endif
