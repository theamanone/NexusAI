#include "NexusMarketplace.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"

void FNexusMarketplace::Initialize()
{
    // Initialize marketplace integration
    MarketplaceEndpoint = TEXT("https://www.unrealengine.com/marketplace/api");
    bIsInitialized = true;
}

void FNexusMarketplace::SearchAssets(const FString& Query)
{
    if (!bIsInitialized)
    {
        Initialize();
    }

    // Create HTTP request
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(FString::Printf(TEXT("%s/assets/search?query=%s"), *MarketplaceEndpoint, *FPlatformHttp::UrlEncode(Query)));
    Request->SetVerb(TEXT("GET"));
    Request->OnProcessRequestComplete().BindRaw(this, &FNexusMarketplace::OnSearchComplete);
    Request->ProcessRequest();
}

void FNexusMarketplace::OnSearchComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess && Response.IsValid())
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
        
        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            // Process marketplace assets
            const TArray<TSharedPtr<FJsonValue>>* AssetsArray;
            if (JsonObject->TryGetArrayField(TEXT("assets"), AssetsArray))
            {
                for (const auto& AssetValue : *AssetsArray)
                {
                    auto AssetObject = AssetValue->AsObject();
                    FString AssetName = AssetObject->GetStringField(TEXT("name"));
                    FString AssetDescription = AssetObject->GetStringField(TEXT("description"));
                    
                    // Analyze asset compatibility and suggest integration
                    AnalyzeAssetCompatibility(AssetName, AssetDescription);
                }
            }
        }
    }
}

void FNexusMarketplace::AnalyzeAssetCompatibility(const FString& AssetName, const FString& AssetDescription)
{
    // Use AI to analyze asset compatibility with current project
    FString AnalysisPrompt = FString::Printf(TEXT("Analyze marketplace asset compatibility: %s - %s"), *AssetName, *AssetDescription);
    ProcessAIIntent(AnalysisPrompt);
}

void FNexusMarketplace::InstallAsset(const FString& AssetId)
{
    // Handle marketplace asset installation
    // This would typically integrate with Epic's launcher
    UE_LOG(LogTemp, Log, TEXT("Installing marketplace asset: %s"), *AssetId);
}

void FNexusMarketplace::ProcessAIIntent(const FString& Intent)
{
    // Forward to main AI processing
    if (OnAIIntentProcessed.IsBound())
    {
        OnAIIntentProcessed.Broadcast(Intent);
    }
}
