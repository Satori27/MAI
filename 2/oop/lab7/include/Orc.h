#pragma once
#include "NPC.h"

struct Orc : public NPC
{   
    Orc(int x, int y);
    Orc(std::istream &is);

    void print() override;

    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Robber> other) override;
    bool fight(std::shared_ptr<Werewolf> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Orc &orc);
};