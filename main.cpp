#include "screen.h"

const int GAME_WIDTH = 320;
const int GAME_HEIGHT = 240;

bool isAlive(std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> &game, const int x, const int y)
{
    int alive = 0;

    // test left border
    if (x > 0 && game[x - 1][y] == 1)
        alive += 1;
    // test right border
    if (x < GAME_WIDTH && game[x + 1][y] == 1)
        alive += 1;
    // test top border
    if (y > 0 && game[x][y - 1] == 1)
        alive += 1;
    // test bottom border
    if (y < GAME_HEIGHT && game[x][y + 1] == 1)
        alive += 1;
    // test top left
    if (x > 0 && y > 0 && game[x - 1][y - 1] == 1)
        alive += 1;
    // test top right
    if (x < GAME_WIDTH && y > 0 && game[x + 1][y - 1] == 1)
        alive += 1;
    // test bottom left
    if (x > 0 && y < GAME_HEIGHT && game[x - 1][y + 1] == 1)
        alive += 1;
    // test bottom right
    if (x < GAME_WIDTH && y < GAME_HEIGHT && game[x + 1][y + 1] == 1)
        alive += 1;

    // alive, < 2 neighbors
    if (game[x][y] == 1 && alive < 2)
        return false;
    // alive, 2 or 3 neighbors
    if (game[x][y] == 1 && (alive == 2 || alive == 3))
        return true;
    // alive, >3 neighbors
    if (alive > 3)
        return false;
    // dead, 3 neighbors
    if (game[x][y] == 0 && alive == 3)
        return true;

    return false;
}

int main()
{
    G screen;
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display{};
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap{};

    // create random points
    for (auto &row : display)
    {
        std::generate(row.begin(), row.end(), []()
                      { return rand() % 10 == 2 ? 1 : 0; });
    }

    while (true)
    {
        // check for alive cells
        for (int i = 0; i < GAME_WIDTH; i++)
        {
            for (int k = 0; k < GAME_HEIGHT; k++)
            {
                swap[i][k] = isAlive(display, i, k) ? 1 : 0;
            }
        }

        // draw
        for (int i = 0; i < GAME_WIDTH; i++)
        {
            for (int k = 0; k < GAME_HEIGHT; k++)
            {
                if (swap[i][k])
                {
                    screen.drawpixel(i, k);
                }
            }
        }

        // swap buffers
        std::copy(swap.begin(), swap.end(), display.begin());

        // Render
        screen.update();
        SDL_Delay(20);
        screen.input();
        screen.clearpixels();
    }
}