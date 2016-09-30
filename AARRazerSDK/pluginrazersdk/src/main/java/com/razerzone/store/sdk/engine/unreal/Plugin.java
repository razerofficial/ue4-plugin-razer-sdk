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

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.FrameLayout;

import com.razerzone.store.sdk.StoreFacade;
import com.razerzone.store.sdk.content.GameMod;
import com.razerzone.store.sdk.content.GameModManager;
import com.razerzone.store.sdk.content.GameModScreenshot;
import com.razerzone.store.sdk.purchases.Product;

import java.security.InvalidParameterException;
import java.util.List;

public class Plugin
{
	private static final String TAG = Plugin.class.getSimpleName();

	private static final boolean sEnableLogging = false;

	private static Activity sActivity = null;
	private static Bundle sSavedInstanceState = null;
	private static StoreFacadeWrapper sStoreFacadeWrapper = null;
	private static GameModManager sGameModManager = null;
	private static List<GameMod> sGameModManagerInstalledResults = null;
	private static List<GameMod> sGameModManagerPublishedResults = null;
	private static List<GameMod> sOuyaContentInstalledResults = null;
	private static List<GameMod> sOuyaContentPublishedResults = null;
	private static CallbacksInitPlugin sCallbacksInitPlugin = new CallbacksInitPlugin();
	private static CallbacksRequestLogin sCallbacksRequestLogin = new CallbacksRequestLogin();
	private static CallbacksRequestGamerInfo sCallbacksRequestGamerInfo = new CallbacksRequestGamerInfo();
	private static CallbacksRequestProducts sCallbacksRequestProducts = new CallbacksRequestProducts();
	private static CallbacksRequestPurchase sCallbacksRequestPurchase = new CallbacksRequestPurchase();
	private static CallbacksRequestReceipts sCallbacksRequestReceipts = new CallbacksRequestReceipts();
    private static CallbacksShutdown sCallbacksShutdown = new CallbacksShutdown();
	private static CallbacksContentInit sCallbacksContentInit = new CallbacksContentInit();
	private static CallbacksContentSearchInstalled sCallbacksContentSearchInstalled = new CallbacksContentSearchInstalled();
	private static CallbacksContentSearchPublished sCallbacksContentSearchPublished = new CallbacksContentSearchPublished();
	private static CallbacksContentSave sCallbacksContentSave = new CallbacksContentSave();
	private static CallbacksContentPublish sCallbacksContentPublish = new CallbacksContentPublish();
	private static CallbacksContentUnpublish sCallbacksContentUnpublish = new CallbacksContentUnpublish();
	private static CallbacksContentDelete sCallbacksContentDelete = new CallbacksContentDelete();
	private static CallbacksContentDownload sCallbacksContentDownload = new CallbacksContentDownload();

	public static Activity getActivity() { return sActivity; }
	public static void setActivity(Activity activity) { sActivity = activity; }

	public static Bundle getSavedInstanceState() { return sSavedInstanceState; }
	public static void setSavedInstanceState(Bundle savedInstanceState) { sSavedInstanceState = savedInstanceState; }

	public static StoreFacadeWrapper getStoreFacadeWrapper() { return sStoreFacadeWrapper; }
	public static void setStoreFacadeWrapper(StoreFacadeWrapper storeFacadeWrapper) { sStoreFacadeWrapper = storeFacadeWrapper; }

	public static GameModManager getGameModManager() { return sGameModManager; }
	public static void setGameModManager(GameModManager gameModManager) { sGameModManager = gameModManager; }

	public static List<GameMod> getGameModManagerInstalledResults() { return sGameModManagerInstalledResults; }
	public static void setGameModManagerInstalledResults(List<GameMod> results) { sGameModManagerInstalledResults = results; }

	public static List<GameMod> getGameModManagerPublishedResults() { return sGameModManagerPublishedResults; }
	public static void setGameModManagerPublishedResults(List<GameMod> results) { sGameModManagerPublishedResults = results; }

	public static List<GameMod> getOuyaContentInstalledResults()	{ return sOuyaContentInstalledResults; }
	public static void setOuyaContentInstalledResults(List<GameMod> results) { sOuyaContentInstalledResults = results; }

	public static List<GameMod> getOuyaContentPublishedResults() { return sOuyaContentPublishedResults; }
	public static void setOuyaContentPublishedResults(List<GameMod> results) { sOuyaContentPublishedResults = results; }

