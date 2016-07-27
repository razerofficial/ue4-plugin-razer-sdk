// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RazerSDKPluginPrivatePCH.h"

#include "RazerSDKPlugin.h"

// this test is Android specific
#if PLATFORM_ANDROID

// Get access to Android logging
#include <android/log.h>

// Get a reference to the JNI environment
#include "Android/AndroidApplication.h"

// Get a reference to the JVM
#include "Android/AndroidJNI.h"

// Razer handles remapping native input
#include "RazerSDK_InputView.h"
#include "RazerSDK_Plugin.h"

// Plugin handles remapping native input
// Include the Razer namespace
using namespace RazerSDK;
using namespace com_razerzone_store_sdk_engine_unreal_InputView;

// function prototypes
int32_t AndroidPluginHandleInput(struct android_app* app, AInputEvent* event);
int RegisterJavaPluginClasses();
int SetupJNI();

// Redefine a tag for logging
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "RazerSDKPlugin"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING false

extern struct android_app* GNativeAndroidApp;

int32_t(*GOriginalInputEvent)(struct android_app* app, AInputEvent* event);

#endif

class FRazerSDKPlugin : public IRazerSDKPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FRazerSDKPlugin, RazerSDKPlugin)

DEFINE_LOG_CATEGORY(LogRazerSDKPlugin);

void FRazerSDKPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)

	if (IRazerSDKPlugin::IsAvailable())
	{
		UE_LOG(LogRazerSDKPlugin, Log, TEXT("*** RazerSDKPlugin has loaded. ***"));
	}
	else
	{
		UE_LOG(LogRazerSDKPlugin, Log, TEXT("*** RazerSDKPlugin has not loaded! ***"));
	}

	// Android specific code
#if PLATFORM_ANDROID
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** StartupModule ***");
#endif

	if (SetupJNI() == JNI_OK)
	{
		UE_LOG(LogRazerSDKPlugin, Log, TEXT("*** JNI has initialized. ***"));
	}
	else
	{
		UE_LOG(LogRazerSDKPlugin, Log, TEXT("*** JNI failed to initialize! ***"));
	}

	// store the original input handler
	GOriginalInputEvent = GNativeAndroidApp->onInputEvent;

	// reassign android input callback
	GNativeAndroidApp->onInputEvent = AndroidPluginHandleInput;
#endif
}

void FRazerSDKPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if PLATFORM_ANDROID
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** ShutdownModule ***");
#endif
#endif
}

// Android specific code
#if PLATFORM_ANDROID

// Setup the JNI classes, called from StartupModule
int SetupJNI()
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI ***");
#endif

	if (InputView::InitJNI() == JNI_ERR)
	{
		return JNI_ERR;
	}

	if (RegisterJavaPluginClasses() == JNI_ERR)
	{
		return JNI_ERR;
	}

#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** SetupJNI initialized successfully. ***");
#endif
	return JNI_OK;
}

// register classes from the Razer SDK
int RegisterJavaPluginClasses()
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Initialize the InputView class ***");
#endif

	if (InputView::InitJNI() == JNI_ERR)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to initialize the InputView class! ***");
		return JNI_ERR;
	}

#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** Initialize the Plugin classes!***");
#endif

	if (Plugin::InitJNI() == JNI_ERR)
	{
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to initialize the Plugin class! ***");
		return JNI_ERR;
	}
	return JNI_OK;
}

// define the callback function that will get the android input events
int32_t AndroidPluginHandleInput(struct android_app* app, AInputEvent* event)
{
#if ENABLE_VERBOSE_LOGGING
	__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "*** AndroidPluginHandleInput: The callback was invoked! ***");
#endif

	// pass input to the original callback
	GOriginalInputEvent(app, event);

	return 0;
}

#endif
