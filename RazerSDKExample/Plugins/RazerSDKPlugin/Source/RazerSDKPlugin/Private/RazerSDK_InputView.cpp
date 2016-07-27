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

#include "RazerSDK_InputView.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <android_native_app_glue.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_engine_unreal_InputView"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

#ifdef MAX_CONTROLLERS
#undef MAX_CONTROLLERS
#endif
#define MAX_CONTROLLERS 4

namespace com_razerzone_store_sdk_engine_unreal_InputView
{
	jclass InputView::_jcInputView = 0;
	jmethodID InputView::_jmGetInstance = 0;
	jmethodID InputView::_jmJavaDispatchKeyEvent = 0;
	jmethodID InputView::_jmJavaDispatchMotionEvent = 0;

	JNINativeMethod InputView::_nativeMethodTable[] = {
		{ "dispatchGenericMotionEventNative", "(IIF)V", (void *)InputView::dispatchGenericMotionEventNative }
	};

	int InputView::_nativeMethodTableSize = sizeof(_nativeMethodTable) / sizeof(_nativeMethodTable[0]);

	JNINativeMethod InputView::_nativeMethodTable2[] = {
		{ "dispatchKeyEventNative", "(III)V", (void *)InputView::dispatchKeyEventNative }
	};

	int InputView::_nativeMethodTableSize2 = sizeof(_nativeMethodTable2) / sizeof(_nativeMethodTable2[0]);

	std::vector< std::map<int, float> > InputView::_axis;
	std::vector< std::map<int, bool> > InputView::_button;
	std::vector< std::map<int, bool> > InputView::_buttonDown;
	std::vector< std::map<int, bool> > InputView::_buttonUp;
	std::vector< std::map<int, bool> > InputView::_lastButtonDown;
	std::vector< std::map<int, bool> > InputView::_lastButtonUp;

	int InputView::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strClass = "com/razerzone/store/sdk/engine/unreal/InputView";
			#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for %s", strClass);
			#endif
				jclass localRef = FAndroidApplication::FindJavaClass(strClass);
			if (localRef)
			{
				#if ENABLE_VERBOSE_LOGGING
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strClass);
				#endif
				_jcInputView = (jclass)env->NewGlobalRef(localRef);
				env->DeleteLocalRef(localRef);
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strClass);
				return JNI_ERR;
			}
		}

		JNIFind();

		// setup native receiving remapped input

		{
			jint ret = env->RegisterNatives(_jcInputView, _nativeMethodTable, _nativeMethodTableSize);
			if (ret < 0)
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to register native methods");
				return JNI_ERR;
			}
		}

		{
			jint ret = env->RegisterNatives(_jcInputView, _nativeMethodTable2, _nativeMethodTableSize2);
			if (ret < 0)
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to register native methods 2");
				return JNI_ERR;
			}
		}

		for (int index = 0; index < MAX_CONTROLLERS; ++index)
		{
			_axis.push_back(std::map<int, float>());
			_button.push_back(std::map<int, bool>());
			_buttonDown.push_back(std::map<int, bool>());
			_buttonUp.push_back(std::map<int, bool>());
			_lastButtonDown.push_back(std::map<int, bool>());
			_lastButtonUp.push_back(std::map<int, bool>());
		}

		return JNI_OK;
	}

	void InputView::JNIFind()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_jcInputView)
		{
			return;
		}

		{
			const char* strMethod = "getInstance";
			#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for method %s", strMethod);
			#endif
			_jmGetInstance = env->GetStaticMethodID(_jcInputView, strMethod, "()Lcom/razerzone/store/sdk/engine/unreal/InputView;");
			if (_jmGetInstance)
			{
				#if ENABLE_VERBOSE_LOGGING
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			}
		}

		{
			const char* strMethod = "javaDispatchKeyEvent";
			#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for method %s", strMethod);
			#endif
			_jmJavaDispatchKeyEvent = env->GetMethodID(_jcInputView, strMethod, "(JJIIIIIIII)Z");
			if (_jmJavaDispatchKeyEvent)
			{
				#if ENABLE_VERBOSE_LOGGING
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			}
		}

		{
			const char* strMethod = "javaDispatchGenericMotionEvent";
			#if ENABLE_VERBOSE_LOGGING
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for method %s", strMethod);
			#endif
			_jmJavaDispatchMotionEvent = env->GetMethodID(_jcInputView, strMethod, "(JJIIIIFFIIII[I[I[F[F[F[F[F[F[F[F[FI[I[F)Z");
			if (_jmJavaDispatchMotionEvent)
			{
				#if ENABLE_VERBOSE_LOGGING
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				#endif
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
			}
		}
	}

	InputView* InputView::getInstance()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_jcInputView)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcInputView is not valid!");
			return 0;
		}

		if (!_jmGetInstance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetInstance is not valid!");
			return 0;
		}

		jobject retVal = env->CallStaticObjectMethod(_jcInputView, _jmGetInstance);
		if (!retVal)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetInstance returned null!");
			return 0;
		}

		InputView* result = new InputView();
		result->_instance = retVal;
		return result;
	}

	bool InputView::dispatchKeyEvent(AInputEvent* keyEvent)
	{
		int64_t downTime = AKeyEvent_getDownTime(keyEvent);
		int64_t eventTime = AKeyEvent_getEventTime(keyEvent);
		int32_t action = AKeyEvent_getAction(keyEvent);
		int32_t code = AKeyEvent_getKeyCode(keyEvent);
		int32_t repeat = AKeyEvent_getRepeatCount(keyEvent);
		int32_t metaState = AKeyEvent_getMetaState(keyEvent);
		int32_t deviceId = AInputEvent_getDeviceId(keyEvent);
		int32_t scancode = AKeyEvent_getScanCode(keyEvent);
		int32_t flags = AKeyEvent_getFlags(keyEvent);
		int32_t source = AInputEvent_getSource(keyEvent);

#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "downTime=%lld eventTime=%lld action=%d code=%d repeat=%d metaState=%d deviceId=%d scancode=%d flags=%d source=%d",
			downTime, eventTime, action, code,
			repeat, metaState, deviceId, scancode, flags, source);
