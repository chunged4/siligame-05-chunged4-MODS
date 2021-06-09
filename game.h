#include <vector>
#include <fstream>
#include <algorithm>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"
#include "heart.h"

const graphics::Color lightBlue(173, 216, 230);
const graphics::Color black(0, 0, 0);
const graphics::Color lightGreen(20, 224, 20);
const graphics::Color red(255, 0, 0);
const graphics::Color blue(0, 0, 255);

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  //  Constructors
  Game();
  Game(int width, int height);

  //  Getters/Setters
  graphics::Image &GetGameScreen();
  std::vector<std::unique_ptr<Opponent>> &GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles();
  Player &GetPlayer();
  int GetScore() const;
  bool HasLost() const;

  //  Member Functions
  void CreateOpponents();
  void CreateHearts();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &event) override;
  void RemoveInactive();
  void LaunchProjectiles();
  void ResetGame();
  void EndGame();
  void HandleHighScores();
  void displayHighScores();
  void HandleHearts();

 private:
  graphics::Image gameScreen_;
  std::vector<std::unique_ptr<Opponent>> enemies_;
  std::vector<std::unique_ptr<OpponentProjectile>> balls_;
  std::vector<std::unique_ptr<PlayerProjectile>> lBolts_;
  std::vector<std::unique_ptr<Opponent>> eEnemies_;
  std::vector<std::unique_ptr<Heart>> hearts_;
  Player thePlayer_;
  int score_;
  bool lost_;
  bool startGame_;
  int timer_;
  bool highScoreScreen;
  std::vector<Heart> displayHearts_;
  std::vector<std::pair<std::string, int>> allScores;
};

#endif