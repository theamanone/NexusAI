# Nexus AI - Unreal Engine AI Integration Plugin

Nexus AI is an advanced AI integration plugin for Unreal Engine that brings the power of modern AI models (Google Gemini and OpenAI) directly into your game development workflow.

## Features

- 🤖 AI-Powered Development Assistant
- 🎮 Blueprint Generation from Natural Language
- 📝 Code Suggestions and Automation
- 🔄 Real-time Project Analysis
- 🛠 Marketplace Integration
- 🎨 Custom Editor UI

## Installation

1. Clone this repository into your Unreal Engine's Plugin directory:
   ```bash
   git clone https://github.com/yourusername/NexusAI.git [UE_PATH]/Engine/Plugins/Marketplace/NexusAI
   ```

2. Create a configuration file at `Config/DefaultNexusAISettings.ini` with your API credentials:
   ```ini
   [/Script/NexusAI.NexusAISettings]
   ActiveModel=GeminiPro
   Temperature=0.7
   MaxTokens=2048
   ```

3. Rebuild your project

## Configuration

1. Open Unreal Editor
2. Go to Edit > Editor Preferences
3. Search for "Nexus AI"
4. Configure your API settings:
   - Select your preferred AI model
   - Enter your API credentials
   - Adjust generation parameters

## Security Note

⚠️ Never commit your API keys to the repository. Use environment variables or the Editor UI to configure your API keys.

## Requirements

- Unreal Engine 5.1 or later
- Valid API key for either:
  - Google Gemini Pro (default)
  - OpenAI (optional)

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Epic Games for Unreal Engine
- Google for Gemini API
- OpenAI for their API
