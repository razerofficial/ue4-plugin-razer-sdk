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

#include <jni.h>

namespace com_razerzone_store_sdk_content_GameModScreenshot
{
	class GameModScreenshot
	{
	public:
		static int InitJNI();
		static int FindJNI();
		static const GameModScreenshot CreateObject(jobject instance);
		jobject GetInstance() const;
		void Dispose() const;
		android_graphics_Bitmap::Bitmap getImage() const;
		android_graphics_Bitmap::Bitmap getThumbnail() const;
	private:
		static jclass _jcGameModScreenshot;
		jobject _instance;
	};
}

#endif
