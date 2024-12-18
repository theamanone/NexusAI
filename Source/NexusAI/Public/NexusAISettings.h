#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DeveloperSettings.h"
#include "NexusAISettings.generated.h"

UENUM()
enum class EAIModelType : uint8
{
    GeminiPro UMETA(DisplayName = "Google Gemini Pro"),
    GPT35 UMETA(DisplayName = "OpenAI GPT-3.5"),
    GPT4 UMETA(DisplayName = "OpenAI GPT-4")
};

UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "Nexus AI Settings"))
class NEXUSAI_API UNexusAISettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UNexusAISettings();

    UPROPERTY(config, EditAnywhere, Category = "AI Model", meta = (DisplayName = "Active AI Model"))
    EAIModelType ActiveModel;

    UPROPERTY(config, EditAnywhere, Category = "AIzaSyAsC-TyAHpAqCpp-A8cA5Z7JBKnt5OPpfc", meta = (DisplayName = "Google Gemini API Key"))
    FString GeminiApiKey;

    UPROPERTY(config, EditAnywhere, Category = "API Keys", meta = (DisplayName = "OpenAI API Key"))
    FString OpenAIApiKey;

    UPROPERTY(config, EditAnywhere, Category = "API Configuration", meta = (DisplayName = "Temperature"))
    float Temperature;

    UPROPERTY(config, EditAnywhere, Category = "API Configuration", meta = (DisplayName = "Max Tokens"))
    int32 MaxTokens;

    virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
    virtual FText GetSectionText() const override;
};
