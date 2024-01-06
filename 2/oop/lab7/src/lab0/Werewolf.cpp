#include "Robber.h"
#include "Orc.h"
#include "Werewolf.h"

Werewolf::Werewolf(int x, int y) : NPC(WerewolfType, x, y, 15) {}
Werewolf::Werewolf(std::istream &is) : NPC(WerewolfType, is) {}

bool Werewolf::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Werewolf>(this,[](Werewolf*){}));
}

void Werewolf::print()
{
    std::cout << *this;
}

void Werewolf::save(std::ostream &os)
{
    os << WerewolfType << std::endl;
    NPC::save(os);
}


bool Werewolf::fight(std::shared_ptr<Orc> other)
{
    fight_notify(other, true);
    return true;
}

bool Werewolf::fight(std::shared_ptr<Robber> other)
{
    fight_notify(other, true);
    return true;
}

bool Werewolf::fight(std::shared_ptr<Werewolf> other)
{
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, Werewolf &werewolf)
{
    os << "werewolf: " << *static_cast<NPC *>(&werewolf) << std::endl;
    return os;
}