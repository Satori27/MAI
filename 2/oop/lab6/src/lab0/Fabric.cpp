#include "Fabric.h"

std::shared_ptr < NPC > Factory::factory(std::istream & is) {
    std::shared_ptr < NPC > result;
    int type {0};
    if (is >> type) {
        switch (type) {
        case RobberType:
            result = std::make_shared < Robber > (is);
            break;
        case WerewolfType:
            result = std::make_shared < Werewolf > (is);
            break;
        case OrcType:
            result = std::make_shared < Orc > (is);
            break;
        }
    } else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result) {
        result -> subscribe(TextObserver::get());
        result -> subscribe(FileObserver::get());
    }

    return result;
}
std::shared_ptr < NPC > Factory::factory(NpcType type, int x, int y,
    std::string name) {
    std::shared_ptr < NPC > result;

    switch (type) {
    case RobberType:
        result = std::make_shared < Robber > (x, y, name);
        break;
    case WerewolfType:
        result = std::make_shared < Werewolf > (x, y, name);
        break;
    case OrcType:
        result = std::make_shared < Orc > (x, y, name);
        break;
    default:
        std::cerr << "unexpected NPC type:" << type << std::endl;
        break;
    }

    if (result) {
        result -> subscribe(TextObserver::get());
        result -> subscribe(FileObserver::get());
    }

    return result;
}