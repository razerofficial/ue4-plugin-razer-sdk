package com.razerzone.store.sdk.engine.unreal;

/**
 * Created by tgraupmann on 7/21/2016.
 */

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;

/**
 UE4 plugins can use the GameActivity's listener to get
 the activity lifecycle events.
 */
public interface OnGameActivityListener {

    // listeners receive motion events
    boolean dispatchGenericMotionEvent(MotionEvent motionEvent);

    // listeners receive key events
    boolean dispatchKeyEvent(KeyEvent keyEvent);

    // listeners receive activity result events
    boolean onActivityResult(int requestCode, int resultCode, Intent data);

    // listeners receive create events
    void onCreate(Bundle savedInstanceState);

    // listeners receive destroy events
    void onDestroy();

    // listeners receive pause events
    void onPause();

    // listeners receive resume events
    void onResume();

    // listeners receive start events
    void onStart();

    // listeners receive stop events
    void onStop();
}
