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

#include "RazerSDK_InputStream.h"
#include "RazerSDK_GameModEditor.h"
#include "RazerSDK_GameModScreenshot.h"

#include <string>
#include <vector>

#include <jni.h>

namespace com_razerzone_store_sdk_content_GameMod
{
	class GameMod
	{
	public:
		static int InitJNI();
		static int FindJNI();
		static const GameMod CreateObject(jobject instance);
		jobject GetInstance() const;
		void Dispose() const;
		com_razerzone_store_sdk_content_GameModEditor::GameModEditor edit() const;
		void flag() const;
		std::string getCategory() const;
		std::string getDescription() const;
		std::vector<std::string> getFilenames() const;
		std::string getMetadata() const;
		float getRatingAverage() const;
		float getRatingCount() const;
		std::vector<com_razerzone_store_sdk_content_GameModScreenshot::GameModScreenshot> getScreenshots() const;
		std::vector<std::string> getTags() const;
		std::string getTitle() const;
		float getUserRating() const;
		bool isDownloading() const;
		bool isFlagged() const;
		bool isInstalled() const;
		bool isPublished() const;
		java_io_InputStream::InputStream openFile(const std::string& filename) const;
		void rate() const;
	private:
		static jclass _jcGameMod;
		static jmethodID _jmEdit;
		static jmethodID _jmFlag;
		static jmethodID _jmGetCategory;
		static jmethodID _jmGetDescription;
		static jmethodID _jmGetFilenames;
		static jmethodID _jmGetMetadata;
		static jmethodID _jmGetRatingAverage;
		static jmethodID _jmGetRatingCount;
		static jmethodID _jmGetScreenshots;
		static jmethodID _jmGetTags;
		static jmethodID _jmGetTitle;
		static jmethodID _jmGetUserRating;
		static jmethodID _jmIsDownloading;
		static jmethodID _jmIsFlagged;
		static jmethodID _jmIsInstalled;
		static jmethodID _jmIsPublished;
		static jmethodID _jmOpenFile;
		static jmethodID _jmRate;
		jobject _instance;
	};
}

#endif
