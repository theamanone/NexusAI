#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAIIntentProcessed, const FString&);

class NEXUSAI_API FNexusMarketplace
{
public:
    void Initialize();
    void SearchAssets(const FString& Query);
    void InstallAsset(const FString& AssetId);
    
    // AI Integration
    FOnAIIntentProcessed OnAIIntentProcessed;
    
private:
    void OnSearchComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
    void AnalyzeAssetCompatibility(const FString& AssetName, const FString& AssetDescription);
    void ProcessAIIntent(const FString& Intent);
    
    FString MarketplaceEndpoint;
    bool bIsInitialized;
};
