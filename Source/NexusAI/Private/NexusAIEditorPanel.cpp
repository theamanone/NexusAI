#include "NexusAIEditorPanel.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "EditorStyleSet.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SNexusAIEditorPanel::Construct(const FArguments& InArgs)
{
    // Initialize model options
    ModelOptions.Add(MakeShareable(new EAIModelType(EAIModelType::GeminiPro)));
    ModelOptions.Add(MakeShareable(new EAIModelType(EAIModelType::GPT35)));
    ModelOptions.Add(MakeShareable(new EAIModelType(EAIModelType::GPT4)));

    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(5)
        [
            CreateModelSelectionUI()
        ]
        + SVerticalBox::Slot()
        .FillHeight(1.0f)
        .Padding(5)
        [
            CreatePromptUI()
        ]
    ];

    UpdateApiKeyStatus();
}

TSharedRef<SWidget> SNexusAIEditorPanel::CreateModelSelectionUI()
{
    return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .AutoWidth()
        .Padding(0, 0, 5, 0)
        .VAlign(VAlign_Center)
        [
            SNew(STextBlock)
            .Text(FText::FromString(TEXT("AI Model:")))
        ]
        + SHorizontalBox::Slot()
        .AutoWidth()
        [
            SAssignNew(ModelComboBox, SComboBox<TSharedPtr<EAIModelType>>)
            .OptionsSource(&ModelOptions)
            .OnSelectionChanged(this, &SNexusAIEditorPanel::OnModelChanged)
            .OnGenerateWidget_Lambda([](TSharedPtr<EAIModelType> Item) {
                FString DisplayName;
                switch (*Item) {
                    case EAIModelType::GeminiPro:
                        DisplayName = TEXT("Google Gemini Pro");
                        break;
                    case EAIModelType::GPT35:
                        DisplayName = TEXT("OpenAI GPT-3.5");
                        break;
                    case EAIModelType::GPT4:
                        DisplayName = TEXT("OpenAI GPT-4");
                        break;
                }
                return SNew(STextBlock).Text(FText::FromString(DisplayName));
            })
            [
                SNew(STextBlock)
                .Text_Lambda([this]() {
                    if (ModelComboBox && ModelComboBox->GetSelectedItem().IsValid()) {
                        switch (*ModelComboBox->GetSelectedItem()) {
                            case EAIModelType::GeminiPro:
                                return FText::FromString(TEXT("Google Gemini Pro"));
                            case EAIModelType::GPT35:
                                return FText::FromString(TEXT("OpenAI GPT-3.5"));
                            case EAIModelType::GPT4:
                                return FText::FromString(TEXT("OpenAI GPT-4"));
                        }
                    }
                    return FText::FromString(TEXT("Select Model"));
                })
            ]
        ];
}

TSharedRef<SWidget> SNexusAIEditorPanel::CreatePromptUI()
{
    return SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .FillHeight(1.0f)
        [
            SNew(SMultiLineEditableTextBox)
            .OnTextCommitted(this, &SNexusAIEditorPanel::OnPromptSubmitted)
            .HintText(FText::FromString(TEXT("Enter your prompt here... (e.g., 'Create a new third-person character blueprint')")))
            .AutoWrapText(true)
        ];
}

void SNexusAIEditorPanel::OnModelChanged(TSharedPtr<EAIModelType> NewModel, ESelectInfo::Type SelectType)
{
    if (NewModel.IsValid())
    {
        auto* Settings = GetMutableDefault<UNexusAISettings>();
        Settings->ActiveModel = *NewModel;
        Settings->SaveConfig();
        UpdateApiKeyStatus();
    }
}

void SNexusAIEditorPanel::OnPromptSubmitted(const FText& NewText, ETextCommit::Type CommitType)
{
    if (CommitType == ETextCommit::OnEnter)
    {
        // Process the prompt based on selected model
        auto* Settings = GetMutableDefault<UNexusAISettings>();
        switch (Settings->ActiveModel)
        {
            case EAIModelType::GeminiPro:
                // Process with Gemini
                break;
            case EAIModelType::GPT35:
            case EAIModelType::GPT4:
                // Process with OpenAI
                break;
        }
    }
}

void SNexusAIEditorPanel::UpdateApiKeyStatus()
{
    auto* Settings = GetMutableDefault<UNexusAISettings>();
    bool bHasGeminiKey = !Settings->GeminiApiKey.IsEmpty();
    bool bHasOpenAIKey = !Settings->OpenAIApiKey.IsEmpty();

    if (!bHasGeminiKey && Settings->ActiveModel == EAIModelType::GeminiPro)
    {
        // Show warning for missing Gemini API key
    }
    else if (!bHasOpenAIKey && (Settings->ActiveModel == EAIModelType::GPT35 || Settings->ActiveModel == EAIModelType::GPT4))
    {
        // Show warning for missing OpenAI API key
    }
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
