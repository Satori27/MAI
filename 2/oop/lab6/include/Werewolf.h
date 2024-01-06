#ifndef WEREWOLF_H_INCLUDED
#define WEREWOLF_H_INCLUDED

#include "NPC.h"

class Werewolf final: public NPC {
    public: 
    
    Werewolf(int x, int y, std::string name);
    Werewolf(std::istream & is);
    
    void print() override;
    void save(std::ostream & os) override;
    
    friend std::ostream & operator << (std::ostream & os, Werewolf & werewolf);
    virtual FightInfo accept(std::shared_ptr<NPC> defender, Visitor & visitor) override;
};

#endif // WEREWOLF_H_INCLUDED