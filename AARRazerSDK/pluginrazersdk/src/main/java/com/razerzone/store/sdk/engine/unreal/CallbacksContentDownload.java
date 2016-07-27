/*
 * Copyright (C) 2012-2015 OUYA, Inc.
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

package com.razerzone.store.sdk.engine.unreal;

import android.util.Log;

import com.razerzone.store.sdk.content.GameMod;


public class CallbacksContentDownload {

	private final String TAG  = CallbacksContentDownload.class.getSimpleName();

	public native void CallbacksContentDownloadOnProgress(GameMod gameMod, int progress);
	public native void CallbacksContentDownloadOnFailed(GameMod gameMod);
	public native void CallbacksContentDownloadOnComplete(GameMod gameMod);

	public void onProgress(GameMod gameMod, int progress) {
		Log.i(TAG, "onProgress progress="+progress);
		
		CallbacksContentDownloadOnProgress(gameMod, progress);
	}

	public void onFailed(GameMod gameMod) {
		Log.e(TAG, "onFailed");

		CallbacksContentDownloadOnFailed(gameMod);
	}
	
	public void onComplete(GameMod gameMod) {
		Log.i(TAG, "onComplete");

		CallbacksContentDownloadOnComplete(gameMod);
	}
}
