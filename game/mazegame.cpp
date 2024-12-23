#include <raylib.h>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <random>

const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 865;

int highestScore = 0;

// Forward declarations
class Maze;
class Player;
class Enemy;
class Weapon;
class Level;

// Cell class
class Cell {
private:
    int x, y;
    bool walls[4];

public:
    Cell(int x = 0, int y = 0) : x(x), y(y) {
        for (int i = 0; i < 4; i++) {
            walls[i] = true;
        }
    }

    void Draw(int cellSize, Color wallColor, int offsetX, int offsetY) {
        int screenX = x * cellSize + offsetX;
        int screenY = y * cellSize + offsetY;

        if (walls[0]) DrawLine(screenX, screenY, screenX + cellSize, screenY, wallColor);
        if (walls[1]) DrawLine(screenX + cellSize, screenY, screenX + cellSize, screenY + cellSize, wallColor);
        if (walls[2]) DrawLine(screenX, screenY + cellSize, screenX + cellSize, screenY + cellSize, wallColor);
        if (walls[3]) DrawLine(screenX, screenY, screenX, screenY + cellSize, wallColor);
    }

    void RemoveWall(int direction) {
        walls[direction] = false;
    }

    bool HasWall(int direction) const {
        return walls[direction];
    }
};

// Maze class
class Maze {
private:
    std::vector<std::vector<Cell>> grid;
    int width, height;
    int cellSize;
    std::vector<Vector2> solution;
    Texture2D startTexture;
    Texture2D endTexture;

    void GenerateMaze() {
        std::stack<std::pair<int, int>> stack;
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

        stack.push({0, 0});
        visited[0][0] = true;

        while (!stack.empty()) {
            int x = stack.top().first;
            int y = stack.top().second;

            std::vector<int> directions = {0, 1, 2, 3};
            std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

            bool moved = false;

            for (int direction : directions) {
                int newX = x + (direction == 1 ? 1 : (direction == 3 ? -1 : 0));
                int newY = y + (direction == 2 ? 1 : (direction == 0 ? -1 : 0));

                if (newX >= 0 && newX < width && newY >= 0 && newY < height && !visited[newY][newX]) {
                    grid[y][x].RemoveWall(direction);
                    grid[newY][newX].RemoveWall((direction + 2) % 4);

                    visited[newY][newX] = true;
                    stack.push({newX, newY});
                    moved = true;
                    break;
                }
            }

            if (!moved) {
                stack.pop();
            }
        }

        // Randomly remove two walls
        for (int i = 0; i < 2; ++i) {
            int x = rand() % width;
            int y = rand() % height;
            int direction = rand() % 4;
            grid[y][x].RemoveWall(direction);
            int newX = x + (direction == 1 ? 1 : (direction == 3 ? -1 : 0));
            int newY = y + (direction == 2 ? 1 : (direction == 0 ? -1 : 0));
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                grid[newY][newX].RemoveWall((direction + 2) % 4);
            }
        }
    }

    void FindSolution() {
        std::queue<Vector2> queue;
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
        std::vector<std::vector<Vector2>> parent(height, std::vector<Vector2>(width, {-1, -1}));

        queue.push({0, 0});
        visited[0][0] = true;

        while (!queue.empty()) {
            Vector2 current = queue.front();
            queue.pop();

            if (current.x == width - 1 && current.y == height - 1) {
                // Found the exit, reconstruct the path
                Vector2 pos = current;
                while (pos.x != -1 && pos.y != -1) {
                    solution.push_back(pos);
                    pos = parent[pos.y][pos.x];
                }
                std::reverse(solution.begin(), solution.end());
                return;
            }

            for (int direction = 0; direction < 4; direction++) {
                if (!grid[current.y][current.x].HasWall(direction)) {
                    int newX = current.x + (direction == 1 ? 1 : (direction == 3 ? -1 : 0));
                    int newY = current.y + (direction == 2 ? 1 : (direction == 0 ? -1 : 0));

                    if (!visited[newY][newX]) {
                        visited[newY][newX] = true;
                        parent[newY][newX] = current;
                        queue.push({(float)newX, (float)newY});
                    }
                }
            }
        }
    }

