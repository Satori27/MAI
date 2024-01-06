#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>

#include <memory>

#include <cstring>

#include <string>

#include <random>

#include <fstream>

#include <set>

#include <math.h>

// using namespace std;


enum NpcType {
    Unknown = 0,
    WerewolfType = 1,
    OrcType = 3,
    RobberType = 2
};

enum FightInfo {
    Win = 1,
    Lose = 0,
    Draw = -1
};

class NPC;
class Werewolf;
class Orc;
class Robber;
class Visitor;
// class Fighters;
using set_t = std::set < std::shared_ptr < NPC >> ;
class IFightObserver {
    public: virtual void on_fight(const std::shared_ptr < NPC > attacker,
        const std::shared_ptr < NPC > defender, bool win) = 0;
};
class NPC: public std::enable_shared_from_this < NPC > {
    NpcType type;
    int x {0};
    int y {0};
    std::string name;
    std::vector < std::shared_ptr < IFightObserver >> observers;

    public:
    NPC(NpcType t, int _x, int _y, std::string _name);
    NPC(NpcType t, std::istream & is);

    void subscribe(std::shared_ptr < IFightObserver > observer);
    void fight_notify(const std::shared_ptr < NPC > defender, bool win);


    virtual bool is_close(const std::shared_ptr < NPC > & other, size_t distance) const;
    virtual void print() = 0;
    virtual void save(std::ostream & os);
    virtual FightInfo accept(std::shared_ptr<NPC> defender, Visitor & visitor) = 0;
        // std::shared_ptr<Orc> def = std::dynamic_pointer_cast<Orc>(defender);
        // if(def){
        //     std::shared_ptr<Orc> def = std::dynamic_pointer_cast<Orc>(defender);
        // }
        // std::shared_ptr<Robber> def = std::dynamic_pointer_cast<Robber>(defender);
        // if(def){
        //     std::shared_ptr<Robber> def = std::dynamic_pointer_cast<Robber>(defender);
        // }
        

    friend std::ostream & operator << (std::ostream & os, NPC & npc);
};


class Visitor {
    public: 
//   virtual int visit(Werewolf* attacker, Orc* defender) = 0;
//   virtual int visit(Werewolf* attacker, Robber* defender) = 0;

//   virtual int visit(Robber* attacker, NPC* defender) = 0;
//   virtual int visit(Werewolf* attacker, NPC* defender) = 0;
//   virtual int visit(Orc* attacker, NPC* defender) = 0;

//   virtual int visit(Orc* attacker, Werewolf* defender) = 0;
//   virtual int visit(Orc* attacker, Robber* defender) = 0;

//   virtual int visit(Robber* attacker, Werewolf* defender) = 0;
//   virtual int visit(Robber* attacker, Orc* defender) = 0;


  virtual FightInfo visit(std::shared_ptr<Orc> atacker, std::shared_ptr<Werewolf>  defender)=0;
  virtual FightInfo visit(std::shared_ptr<Orc> atacker, std::shared_ptr<Robber>  defender)=0;

  virtual FightInfo visit(std::shared_ptr<Robber> atacker, std::shared_ptr<Werewolf>  defender)=0;
  virtual FightInfo visit(std::shared_ptr<Robber> atacker, std::shared_ptr<Orc>  defender)=0;

  virtual FightInfo visit(std::shared_ptr<Werewolf> atacker, std::shared_ptr<Robber>  defender)=0;
  virtual FightInfo visit(std::shared_ptr<Werewolf> atacker, std::shared_ptr<Orc>  defender)=0;

};
#endif // NPC_H_INCLUDED