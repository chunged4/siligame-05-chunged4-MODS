#include "game_element.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  //  Constructors
  Player();
  Player(int x, int y);
  // Getters/setters
  int GetToggle() const;
  void SetToggle(int drawToggle);
  int GetCoolDown() const;
  void SetCoolDown(int coolDown);
  int GetLives() const;
  void SetLives(int lives);
  //  Member Functions
  void Draw(graphics::Image &image) override;
  void DrawBackwords(graphics::Image &image);
  void Move(const graphics::Image &image) override;

 private:
  int drawToggle_;
  int coolDown_;
  int lives_;
};

class PlayerProjectile : public GameElement {
 public:
  //  Constructors
  PlayerProjectile();
  PlayerProjectile(int x, int y);
  // getters/setters
  int GetMoveSpeed() const;
  void SetMoveSpeed(int moveSpeed);
  //  Member Functions
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
  int moveSpeed_;
};

#endif