public:
    Maze(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize) {
        grid.resize(height, std::vector<Cell>(width));
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x] = Cell(x, y);
            }
        }
        GenerateMaze();
        FindSolution();
        startTexture = LoadTexture("src/start.png");
        endTexture = LoadTexture("src/end.png");
    }

    ~Maze() {
        UnloadTexture(startTexture);
        UnloadTexture(endTexture);
    }

    void Draw(Color wallColor, int offsetX, int offsetY) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x].Draw(cellSize, wallColor, offsetX, offsetY);
            }
        }

        // Draw start icon
        DrawTextureEx(startTexture, {(float)offsetX, (float)offsetY}, 0, (float)cellSize / startTexture.width, WHITE);

        // Draw end icon
        DrawTextureEx(endTexture, 
            {(float)(offsetX + (width - 1) * cellSize), (float)(offsetY + (height - 1) * cellSize)}, 
            0, (float)cellSize / endTexture.width, WHITE);
    }

    void DrawSolution(int offsetX, int offsetY) {
        for (size_t i = 0; i < solution.size() - 1; i++) {
            Vector2 start = solution[i];
            Vector2 end = solution[i + 1];
            DrawLine(
                start.x * cellSize + cellSize / 2 + offsetX,
                start.y * cellSize + cellSize / 2 + offsetY,
                end.x * cellSize + cellSize / 2 + offsetX,
                end.y * cellSize + cellSize / 2 + offsetY,
                RED
            );
        }
    }

    bool CanMove(int x, int y, int direction) const {
        return !grid[y][x].HasWall(direction);
    }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetCellSize() const { return cellSize; }
};

// Player class
class Player {
private:
    int x, y;
    int power;
    Texture2D texture;

public:
    Player(int startX, int startY, Texture2D playerTexture) 
        : x(startX), y(startY), power(0), texture(playerTexture) {}

    void Draw(int cellSize, int offsetX, int offsetY) {
        float scale = (float)cellSize / std::max(texture.width, texture.height);
        DrawTextureEx(texture, {(float)(x * cellSize + offsetX), (float)(y * cellSize + offsetY)}, 0, scale, WHITE);
    }

    void Move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetPower() const { return power; }

    void IncreasePower(int amount) {
        power += amount;
    }

    void DecreasePower(int amount) {
        power -= amount;
        if (power < 0) power = 0;
    }
};

// Enemy class
class Enemy {
private:
    int x, y;
    int health;

public:
    Enemy(int startX, int startY) : x(startX), y(startY), health(10) {}

    void Draw(int cellSize, int offsetX, int offsetY) const {
        DrawRectangle(x * cellSize + offsetX, y * cellSize + offsetY, cellSize, cellSize, RED);
    }

    void Move(const Maze& maze) {
        int direction = rand() % 4;
        int newX = x + (direction == 1 ? 1 : (direction == 3 ? -1 : 0));
        int newY = y + (direction == 2 ? 1 : (direction == 0 ? -1 : 0));

        if (maze.CanMove(x, y, direction)) {
            x = newX;
            y = newY;
        }
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetHealth() const { return health; }
    void SetHealth(int newHealth) { health = newHealth; }
};

// Weapon class
class Weapon {
private:
    int x, y;

public:
    Weapon(int startX, int startY) : x(startX), y(startY) {}

    void Draw(int cellSize, int offsetX, int offsetY) const {
        DrawCircle(x * cellSize + cellSize / 2 + offsetX, y * cellSize + cellSize / 2 + offsetY, cellSize / 4, GREEN);
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
};

// Level class
class Level {
private:
    int difficulty;
    int mazeSize;

public:
    Level(int difficulty) : difficulty(difficulty) {
        switch (difficulty) {
            case 1: mazeSize = 10; break;
            case 2: mazeSize = 15; break;
            case 3: mazeSize = 20; break;
            default: mazeSize = 10; break;
        }
    }

