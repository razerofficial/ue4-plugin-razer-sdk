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


public class CallbacksContentDelete {

	private final String TAG  = CallbacksContentDelete.class.getSimpleName();

	public native void CallbacksContentDeleteOnDeleteFailed(GameMod gameMod, int code, String reason);
	public native void CallbacksContentDeleteOnDeleted(GameMod gameMod);

	public void onDeleteFailed(GameMod gameMod, final int code, final String reason) {
		Log.e(TAG, "onDeleteFailed code=" + code + " reason="+reason);
		
		CallbacksContentDeleteOnDeleteFailed(gameMod, code, reason);
	}

	public void onDeleted(GameMod gameMod) {
		Log.i(TAG, "onDeleted");

		CallbacksContentDeleteOnDeleted(gameMod);
	}
}
