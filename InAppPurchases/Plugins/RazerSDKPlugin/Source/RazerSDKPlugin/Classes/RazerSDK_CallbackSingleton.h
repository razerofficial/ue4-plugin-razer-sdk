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

#include <jni.h>
#include <string>

class CallbacksContentDelete;
class CallbacksContentDownload;
class CallbacksContentInit;
class CallbacksContentPublish;
class CallbacksContentSave;
class CallbacksContentSearchInstalled;
class CallbacksContentSearchPublished;
class CallbacksContentUnpublish;
class CallbacksInitPlugin;
class CallbacksRequestLogin;
class CallbacksRequestGamerInfo;
class CallbacksRequestProducts;
class CallbacksRequestPurchase;
class CallbacksRequestReceipts;
class CallbacksShutdown;

namespace RazerSDK
{
	class CallbackSingleton
	{
	private:
		static CallbackSingleton* m_instance;

		CallbackSingleton();
		~CallbackSingleton();

	public:

		static int InitJNI();

		static CallbackSingleton* GetInstance();

		CallbacksContentDelete* m_callbacksContentDelete;
		CallbacksContentDownload* m_callbacksContentDownload;
		CallbacksContentInit* m_callbacksContentInit;
		CallbacksContentPublish* m_callbacksContentPublish;
		CallbacksContentSave* m_callbacksContentSave;
		CallbacksContentSearchInstalled* m_callbacksContentSearchInstalled;
		CallbacksContentSearchPublished* m_callbacksContentSearchPublished;
		CallbacksContentUnpublish* m_callbacksContentUnpublish;
		CallbacksInitPlugin* m_callbacksInitPlugin;
		CallbacksRequestLogin* m_callbacksRequestLogin;
		CallbacksRequestGamerInfo* m_callbacksRequestGamerInfo;
		CallbacksRequestProducts* m_callbacksRequestProducts;
		CallbacksRequestPurchase* m_callbacksRequestPurchase;
		CallbacksRequestReceipts* m_callbacksRequestReceipts;
		CallbacksShutdown* m_callbacksShutdown;
	};
};

#endif
