#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Engine/EngineTypes.h"
#include "Framework/Commands/Commands.h"

class FNexusAIModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // Core AI Functions
    void ProcessAIIntent(const FString& Intent, const FString& Context = TEXT(""));
    FString GenerateResponse(const FString& Prompt);
    
    // File Operations
    void HandleFileChanged(const FString& FilePath);
    void HandleAssetCreated(UObject* Asset);
    void CreateFileFromPrompt(const FString& Prompt);
    void ModifyFileFromPrompt(const FString& FilePath, const FString& Prompt);
    
    // Blueprint & Code Generation
    void GenerateBlueprintFromPrompt(const FString& Prompt);
    void GenerateCppClassFromPrompt(const FString& Prompt);
    void GenerateTestsFromImplementation(const FString& SourcePath);
    
    // Context Understanding
    void AnalyzeCodebase(const FString& Directory);
    void UnderstandProjectStructure();
    void SuggestOptimizations();
    
    // UI Commands
    void RegisterNexusCommands();
    void ExtendEditorToolbar();
    
private:
    // AI Service Management
    void InitializeAIService();
    void HandleAIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
    
    // Event Bindings
    void BindEditorCallbacks();
    void UnbindEditorCallbacks();
    
    // Context Management
    TMap<FString, FString> ProjectContext;
    void UpdateContextFromFile(const FString& FilePath);
    
    // Command Handlers
    void HandleNexusCommand(const FString& CommandName);
    
    // Settings
    FString AIEndpoint;
    FString APIKey;
    bool bIsProcessingRequest;
};
