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
import android.content.*;
import android.os.Bundle;
import android.util.Log;

import com.razerzone.store.sdk.CancelIgnoringResponseListener;
import com.razerzone.store.sdk.GamerInfo;
import com.razerzone.store.sdk.PurchaseResult;
import com.razerzone.store.sdk.ResponseListener;
import com.razerzone.store.sdk.StoreFacade;
import com.razerzone.store.sdk.content.GameMod;
import com.razerzone.store.sdk.content.GameModException;
import com.razerzone.store.sdk.content.GameModManager;
import com.razerzone.store.sdk.purchases.Product;
import com.razerzone.store.sdk.purchases.Purchasable;
import com.razerzone.store.sdk.purchases.Receipt;

import java.util.*;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class StoreFacadeWrapper
{
    private static final String TAG = StoreFacadeWrapper.class.getSimpleName();

	private static final boolean sEnableLogging = false;

    private StoreFacade mStoreFacade;

	// listener for init complete
	private CancelIgnoringResponseListener<Bundle> mInitCompleteListener = null;

	// listener for requesting login
	private ResponseListener<Void> mRequestLoginListener = null;

	// listener for requesting gamer info
	private ResponseListener<GamerInfo> mRequestGamerInfoListener = null;

	// listener for getting products
	private ResponseListener<List<Product>> mRequestProductsListener = null;

	// listener for requesting purchase
	private ResponseListener<PurchaseResult> mRequestPurchaseListener = null;

	// listener for getting receipts
	private ResponseListener<Collection<Receipt>> mRequestReceiptsListener = null;

	// listener for shutdown
	private CancelIgnoringResponseListener mShutdownListener = null;

	// Content interface for community content
	private GameModManager mGameModManager;

	// listener for initializing community content
	private GameModManager.InitializedListener mGameModManagerInitListener = null;

	// listener for looking for installed content
	private GameModManager.SearchListener mInstalledSearchListener = null;

	// listener for looking for published content
	private GameModManager.SearchListener mPublishedSearchListener = null;
	
	// listener for saving content
	private GameModManager.SaveListener mSaveListener;

	// listener for publishing content
    private GameModManager.PublishListener mPublishListener;

	// listener for unpublishing content
    private GameModManager.UnpublishListener mUnpublishListener;

	// listener for downloading content
    private GameModManager.DownloadListener mDownloadListener;

	// listener for deleting content
    private GameModManager.DeleteListener mDeleteListener;

	public StoreFacadeWrapper(Bundle developerInfo)
	{
		try {
			if (sEnableLogging) {
				Log.i(TAG, "StoreFacadeWrapper");
			}
			if (null == mStoreFacade) {
				mStoreFacade = StoreFacade.getInstance();
			}

			Init(developerInfo);

		} catch (Exception ex) {
			Log.e(TAG, "StoreFacadeWrapper constructor exception", ex);
		}
	}

	public class ErrorResponse
	{
		public int errorCode = 0;
		public String errorMessage = "";
	}

	private void Init(Bundle developerInfo)
	{
        if (sEnableLogging) {
            Log.i(TAG, "Init(Bundle developerInfo)");
        }

        Activity activity = Plugin.getActivity();
        if (null == activity) {
            Log.e(TAG, "Activity is null!");
            return;
        }

        mInitCompleteListener = new CancelIgnoringResponseListener<Bundle>() {
            @Override
            public void onSuccess(Bundle bundle) {
                if (sEnableLogging) {
                    Log.d(TAG, "InitCompleteListener: onSuccess");
                }
                Plugin.getCallbacksInitPlugin().onSuccess();
            }

            @Override
            public void onFailure(int errorCode, String errorMessage, Bundle data) {
                if (sEnableLogging) {
                    Log.d(TAG, "InitCompleteListener: onFailure errorCode="+errorCode+" errorMessage="+errorMessage);
                }
                Plugin.getCallbacksInitPlugin().onFailure(errorCode, errorMessage);
            }
        };

        mRequestLoginListener = new ResponseListener<Void>() {
            @Override
            public void onSuccess(Void result) {

                if (sEnableLogging) {
                    Log.d(TAG, "RequestLoginListener: onSuccess");
                }

                Plugin.getCallbacksRequestLogin().onSuccess();
            }

            @Override
            public void onFailure(int errorCode, String errorMessage, Bundle optionalData) {
                Log.e(TAG, "RequestLoginListener: onFailure errorCode="+errorCode+" errorMessage="+errorMessage);
                Plugin.getCallbacksRequestLogin().onFailure(errorCode, errorMessage);
            }

            @Override
            public void onCancel() {
                if (sEnableLogging) {
                    Log.d(TAG, "RequestLoginListener: onCancel");
                }

                Plugin.getCallbacksRequestLogin().onCancel();
            }
        };

        mRequestGamerInfoListener = new CancelIgnoringResponseListener<GamerInfo>() {
            @Override
            public void onSuccess(GamerInfo info) {

            	JSONObject json = new JSONObject();
				try {
					json.put("uuid", info.getUuid());
					json.put("username", info.getUsername());
				} catch (JSONException e1) {
				}
				String jsonData = json.toString();

                if (sEnableLogging) {
                    Log.d(TAG, "RequestGamerInfoListener: onSuccess jsonData=" + jsonData);
                }

				Plugin.getCallbacksRequestGamerInfo().onSuccess(jsonData);
            }

            @Override
            public void onFailure(int errorCode, String errorMessage, Bundle optionalData) {
				Log.e(TAG, "RequestGamerInfoListener: onFailure errorCode="+errorCode+" errorMessage="+errorMessage);
				Plugin.getCallbacksRequestGamerInfo().onFailure(errorCode, errorMessage);
            }
        };

		mRequestProductsListener = new ResponseListener<List<Product>>()
		{
			@Override
			public void onSuccess(final List<Product> products) {

                if (sEnableLogging) {
                    Log.i(TAG, "RequestProductsListener: onSuccess");
                }

				//send each item in the list
				if (null != products) {

					JSONArray jarray = new JSONArray();
					for (Product product : products)
					{
						JSONObject json = new JSONObject();
						try {
							json.put("currencyCode", product.getCurrencyCode());
							json.put("description", product.getDescription());
                            json.put("developerName", product.getDeveloperName());
							json.put("identifier", product.getIdentifier());
							json.put("localPrice", product.getLocalPrice());
							json.put("name", product.getName());
							json.put("originalPrice", product.getOriginalPrice());
							json.put("percentOff", product.getPercentOff());
                            json.put("priceInCents", product.getPriceInCents());
                            json.put("productType", product.getType().toString());
							jarray.put(products.indexOf(product), json);
						} catch (JSONException e1) {
						}
					}

					String jsonData = jarray.toString();

                    if (sEnableLogging) {
                        Log.d(TAG, "RequestProductsListener: onSuccess jsonData=" + jsonData);
                    }
					Plugin.getCallbacksRequestProducts().onSuccess(jsonData);
				} else {
					if (sEnableLogging) {
                        Log.d(TAG, "RequestProductsListener: onSuccess (empty)");
                    }
					Plugin.getCallbacksRequestProducts().onSuccess("");
				}
			}

			@Override
			public void onFailure(int errorCode, String errorMessage, Bundle optionalData) {

                Log.e(TAG, "RequestProductsListener: onFailure errorCode=" + errorCode + " errorMessage=" + errorMessage);
				Plugin.getCallbacksRequestProducts().onFailure(errorCode, errorMessage);
			}

			@Override
			public void onCancel() {
				Plugin.getCallbacksRequestProducts().onCancel();
			}
		};

		mRequestPurchaseListener = new ResponseListener<PurchaseResult>() {

			@Override
			public void onSuccess(PurchaseResult result)
			{
                if (sEnableLogging) {
                    Log.d(TAG, "RequestPurchaseListener: onSuccess");
                }

				if (null != result)
				{
					JSONObject json = new JSONObject();
					try {
						json.put("identifier", result.getProductIdentifier());
                        json.put("orderId", result.getOrderId());
					} catch (JSONException e1) {
					}
					String jsonData = json.toString();

                    if (sEnableLogging) {
                        Log.d(TAG, "RequestPurchaseListener: onSuccess jsonData=" + jsonData);
                    }
					Plugin.getCallbacksRequestPurchase().onSuccess(jsonData);
				}
			}

			@Override
			public void onFailure(int errorCode, String errorMessage, Bundle optionalData) {
                Log.e(TAG, "RequestPurchaseListener: onFailure errorCode="+errorCode+" errorMessage="+errorMessage);
				Plugin.getCallbacksRequestPurchase().onFailure(errorCode, errorMessage);
			}

			@Override
			public void onCancel()
			{
                if (sEnableLogging) {
                    Log.d(TAG, "RequestPurchaseListener: onCancel");
                }
				Plugin.getCallbacksRequestPurchase().onCancel();
			}
		};

        mRequestReceiptsListener = new ResponseListener<Collection<Receipt>>() {
            @Override
            public void onSuccess(Collection<Receipt> receipts) {
                if (receipts != null) {

                    JSONArray jarray = new JSONArray();
                    int index = 0;
                    for (Receipt receipt : receipts)
                    {
                        JSONObject json = new JSONObject();
                        try {
                            json.put("currency", receipt.getCurrency());
                            json.put("gamerUuid", receipt.getGamer());
                            json.put("generatedDate", receipt.getGeneratedDate());
                            json.put("identifier", receipt.getIdentifier());
                            json.put("localPrice", receipt.getLocalPrice());
                            json.put("priceInCents", receipt.getPriceInCents());
                            json.put("purchaseDate", receipt.getPurchaseDate());
                            json.put("uuid", receipt.getUuid());
                            jarray.put(index, json);
                            ++index;
                        } catch (JSONException e1) {
                        }
                    }

                    String jsonData = jarray.toString();

                    if (sEnableLogging) {
                        Log.i(TAG, "RequestReceiptsListener: onSuccess jsonData=" + jsonData);
                    }
                    Plugin.getCallbacksRequestReceipts().onSuccess(jsonData);
                } else {
                    if (sEnableLogging) {
                        Log.i(TAG, "RequestReceiptsListener: onSuccess jsonData=(empty)");
                    }
                    Plugin.getCallbacksRequestReceipts().onSuccess("");
                }
            }

            @Override
            public void onFailure(int errorCode, String errorMessage, Bundle bundle) {
                Log.e(TAG, "RequestReceiptsListener onFailure errorCode="+errorCode+" errorMessage="+errorMessage);
                Plugin.getCallbacksRequestReceipts().onFailure(errorCode, errorMessage);
            }

            @Override
            public void onCancel() {
                if (sEnableLogging) {
                    Log.d(TAG, "RequestReceiptsListener invoke onCancel");
                }
                Plugin.getCallbacksRequestReceipts().onCancel();
            }
        };

        mShutdownListener = new CancelIgnoringResponseListener() {
            @Override
            public void onSuccess(Object o) {
                if (sEnableLogging) {
                    Log.d(TAG, "ShutdownListener: onSuccess");
                }
                Plugin.getCallbacksShutdown().onSuccess();
            }

            @Override
            public void onFailure(int errorCode, String errorMessage, Bundle data) {
                Log.e(TAG, "ShutdownListener onFailure failed to shutdown! errorCode="+errorCode+" message="+errorMessage);
                Plugin.getCallbacksShutdown().onFailure(errorCode, errorMessage);
            }
        };

        try {
            mStoreFacade.init(activity, developerInfo, mInitCompleteListener);
        } catch (Exception e) {
            e.printStackTrace();
        }

        mGameModManager = GameModManager.getInstance();
        Plugin.setGameModManager(mGameModManager);

		mGameModManagerInitListener = new GameModManager.InitializedListener() {

			@Override
			public void onDestroyed() {
				Log.i(TAG, "ContentInitListener: onDestroyed");
				Plugin.getCallbacksContentInit().onDestroyed();
			}

			@Override
			public void onInitialized() {
				Log.i(TAG, "ContentInitListener: onInitialized");
				Plugin.getCallbacksContentInit().onInitialized();
			}
			
		};

		mGameModManager.registerInitializedListener(mGameModManagerInitListener);

		mInstalledSearchListener = new GameModManager.SearchListener() {
			@Override
			public void onError(int code, String reason) {
				Log.e(TAG, "InstalledSearchListener: onError code="+code+" reason="+reason);
				Plugin.getCallbacksContentSearchInstalled().onError(code, reason);
			}

			@Override
			public void onResults(List<GameMod> gameMods, int count) {
				Log.i(TAG, "InstalledSearchListener: onResults count="+count+" list count="+gameMods.size());
				Plugin.getCallbacksContentSearchInstalled().onResults(gameMods.toArray(new GameMod[gameMods.size()]), count);
			}
		};
		
		mPublishedSearchListener = new GameModManager.SearchListener() {
			@Override
			public void onError(int code, String reason) {
				Log.e(TAG, "PublishedSearchListener: onError code="+code+" reason="+reason);
				Plugin.getCallbacksContentSearchPublished().onError(code, reason);
			}

			@Override
			public void onResults(List<GameMod> gameMods, int count) {
				Log.i(TAG, "PublishedSearchListener: onResults count="+count+" list count="+gameMods.size());
				Plugin.getCallbacksContentSearchPublished().onResults(gameMods.toArray(new GameMod[gameMods.size()]), count);
			}
		};
		
		mSaveListener = new GameModManager.SaveListener() {

			@Override
			public void onError(GameMod gameMod, int code, String reason) {
				Log.e(TAG, "SaveListener: onError code="+code+" reason="+reason);
				Plugin.getCallbacksContentSave().onError(gameMod, code, reason);
			}

			@Override
			public void onSuccess(GameMod gameMod) {
				Log.i(TAG, "SaveListener: onSuccess");
				Plugin.getCallbacksContentSave().onSuccess(gameMod);
			}			
		};
		
	    mPublishListener = new GameModManager.PublishListener() {

			@Override
			public void onError(GameMod gameMod, int code, String reason, Bundle bundle) {
				Log.e(TAG, "PublishListener: onError code="+code+" reason="+reason);
				Plugin.getCallbacksContentPublish().onError(gameMod, code, reason, bundle);
			}

			@Override
			public void onSuccess(GameMod gameMod) {
				Log.i(TAG, "PublishListener: onSuccess");
				Plugin.getCallbacksContentPublish().onSuccess(gameMod);
			}
	    	
	    };
	    
	    mUnpublishListener = new GameModManager.UnpublishListener() {

			@Override
			public void onError(GameMod gameMod, int code, String reason) {
				Log.e(TAG, "UnpublishListener: onError code="+code+" reason="+reason);
				Plugin.getCallbacksContentUnpublish().onError(gameMod, code, reason);
			}

			@Override
			public void onSuccess(GameMod gameMod) {
				Log.i(TAG, "UnpublishListener: onSuccess");
				Plugin.getCallbacksContentUnpublish().onSuccess(gameMod);
			}
	    	
	    };
	    
	    mDeleteListener = new GameModManager.DeleteListener() {

			@Override
			public void onDeleteFailed(GameMod gameMod, int code, String reason) {
				Log.e(TAG, "DeleteListener: onError code="+code+" reason="+reason);
                Plugin.getCallbacksContentDelete().onDeleteFailed(gameMod, code, reason);
			}

			@Override
			public void onDeleted(GameMod gameMod) {
				Log.i(TAG, "DeleteListener: onDeleted");
                Plugin.getCallbacksContentDelete().onDeleted(gameMod);
			}
	    	
	    };
	    
	    mDownloadListener = new GameModManager.DownloadListener() {
			
			@Override
			public void onProgress(GameMod gameMod, int progress) {
                Plugin.getCallbacksContentDownload().onProgress(gameMod, progress);
			}
			
			@Override
			public void onFailed(GameMod gameMod) {
                Plugin.getCallbacksContentDownload().onFailed(gameMod);
			}
			
			@Override
			public void onComplete(GameMod gameMod) {
                Plugin.getCallbacksContentDownload().onComplete(gameMod);
			}			
		};
	}

	public void shutdown() {
		if (sEnableLogging) {
			Log.i(TAG, "shutdown");
		}
		if (null == mStoreFacade) {
			Log.e(TAG, "shutdown: StoreFacade is null!");
		} else {
			mStoreFacade.shutdown(mShutdownListener);
		}
	}

	public boolean processActivityResult(final int requestCode, final int resultCode, final Intent data) {
		if (null == mStoreFacade) {
            Log.e(TAG, "processActivityResult: StoreFacade is null!");
            return false;
        }
		return mStoreFacade.processActivityResult(requestCode, resultCode, data);
	}

	public void requestProducts(String[] products) {
		if (sEnableLogging) {
			Log.i(TAG, "requestProducts");
		}
		if (null == mStoreFacade) {
			Log.e(TAG, "requestProducts: StoreFacade is null!");
			return;
		}
		if (null != mRequestProductsListener) {
			mStoreFacade.requestProductList(Plugin.getActivity(), products, mRequestProductsListener);
		} else {
			Log.e(TAG, "mRequestProductsListener is null");
		}
	}

    public void requestLogin() {
        if (sEnableLogging) {
            Log.i(TAG, "requestLogin");
        }
        if (null == mStoreFacade) {
            Log.e(TAG, "requestLogin: StoreFacade is null!");
            return;
        }
        if (null != mRequestLoginListener) {
            mStoreFacade.requestLogin(Plugin.getActivity(), mRequestLoginListener);
        } else {
            Log.e(TAG, "StoreFacadeWrapper.requestLogin mRequestLoginListener is null");
        }
    }

	public void requestGamerInfo() {
		if (sEnableLogging) {
			Log.i(TAG, "requestGamerInfo");
		}
		if (null == mStoreFacade) {
			Log.e(TAG, "requestGamerInfo: StoreFacade is null!");
			return;
		}
		if (null != mRequestGamerInfoListener) {
			mStoreFacade.requestGamerInfo(Plugin.getActivity(), mRequestGamerInfoListener);
		} else {
			Log.e(TAG, "StoreFacadeWrapper.requestGamerInfo mRequestGamerInfoListener is null");
		}
	}

	public void putGameData(String key, String val) {
		mStoreFacade.putGameData(key, val);
	}

	public String getGameData(String key) {
		return mStoreFacade.getGameData(key);
	}

	public void requestReceipts() {
		if (sEnableLogging) {
			Log.i(TAG, "requestReceipts");
		}
		if (null == mStoreFacade) {
			Log.e(TAG, "requestReceipts: StoreFacade is null!");
			return;
		}
		if (null != mRequestReceiptsListener) {
			mStoreFacade.requestReceipts(Plugin.getActivity(), mRequestReceiptsListener);
		} else {
			Log.e(TAG, "mRequestReceiptsListener is null");
		}
	}

	public Boolean isRunningOnSupportedHardware() {
		return mStoreFacade.isRunningOnSupportedHardware();
	}

	public void requestPurchase(final Product product) {
		if (sEnableLogging) {
			Log.i(TAG, "requestPurchase(" + product.getIdentifier() + ")");
		}
		if (null == mStoreFacade) {
			Log.e(TAG, "requestPurchase: StoreFacade is null!");
			return;
		}
		if (null != mRequestPurchaseListener) {
			Purchasable purchasable = product.createPurchasable();
			mStoreFacade.requestPurchase(Plugin.getActivity(), purchasable, mRequestPurchaseListener);
		} else {
			Log.e(TAG, "mRequestPurchaseListener is null");
		}
	}

    private class ReceiptListener implements ResponseListener<Collection<Receipt>> {

        @Override
        public void onSuccess(Collection<Receipt> receipts)
		{
            if (receipts != null) {

				JSONArray jarray = new JSONArray();
				int index = 0;
				for (Receipt receipt : receipts)
				{
					JSONObject json = new JSONObject();
					try {
						json.put("identifier", receipt.getIdentifier());
						json.put("purchaseDate", receipt.getPurchaseDate());
						json.put("gamer", receipt.getGamer());
						json.put("uuid", receipt.getUuid());
						json.put("localPrice", receipt.getLocalPrice());
						json.put("currency", receipt.getCurrency());
						json.put("generatedDate", receipt.getGeneratedDate());
						jarray.put(index, json);
						++index;
					} catch (JSONException e1) {
					}
				}

				String jsonData = jarray.toString();

				Log.i(TAG, "ReceiptListener ReceiptListListener jsonData=" + jsonData);
                Plugin.getCallbacksRequestReceipts().onSuccess(jsonData);
			} else {
				Log.i(TAG, "ReceiptListener ReceiptListListener jsonData=(empty)");
                Plugin.getCallbacksRequestReceipts().onSuccess("");
			}
        }

        @Override
        public void onFailure(int errorCode, String errorMessage, Bundle optionalData) {
            Log.w(TAG, "Request Receipts error (code " + errorCode + ": " + errorMessage + ")");
            Plugin.getCallbacksRequestReceipts().onFailure(errorCode, errorMessage);
        }

        @Override
        public void onCancel()
		{
			Log.i(TAG, "ReceiptListener Invoke ReceiptListCancelListener");
            Plugin.getCallbacksRequestReceipts().onCancel();
		}
    }
    
    public void saveOuyaMod(GameMod gameMod, GameMod.Editor editor) {
    	
    	try {
            editor.save(mSaveListener);
        } catch(GameModException e) {
            switch(e.getCode()) {
                case GameModException.CONTENT_NO_TITLE:
                	mSaveListener.onError(gameMod, e.getCode(), "Title required!");
                    break;
                case GameModException.CONTENT_NO_CATEGORY:
                	mSaveListener.onError(gameMod, e.getCode(), "Category required!");
                    break;
                case GameModException.CONTENT_NO_SCREENSHOTS:
                	mSaveListener.onError(gameMod, e.getCode(), "At least one screenshot required!");
                    break;
                case GameModException.CONTENT_NO_FILES:
                	mSaveListener.onError(gameMod, e.getCode(), "At least one file required!");
                    break;
                case GameModException.CONTENT_NOT_EDITABLE:
                	mSaveListener.onError(gameMod, e.getCode(), "OuyaMod is not editable!");
                    break;
                default:
                	mSaveListener.onError(gameMod, e.getCode(), "Save Exception!");
                	break;
            }
        }
    }
    
	public void getOuyaContentInstalled() {
		if (null == mGameModManager) {
			Log.e(TAG, "mGameModManager is null");
		} else if (null == mInstalledSearchListener) {
			Log.e(TAG, "mInstalledSearchListener is null");
		} else {
			mGameModManager.getInstalled(mInstalledSearchListener);
		}
	}

	public void getOuyaContentPublished(final GameModManager.SortMethod sortMethod) {
		if (null == mGameModManager) {
			Log.e(TAG, "mGameModManager is null");
		} else if (null == mPublishedSearchListener) {
			Log.e(TAG, "mPublishedSearchListener is null");
		} else {
			mGameModManager.search(sortMethod, mPublishedSearchListener);
		}
	}

	public void contentDelete(final GameMod gameMod) {
		if (null == mDeleteListener) {
			Log.e(TAG, "mDeleteListener is null");
		} else {
			gameMod.delete(mDeleteListener);
		}

	}

	public void contentPublish(final GameMod gameMod) {
		if (null == mPublishListener) {
			Log.e(TAG, "mPublishListener is null");
		} else {
			gameMod.publish(mPublishListener);
		}
	}

	public void contentUnpublish(final GameMod gameMod) {
		if (null == mUnpublishListener) {
			Log.e(TAG, "mUnpublishListener is null");
		} else {
			gameMod.unpublish(mUnpublishListener);
		}
	}

	public void contentDownload(final GameMod gameMod) {
		if (null == mDownloadListener) {
			Log.e(TAG, "mDownloadListener is null");
		} else {
			gameMod.download(mDownloadListener);
		}
	}
}