#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "NexusAISettings.h"

class SNexusAIEditorPanel : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SNexusAIEditorPanel) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedRef<SWidget> CreateModelSelectionUI();
    TSharedRef<SWidget> CreatePromptUI();
    void OnModelChanged(EAIModelType NewModel);
    void OnPromptSubmitted(const FText& NewText, ETextCommit::Type CommitType);
    void UpdateApiKeyStatus();

    TSharedPtr<class SComboBox<TSharedPtr<EAIModelType>>> ModelComboBox;
    TArray<TSharedPtr<EAIModelType>> ModelOptions;
};
