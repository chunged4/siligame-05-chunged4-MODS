#include "opponent.h"

// OpponentProjectile constructors
OpponentProjectile::OpponentProjectile() : OpponentProjectile(0, 0) {}
OpponentProjectile::OpponentProjectile(int x, int y)
    : GameElement(x, y, 12, 12) {}

// OpponentProjectile member functions
void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image opImage(GetWidth(), GetHeight());
  opImage.Load("pokeball.bmp");
  graphics::Color green(0, 255, 0);
  for (int i = 0; i < opImage.GetWidth(); i++) {
    for (int j = 0; j < opImage.GetHeight(); j++) {
      if (opImage.GetColor(i, j) != green) {
        image.SetColor(GetX() + i, GetY() + j, opImage.GetColor(i, j));
      }
    }
  }
}
void OpponentProjectile::Move(const graphics::Image &image) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}

// Opponent constructors
Opponent::Opponent() : Opponent(0, 0) {}
Opponent::Opponent(int x, int y)
    : GameElement(x, y, 50, 50), shootTimer_(0), xSpeed_(3), ySpeed_(3), moveTimer_(0) {
  int randomMove = rand() % 4 + 1;
  if (randomMove == 1) {
    XToggle_ = true;
  } else if (randomMove == 2) {
    XToggle_ = false;
  } else if (randomMove == 3) {
    YToggle_ = true;
  } else if (randomMove == 4) {
    YToggle_ = false;
  }
}

// getters/setters
int Opponent::GetToggle() const { return drawToggle_; }
void Opponent::SetToggle(int drawToggle) { drawToggle_ = drawToggle; }
bool Opponent::GetXToggle() const { return XToggle_; }
void Opponent::SetXToggle(bool xToggle) { XToggle_ = xToggle; }
bool Opponent::GetYToggle() const { return YToggle_; }
void Opponent::SetYToggle(bool yToggle) { YToggle_ = yToggle; }
int Opponent::GetMoveTimer() const { return moveTimer_; }
void Opponent::SetMoveTimer(int moveTimer) { moveTimer_ = moveTimer; }

// Opponent member functions
void Opponent::Draw(graphics::Image &image) {
  graphics::Image oImage(GetWidth(), GetHeight());
  oImage.Load("ash-ketchup.bmp");
  graphics::Color green(0, 255, 0);
  for (int i = 0; i < oImage.GetWidth(); i++) {
    for (int j = 0; j < oImage.GetHeight(); j++) {
      if (oImage.GetColor(i, j) != green) {
        image.SetColor(GetX() + i, GetY() + j, oImage.GetColor(i, j));
      }
    }
  }
}
void Opponent::DrawBackwords(graphics::Image &image) {
  graphics::Image pImage(GetWidth(), GetHeight());
  pImage.Load("ash-ketchup.bmp");
  graphics::Color green(0, 255, 0);
  for (int i = pImage.GetWidth() - 1; i >= 0; i--) {
    for (int j = pImage.GetHeight() - 1; j >= 0; j--) {
      if (pImage.GetColor(i, j) != green) {
        image.SetColor(GetX() + (GetWidth() - i), GetY() + j,
                       pImage.GetColor(i, j));
      }
    }
  }
}
void Opponent::Move(const graphics::Image &image) {
  if (GetWidth() + GetX() >= image.GetWidth() - GetWidth() / 2) {
    SetXToggle(true);
  } else if (GetX() <= GetWidth() / 2) {
    SetXToggle(false);
  }
  if (GetHeight() + GetY() >= image.GetHeight() / 2 - GetHeight() / 2) {
    SetYToggle(true);
  } else if (GetY() <= GetHeight() / 2) {
    SetYToggle(false);
  }
  if (GetXToggle()) {
    SetX(GetX() - xSpeed_);
    SetToggle(1);
  } else {
    SetX(GetX() + xSpeed_);
    SetToggle(2);
  }
  if (GetYToggle()) {
    SetY(GetY() - ySpeed_);
  } else {
    SetY(GetY() + ySpeed_);
  }
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
void Opponent::eMove(const graphics::Image &image) {
  moveTimer_++;
  // SetToggle(1);
  double scale = 2 / (3 - cos(2 * moveTimer_));
  int x = scale * cos(moveTimer_);
  int y = scale * sin(2 * moveTimer_) / 2;
  SetX(GetX() + xSpeed_ + x);
  SetY(GetY() + ySpeed_ + y);
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  shootTimer_++;
  std::unique_ptr<OpponentProjectile> oProj_ptr =
      std::make_unique<OpponentProjectile>();
  oProj_ptr->SetX(GetWidth() / 2 + GetX());
  oProj_ptr->SetY(GetHeight() + GetY());
  if (shootTimer_ % 60 == 0) {
    shootTimer_ = 0;
    return std::move(oProj_ptr);
  } else {
    return nullptr;
  }
}
