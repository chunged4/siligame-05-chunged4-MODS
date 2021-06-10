#include "game.h"

// constructors
Game::Game() : Game(800, 600) {}
Game::Game(int width, int height) : score_(0), lost_(false), startGame_(true), timer_(1) {
  gameScreen_.Initialize(width, height);
}

// getters/setters
graphics::Image &Game::GetGameScreen() { return gameScreen_; }
std::vector<std::unique_ptr<Opponent>> &Game::GetOpponents() {
  return enemies_;
}
std::vector<std::unique_ptr<OpponentProjectile>>
    &Game::GetOpponentProjectiles() {
  return balls_;
}
std::vector<std::unique_ptr<PlayerProjectile>> &Game::GetPlayerProjectiles() {
  return lBolts_;
}
Player &Game::GetPlayer() { return thePlayer_; }
int Game::GetScore() const { return score_; }
bool Game::HasLost() const { return lost_; }

// Member Functions
// *CreateOpponents() creates an opponent with a feature to randomly place
// the opponent object somewhere on the screen*
void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>();
  int xPos = rand() % ((gameScreen_.GetWidth()) - (opponent->GetWidth() + opponent->GetWidth())) + opponent->GetWidth() / 2;
  int yPos = rand() % ((gameScreen_.GetHeight() / 2) - (opponent->GetHeight()) + opponent->GetHeight() / 2);
  opponent->SetX(xPos);
  opponent->SetY(yPos);
  enemies_.push_back(std::move(opponent));
}
void Game::CreateHearts() {
  std::unique_ptr<Heart> heart = std::make_unique<Heart>();
  int xPos = rand() % ((gameScreen_.GetWidth()) - (heart->GetWidth() + (heart->GetWidth() / 2))) + heart->GetWidth() / 2;
  heart->SetX(xPos);
  heart->SetY(5);
  hearts_.push_back(std::move(heart));
}
// Init() starts up the game with a random position for the player, and adds
// a mouse and animation event listener to the graphics::Image object,
// gameScreen_
void Game::Init() {
  int xPos = gameScreen_.GetWidth() / 2;
  int yPos = gameScreen_.GetHeight() * .75;
  thePlayer_.SetX(xPos);
  thePlayer_.SetY(yPos);
  gameScreen_.AddMouseEventListener(*this);
  gameScreen_.AddAnimationEventListener(*this);
}
// UpdateScreen() will have checks for if (1.) if a player has lost, (2.) the
// score, (3.) redrawing the background on the screen, and drawing the rest of
// the game elements Actions as follows: (1.) displys "GAME OVER" on screen once
// lost (2.) updates score after an opponent is hit (3.) calls the Draw() of
// each game element that is active Feature to call DrawBackwords() for the
// oppoenent and player depending on the toggle that determines which way they
// are facing
void Game::UpdateScreen() {
  if (startGame_) {
    gameScreen_.Load("background.bmp");
    std::string startMsg("SILIG  ME");
    gameScreen_.DrawText(gameScreen_.GetWidth() / 3, gameScreen_.GetHeight() / 6, startMsg, 75, black);
    thePlayer_.SetLives(2);
    thePlayer_.SetX(gameScreen_.GetWidth() / 2 + 8);
    thePlayer_.SetY(gameScreen_.GetHeight() / 6 + 10);
    if (thePlayer_.GetToggle() == 1) {
      thePlayer_.DrawBackwords(gameScreen_);
      if (timer_ % 15 == 0) {
        thePlayer_.SetToggle(2);
      }
    } else {
      thePlayer_.Draw(gameScreen_);
      if (timer_ % 15 == 0) {
        thePlayer_.SetToggle(1);
      }
    }
    gameScreen_.DrawRectangle(170, gameScreen_.GetHeight() * 0.5, 200 , 90, lightGreen);
    gameScreen_.DrawText(200, gameScreen_.GetHeight() * 0.5 + 10, "PLAY", 70, black);
    gameScreen_.DrawRectangle(470, gameScreen_.GetHeight() * 0.5, 200 , 90, red);
    gameScreen_.DrawText(510, gameScreen_.GetHeight() * 0.5 + 10, "QUIT", 70, black);
  } else {
    gameScreen_.Load("background.bmp");
    std::string scoreMsg("Score: " + std::to_string(score_));
    gameScreen_.DrawText(0, 0, scoreMsg, 30, black);
    for (int i = 0; i < displayHearts_.size(); i++) {
      displayHearts_[i].Draw(gameScreen_);
    }
    for (int i = 0; i < enemies_.size(); i++) {
      if (enemies_[i]->GetIsActive() && enemies_[i]->GetToggle() == 1) {
        enemies_[i]->Draw(gameScreen_);
      } else if (enemies_[i]->GetIsActive() && enemies_[i]->GetToggle() == 2) {
        enemies_[i]->DrawBackwords(gameScreen_);
      }
    }
    for (int i = 0; i < balls_.size(); i++) {
      if (balls_[i]->GetIsActive()) {
        balls_[i]->Draw(gameScreen_);
      }
    }
    for (int i = 0; i < lBolts_.size(); i++) {
      if (lBolts_[i]->GetIsActive()) {
        lBolts_[i]->Draw(gameScreen_);
      }
    }
    for (int i = 0; i < hearts_.size(); i++) {
      if (hearts_[i]->GetIsActive()) {
        hearts_[i]->Draw(gameScreen_);
      }
    }
    if (thePlayer_.GetIsActive() && thePlayer_.GetToggle() == 1) {
      thePlayer_.Draw(gameScreen_);
    } else if (thePlayer_.GetIsActive() && thePlayer_.GetToggle() == 2) {
      thePlayer_.DrawBackwords(gameScreen_);
    }
  }
  if (highScoreScreen && HasLost()) {
    gameScreen_.DrawRectangle(0, 0, gameScreen_.GetWidth(), gameScreen_.GetHeight(), black);
    std::string endGameMsg("GAME OVER\nSCORE: " +
                           std::to_string(score_));
    gameScreen_.DrawText(gameScreen_.GetWidth() / 3,
                         gameScreen_.GetHeight() / 5, endGameMsg, 70, red);
    // animation until user inputs the name
  } else if (HasLost()) {
    gameScreen_.Load("background.bmp");
    gameScreen_.DrawRectangle(250, gameScreen_.GetHeight() * 0.5 + 30, 200 , 110, lightGreen);
    gameScreen_.DrawText(300, gameScreen_.GetHeight() * 0.5 + 40, "PLAY", 50, black);
    gameScreen_.DrawText(285, gameScreen_.GetHeight() * 0.5 + 85, "AGAIN", 50, black);
    gameScreen_.DrawRectangle(540, gameScreen_.GetHeight() * 0.5 + 30, 200 , 100, red);
    gameScreen_.DrawText(585, gameScreen_.GetHeight() * 0.5 + 50, "QUIT", 60, black);
    gameScreen_.DrawText(100, 100, "HIGH SCORES: ", 60, black);
    std::string name_out;
    int score_out;
    if (allScores.size() < 3) {
      for (int i = 0; i < allScores.size(); i++) {
        
      }
    } else {
      for (int i = 0; i < 3; i++) {

      }
    }
  }
}
// Start() shows the screen displayed and exits the program when closed
void Game::Start() { gameScreen_.ShowUntilClosed(); }
// MoveGameElements() calls the move function of each game element object
void Game::MoveGameElements() {
  for (int i = 0; i < enemies_.size(); i++) {
    if (enemies_[i]->GetIsActive()) {
      enemies_[i]->Move(gameScreen_);
    }
  }
  for (int i = 0; i < balls_.size(); i++) {
    if (balls_[i]->GetIsActive()) {
      balls_[i]->Move(gameScreen_);
    }
  }
  for (int i = 0; i < lBolts_.size(); i++) {
    if (lBolts_[i]->GetIsActive()) {
      lBolts_[i]->Move(gameScreen_);
    }
  }
  for (int i = 0; i < hearts_.size(); i++) {
    if (hearts_[i]->GetIsActive()) {
      hearts_[i]->Move(gameScreen_);
    }
  }
}
// FilterIntersections() checks for intersects and handles setting those
// specific game elements false when hit
void Game::FilterIntersections() {
  // player vs opponent intersections
  for (int i = 0; i < enemies_.size(); i++) {
    if (enemies_[i]->GetIsActive() && thePlayer_.GetIsActive() &&
        enemies_[i]->IntersectsWith(&thePlayer_)) {
      enemies_[i]->SetIsActive(false);
      thePlayer_.SetLives(thePlayer_.GetLives() - 1);
      displayHearts_[thePlayer_.GetLives()].SetToggleDraw(2);
    } else {
      // playerprojectile vs opponent intersections
      for (int j = 0; j < lBolts_.size(); j++) {
        if (enemies_[i]->GetIsActive() && lBolts_[j]->GetIsActive() &&
            lBolts_[j]->IntersectsWith(enemies_[i].get())) {
          lBolts_[j]->SetIsActive(false);
          enemies_[i]->SetIsActive(false);
          if (thePlayer_.GetIsActive()) {
            score_++;
          }
        }
      }
    }
  }
  // player vs opponentprojectile intersections
  for (int i = 0; i < balls_.size(); i++) {
    if (balls_[i]->GetIsActive() && thePlayer_.GetIsActive() &&
        balls_[i]->IntersectsWith(&thePlayer_)) {
      balls_[i]->SetIsActive(false);
      thePlayer_.SetLives(thePlayer_.GetLives() - 1);
      displayHearts_[thePlayer_.GetLives()].SetToggleDraw(2);
    }
  }
  for (int i = 0; i < hearts_.size(); i++) {
    if (hearts_[i]->GetIsActive() && thePlayer_.GetIsActive() &&
        hearts_[i]->IntersectsWith(&thePlayer_)) {
        hearts_[i]->SetIsActive(false);
        if (thePlayer_.GetLives() != 3) {
          displayHearts_[thePlayer_.GetLives()].SetToggleDraw(1);
          thePlayer_.SetLives(thePlayer_.GetLives() + 1);
        }
    }
  }
  if (thePlayer_.GetLives() == 0) {
    lost_ = true;
    highScoreScreen = true;
    thePlayer_.SetIsActive(false);
    EndGame();
  }
}
// RemoveInactive() goes through each game element and makes sure to remove them
// out of the vector in order to keep the game running and smooth
void Game::RemoveInactive() {
  for (int i = enemies_.size() - 1; i >= 0; i--) {
    if (!(enemies_[i]->GetIsActive())) {
      enemies_.erase(enemies_.end() - (enemies_.size() - i));
    }
  }
  for (int i = balls_.size() - 1; i >= 0; i--) {
    if (!(balls_[i]->GetIsActive())) {
      balls_.erase(balls_.end() - (balls_.size() - i));
    }
  }
  for (int i = lBolts_.size() - 1; i >= 0; i--) {
    if (!(lBolts_[i]->GetIsActive())) {
      lBolts_.erase(lBolts_.end() - (lBolts_.size() - i));
    }
  }
  for (int i = hearts_.size() - 1; i >= 0; i--) {
    if (!(hearts_[i]->GetIsActive())) {
      hearts_.erase(hearts_.end() - (hearts_.size() - i));
    }
  }
}
// LaunchProjectiles() goes through each Opponent object in the vector and calls
// the Opponent::LaunchProjectile() function and will add the non-nullptr
// projecties into the <OpponenentProjectile> vector
void Game::LaunchProjectiles() {
  for (int i = 0; i < enemies_.size(); i++) {
    if (enemies_[i]->GetIsActive()) {
      std::unique_ptr<OpponentProjectile> oProj =
          enemies_[i]->LaunchProjectile(thePlayer_.GetX(), thePlayer_.GetY());
      if (oProj != nullptr) {
        balls_.push_back(std::move(oProj));
      }
    }
  }
}
// OnAnimationStep() is a listener run every millisecond, making the animations
// run smoothly
void Game::OnAnimationStep() {
  timer_++;
  if (!(HasLost()) && !startGame_ && !highScoreScreen) {
    if (enemies_.size() == 0 || timer_ % 50 == 0) {
      CreateOpponents();
    }
    if (timer_ % 200 == 0) {
      CreateHearts();
    }
    MoveGameElements();
    LaunchProjectiles();
    FilterIntersections();
    RemoveInactive();
  }
  UpdateScreen();
  gameScreen_.Flush();
}
// OnMouseEvent() is a listener that takes in input from the mouse as an event
// and and the function uses the event to update the player's movement using the
// mouse coordinates and the player's actions using the mouse's key presses
void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (startGame_) {
    if (event.GetMouseAction() == graphics::MouseAction::kPressed
        && event.GetX() > 170 && event.GetX() < 370
        && event.GetY() > gameScreen_.GetHeight() * 0.5
        && event.GetY() < gameScreen_.GetHeight() * 0.5 + 110) {
      startGame_ = false;
      int xPos = gameScreen_.GetWidth() / 2;
      int yPos = gameScreen_.GetHeight() * .75;
      thePlayer_.SetX(xPos);
      thePlayer_.SetY(yPos);
      thePlayer_.SetLives(3);
      HandleHearts();
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed
        && event.GetX() > 470 && event.GetX() < 670
        && event.GetY() > gameScreen_.GetHeight() * 0.5
        && event.GetY() < gameScreen_.GetHeight() * 0.5 + 100) {
      gameScreen_.Hide();
    }
  } else if (!lost_) {
    if (event.GetX() > 0 || event.GetX() < gameScreen_.GetWidth() ||
      event.GetY() > 0 || event.GetY() < gameScreen_.GetHeight()) {
      if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
          event.GetMouseAction() == graphics::MouseAction::kDragged) {
        if (thePlayer_.GetLives() == 3) {
          if (event.GetX() - (thePlayer_.GetX() + thePlayer_.GetWidth() / 2) > 0) {
            thePlayer_.SetToggle(1);
          } else if (event.GetX() - (thePlayer_.GetX() + thePlayer_.GetWidth() / 2) < 0) {
            thePlayer_.SetToggle(2);
          }
        } else {
          if (event.GetX() - (thePlayer_.GetX() + thePlayer_.GetWidth() / 2) > 0) {
            thePlayer_.SetToggle(2);
          } else if (event.GetX() - (thePlayer_.GetX() + thePlayer_.GetWidth() / 2) < 0) {
            thePlayer_.SetToggle(1);
          }
        }
        thePlayer_.SetX(event.GetX() - (thePlayer_.GetWidth() / 2));
        thePlayer_.SetY(event.GetY() - (thePlayer_.GetHeight() / 2));
        if (thePlayer_.IsOutOfBounds(gameScreen_)) {
          if (thePlayer_.GetX() < 0) {
            thePlayer_.SetX(event.GetX());
          }
          if (thePlayer_.GetY() < 40) {
            thePlayer_.SetY(event.GetY());
          }
          if (thePlayer_.GetX() + thePlayer_.GetWidth() >
              gameScreen_.GetWidth()) {
            thePlayer_.SetX(event.GetX() - thePlayer_.GetWidth());
          }
          if (thePlayer_.GetY() + thePlayer_.GetHeight() >
              gameScreen_.GetHeight()) {
            thePlayer_.SetY(event.GetY() - thePlayer_.GetHeight());
          }
        }
      }
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
      if (thePlayer_.GetIsActive()) {
        std::unique_ptr<PlayerProjectile> bolt =
            std::make_unique<PlayerProjectile>();
        bolt->SetX(thePlayer_.GetWidth() / 2 + thePlayer_.GetX());
        bolt->SetY(thePlayer_.GetY());
        lBolts_.push_back(std::move(bolt));
      }
    }
  } else if (lost_ && !startGame_ && !highScoreScreen) {
    if (event.GetMouseAction() == graphics::MouseAction::kPressed
        && event.GetX() > 250 && event.GetX() < 450
        && event.GetY() > gameScreen_.GetHeight() * 0.5 + 30
        && event.GetY() < gameScreen_.GetHeight() * 0.5 + 110) {
      ResetGame();
      HandleHearts();
    }
    if (event.GetMouseAction() == graphics::MouseAction::kPressed
        && event.GetX() > 540 && event.GetX() < 740
        && event.GetY() > gameScreen_.GetHeight() * 0.5 + 30
        && event.GetY() < gameScreen_.GetHeight() * 0.5 + 100) {
      gameScreen_.Hide();
    }
  }
}
void Game::ResetGame() { 
  lost_ = false;
  score_ = 0;
  timer_ = 0;
  thePlayer_.SetCoolDown(0);
  int xPos = gameScreen_.GetWidth() / 2;
  int yPos = gameScreen_.GetHeight() * .75;
  thePlayer_.SetX(xPos);
  thePlayer_.SetY(yPos);
  thePlayer_.SetIsActive(!lost_);
  thePlayer_.Draw(gameScreen_);
  thePlayer_.SetLives(3);
  timer_ = 1;
}
void Game::EndGame() {
  thePlayer_.SetIsActive(false);
  for (int i = 0; i < enemies_.size(); i++) {
    enemies_[i]->SetIsActive(false);
  }
  for (int i = 0; i < balls_.size(); i++) {
    balls_[i]->SetIsActive(false);
  }
  for (int i = 0; i < lBolts_.size(); i ++) {
    lBolts_[i]->SetIsActive(false);
  }
  for (int i = 0; i < hearts_.size(); i++) {
    hearts_[i]->SetIsActive(false);
  }
  for (int i = 0; i < displayHearts_.size(); i++) {
    displayHearts_[i].SetIsActive(false);
  }
  HandleHearts();
  // HandleHighScores();
}
void Game::HandleHighScores() {
  std::ofstream highScoreFile("high_score.txt");
  std::string userName;
  std::cout << "Please enter your name: ";
  std::getline(std::cin, userName);
  if (highScoreFile.is_open()) { 
    highScoreFile << userName << std::endl;
    highScoreFile << score_ << std::endl;
    highScoreFile << std::endl;
    allScores.push_back(std::make_pair(userName, score_));
    std::sort(allScores.begin(), allScores.end());
    std::reverse(allScores.begin(), allScores.end());
  } else {
    std::cout << "Unable to open text" << std::endl;
  }
  highScoreScreen = false;
  highScoreFile.close();
}
void Game::HandleHearts() {
  Heart h1(gameScreen_.GetWidth() - 90, 5);
  Heart h2(gameScreen_.GetWidth() - 60, 5);
  Heart h3(gameScreen_.GetWidth() - 30, 5);
  displayHearts_.push_back(h1);
  displayHearts_.push_back(h2);
  displayHearts_.push_back(h3);
  for (int i = 0; i < displayHearts_.size(); i++) {
    displayHearts_[i].SetYSpeed(0);
  }
}