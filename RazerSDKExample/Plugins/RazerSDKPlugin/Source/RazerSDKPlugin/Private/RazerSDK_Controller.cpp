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

#include "RazerSDK_Controller.h"

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

#include <android/log.h>
#include <jni.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "com_razerzone_store_sdk_Controller"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define VERBOSE_LOGGING true

namespace com_razerzone_store_sdk_Controller
{
	jclass Controller::_jcController = 0;
	jmethodID Controller::_jmGetButtonData = 0;
	jmethodID Controller::_jmGetControllerByPlayer = 0;
	jmethodID Controller::_jmGetDeviceName = 0;
	jmethodID Controller::_jmShowCursor = 0;

	int Controller::InitJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		{
			const char* strControllerClass = "com/razerzone/store/sdk/Controller";
			if (VERBOSE_LOGGING)
			{
				__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for %s", strControllerClass);
			}
			_jcController = FAndroidApplication::FindJavaClass(strControllerClass);
			if (_jcController)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strControllerClass);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strControllerClass);
				return JNI_ERR;
			}
		}

		return JNI_OK;
	}

	void Controller::FindJNI()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		GJavaVM->AttachCurrentThread(&env, 0);

		{
			const char* strMethod = "getButtonData";
			_jmGetButtonData = env->GetStaticMethodID(_jcController, strMethod, "(I)Lcom/razerzone/store/sdk/Controller$ButtonData;");
			if (_jmGetButtonData)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "getControllerByPlayer";
			_jmGetControllerByPlayer = env->GetStaticMethodID(_jcController, strMethod, "(I)Lcom/razerzone/store/sdk/Controller;");
			if (_jmGetControllerByPlayer)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "getDeviceName";
			_jmGetDeviceName = env->GetMethodID(_jcController, strMethod, "()Ljava/lang/String;");
			if (_jmGetDeviceName)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}

		{
			const char* strMethod = "showCursor";
			_jmShowCursor = env->GetStaticMethodID(_jcController, strMethod, "(Z)V");
			if (_jmShowCursor)
			{
				if (VERBOSE_LOGGING)
				{
					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strMethod);
				}
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strMethod);
				return;
			}
		}
	}

	void Controller::SetInstance(jobject instance)
	{
		_instance = instance;
	}

	void Controller::Dispose()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();

		if (_instance)
		{
			env->DeleteLocalRef(_instance);
			_instance = 0;
		}
	}

	Controller* Controller::getControllerByPlayer(int playerNum)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		if (!_jcController)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcController is not initialized");
			return 0;
		}

		if (!_jmGetControllerByPlayer)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetControllerByPlayer is not initialized");
			return 0;
		}

		jint arg1 = playerNum;
		jobject retVal = env->CallStaticObjectMethod(_jcController, _jmGetControllerByPlayer, arg1);
		if (!retVal)
		{
			// May return null if controller isn't connected
			//__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "getControllerByPlayer returned null");
			return 0;
		}

		Controller* result = new Controller();
		result->SetInstance(retVal);
		return result;
	}

	void Controller::showCursor(bool visible)
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		if (!_jcController)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jcController is not initialized");
			return;
		}

		if (!_jmShowCursor)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmShowCursor is not initialized");
			return;
		}

		env->CallStaticVoidMethod(_jcController, _jmShowCursor, visible);
	}

	const std::string& Controller::getDeviceName()
	{
		JNIEnv* env = FAndroidApplication::GetJavaEnv();
		FindJNI();

		_deviceName = "Unavailable";

		if (!_instance)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_instance is not initialized");
			return _deviceName;
		}

		if (!_jmGetDeviceName)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "_jmGetDeviceName is not initialized");
			return _deviceName;
		}

		jstring retVal = (jstring)env->CallObjectMethod(_instance, _jmGetDeviceName);
		if (!retVal)
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "getDeviceName returned null");
			return _deviceName;
		}

		const char* nativeString = env->GetStringUTFChars(retVal, 0);
		_deviceName = nativeString;
		env->ReleaseStringUTFChars(retVal, nativeString);
		env->DeleteLocalRef(retVal);

		return _deviceName;
	}
}

#endif
