#ifndef ROBBER_H_INCLUDED
#define ROBBER_H_INCLUDED
#include "NPC.h"

class Robber final: public NPC {
    public:

    Robber(int x, int y, std::string name);
    Robber(std::istream & is);

    void print() override;
    void save(std::ostream & os) override;
    
    friend std::ostream & operator << (std::ostream & os, Robber & robber);
    virtual FightInfo accept(std::shared_ptr<NPC> defender, Visitor & visitor) override;
};

#endif // ROBBER_H_INCLUDED