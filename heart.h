#include "game_element.h"

#ifndef HEART_H
#define HEART_H

class Heart : public GameElement {
 public:
  // Constructors
  Heart();
  Heart(int x, int y);
  // getters/setters
  int GetToggleDraw() const;
  void SetToggleDraw(int toggleDraw);
  void SetYSpeed(int ySpeed);
  // Member functions
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;

 private:
  int toggleDraw_;
  int ySpeed_;
};

#endif