	public static CallbacksInitPlugin getCallbacksInitPlugin() { return sCallbacksInitPlugin; }
	public static CallbacksRequestLogin getCallbacksRequestLogin() { return sCallbacksRequestLogin; }
	public static CallbacksRequestGamerInfo getCallbacksRequestGamerInfo() { return sCallbacksRequestGamerInfo; }
	public static CallbacksRequestProducts getCallbacksRequestProducts() { return sCallbacksRequestProducts; }
	public static CallbacksRequestPurchase getCallbacksRequestPurchase() { return sCallbacksRequestPurchase; }
	public static CallbacksRequestReceipts getCallbacksRequestReceipts() { return sCallbacksRequestReceipts; }
    public static CallbacksShutdown getCallbacksShutdown() { return sCallbacksShutdown; }
	public static CallbacksContentInit getCallbacksContentInit()
	{
		return sCallbacksContentInit;
	}
	public static CallbacksContentSearchInstalled getCallbacksContentSearchInstalled() { return sCallbacksContentSearchInstalled; }
	public static CallbacksContentSearchPublished getCallbacksContentSearchPublished() { return sCallbacksContentSearchPublished; }
	public static CallbacksContentSave getCallbacksContentSave()
	{
		return sCallbacksContentSave;
	}
	public static CallbacksContentPublish getCallbacksContentPublish() { return sCallbacksContentPublish; }
	public static CallbacksContentUnpublish getCallbacksContentUnpublish() { return sCallbacksContentUnpublish; }
	public static CallbacksContentDelete getCallbacksContentDelete() { return sCallbacksContentDelete; }
	public static CallbacksContentDownload getCallbacksContentDownload() { return sCallbacksContentDownload; }

