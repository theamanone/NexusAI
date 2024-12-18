#include "NexusAITest.h"
#include "NexusAISettings.h"
#include "HttpModule.h"
#include "Json.h"

void FNexusAITest::TestGeminiIntegration()
{
    // Get settings
    auto* Settings = GetMutableDefault<UNexusAISettings>();
    if (!Settings || Settings->GeminiApiKey.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Gemini API key not configured!"));
        return;
    }

    // Create test request
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(TEXT("https://generativelanguage.googleapis.com/v1/models/gemini-pro:generateContent"));
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("x-goog-api-key"), Settings->GeminiApiKey);

    // Create test prompt
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> Contents;
    
    auto ContentObj = MakeShared<FJsonObject>();
    ContentObj->SetStringField(TEXT("role"), TEXT("user"));
    ContentObj->SetStringField(TEXT("parts"), TEXT("Create a simple Blueprint for a rotating cube"));
    
    Contents.Add(MakeShared<FJsonValueObject>(ContentObj));
    JsonObject->SetArrayField(TEXT("contents"), Contents);

    FString RequestString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    Request->SetContentAsString(RequestString);
    Request->OnProcessRequestComplete().BindRaw(this, &FNexusAITest::OnTestComplete);
    Request->ProcessRequest();
}

void FNexusAITest::OnTestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
    if (bSuccess && Response.IsValid())
    {
        UE_LOG(LogTemp, Log, TEXT("Gemini Test Response: %s"), *Response->GetContentAsString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Gemini Test Failed!"));
    }
}