#endif

		return javaDispatchKeyEvent(downTime, eventTime, action, code,
			repeat, metaState, deviceId, scancode, flags, source);
	}

	bool InputView::dispatchGenericMotionEvent(AInputEvent* motionEvent)
	{
		int64_t downTime = AMotionEvent_getDownTime(motionEvent);
		int64_t eventTime = AMotionEvent_getEventTime(motionEvent);
		int32_t action = AMotionEvent_getAction(motionEvent);
		int32_t metaState = AMotionEvent_getMetaState(motionEvent);
		int32_t pointerCount = AMotionEvent_getPointerCount(motionEvent);
		int32_t buttonState = AMotionEvent_getButtonState(motionEvent);
		float xPrecision = AMotionEvent_getXPrecision(motionEvent);
		float yPrecision = AMotionEvent_getYPrecision(motionEvent);
		int32_t deviceId = AInputEvent_getDeviceId(motionEvent);
		int32_t edgeFlags = AMotionEvent_getEdgeFlags(motionEvent);
		int32_t flags = AMotionEvent_getFlags(motionEvent);
		int32_t source = AInputEvent_getSource(motionEvent);

		int* pointerPropertiesId = new int[pointerCount];
		int* pointerPropertiesToolType = new int[pointerCount];
		float* pointerCoordsOrientation = new float[pointerCount];
		float* pointerCoordsPressure = new float[pointerCount];
		float* pointerCoordsSize = new float[pointerCount];
		float* pointerCoordsToolMajor = new float[pointerCount];
		float* pointerCoordsToolMinor = new float[pointerCount];
		float* pointerCoordsTouchMajor = new float[pointerCount];
		float* pointerCoordsTouchMinor = new float[pointerCount];
		float* pointerCoordsX = new float[pointerCount];
		float* pointerCoordsY = new float[pointerCount];

		std::vector<int> listAxisIndices;
		std::vector<float> listAxisValues;

		if (pointerCount > 0)
		{
#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "pointerCount=%d deviceId=%d source=%d",
				pointerCount, deviceId, source);
#endif

			// MotionEvent.PointerProperties
			long long pointerId = AMotionEvent_getPointerId(motionEvent, 0);
			int32_t toolType = AMotionEvent_getToolType(motionEvent, 0);

#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "PointerProperties pointerId=%lld toolType-%d",
				pointerId, toolType);
