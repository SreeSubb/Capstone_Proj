#include "game.h"
#include <iostream>
#include <thread>
#include <future>
#include <memory>

#include "SDL.h"
#include "controller.h"


//getter/setter for class Threat
Threat::Threat() : loc_x(0), loc_y(0) {
  Threat::predatorType = NoPredator;
}

Threat::Threat(int x, int y, Predator type) : loc_x(x), loc_y(y) {
  Threat::predatorType = type;
}

Threat::~Threat() {};

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, 1),
      snake2(grid_width, grid_height, 2),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        snake.snakeLocation(random_w(engine), random_h(engine));   // setting the base snake at random location
        snake2.snakeLocation(random_w(engine), random_h(engine));  // setting the 2nd snake at random location
        PlaceFood();
        PlaceThreat();
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Initializing player objects of the controller class

  Controller snakePlayer1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
  Controller snakePlayer2(SDLK_w, SDLK_s, SDLK_a, SDLK_d); 

  while (running) {
    frame_start = SDL_GetTicks();

    //Starting threads with std::async to let the system decide to run the thread in sync or async
    //using deferred launch parameter to see the performance in async execution at first

    std::future<void> player1(std::async(std::launch::deferred, 
                            &Controller::HandleInput, snakePlayer1, std::ref(running), std::ref(snake)));
    std::future<void> player2(std::async(std::launch::deferred, 
                            &Controller::HandleInput, snakePlayer2, std::ref(running), std::ref(snake2)));

    // Input, Update, Render - the main game loop.// added 2nd snake
   
    Update();
    renderer.Render(snake, snake2, food, threat);
 

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(scorePlayer1, scorePlayer2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

//place threat
void Game::PlaceThreat() {
  int x, y;
  Predator type;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    type = Predator(rand() % 3);

    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && !Game::FoodCell(x, y)) {
      threat = std::make_unique<Threat> (x, y, type);              // create and place threat
      threat->loc_x = x;
      threat->loc_y = y;
      threat->predatorType = type;
      return;
      }
  }
}

void Game::Update() {
  if (!snake.alive || !snake2.alive) return;

  snake.Update();
  snake2.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  int new_x2 = static_cast<int>(snake2.head_x);
  int new_y2 = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    scorePlayer1++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    //encountered threat and getting weaker
  } else if (threat->loc_x == new_x && threat->loc_y == new_y)
  {
    scorePlayer1--;
    snake.speed -= 0.05;
    PlaceFood(); 
  }

// 2nsd snake
  if (food.x == new_x2 && food.y == new_y2) {
    scorePlayer2++;
    PlaceFood();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
    //encountered threat and getting weaker
  } else if (threat->loc_x == new_x2 && threat->loc_y == new_y2)
  {
    scorePlayer2--;
    snake2.speed -= 0.05;
    PlaceFood(); 
  }
}
//check for food
bool Game::FoodCell(int x, int y) {
  if (x == food.x && y == food.y) {
    return true;
  }
}

int Game::Player1GetScore() const { return scorePlayer1; }
int Game::Player2GetScore() const { return scorePlayer2; }
int Game::Player2GetSize() const { return snake.size; }
int Game::Player1GetSize() const { return snake2.size; }