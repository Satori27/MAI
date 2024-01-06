#include "Observer.h"

std::shared_ptr < IFightObserver > TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr < IFightObserver > ( & instance, [](IFightObserver * ) {});

}
void TextObserver::on_fight(const std::shared_ptr < NPC > attacker,
    const std::shared_ptr < NPC > defender, bool win) {

    if (!win) {
        return;
    }
    std::cout << std::endl <<
        "Kill was completed--------" << std::endl;

    attacker -> print();
    defender -> print();

}

std::shared_ptr < IFightObserver > FileObserver::get() {
    static FileObserver instance;
    return std::shared_ptr < IFightObserver > ( & instance, [](IFightObserver * ) {});
}

void FileObserver::on_fight(const std::shared_ptr < NPC > attacker,
    const std::shared_ptr < NPC > defender, bool win) {
    std::fstream op;
    op.open("log.txt", std::ios::app);
    if (win) {
        op << std::endl <<
            "Kill was completed --------" << std::endl;
        op << ( * attacker);
        op << * defender;
    }
    op.flush();
    op.close();
}