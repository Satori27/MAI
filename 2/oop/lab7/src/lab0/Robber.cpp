#include "Robber.h"
#include "Orc.h"
#include "Werewolf.h"

Robber::Robber(int x, int y) : NPC(RobberType, x, y, 5) {}
Robber::Robber(std::istream &is) : NPC(RobberType, is) {}

void Robber::print() { std::cout << *this; }

bool Robber::accept(std::shared_ptr<NPC> visitor) {
  return visitor->fight(std::shared_ptr<Robber>(this, [](Robber *) {}));
}

void Robber::save(std::ostream &os) {
  os << RobberType << std::endl;
  NPC::save(os);
}

bool Robber::fight(std::shared_ptr<Orc> other) {
  fight_notify(other, true);
  return true;
}

bool Robber::fight(std::shared_ptr<Robber> other) {
  fight_notify(other, false);
  return false;
}

bool Robber::fight(std::shared_ptr<Werewolf> other) {
  fight_notify(other, false);
  return false;
}

std::ostream &operator<<(std::ostream &os, Robber &robber) {
  os << "robber: " << *static_cast<NPC *>(&robber) << std::endl;
  return os;
}