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

import android.os.Bundle;
import android.util.Log;

import com.razerzone.store.sdk.content.GameMod;


public class CallbacksContentPublish {

	private final String TAG  = CallbacksContentPublish.class.getSimpleName();

	public native void CallbacksContentPublishOnError(GameMod gameMod, int code, String reason, Bundle bundle);
	public native void CallbacksContentPublishOnSuccess(GameMod gameMod);

	public void onError(GameMod gameMod, int code, String reason, Bundle bundle) {
		Log.e(TAG, "onError code="+code+" reason="+reason);
		
		CallbacksContentPublishOnError(gameMod, code, reason, bundle);
	}

	public void onSuccess(GameMod gameMod) {
		Log.i(TAG, "onSuccess");

		CallbacksContentPublishOnSuccess(gameMod);
	}
}
