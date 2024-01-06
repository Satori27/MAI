#ifndef ORC_H_INCLUDED
#define ORC_H_INCLUDED
#include "NPC.h"

class Orc final: public NPC {
    public:
    
    Orc(int x, int y, std::string name);
    Orc(std::istream & is);

    void print() override;
    void save(std::ostream & os) override;

    friend std::ostream & operator << (std::ostream & os, Orc & orc);
    virtual FightInfo accept(std::shared_ptr<NPC> defender, Visitor & visitor) override;
};

#endif // ORC_H_INCLUDED