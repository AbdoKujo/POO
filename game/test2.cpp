#include <raylib.h>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

// Constants
const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 800;
const int CELL_SIZE = 35;
const int PLAYER_SIZE = 15;
const int ENEMY_SIZE = 15;
const int WEAPON_SIZE = 10;
const float ENEMY_MOVE_INTERVAL = 1.0f;

// Cell class
class Cell {
public:
    bool walls[4] = {true, true, true, true};  // top, right, bottom, left
    bool visited = false;
};

// Maze class
class Maze {
private:
    int width, height;
    std::vector<std::vector<Cell>> grid;

public:
    Maze(int w, int h) : width(w), height(h) {
        grid.resize(height, std::vector<Cell>(width));
    }

    void generate() {
        std::stack<std::pair<int, int>> stack;
        stack.push({0, 0});
        grid[0][0].visited = true;

        while (!stack.empty()) {
            auto [x, y] = stack.top();
            std::vector<int> neighbors;

            if (y > 0 && !grid[y-1][x].visited) neighbors.push_back(0);
            if (x < width-1 && !grid[y][x+1].visited) neighbors.push_back(1);
            if (y < height-1 && !grid[y+1][x].visited) neighbors.push_back(2);
            if (x > 0 && !grid[y][x-1].visited) neighbors.push_back(3);

            if (!neighbors.empty()) {
                int next = neighbors[rand() % neighbors.size()];
                int nx = x + (next == 1 ? 1 : (next == 3 ? -1 : 0));
                int ny = y + (next == 2 ? 1 : (next == 0 ? -1 : 0));

                grid[y][x].walls[next] = false;
                grid[ny][nx].walls[(next + 2) % 4] = false;
                grid[ny][nx].visited = true;
                stack.push({nx, ny});
            } else {
                stack.pop();
            }
        }

        // Randomly remove some walls
        for (int i = 0; i < width * height / 10; ++i) {
            int x = rand() % width;
            int y = rand() % height;
            int wall = rand() % 4;
            if (grid[y][x].walls[wall]) {
                grid[y][x].walls[wall] = false;
                int nx = x + (wall == 1 ? 1 : (wall == 3 ? -1 : 0));
                int ny = y + (wall == 2 ? 1 : (wall == 0 ? -1 : 0));
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    grid[ny][nx].walls[(wall + 2) % 4] = false;
                }
            }
        }
    }

    void draw() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int screenX = x * CELL_SIZE;
                int screenY = y * CELL_SIZE;
                if (grid[y][x].walls[0]) DrawLine(screenX, screenY, screenX + CELL_SIZE, screenY, BLACK);
                if (grid[y][x].walls[1]) DrawLine(screenX + CELL_SIZE, screenY, screenX + CELL_SIZE, screenY + CELL_SIZE, BLACK);
                if (grid[y][x].walls[2]) DrawLine(screenX, screenY + CELL_SIZE, screenX + CELL_SIZE, screenY + CELL_SIZE, BLACK);
                if (grid[y][x].walls[3]) DrawLine(screenX, screenY, screenX, screenY + CELL_SIZE, BLACK);
            }
        }
    }

    bool canMove(int x, int y, int direction) const {
        return !grid[y][x].walls[direction];
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// Player class
class Player {
private:
    int x, y;
    int power;
    int score;
    int weaponsCollected;

public:
    Player(int startX, int startY) : x(startX), y(startY), power(0), score(0), weaponsCollected(0) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void draw() const {
        DrawRectangle(x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
                      y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2, 
                      PLAYER_SIZE, PLAYER_SIZE, BLUE);
    }

    void collectWeapon() {
        power += 10;
        weaponsCollected++;
    }

    void hitEnemy() {
        power -= 10;
        if (power < 0) power = 0;
    }

    void addScore(int points) {
        score += points;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getPower() const { return power; }
    int getScore() const { return score; }
    int getWeaponsCollected() const { return weaponsCollected; }
};

// Enemy class
class Enemy {
private:
    int x, y;
    int health;
    float moveTimer;

public:
    Enemy(int startX, int startY) : x(startX), y(startY), health(10), moveTimer(0) {}

    void draw() const {
        DrawRectangle(x * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2, 
                      y * CELL_SIZE + (CELL_SIZE - ENEMY_SIZE) / 2, 
                      ENEMY_SIZE, ENEMY_SIZE, RED);
    }

    void move(const Maze& maze) {
        moveTimer += GetFrameTime();
        if (moveTimer >= ENEMY_MOVE_INTERVAL) {
            moveTimer = 0;
            std::vector<int> possibleMoves;
            if (maze.canMove(x, y, 0)) possibleMoves.push_back(0);
            if (maze.canMove(x, y, 1)) possibleMoves.push_back(1);
            if (maze.canMove(x, y, 2)) possibleMoves.push_back(2);
            if (maze.canMove(x, y, 3)) possibleMoves.push_back(3);

            if (!possibleMoves.empty()) {
                int move = possibleMoves[rand() % possibleMoves.size()];
                switch (move) {
                    case 0: y--; break;
                    case 1: x++; break;
                    case 2: y++; break;
                    case 3: x--; break;
                }
            }
        }
    }

    bool isAlive() const { return health > 0; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    void damage(int amount) { health -= amount; }
};

// Weapon class
class Weapon {
private:
    int x, y;

public:
    Weapon(int startX, int startY) : x(startX), y(startY) {}

    void draw() const {
        DrawCircle(x * CELL_SIZE + CELL_SIZE / 2, 
                   y * CELL_SIZE + CELL_SIZE / 2, 
                   WEAPON_SIZE / 2, GREEN);
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

// Game class
class Game {
private:
    Maze maze;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Weapon> weapons;
    int level;
    float timer;
    bool gameOver;
    std::vector<Vector2> solution;
    bool showSolution;

    void FindSolution() {
        std::queue<Vector2> queue;
        std::vector<std::vector<bool>> visited(maze.getHeight(), std::vector<bool>(maze.getWidth(), false));
        std::vector<std::vector<Vector2>> parent(maze.getHeight(), std::vector<Vector2>(maze.getWidth(), {-1, -1}));

        queue.push({0, 0});
        visited[0][0] = true;

        while (!queue.empty()) {
            Vector2 current = queue.front();
            queue.pop();

            if (current.x == maze.getWidth() - 1 && current.y == maze.getHeight() - 1) {
                // Found the exit, reconstruct the path
                Vector2 pos = current;
                while (pos.x != -1 && pos.y != -1) {
                    solution.push_back(pos);
                    pos = parent[(int)pos.y][(int)pos.x];
                }
                std::reverse(solution.begin(), solution.end());
                return;
            }

            for (int direction = 0; direction < 4; direction++) {
                if (maze.canMove(current.x, current.y, direction)) {
                    int newX = current.x + (direction == 1 ? 1 : (direction == 3 ? -1 : 0));
                    int newY = current.y + (direction == 2 ? 1 : (direction == 0 ? -1 : 0));

                    if (newX >= 0 && newX < maze.getWidth() && newY >= 0 && newY < maze.getHeight() && !visited[newY][newX]) {
                        visited[newY][newX] = true;
                        parent[newY][newX] = current;
                        queue.push({(float)newX, (float)newY});
                    }
                }
            }
        }
    }

    bool enemyAt(int x, int y) const {
        return std::any_of(enemies.begin(), enemies.end(), 
            [x, y](const Enemy& e) { return e.getX() == x && e.getY() == y; });
    }

    bool weaponAt(int x, int y) const {
        return std::any_of(weapons.begin(), weapons.end(), 
            [x, y](const Weapon& w) { return w.getX() == x && w.getY() == y; });
    }

public:
    Game() : maze(20, 15), player(0, 0), level(1), timer(0), gameOver(false), showSolution(false) {
        srand(time(nullptr));
        startNewLevel();
    }

    void startNewLevel() {
        maze = Maze(20 + level * 2, 15 + level * 2);
        maze.generate();
        player = Player(0, 0);
        enemies.clear();
        weapons.clear();
        solution.clear();
        showSolution = false;

        int numEnemies = 3 + level;
        int numWeapons = 5 + level;

        // Generate weapons first
        for (int i = 0; i < numWeapons; ++i) {
            int x, y;
            do {
                x = rand() % maze.getWidth();
                y = rand() % maze.getHeight();
            } while ((x == 0 && y == 0) || weaponAt(x, y));
            weapons.emplace_back(x, y);
        }

        // Generate enemies
        for (int i = 0; i < numEnemies; ++i) {
            int x, y;
            do {
                x = rand() % maze.getWidth();
                y = rand() % maze.getHeight();
            } while ((x == 0 && y == 0) || enemyAt(x, y) || weaponAt(x, y));
            enemies.emplace_back(x, y);
        }
    }

    void update() {
        if (gameOver) {
            if (IsKeyPressed(KEY_SPACE)) {
                gameOver = false;
                level = 1;
                startNewLevel();
            }
            return;
        }

        timer += GetFrameTime();

        if (IsKeyPressed(KEY_UP) && maze.canMove(player.getX(), player.getY(), 0)) player.move(0, -1);
        if (IsKeyPressed(KEY_RIGHT) && maze.canMove(player.getX(), player.getY(), 1)) player.move(1, 0);
        if (IsKeyPressed(KEY_DOWN) && maze.canMove(player.getX(), player.getY(), 2)) player.move(0, 1);
        if (IsKeyPressed(KEY_LEFT) && maze.canMove(player.getX(), player.getY(), 3)) player.move(-1, 0);

        if (IsKeyPressed(KEY_SPACE)) {
            toggleSolution();
        }

        // Check for weapon collection
        for (auto it = weapons.begin(); it != weapons.end(); ) {
            if (it->getX() == player.getX() && it->getY() == player.getY()) {
                player.collectWeapon();
                it = weapons.erase(it);
            } else {
                ++it;
            }
        }

        // Update and check enemies
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            it->move(maze);
            if (it->getX() == player.getX() && it->getY() == player.getY()) {
                if (player.getPower() > it->getHealth()) {
                    player.addScore(100);
                    it = enemies.erase(it);
                } else {
                    player.hitEnemy();
                    if (player.getPower() == 0) {
                        gameOver = true;
                        return;
                    }
                    ++it;
                }
            } else {
                ++it;
            }
        }

        // Check if level is complete
        if (player.getX() == maze.getWidth() - 1 && player.getY() == maze.getHeight() - 1) {
            level++;
            startNewLevel();
        }
    }

    void toggleSolution() {
        showSolution = !showSolution;
        if (showSolution && solution.empty()) {
            FindSolution();
        }
    }

    void draw() const {
        ClearBackground(RAYWHITE);

        if (gameOver) {
            DrawText("Game Over!", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 30, 20, BLACK);
            DrawText("Press SPACE to restart", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 10, 20, BLACK);
            return;
        }

        maze.draw();
        for (const auto& weapon : weapons) weapon.draw();
        for (const auto& enemy : enemies) enemy.draw();
        player.draw();

        if (showSolution) {
            for (size_t i = 1; i < solution.size(); ++i) {
                DrawLine(
                    solution[i-1].x * CELL_SIZE + CELL_SIZE / 2,
                    solution[i-1].y * CELL_SIZE + CELL_SIZE / 2,
                    solution[i].x * CELL_SIZE + CELL_SIZE / 2,
                    solution[i].y * CELL_SIZE + CELL_SIZE / 2,
                    RED
                );
            }
        }

        DrawText(("Level: " + std::to_string(level)).c_str(), 10, 10, 20, BLACK);
        DrawText(("Score: " + std::to_string(player.getScore())).c_str(), 10, 40, 20, BLACK);
        DrawText(("Power: " + std::to_string(player.getPower())).c_str(), 10, 70, 20, BLACK);
        DrawText(("Time: " + std::to_string(static_cast<int>(timer))).c_str(), 10, 100, 20, BLACK);
    }
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Game");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.update();

        BeginDrawing();
        game.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

