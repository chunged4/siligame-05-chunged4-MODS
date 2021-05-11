#include <time.h>

#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  //  Constructors
  OpponentProjectile();
  OpponentProjectile(int x, int y);
  //  Member Functions
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
};

class Opponent : public GameElement {
 public:
  //  Constructors
  Opponent();
  Opponent(int x, int y);
  // getters/setters
  bool GetXToggle() const;
  void SetXToggle(bool xToggle);
  bool GetYToggle() const;
  void SetYToggle(bool yToggle);
  int GetToggle() const;
  void SetToggle(int drawToggle);
  int GetMoveTimer() const;
  void SetMoveTimer(int moveTimer);

  //  Member Functions
  void Draw(graphics::Image &image) override;
  void DrawBackwords(graphics::Image &image);
  void Move(const graphics::Image &image) override;
  void eMove(const graphics::Image &image);
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  bool XToggle_;
  bool YToggle_;
  int shootTimer_;
  int drawToggle_;
  int drawChar_;
  int xSpeed_;
  int ySpeed_;
  int moveTimer_;
};

#endif