    int GetMazeSize() const { return mazeSize; }
};

// Game class
enum class GameState {
    FIRST_SCREEN,
    CHARACTER_SELECTION,
    LEVEL_SELECTION,
    PLAYING,
    GAME_OVER,
    VICTORY
};

class Game {
private:
    GameState state;
    Maze* maze;
    Player* player;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    Level* level;
    float timer;
    int score;
    bool showSolution;
    
    Texture2D player1Texture;
    Texture2D player2Texture;
    Texture2D player3Texture;
    Texture2D starWarsBackground;
    Music spaceMusic;

    int selectedCharacter;
    int selectedLevel;

public:
    Game() : state(GameState::FIRST_SCREEN), maze(nullptr), player(nullptr), level(nullptr),
             timer(0), score(0), showSolution(false), selectedCharacter(0), selectedLevel(0) {
        InitAudioDevice();
        LoadResources();
        PlayMusicStream(spaceMusic);
    }

    ~Game() {
        UnloadResources();
        CloseAudioDevice();
    }

    void Run() {
        while (!WindowShouldClose()) {
            Update();
            Draw();
        }
    }

private:
    void LoadResources() {
        player1Texture = LoadTexture("src/player1.png");
        player2Texture = LoadTexture("src/player2.png");
        player3Texture = LoadTexture("src/player3.png");
        starWarsBackground = LoadTexture("src/star_wars.png");
        spaceMusic = LoadMusicStream("src/music.mp3");
    }

    void UnloadResources() {
        UnloadTexture(player1Texture);
        UnloadTexture(player2Texture);
        UnloadTexture(player3Texture);
        UnloadTexture(starWarsBackground);
        UnloadMusicStream(spaceMusic);
    }

    void Update() {
        UpdateMusicStream(spaceMusic);

        switch (state) {
            case GameState::FIRST_SCREEN:
                UpdateFirstScreen();
                break;
            case GameState::CHARACTER_SELECTION:
                UpdateCharacterSelection();
                break;
            case GameState::LEVEL_SELECTION:
                UpdateLevelSelection();
                break;
            case GameState::PLAYING:
                UpdatePlaying();
                break;
            case GameState::GAME_OVER:
                UpdateGameOver();
                break;
            case GameState::VICTORY:
                UpdateVictory();
                break;
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(starWarsBackground, 0, 0, WHITE);

        switch (state) {
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
                DrawPlaying();
                break;
            case GameState::GAME_OVER:
                DrawGameOver();
                break;
            case GameState::VICTORY:
                DrawVictory();
                break;
        }

        EndDrawing();
    }

    void UpdateFirstScreen() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Rectangle startButton = {(float)(SCREEN_WIDTH - 200) / 2, 400, 200, 60};
            Rectangle exitButton = {(float)(SCREEN_WIDTH - 200) / 2, 500, 200, 60};

            if (CheckCollisionPointRec(mousePos, startButton)) {
                state = GameState::CHARACTER_SELECTION;
            } else if (CheckCollisionPointRec(mousePos, exitButton)) {
                CloseWindow();
            }
        }
    }

    void DrawFirstScreen() {
        const char* titleText = "Star Wars Maze";
        int titleFontSize = 70;
        int titleWidth = MeasureText(titleText, titleFontSize);
        int titleX = (SCREEN_WIDTH - titleWidth) / 2;

        DrawText(titleText, titleX, 100, titleFontSize, GOLD);

        const char* subtitleText = "Navigate through the maze to win!";
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
    }

    void UpdateCharacterSelection() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int buttonWidth = 100, buttonHeight = 100;
            int spacing = 50;
            int totalWidth = 3 * buttonWidth + 2 * spacing;
            int startX = (SCREEN_WIDTH - totalWidth) / 2;

