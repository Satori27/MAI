#ifndef OBSERVER_H_INCLUDED
#define OBSERVER_H_INCLUDED
#include "NPC.h"

#include <fstream>

#include <string>

class TextObserver final: public IFightObserver {
    private: 
    TextObserver() = default;

    public: 
    static std::shared_ptr < IFightObserver > get();
    void on_fight(const std::shared_ptr < NPC > attacker,
                 const std::shared_ptr < NPC > defender, bool win) override;
                 
    ~TextObserver() = default;
}; 
class FileObserver final: public IFightObserver {
    private: 
    FileObserver() = default;

    public: 
    static std::shared_ptr < IFightObserver > get();
    void on_fight(const std::shared_ptr < NPC > attacker,
                 const std::shared_ptr < NPC > defender, 
                 bool win) override;

    ~FileObserver() = default;
};
#endif // OBSERVER_H_INCLUDED