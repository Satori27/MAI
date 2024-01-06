#include "Orc.h"
#include "Robber.h"
#include "Werewolf.h"

Werewolf::Werewolf(int x, int y, std::string name): NPC(WerewolfType, x, y, name) {}

Werewolf::Werewolf(std::istream & is): NPC(WerewolfType, is) {}
void Werewolf::print() {
    std::cout << * this;
}
std::ostream & operator << (std::ostream & os, Werewolf & werewolf) {
    os << "Werewolf: " << * static_cast < NPC * > ( & werewolf) << std::endl;
    return os;
}

void Werewolf::save(std::ostream & os) {
    os << WerewolfType << std::endl;
    NPC::save(os);
}

FightInfo Werewolf::accept(std::shared_ptr<NPC> defender, Visitor & visitor) {
    // std::shared_ptr<Orc> atacker_ptr = std::make_shared<Orc>(this);
    if(std::dynamic_pointer_cast<Robber>(defender).get())
        return visitor.visit( std::dynamic_pointer_cast<Werewolf>(shared_from_this()), std::dynamic_pointer_cast<Robber>(defender));
    if(std::dynamic_pointer_cast<Orc>(defender))
        return visitor.visit( std::dynamic_pointer_cast<Werewolf>(shared_from_this()), std::dynamic_pointer_cast<Orc>(defender));
}
