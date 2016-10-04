ECHO ON
COPY /Y store-sdk-standard-release.aar AARRazerSDK\pluginrazersdk\libs
COPY /Y store-sdk-standard-release.aar InAppPurchases\Plugins\RazerSDKPlugin\Build\Android\libs
COPY /Y store-sdk-standard-release.jar InAppPurchases\Plugins\RazerSDKPlugin\Build\Android\libs
COPY /Y store-sdk-standard-release.aar RazerSDKExample\Plugins\RazerSDKPlugin\Build\Android\libs
COPY /Y store-sdk-standard-release.jar RazerSDKExample\Plugins\RazerSDKPlugin\Build\Android\libs
PAUSE
