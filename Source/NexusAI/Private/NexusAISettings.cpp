#include "NexusAISettings.h"
#include "HAL/PlatformProcess.h"

UNexusAISettings::UNexusAISettings()
{
    // Set Gemini as default
    ActiveModel = EAIModelType::GeminiPro;
    
    // Default configuration
    Temperature = 0.7f;
    MaxTokens = 2048;
    
    // Load API keys from environment variables
    FString EnvGeminiKey = FPlatformProcess::GetEnvironmentVariable(TEXT("NEXUS_GEMINI_API_KEY"));
    FString EnvOpenAIKey = FPlatformProcess::GetEnvironmentVariable(TEXT("NEXUS_OPENAI_API_KEY"));
    
    GeminiApiKey = EnvGeminiKey;
    OpenAIApiKey = EnvOpenAIKey;
}

FText UNexusAISettings::GetSectionText() const
{
    return FText::FromString(TEXT("Nexus AI"));
}
