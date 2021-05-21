#include "heart.h"

// Constructors
Heart::Heart() : Heart(0, 0) {}
Heart::Heart(int x, int y) : GameElement(x, y, 25, 25), toggleDraw_(1), ySpeed_(4) {}
// getters/setters
int Heart::GetToggleDraw() const { return toggleDraw_; }
void Heart::SetToggleDraw(int toggleDraw) { toggleDraw_ = toggleDraw; }
void Heart::SetYSpeed(int ySpeed) { ySpeed_ = ySpeed; }
// Member functions
void Heart::Draw(graphics::Image &image) {
  graphics::Image hImage(GetWidth(), GetHeight());
  if (toggleDraw_ == 1) {
    hImage.Load("life_heart.bmp");
  } else if (toggleDraw_ == 2) {
    hImage.Load("lost_heart.bmp");
  }
  graphics::Color green(0, 255, 0);
  for (int i = 0; i < hImage.GetWidth(); i++) {
    for (int j = 0; j < hImage.GetHeight(); j++) {
      if (hImage.GetColor(i, j) != green) {
        image.SetColor(GetX() + i, GetY() + j, hImage.GetColor(i, j));
      }
    }
  }
}
void Heart::Move(const graphics::Image &image) {
  SetY(GetY() + ySpeed_);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}