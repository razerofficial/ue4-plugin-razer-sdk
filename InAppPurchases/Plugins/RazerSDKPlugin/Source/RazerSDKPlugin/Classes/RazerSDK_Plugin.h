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

#include "RazerSDK_Bitmap.h"
#include "RazerSDK_GameMod.h"
#include "RazerSDK_GameModEditor.h"
#include "RazerSDK_GameModScreenshot.h"

#include <jni.h>
#include <string>
#include <vector>

class CallbacksContentDelete;
class CallbacksContentDownload;
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
	class Plugin
	{
	public:

		static int InitJNI();

		static void initPlugin(const std::string& secretApiKey, CallbacksInitPlugin* callbacks);

		static void requestLogin(CallbacksRequestLogin* callbacks);

		static void requestGamerInfo(CallbacksRequestGamerInfo* callbacks);

		static void requestProducts(const std::vector<std::string>& products, CallbacksRequestProducts* callbacks);

		static void requestPurchase(const std::string& purchasable, const string& productType, CallbacksRequestPurchase* callbacks);

		static void requestReceipts(CallbacksRequestReceipts* callbacks);

		static void updateSafeArea(float amount);

		static void shutdown(CallbacksShutdown* callbacks);

		static void quit();

		static void contentDelete(const com_razerzone_store_sdk_content_GameMod::GameMod& gameMod, CallbacksContentDelete* callbacks);

		static void contentDownload(const com_razerzone_store_sdk_content_GameMod::GameMod& gameMod, CallbacksContentDownload* callbacks);

		static void contentPublish(const com_razerzone_store_sdk_content_GameMod::GameMod& gameMod, CallbacksContentPublish* callbacks);

		static void contentUnpublish(const com_razerzone_store_sdk_content_GameMod::GameMod& gameMod, CallbacksContentUnpublish* callbacks);

		static void getOuyaContentInstalled(CallbacksContentSearchInstalled* callbacks);

		static void getOuyaContentPublished(std::string sortMethod, CallbacksContentSearchPublished* callbacks);

		static void saveGameMod(const com_razerzone_store_sdk_content_GameModEditor::GameModEditor& gameModEditor,
			const com_razerzone_store_sdk_content_GameMod::GameMod& gameMod,
			CallbacksContentSave* callbacks);

		static float getFloat(jobject fFloat);

		static std::vector<android_graphics_Bitmap::Bitmap> getBitmapArray(jobject listBitmaps);

		static std::vector<com_razerzone_store_sdk_content_GameModScreenshot::GameModScreenshot> getGameModScreenshotArray(jobject listGameModScreenshots);

		static std::vector<std::string> getStringArray(jobject listStrings);

	private:

		// cached references
		static jclass jc_Plugin;
	};
}

#endif