#endif

			pointerPropertiesId[0] = pointerId;
			pointerPropertiesToolType[0] = toolType;

			// MotionEvent.PointerCoords
			float orientation = AMotionEvent_getOrientation(motionEvent, pointerId);
			float pressure = AMotionEvent_getPressure(motionEvent, pointerId);
			float size = AMotionEvent_getSize(motionEvent, pointerId);
			float toolMajor = AMotionEvent_getTouchMajor(motionEvent, pointerId);
			float toolMinor = AMotionEvent_getToolMinor(motionEvent, pointerId);
			float touchMajor = AMotionEvent_getTouchMajor(motionEvent, pointerId);
			float touchMinor = AMotionEvent_getTouchMinor(motionEvent, pointerId);
			float x = AMotionEvent_getX(motionEvent, pointerId);
			float y = AMotionEvent_getY(motionEvent, pointerId);

#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "PointerCoords orientation=%f pressure=%f size=%f toolMajor=%f toolMinor=%f touchMajor=%f touchMinor=%f x=%f y=%f",
				orientation, pressure, size,
				toolMajor, toolMinor, touchMajor, touchMinor,
				x, y);
#endif

			pointerCoordsOrientation[0] = orientation;
			pointerCoordsPressure[0] = pressure;
			pointerCoordsSize[0] = size;
			pointerCoordsToolMajor[0] = toolMajor;
			pointerCoordsToolMinor[0] = toolMinor;
			pointerCoordsTouchMajor[0] = touchMajor;
			pointerCoordsTouchMinor[0] = touchMinor;
			pointerCoordsX[0] = x;
			pointerCoordsY[0] = y;

			for (int32_t axis = 0; axis < 50; ++axis) // 50 is based on the AXIS_value range I saw in the documentation
			{
				float val = AMotionEvent_getAxisValue(motionEvent, axis, pointerId);
				if (val != 0.0f)
				{
#if ENABLE_VERBOSE_LOGGING
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "axis=%d val=%f", axis, val);
#endif
					listAxisIndices.push_back(axis);
					listAxisValues.push_back(val);
				}
			}
		}

		int axisCount = listAxisIndices.size();
		int* axisIndexes = new int[axisCount];
		float* axisValues = new float[axisCount];
		for (int index = 0; index < axisCount; ++index)
		{
			axisIndexes[index] = listAxisIndices[index];
			axisValues[index] = listAxisValues[index];
		}
		listAxisIndices.clear();
		listAxisValues.clear();

		bool handled = javaDispatchGenericMotionEvent(
			downTime,
			eventTime,
			action,
			pointerCount,
			metaState,
			buttonState,
			xPrecision,
			yPrecision,
			deviceId,
			edgeFlags,
			source,
			flags,
			pointerPropertiesId,
			pointerPropertiesToolType,
			pointerCoordsOrientation,
			pointerCoordsPressure,
			pointerCoordsSize,
			pointerCoordsToolMajor,
			pointerCoordsToolMinor,
			pointerCoordsTouchMajor,
			pointerCoordsTouchMinor,
			pointerCoordsX,
			pointerCoordsY,
			axisCount,
			axisIndexes,
			axisValues);

		delete pointerPropertiesId;
		delete pointerPropertiesToolType;
		delete pointerCoordsOrientation;
		delete pointerCoordsPressure;
		delete pointerCoordsSize;
		delete pointerCoordsToolMajor;
		delete pointerCoordsToolMinor;
		delete pointerCoordsTouchMajor;
		delete pointerCoordsTouchMinor;
		delete pointerCoordsX;
		delete pointerCoordsY;
		delete axisIndexes;
		delete axisValues;
		return handled;
	}

	bool InputView::javaDispatchKeyEvent(long long downTime, long long eventTime, int action, int code,
		int repeat, int metaState, int deviceId, int scancode, int flags, int source)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not valid!");
			return false;
		}

		if (!_jmJavaDispatchKeyEvent)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmJavaDispatchKeyEvent is not valid!");
			return false;
		}

		return env->CallBooleanMethod(_instance, _jmJavaDispatchKeyEvent,
			downTime, eventTime, action, code,
			repeat, metaState, deviceId, scancode, flags, source);
	}

	bool InputView::javaDispatchGenericMotionEvent(
		long long downTime,
		long long eventTime,
		int action,
		int pointerCount,
		int metaState,
		int buttonState,
		float xPrecision,
		float yPrecision,
		int deviceId,
		int edgeFlags,
		int source,
		int flags,
		int* pointerPropertiesId,
		int* pointerPropertiesToolType,
		float* pointerCoordsOrientation,
		float* pointerCoordsPressure,
		float* pointerCoordsSize,
		float* pointerCoordsToolMajor,
		float* pointerCoordsToolMinor,
		float* pointerCoordsTouchMajor,
		float* pointerCoordsTouchMinor,
		float* pointerCoordsX,
		float* pointerCoordsY,
		int axisCount,
		int* axisIndexes,
		float* axisValues)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not valid!");
			return false;
		}

		if (!_jmJavaDispatchMotionEvent)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmJavaDispatchMotionEvent is not valid!");
			return false;
		}

		jintArray argPointerPropertiesId = env->NewIntArray(pointerCount);
		jintArray argpointerPropertiesToolType = env->NewIntArray(pointerCount);
		jfloatArray argpointerCoordsOrientation = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsPressure = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsSize = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsToolMajor = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsToolMinor = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsTouchMajor = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsTouchMinor = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsX = env->NewFloatArray(pointerCount);
		jfloatArray argpointerCoordsY = env->NewFloatArray(pointerCount);
		jintArray argAxisIndexes = env->NewIntArray(axisCount);
		jfloatArray argAxisValues = env->NewFloatArray(axisCount);

		env->SetIntArrayRegion(argPointerPropertiesId, 0, pointerCount, pointerPropertiesId);
		env->SetIntArrayRegion(argpointerPropertiesToolType, 0, pointerCount, pointerPropertiesToolType);
		env->SetFloatArrayRegion(argpointerCoordsOrientation, 0, pointerCount, pointerCoordsOrientation);
		env->SetFloatArrayRegion(argpointerCoordsPressure, 0, pointerCount, pointerCoordsPressure);
		env->SetFloatArrayRegion(argpointerCoordsSize, 0, pointerCount, pointerCoordsSize);
		env->SetFloatArrayRegion(argpointerCoordsToolMajor, 0, pointerCount, pointerCoordsToolMajor);
		env->SetFloatArrayRegion(argpointerCoordsToolMinor, 0, pointerCount, pointerCoordsToolMinor);
		env->SetFloatArrayRegion(argpointerCoordsTouchMajor, 0, pointerCount, pointerCoordsTouchMajor);
		env->SetFloatArrayRegion(argpointerCoordsTouchMinor, 0, pointerCount, pointerCoordsTouchMinor);
		env->SetFloatArrayRegion(argpointerCoordsX, 0, pointerCount, pointerCoordsX);
		env->SetFloatArrayRegion(argpointerCoordsY, 0, pointerCount, pointerCoordsY);
		env->SetIntArrayRegion(argAxisIndexes, 0, axisCount, axisIndexes);
		env->SetFloatArrayRegion(argAxisValues, 0, axisCount, axisValues);

		bool handled = env->CallBooleanMethod(_instance, _jmJavaDispatchMotionEvent,
				downTime,
				eventTime,
				action,
				pointerCount,
				metaState,
				buttonState,
				xPrecision,
				yPrecision,
				deviceId,
				edgeFlags,
				source,
				flags,
				argPointerPropertiesId,
				argpointerPropertiesToolType,
				argpointerCoordsOrientation,
				argpointerCoordsPressure,
				argpointerCoordsSize,
				argpointerCoordsToolMajor,
				argpointerCoordsToolMinor,
				argpointerCoordsTouchMajor,
				argpointerCoordsTouchMinor,
				argpointerCoordsX,
				argpointerCoordsY,
				axisCount,
				argAxisIndexes,
				argAxisValues);

		env->DeleteLocalRef(argPointerPropertiesId);
		env->DeleteLocalRef(argpointerPropertiesToolType);
		env->DeleteLocalRef(argpointerCoordsOrientation);
		env->DeleteLocalRef(argpointerCoordsPressure);
		env->DeleteLocalRef(argpointerCoordsSize);
		env->DeleteLocalRef(argpointerCoordsToolMajor);
		env->DeleteLocalRef(argpointerCoordsToolMinor);
		env->DeleteLocalRef(argpointerCoordsTouchMajor);
		env->DeleteLocalRef(argpointerCoordsTouchMinor);
		env->DeleteLocalRef(argpointerCoordsX);
		env->DeleteLocalRef(argpointerCoordsY);
		env->DeleteLocalRef(argAxisIndexes);
		env->DeleteLocalRef(argAxisValues);

		return handled;
	}

	jobject InputView::GetInstance()
	{
		return _instance;
	}

	void InputView::dispatchGenericMotionEventNative(JNIEnv* env, jobject thiz,
		jint playerNum,
		jint axis,
		jfloat val)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Native remapped playerNum=%d axis=%d val=%f", playerNum, axis, val);
