#include "Orc.h"
#include "Robber.h"
#include "Werewolf.h"

Robber::Robber(int x, int y, std::string name): NPC(RobberType, x, y, name) {}
Robber::Robber(std::istream & is): NPC(RobberType, is) {}
void Robber::print() {
    std::cout << * this;
}
std::ostream & operator << (std::ostream & os, Robber & robber) {
    os << "Robber: " << * static_cast < NPC * > ( & robber) << std::endl;
    return os;
}


void Robber::save(std::ostream & os) {
    os << RobberType << std::endl;
    NPC::save(os);
}

FightInfo Robber::accept(std::shared_ptr<NPC> defender, Visitor & visitor) {
    // std::shared_ptr<Orc> atacker_ptr = std::make_shared<Orc>(this);
    if(std::dynamic_pointer_cast<Orc>(defender).get())
        return visitor.visit( std::dynamic_pointer_cast<Robber>(shared_from_this()), std::dynamic_pointer_cast<Orc>(defender));
    if(std::dynamic_pointer_cast<Werewolf>(defender).get())
        return visitor.visit( std::dynamic_pointer_cast<Robber>(shared_from_this()), std::dynamic_pointer_cast<Werewolf>(defender));
}