	private static void abort() {
		Log.e(TAG, "Plugin failed to load and stopped application!");
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public static void initPlugin(String secretApiKey) {
		try
		{
			if (null == Plugin.getActivity())
			{
				Log.e(TAG, "initPlugin: activity is null");
				return;
			}

			Bundle developerInfo = null;
			try {
				developerInfo = StoreFacade.createInitBundle(secretApiKey);
			} catch (InvalidParameterException e) {
				Log.e(TAG, e.getMessage());
				abort();
				return;
			}

			if (sEnableLogging) {
				Log.d(TAG, "initPlugin: developer_id=" + developerInfo.getString(StoreFacade.DEVELOPER_ID));
			}

			if (sEnableLogging) {
				Log.d(TAG, "initPlugin: developer_public_key length=" + developerInfo.getByteArray(StoreFacade.DEVELOPER_PUBLIC_KEY).length);
			}

			StoreFacadeWrapper storeFacadeWrapper = new StoreFacadeWrapper(developerInfo);

			//make facade accessible by activity
			Plugin.setStoreFacadeWrapper(storeFacadeWrapper);

			if (sEnableLogging) {
				Log.i(TAG, "initPlugin: complete.");
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "initPlugin: exception");
			e.printStackTrace();
			Plugin.getCallbacksInitPlugin().onFailure(0, "initPlugin: exception");
		}
	}

    public static boolean processOnActivityResult(final int requestCode, final int resultCode, final Intent data) {
        if (sEnableLogging) {
            Log.i(TAG, "onActivityResult: START");
        }

        StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
        if (null == storeFacadeWrapper) {
            Log.e(TAG, "onActivityResult: StoreFacadeWrapper is null!");
            return false;
        }
        if (sEnableLogging) {
            Log.i(TAG, "onActivityResult: processActivityResult START");
        }
        // Forward this result to the facade, in case it is waiting for any activity results
        if (storeFacadeWrapper.processActivityResult(requestCode, resultCode, data)) {
            if (sEnableLogging) {
                Log.i(TAG, "onActivityResult: processActivityResult END");
            }
            return true;
        }
        if (sEnableLogging) {
            Log.i(TAG, "onActivityResult: END");
        }
        return false;
    }

	public static void requestLogin()
	{
		try
		{
			if (sEnableLogging) {
				Log.i(TAG, "requestLogin");
			}

			StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
			if (null == storeFacadeWrapper)
			{
				Log.e(TAG, "requestLogin: storeFacadeWrapper is null!");
				return;
			}

			storeFacadeWrapper.requestLogin();
		}
		catch (Exception e)
		{
			Log.e(TAG, "requestLogin exception");
			e.printStackTrace();
		}
	}

	public static void requestGamerInfo()
	{
		try
		{
			if (sEnableLogging) {
				Log.i(TAG, "requestGamerInfo");
			}

			StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
			if (null == storeFacadeWrapper)
			{
				Log.e(TAG, "requestGamerInfo: storeFacadeWrapper is null!");
				return;
			}

			storeFacadeWrapper.requestGamerInfo();
		}
		catch (Exception e)
		{
			Log.e(TAG, "requestGamerInfo exception");
			e.printStackTrace();
		}
	}

	public static void requestProducts(String[] products)
	{
		try
		{
			if (sEnableLogging) {
				Log.i(TAG, "Plugin.getProductsAsync");
			}

			StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
			if (null == storeFacadeWrapper)
			{
				Log.e(TAG, "requestProducts: storeFacadeWrapper is null!");
				return;
			}

			storeFacadeWrapper.requestProducts(products);
		}
		catch (Exception e)
		{
			Log.e(TAG, "getProductsAsync exception");
			e.printStackTrace();
		}
	}

	public static void requestPurchase(String identifier, String productType)
	{
		try
		{
			if (sEnableLogging) {
				Log.i(TAG, "requestPurchase identifier: " + identifier);
			}

			StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
			if (null == storeFacadeWrapper)
			{
				Log.e(TAG, "requestPurchase: storeFacadeWrapper is null!");
				return;
			}

            Product product = new Product(identifier, "", 0, 0, "", 0, 0, "", "", Product.Type.valueOf(productType));

			storeFacadeWrapper.requestPurchase(product);
		}
		catch (Exception e)
		{
			Log.e(TAG, "requestPurchase: exception");
			e.printStackTrace();
		}
	}

	public static void requestReceipts()
	{
		try
		{
			if (sEnableLogging) {
				Log.i(TAG, "requestReceipts");
			}

			StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
			if (null == storeFacadeWrapper)
			{
				Log.e(TAG, "requestReceipts: storeFacadeWrapper is null!");
				return;
			}

			storeFacadeWrapper.requestReceipts();
		}
		catch (Exception e)
		{
			Log.e(TAG, "requestReceipts: exception");
			e.printStackTrace();
		}
	}

	private static int getDisplayWidth() {
		Activity activity = Plugin.getActivity();
		if (null == activity)
		{
			Log.e(TAG, "getDisplayWidth: activity is null");
			return 0;
		}
		WindowManager windowManager = activity.getWindowManager();
		Display display = windowManager.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		return size.x;
	}
	private static int getDisplayHeight() {
		Activity activity = Plugin.getActivity();
		if (null == activity)
		{
			Log.e(TAG, "getDisplayHeight: activity is null");
			return 0;
		}
		WindowManager windowManager = activity.getWindowManager();
		Display display = windowManager.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		return size.y;
	}

	public static void updateSafeArea(final float progress) {
		final Activity activity = Plugin.getActivity();
		if (null == activity)
		{
			Log.e(TAG, "updateSafeArea: activity is null");
			return;
		}
		Runnable runnable = new Runnable() {
			public void run() {
				// bring in by %
				float percent = 0.1f;
				float ratio = 1 - (1 - progress) * percent;
				float halfRatio = 1 - (1 - progress) * percent * 0.5f;
				float maxWidth = getDisplayWidth();
				float maxHeight = getDisplayHeight();
				FrameLayout content = (FrameLayout)activity.findViewById(android.R.id.content);
				ViewGroup.LayoutParams layout = content.getLayoutParams();
				layout.width = (int)(maxWidth * ratio);
				layout.height = (int)(maxHeight * ratio);
				content.setLayoutParams(layout);
				content.setX(maxWidth - maxWidth * halfRatio);
				content.setY(maxHeight - maxHeight * halfRatio);
			}
		};
		activity.runOnUiThread(runnable);
	}

	public static void shutdown() {
		final Activity activity = Plugin.getActivity();
		if (null == activity)
		{
			Log.e(TAG, "shutdown: activity is null!");
			return;
		}
		Runnable runnable = new Runnable() {
			public void run() {
				StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
				if (null == storeFacadeWrapper) {
					Log.e(TAG, "shutdown: storeFacadeWrapper is null!");
				} else {
					storeFacadeWrapper.shutdown();
				}
			}
		};
		activity.runOnUiThread(runnable);
	}

	public static void saveGameaMod(final GameMod.Editor editor, final GameMod gameMod) {
		try
		{
			//Log.i(TAG, "saveOuyaMod");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "saveGameaMod: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.saveOuyaMod(gameMod, editor);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "saveOuyaMod: exception");
			e.printStackTrace();
		}
	}

	public static void getOuyaContentInstalled() {
		try
		{
			//Log.i(TAG, "getOuyaContentInstalled");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						GameModManager gameModManager = Plugin.getGameModManager();
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "getOuyaContentInstalled: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.getOuyaContentInstalled();
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "getOuyaContentInstalled: exception");
			e.printStackTrace();
		}
	}