#endif
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}
		_axis[playerNum][axis] = val;
	}

	void InputView::dispatchKeyEventNative(JNIEnv* env, jobject thiz,
		jint playerNum,
		jint keyCode,
		jint action)
	{
#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Native remapped playerNum=%d KeyCode=%d Action=%d", playerNum, keyCode, action);
#endif
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}

		bool buttonDown = action == 0;

		if (_button[playerNum][keyCode] != buttonDown)
		{
			_button[playerNum][keyCode] = buttonDown;
			if (buttonDown)
			{
				_buttonDown[playerNum][keyCode] = true;
			}
			else
			{
				_buttonUp[playerNum][keyCode] = true;
			}
		}
	}

	// get axis value
	float InputView::getAxis(int playerNum, int axis)
	{
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}

		std::map<int, float>::const_iterator search = _axis[playerNum].find(axis);
		if (search != _axis[playerNum].end())
		{
			return search->second;
		}
		return 0.0f;
	}

	// check if a button is pressed
	bool InputView::isPressed(int playerNum, int keyCode)
	{
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}

		std::map<int, bool>::const_iterator search = _button[playerNum].find(keyCode);
		if (search != _button[playerNum].end())
		{
			return search->second;
		}
		return false;
	}

	// check if a button was down
	bool InputView::isPressedDown(int playerNum, int keyCode)
	{
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}

		std::map<int, bool>::const_iterator search = _lastButtonDown[playerNum].find(keyCode);
		if (search != _lastButtonDown[playerNum].end())
		{
			return search->second;
		}
		return false;
	}

	// check if a button was up
	bool InputView::isPressedUp(int playerNum, int keyCode)
	{
		if (playerNum < 0 ||
			playerNum >= MAX_CONTROLLERS)
		{
			playerNum = 0;
		}

		std::map<int, bool>::const_iterator search = _lastButtonUp[playerNum].find(keyCode);
		if (search != _lastButtonUp[playerNum].end())
		{
			return search->second;
		}
		return false;
	}

	// clear the button state for detecting up and down
	void InputView::clearButtonStates()
	{
		for (int playerNum = 0; playerNum < MAX_CONTROLLERS; ++playerNum)
		{
			_lastButtonDown[playerNum].clear();
			_lastButtonUp[playerNum].clear();
			for (std::map<int, bool>::iterator it = _buttonDown[playerNum].begin(); it != _buttonDown[playerNum].end(); ++it)
			{
				int keyCode = it->first;
				_lastButtonDown[playerNum][keyCode] = _buttonDown[playerNum][keyCode];
			}
			for (std::map<int, bool>::iterator it = _buttonUp[playerNum].begin(); it != _buttonUp[playerNum].end(); ++it)
			{
				int keyCode = it->first;
				_lastButtonUp[playerNum][keyCode] = _buttonUp[playerNum][keyCode];
			}
			_buttonDown[playerNum].clear();
			_buttonUp[playerNum].clear();
		}
	}

	// clear the axis values
	void InputView::clearAxes()
	{
		for (int playerNum = 0; playerNum < MAX_CONTROLLERS; ++playerNum) {
			_axis[playerNum].clear();
		}
	}

	// clear the button values
	void InputView::clearButtons()
	{
		for (int playerNum = 0; playerNum < MAX_CONTROLLERS; ++playerNum) {
			_button[playerNum].clear();
			_buttonDown[playerNum].clear();
			_buttonUp[playerNum].clear();
			_lastButtonDown[playerNum].clear();
			_lastButtonUp[playerNum].clear();
		}
	}

}

#endif
