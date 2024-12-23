#include <raylib.h>
#include <string>

const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 864;

int highestScore = 0;

enum class GameState {
    FIRST_SCREEN,
    CHARACTER_SELECTION,
    LEVEL_SELECTION,
    PLAYING,
    GAME_OVER,
    VICTORY
};

GameState currentState = GameState::FIRST_SCREEN;
int selectedCharacter = 0;
int selectedLevel = 0;
float gameTimer = 0.0f;
int lastScore = 0;

Texture2D player1Texture;
Texture2D player2Texture;
Texture2D player3Texture;
Texture2D starWarsBackground;

Music backgroundMusic;

void DrawFirstScreen() {
    DrawTexture(starWarsBackground, 0, 0, WHITE);

    const char* titleText = "Star Wars Game";
    int titleFontSize = 70;
    int titleWidth = MeasureText(titleText, titleFontSize);
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;

    DrawText(titleText, titleX, 100, titleFontSize, GOLD);

    const char* subtitleText = "Your game subtitle here!";
    int subtitleFontSize = 30;
    int subtitleWidth = MeasureText(subtitleText, subtitleFontSize);
    int subtitleX = (SCREEN_WIDTH - subtitleWidth) / 2;

    DrawText(subtitleText, subtitleX, 200, subtitleFontSize, RAYWHITE);

    int buttonWidth = 200, buttonHeight = 60;
    int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
    Rectangle startButton = {(float)buttonX, 400, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(startButton, 0.2f, 10, DARKGREEN);
    DrawText("Start", buttonX + (buttonWidth - MeasureText("Start", 30)) / 2, 415, 30, WHITE);

    Rectangle exitButton = {(float)buttonX, 500, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(exitButton, 0.2f, 10, MAROON);
    DrawText("Exit", buttonX + (buttonWidth - MeasureText("Exit", 30)) / 2, 515, 30, WHITE);

    const char* highScoreText = TextFormat("Highest Score: %d", highestScore);
    int highScoreFontSize = 30;
    int highScoreWidth = MeasureText(highScoreText, highScoreFontSize);
    int highScoreX = (SCREEN_WIDTH - highScoreWidth) / 2;
    DrawText(highScoreText, highScoreX, 600, highScoreFontSize, GOLD);

    if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        currentState = GameState::CHARACTER_SELECTION;
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        CloseWindow();
    }
}

void DrawCharacterSelection() {
    DrawTexture(starWarsBackground, 0, 0, WHITE);

    const char* titleText = "Choose Your Character";
    int titleFontSize = 50;
    int titleWidth = MeasureText(titleText, titleFontSize);
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;

    DrawText(titleText, titleX, 100, titleFontSize, GOLD);

    int buttonWidth = 100, buttonHeight = 100;
    int imageSize = 40;
    int spacing = 50;
    int totalWidth = 3 * buttonWidth + 2 * spacing;
    int startX = (SCREEN_WIDTH - totalWidth) / 2;

    Rectangle player1Button = {(float)startX, 300, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(player1Button, 0.2f, 10, DARKPURPLE);
    DrawTextureEx(player1Texture, 
        {startX + (buttonWidth - imageSize) / 2.0f, 300 + (buttonHeight - imageSize) / 2.0f}, 
        0, (float)imageSize / player1Texture.width, WHITE);

    Rectangle player2Button = {(float)(startX + buttonWidth + spacing), 300, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(player2Button, 0.2f, 10, DARKBLUE);
    DrawTextureEx(player2Texture, 
        {startX + buttonWidth + spacing + (buttonWidth - imageSize) / 2.0f, 300 + (buttonHeight - imageSize) / 2.0f}, 
        0, (float)imageSize / player2Texture.width, WHITE);

    Rectangle player3Button = {(float)(startX + 2 * (buttonWidth + spacing)), 300, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(player3Button, 0.2f, 10, DARKGREEN);
    DrawTextureEx(player3Texture, 
        {startX + 2 * (buttonWidth + spacing) + (buttonWidth - imageSize) / 2.0f, 300 + (buttonHeight - imageSize) / 2.0f}, 
        0, (float)imageSize / player3Texture.width, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), player1Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedCharacter = 1;
        currentState = GameState::LEVEL_SELECTION;
    }
    if (CheckCollisionPointRec(GetMousePosition(), player2Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedCharacter = 2;
        currentState = GameState::LEVEL_SELECTION;
    }
    if (CheckCollisionPointRec(GetMousePosition(), player3Button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedCharacter = 3;
        currentState = GameState::LEVEL_SELECTION;
    }
}

void DrawLevelSelection() {
    DrawTexture(starWarsBackground, 0, 0, WHITE);

    const char* titleText = "Choose Difficulty";
    int titleFontSize = 50;
    int titleWidth = MeasureText(titleText, titleFontSize);
    int titleX = (SCREEN_WIDTH - titleWidth) / 2;

    DrawText(titleText, titleX, 100, titleFontSize, GOLD);

    int buttonWidth = 200, buttonHeight = 60;
    int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;

    Rectangle easyButton = {(float)buttonX, 300, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(easyButton, 0.2f, 10, DARKGREEN);
    DrawText("Easy", buttonX + (buttonWidth - MeasureText("Easy", 30)) /2, 315, 30, WHITE);

    Rectangle mediumButton = {(float)buttonX, 400, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(mediumButton, 0.2f, 10, ORANGE);
    DrawText("Medium", buttonX + (buttonWidth - MeasureText("Medium", 30)) / 2, 415, 30, WHITE);

    Rectangle hardButton = {(float)buttonX, 500, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(hardButton, 0.2f, 10, MAROON);
    DrawText("Hard", buttonX + (buttonWidth - MeasureText("Hard", 30)) / 2, 515, 30, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), easyButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedLevel = 1;
        currentState = GameState::PLAYING;
    }
    if (CheckCollisionPointRec(GetMousePosition(), mediumButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedLevel = 2;
        currentState = GameState::PLAYING;
    }
    if (CheckCollisionPointRec(GetMousePosition(), hardButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedLevel = 3;
        currentState = GameState::PLAYING;
    }

    if (currentState == GameState::PLAYING) {
        // Initialize game-specific elements here
        gameTimer = 0.0f;
    }
}

void DrawGameScreen() {
    DrawTexture(starWarsBackground, 0, 0, WHITE);

    // Draw game-specific elements here

    gameTimer += GetFrameTime();

    DrawRectangle(0, 0, SCREEN_WIDTH, 50, Fade(BLACK, 0.5f));
    DrawText(TextFormat("Time: %.2f", gameTimer), 10, 10, 30, WHITE);

    // Add game-specific logic here

    // Example victory condition (replace with your own)
    if (gameTimer > 60.0f) {
        currentState = GameState::VICTORY;
        lastScore = static_cast<int>(1000 / gameTimer);
        if (lastScore > highestScore) {
            highestScore = lastScore;
        }
    }
}

void DrawVictoryScreen() {
    DrawTexture(starWarsBackground, 0, 0, WHITE);

    const char* victoryText = "Congratulations! You Won!";
    int victoryFontSize = 60;
    int victoryWidth = MeasureText(victoryText, victoryFontSize);
    int victoryX = (SCREEN_WIDTH - victoryWidth) / 2;

    DrawText(victoryText, victoryX, 100, victoryFontSize, GOLD);

    const char* scoreText = TextFormat("Your Score: %d", lastScore);
    int scoreFontSize = 40;
    int scoreWidth = MeasureText(scoreText, scoreFontSize);
    int scoreX = (SCREEN_WIDTH - scoreWidth) / 2;

    DrawText(scoreText, scoreX, 200, scoreFontSize, WHITE);

    int buttonWidth = 250, buttonHeight = 60;
    int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;

    Rectangle playAgainButton = {(float)buttonX, 300, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(playAgainButton, 0.2f, 10, DARKGREEN);
    DrawText("Play Again", buttonX + (buttonWidth - MeasureText("Play Again", 30)) / 2, 315, 30, WHITE);

    Rectangle mainMenuButton = {(float)buttonX, 400, (float)buttonWidth, (float)buttonHeight};
    DrawRectangleRounded(mainMenuButton, 0.2f, 10, MAROON);
    DrawText("Main Menu", buttonX + (buttonWidth - MeasureText("Main Menu", 30)) / 2, 415, 30, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), playAgainButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        currentState = GameState::LEVEL_SELECTION;
    }
    if (CheckCollisionPointRec(GetMousePosition(), mainMenuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        currentState = GameState::FIRST_SCREEN;
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Star Wars Game Template");
    SetTargetFPS(60);

    player1Texture = LoadTexture("src/player1.png");
    player2Texture = LoadTexture("src/player2.png");
    player3Texture = LoadTexture("src/player3.png");
    starWarsBackground = LoadTexture("src/star_wars.png");

    InitAudioDevice();
    backgroundMusic = LoadMusicStream("src/music.mp3");
    PlayMusicStream(backgroundMusic);

    while (!WindowShouldClose()) {
        UpdateMusicStream(backgroundMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            case GameState::FIRST_SCREEN:
                DrawFirstScreen();
                break;
            case GameState::CHARACTER_SELECTION:
                DrawCharacterSelection();
                break;
            case GameState::LEVEL_SELECTION:
                DrawLevelSelection();
                break;
            case GameState::PLAYING:
                DrawGameScreen();
                break;
            case GameState::VICTORY:
                DrawVictoryScreen();
                break;
        }

        EndDrawing();
    }

    UnloadTexture(player1Texture);
    UnloadTexture(player2Texture);
    UnloadTexture(player3Texture);
    UnloadTexture(starWarsBackground);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}