	public static GameMod[] getOuyaContentInstalledResultsArray() {
		List<GameMod> result = Plugin.getOuyaContentInstalledResults();
		if (null == result) {
			return null;
		}
		GameMod[] retVal = new GameMod[result.size()];
		result.toArray(retVal);
		return retVal;
	}

	public static void getOuyaContentPublished(final String sortMethod) {
		try
		{
			//Log.i(TAG, "getOuyaContentPublished");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "getOuyaContentPublished: storeFacadeWrapper is null!");
						} else {
							GameModManager.SortMethod sort = GameModManager.SortMethod.valueOf(sortMethod);
							//Log.i(TAG, "sortMethod="+sortMethod);
							storeFacadeWrapper.getOuyaContentPublished(sort);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "getOuyaContentPublished: exception");
			e.printStackTrace();
		}
	}

	public static GameMod[] getOuyaContentPublishedResultsArray() {
		List<GameMod> result = Plugin.getOuyaContentPublishedResults();
		if (null == result) {
			Log.e(TAG, "getOuyaContentPublishedResults: result is null!");
			return null;
		}
		//Log.i(TAG, "getOuyaContentPublishedResults returning size="+result.size());
		GameMod[] retVal = new GameMod[result.size()];
		result.toArray(retVal);
		return retVal;
	}

	public static void contentDelete(final GameMod gameMod) {
		try
		{
			//Log.i(TAG, "contentDelete");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "contentDelete: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.contentDelete(gameMod);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "contentDelete: exception");
			e.printStackTrace();
		}
	}

	public static void contentPublish(final GameMod gameMod) {
		try
		{
			//Log.i(TAG, "contentPublish");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "contentPublish: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.contentPublish(gameMod);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "contentPublish: exception");
			e.printStackTrace();
		}
	}

	public static void contentUnpublish(final GameMod gameMod) {
		try
		{
			//Log.i(TAG, "contentUnpublish");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "contentUnpublish: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.contentUnpublish(gameMod);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "contentUnpublish: exception");
			e.printStackTrace();
		}
	}

	public static void contentDownload(final GameMod gameMod) {
		try
		{
			//Log.i(TAG, "contentDownload");
			final Activity activity = Plugin.getActivity();
			if (null != activity) {
				Runnable runnable = new Runnable()
				{
					public void run()
					{
						StoreFacadeWrapper storeFacadeWrapper = Plugin.getStoreFacadeWrapper();
						if (null == storeFacadeWrapper) {
							Log.e(TAG, "contentDownload: storeFacadeWrapper is null!");
						} else {
							storeFacadeWrapper.contentDownload(gameMod);
						}
					}
				};
				activity.runOnUiThread(runnable);
			}
		}
		catch (Exception e)
		{
			Log.e(TAG, "contentDownload: exception");
			e.printStackTrace();
		}
	}

	public static float getFloat(Float f) {
		if (null == f) {
			return 0;
		}
		return f.floatValue();
	}

	public static Bitmap[] getBitmapArray(List<Bitmap> list) {
		if (null == list) {
			return new Bitmap[0];
		}
		Bitmap[] retVal = new Bitmap[list.size()];
		list.toArray(retVal);
		return retVal;
	}

	public static GameModScreenshot[] getOuyaModScreenshotArray(List<GameModScreenshot> list) {
		if (null == list) {
			return new GameModScreenshot[0];
		}
		GameModScreenshot[] retVal = new GameModScreenshot[list.size()];
		list.toArray(retVal);
		return retVal;
	}

	public static String[] getStringArray(List<String> list) {
		if (null == list) {
			return new String[0];
		}
		String[] retVal = new String[list.size()];
		list.toArray(retVal);
		return retVal;
	}

    public static void quit() {
        if (sEnableLogging) {
            Log.d(TAG, "quit: Application quiting...");
        }

        final Activity activity = getActivity();
        if (null == activity) {
            Log.e(TAG, "quit: activity is null!");
            return;
        }

        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                activity.finish();
            }
        };
        activity.runOnUiThread(runnable);
    }
}
