#include "Visitor.h"

#include <cmath>

FightInfo WarVisitor::visit(std::shared_ptr < Werewolf > atacker, std::shared_ptr < Orc > defender) {
    atacker -> fight_notify(defender, false);
    return Lose;
}

FightInfo WarVisitor::visit(std::shared_ptr < Werewolf > atacker, std::shared_ptr < Robber > defender) {
    atacker -> fight_notify(defender, true);
    return Win;
}

FightInfo WarVisitor::visit(std::shared_ptr < Robber > atacker, std::shared_ptr < Werewolf > defender) {
    atacker -> fight_notify(defender, true);
    return Win;
}
FightInfo WarVisitor::visit(std::shared_ptr < Robber > atacker, std::shared_ptr < Orc > defender) {
    atacker -> fight_notify(defender, false);
    return Lose;
}

FightInfo WarVisitor::visit(std::shared_ptr < Orc > atacker, std::shared_ptr < Robber > defender) {
    atacker -> fight_notify(defender, true);
    return Win;
}
FightInfo WarVisitor::visit(std::shared_ptr < Orc > atacker, std::shared_ptr < Werewolf > defender) {
    atacker -> fight_notify(defender, false);
    return Lose;
}