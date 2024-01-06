#include "Orc.h"
#include "Robber.h"
#include "Werewolf.h"

Orc::Orc(int x, int y) : NPC(OrcType, x, y, 10) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

bool Orc::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Orc>(this,[](Orc*){}));
}

void Orc::print()
{
    std::cout << *this;
}


bool Orc::fight(std::shared_ptr<Orc> other) 
{
    fight_notify(other, false);
    return false;
}

bool Orc::fight(std::shared_ptr<Robber> other) 
{
    fight_notify(other, false);
    return false;
}

bool Orc::fight(std::shared_ptr<Werewolf> other) 
{
    fight_notify(other, false);
    return false;
}

void Orc::save(std::ostream &os) 
{
    os << OrcType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Orc &orc)
{
    os << "orc: " << *static_cast<NPC *>(&orc) << std::endl;
    return os;
}