package com.razerzone.store.sdk.engine.unreal;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class HookOnGameActivityListener implements OnGameActivityListener {

	private static final String TAG = HookOnGameActivityListener.class.getSimpleName();

    private static final boolean sEnableLogging = true;

	private InputView mInputView = null;

	public boolean dispatchGenericMotionEvent(MotionEvent motionEvent) {
		if (sEnableLogging) {
            Log.i(TAG, "*** dispatchGenericMotionEvent ***");
        }

		if (null != mInputView) {
			// Plugin handles remapping native input
			// Pass the native input that's been remapped to the view
			mInputView.remappedDispatchGenericMotionEvent(motionEvent);
		}
		return true;
	}

	public boolean dispatchKeyEvent(KeyEvent keyEvent) {
		if (sEnableLogging) {
            Log.i(TAG, "*** dispatchKeyEvent ***");
        }

		if (null != mInputView) {
			// Pass the native input that's been remapped to the view
			mInputView.remappedDispatchKeyEvent(keyEvent);
		}
		return true;
	}
		
	public boolean onActivityResult(int requestCode, int resultCode, Intent data) {
        if (sEnableLogging) {
            Log.i(TAG, "*** onActivityResult ***");
        }
        return Plugin.processOnActivityResult(requestCode, resultCode, data);
	}

	public void onCreate(Bundle savedInstanceState) {
        if (sEnableLogging) {
            Log.i(TAG, "*** onCreate ***");
        }

		// Get the GameActivity static reference
		final Activity activity = Plugin.getActivity();

		if (null == activity) {
			Log.e(TAG, "onCreate: activity is null!");
			return;
		}

		// Handle native input remapping
		mInputView = new InputView(activity);
	}

	public void onDestroy() {
        if (sEnableLogging) {
            Log.i(TAG, "*** onDestroy ***");
        }

		if (null != mInputView) {
			// shutdown input remapping
			mInputView.shutdown();
		}
	}

	public void onPause() {
        if (sEnableLogging) {
            Log.i(TAG, "*** onPause ***");
        }
	}

	public void onResume() {
        if (sEnableLogging) {
            Log.i(TAG, "*** onResume ***");
        }
	}

	public void onStart() {
		if (sEnableLogging) {
            Log.i(TAG, "*** onStart ***");
        }
	}

	public void onStop() {
		if (sEnableLogging) {
            Log.i(TAG, "*** onStop ***");
        }
	}
}
