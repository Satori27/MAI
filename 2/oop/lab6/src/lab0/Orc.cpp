#include "Orc.h"
#include "Robber.h"
#include "Werewolf.h"


Orc::Orc(int x, int y, std::string name): NPC(OrcType, x, y, name) {}
Orc::Orc(std::istream & is): NPC(OrcType, is) {}
void Orc::print() {
    std::cout << * this;
}
std::ostream & operator << (std::ostream & os, Orc & orc) {
    os << "Orc: " << * static_cast < NPC * > ( & orc) << std::endl;
    return os;
}
void Orc::save(std::ostream & os) {
    os << OrcType << std::endl;
    NPC::save(os);
}


FightInfo Orc::accept(std::shared_ptr<NPC> defender, Visitor & visitor) {
    if(std::dynamic_pointer_cast<Robber>(defender).get())
        return visitor.visit( std::dynamic_pointer_cast<Orc>(shared_from_this()), std::dynamic_pointer_cast<Robber>(defender));
    if(std::dynamic_pointer_cast<Werewolf>(defender).get())
        return visitor.visit( std::dynamic_pointer_cast<Orc>(shared_from_this()), std::dynamic_pointer_cast<Werewolf>(defender));
}