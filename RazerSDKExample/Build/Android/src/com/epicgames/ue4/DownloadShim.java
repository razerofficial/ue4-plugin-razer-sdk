package com.epicgames.ue4;

import com.razerzone.store.sdk.engine.unreal.examples.razersdkexample.OBBDownloaderService;
import com.razerzone.store.sdk.engine.unreal.examples.razersdkexample.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

