#include "NexusAI.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "Editor.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Commands/UICommandList.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FNexusAIModule"

void FNexusAIModule::StartupModule()
{
    InitializeAIService();
    BindEditorCallbacks();
    RegisterNexusCommands();
    ExtendEditorToolbar();
    
    UE_LOG(LogTemp, Log, TEXT("Nexus AI Module Started - Your intelligent companion for Unreal Engine"));
}

void FNexusAIModule::ShutdownModule()
{
    UnbindEditorCallbacks();
    UE_LOG(LogTemp, Log, TEXT("Nexus AI Module Shutdown"));
}

void FNexusAIModule::ProcessAIIntent(const FString& Intent, const FString& Context)
{
    if (bIsProcessingRequest)
    {
        UE_LOG(LogTemp, Warning, TEXT("Already processing a request. Please wait."));
        return;
    }

    bIsProcessingRequest = true;

    // Create HTTP request to AI service
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(AIEndpoint);
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *APIKey));
    
    // Create JSON payload
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("intent"), Intent);
    JsonObject->SetStringField(TEXT("context"), Context);
    JsonObject->SetObjectField(TEXT("project_context"), ProjectContext);
    
    FString RequestString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    
    Request->SetContentAsString(RequestString);
    Request->OnProcessRequestComplete().BindRaw(this, &FNexusAIModule::HandleAIResponse);
    Request->ProcessRequest();
}

void FNexusAIModule::HandleAIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    bIsProcessingRequest = false;

    if (bSuccess && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();
        
        // Parse JSON response
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
        
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            // Process different response types
            FString ActionType = JsonObject->GetStringField("action_type");
            
            if (ActionType == "generate_blueprint")
            {
                FString BlueprintCode = JsonObject->GetStringField("blueprint_code");
                // Handle Blueprint generation
            }
            else if (ActionType == "modify_file")
            {
                FString FilePath = JsonObject->GetStringField("file_path");
                FString ModifiedContent = JsonObject->GetStringField("content");
                // Handle file modification
            }
            else if (ActionType == "suggestion")
            {
                FString Suggestion = JsonObject->GetStringField("suggestion");
                UE_LOG(LogTemp, Log, TEXT("Nexus AI Suggestion: %s"), *Suggestion);
            }
        }
    }
}

void FNexusAIModule::InitializeAIService()
{
    // Initialize HTTP module
    FHttpModule::Get().SetHttpTimeout(30.0f);
    
    // Load API settings from config
    // TODO: Implement secure API key storage
    AIEndpoint = TEXT("YOUR_AI_ENDPOINT");
    APIKey = TEXT("YOUR_API_KEY");
    bIsProcessingRequest = false;
}

void FNexusAIModule::RegisterNexusCommands()
{
    // Register UI commands for Nexus AI
    // TODO: Implement command registration
}

void FNexusAIModule::ExtendEditorToolbar()
{
    // Add Nexus AI button to editor toolbar
    // TODO: Implement toolbar extension
}

void FNexusAIModule::AnalyzeCodebase(const FString& Directory)
{
    // Analyze project structure and update context
    // TODO: Implement codebase analysis
}

void FNexusAIModule::GenerateCppClassFromPrompt(const FString& Prompt)
{
    ProcessAIIntent(TEXT("generate_cpp_class"), Prompt);
}

void FNexusAIModule::GenerateTestsFromImplementation(const FString& SourcePath)
{
    ProcessAIIntent(TEXT("generate_tests"), SourcePath);
}

void FNexusAIModule::UpdateContextFromFile(const FString& FilePath)
{
    // Update project context when files change
    // TODO: Implement context updating
}

void FNexusAIModule::BindEditorCallbacks()
{
    // Bind to asset registry events
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    AssetRegistryModule.Get().OnAssetAdded().AddRaw(this, &FNexusAIModule::HandleAssetCreated);
}

void FNexusAIModule::UnbindEditorCallbacks()
{
    if (FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
    {
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
        AssetRegistryModule.Get().OnAssetAdded().RemoveAll(this);
    }
}

void FNexusAIModule::HandleAssetCreated(UObject* Asset)
{
    if (Asset)
    {
        UE_LOG(LogTemp, Log, TEXT("New Asset Created: %s"), *Asset->GetName());
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNexusAIModule, NexusAI)