            Rectangle player1Button = {(float)startX, 300, (float)buttonWidth, (float)buttonHeight};
            Rectangle player2Button = {(float)(startX + buttonWidth + spacing), 300, (float)buttonWidth, (float)buttonHeight};
            Rectangle player3Button = {(float)(startX + 2 * (buttonWidth + spacing)), 300, (float)buttonWidth, (float)buttonHeight};

            if (CheckCollisionPointRec(mousePos, player1Button)) {
                selectedCharacter = 1;
                state = GameState::LEVEL_SELECTION;
            } else if (CheckCollisionPointRec(mousePos, player2Button)) {
                selectedCharacter = 2;
                state = GameState::LEVEL_SELECTION;
            } else if (CheckCollisionPointRec(mousePos, player3Button)) {
                selectedCharacter = 3;
                state = GameState::LEVEL_SELECTION;
            }
        }
    }

    void DrawCharacterSelection() {
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
    }

    void UpdateLevelSelection() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int buttonWidth = 200, buttonHeight = 60;
            int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;

            Rectangle easyButton = {(float)buttonX, 300, (float)buttonWidth, (float)buttonHeight};
            Rectangle mediumButton = {(float)buttonX, 400, (float)buttonWidth, (float)buttonHeight};
            Rectangle hardButton = {(float)buttonX, 500, (float)buttonWidth, (float)buttonHeight};

            if (CheckCollisionPointRec(mousePos, easyButton)) {
                selectedLevel = 1;
                InitializeGame();
            } else if (CheckCollisionPointRec(mousePos, mediumButton)) {
                selectedLevel = 2;
                InitializeGame();
            } else if (CheckCollisionPointRec(mousePos, hardButton)) {
                selectedLevel = 3;
                InitializeGame();
            }
        }
    }

    void DrawLevelSelection() {
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
    }

    void UpdatePlaying() {
        timer += GetFrameTime();

        // Player movement
        if (IsKeyPressed(KEY_UP) && maze->CanMove(player->GetX(), player->GetY(), 0)) player->Move(0, -1);
        if (IsKeyPressed(KEY_RIGHT) && maze->CanMove(player->GetX(), player->GetY(), 1)) player->Move(1, 0);
        if (IsKeyPressed(KEY_DOWN) && maze->CanMove(player->GetX(), player->GetY(), 2)) player->Move(0, 1);
        if (IsKeyPressed(KEY_LEFT) && maze->CanMove(player->GetX(), player->GetY(), 3)) player->Move(-1, 0);

        // Toggle solution display
        if (IsKeyPressed(KEY_SPACE)) {
            showSolution = !showSolution;
        }

        // Update enemies
        for (auto& enemy : enemies) {
            enemy.Move(*maze);
        }

        // Check collisions
        CheckCollisions();

        // Check for victory
        if (player->GetX() == maze->GetWidth() - 1 && player->GetY() == maze->GetHeight() - 1) {
            state = GameState::VICTORY;
            int newScore = static_cast<int>(10000 / timer);
            if (newScore > highestScore) {
                highestScore = newScore;
            }
            score = newScore;
        }
    }

    void DrawPlaying() {
        int offsetX = (SCREEN_WIDTH - maze->GetWidth() * maze->GetCellSize()) / 2;
        int offsetY = (SCREEN_HEIGHT - maze->GetHeight() * maze->GetCellSize()) / 2;

        maze->Draw(LIGHTGRAY, offsetX, offsetY);
        if (showSolution) {
            maze->DrawSolution(offsetX, offsetY);
        }
        for (const auto& weapon : weapons) {
            weapon.Draw(maze->GetCellSize(), offsetX, offsetY);
        }
        for (const auto& enemy : enemies) {
            enemy.Draw(maze->GetCellSize(), offsetX, offsetY);
        }
        player->Draw(maze->GetCellSize(), offsetX, offsetY);

        DrawRectangle(0, 0, SCREEN_WIDTH, 50, Fade(BLACK, 0.5f));
        DrawText(TextFormat("Time: %.2f", timer), 10, 10, 30, WHITE);
        DrawText(TextFormat("Score: %d", score), 200, 10, 30, WHITE);
        DrawText(TextFormat("Power: %d", player->GetPower()), 400, 10, 30, WHITE);
    }

    void UpdateGameOver() {
        if (IsKeyPressed(KEY_SPACE)) {
            RestartLevel();
        }
    }

    void DrawGameOver() {
        DrawText("Game Over!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30, 40, RED);
        DrawText("Press SPACE to restart", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20, 30, WHITE);
    }

    void UpdateVictory() {
        if (IsKeyPressed(KEY_SPACE)) {
            state = GameState::FIRST_SCREEN;
        }
    }

    void DrawVictory() {
        DrawText("Victory!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 30, 40, GREEN);
        DrawText(TextFormat("Score: %d", score), SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 20, 30, WHITE);
        DrawText("Press SPACE to return to main menu", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 70, 30, WHITE);
    }

    void CheckCollisions() {
        int playerX = player->GetX();
        int playerY = player->GetY();

        // Check weapon collisions
        weapons.erase(std::remove_if(weapons.begin(), weapons.end(),
            [this, playerX, playerY](const Weapon& weapon) {
                if (weapon.GetX() == playerX && weapon.GetY() == playerY) {
                    player->IncreasePower(10);
                    return true;
                }
                return false;
            }), weapons.end());

        // Check enemy collisions
        for (auto& enemy : enemies) {
            if (enemy.GetX() == playerX && enemy.GetY() == playerY) {
                if (player->GetPower() > enemy.GetHealth()) {
                    player->DecreasePower(enemy.GetHealth());
                    score += 100;
                    enemy.SetHealth(0);
                } else {
                    state = GameState::GAME_OVER;
                    return;
                }
            }
        }

        // Remove defeated enemies
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& enemy) { return enemy.GetHealth() <= 0; }), enemies.end());
    }

    void RestartLevel() {
        delete player;
        player = new Player(0, 0, GetPlayerTexture());
        
        enemies.clear();
        weapons.clear();
        GenerateWeaponsAndEnemies();

        timer = 0.0f;
        score = 0;
        showSolution = false;
        state = GameState::PLAYING;
    }

    void InitializeGame() {
        delete maze;
        delete player;
        delete level;

        level = new Level(selectedLevel);
        int mazeSize = level->GetMazeSize();
        int cellSize = std::min((SCREEN_WIDTH - 100) / mazeSize, (SCREEN_HEIGHT - 100) / mazeSize);
        maze = new Maze(mazeSize, mazeSize, cellSize);
        
        player = new Player(0, 0, GetPlayerTexture());
        
        GenerateWeaponsAndEnemies();

        timer = 0.0f;
        score = 0;
        showSolution = false;
        state = GameState::PLAYING;
    }

    void GenerateWeaponsAndEnemies() {
        int numWeapons = level->GetMazeSize() / 2;
        int numEnemies = level->GetMazeSize() / 3;

        for (int i = 0; i < numWeapons; ++i) {
            int x, y;
            do {
                x = rand() % maze->GetWidth();
                y = rand() % maze->GetHeight();
            } while ((x == 0 && y == 0) || (x == maze->GetWidth() - 1 && y == maze->GetHeight() - 1));
            weapons.emplace_back(x, y);
        }

        for (int i = 0; i < numEnemies; ++i) {
            int x, y;
            do {
                x = rand() % maze->GetWidth();
                y = rand() % maze->GetHeight();
            } while ((x == 0 && y == 0) || (x == maze->GetWidth() - 1 && y == maze->GetHeight() - 1));
            enemies.emplace_back(x, y);
        }
    }

    Texture2D GetPlayerTexture() {
        switch (selectedCharacter) {
            case 1: return player1Texture;
            case 2: return player2Texture;
            case 3: return player3Texture;
            default: return player1Texture;
        }
    }
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Star Wars Maze");
    SetTargetFPS(20);

    Game game;
    game.Run();

    CloseWindow();
    return 0;
}

