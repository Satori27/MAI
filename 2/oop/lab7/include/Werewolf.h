#pragma once
#include "NPC.h"

struct Werewolf : public NPC
{
    Werewolf(int x, int y);
    Werewolf(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Robber> other) override;
    bool fight(std::shared_ptr<Werewolf> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    friend std::ostream &operator<<(std::ostream &os, Werewolf &werewolf);
};