#pragma once
#include "NPC.h"

struct Robber : public NPC
{
    int dist=20;
    Robber(int x, int y);
    Robber(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Robber> other) override;
    bool fight(std::shared_ptr<Werewolf> other) override;
    friend std::ostream &operator<<(std::ostream &os, Robber &robber);

    bool accept(std::shared_ptr<NPC> visitor) override;
};