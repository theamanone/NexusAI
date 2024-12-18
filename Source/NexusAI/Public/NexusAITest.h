#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

class NEXUSAI_API FNexusAITest
{
public:
    void TestGeminiIntegration();

private:
    void OnTestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
};
