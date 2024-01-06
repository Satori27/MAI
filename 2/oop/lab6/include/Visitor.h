#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED
#include "Fabric.h"

// #include "Fighters.h"

class WarVisitor : public Visitor {
public:
  // virtual FightInfo visit(Werewolf* atacker, Orc* defender);
  // virtual FightInfo visit(Werewolf* atacker, Robber* defender);

  // virtual FightInfo visit(Orc* atacker, Werewolf* defender);
  // virtual FightInfo visit(Orc* atacker, Robber* defender);

  // virtual FightInfo visit(Orc* atacker, NPC* defender);
  // virtual FightInfo visit(Robber* atacker, NPC* defender);
  // virtual FightInfo visit(Werewolf* atacker, NPC* defender);

  // virtual FightInfo visit(Robber* atacker, Werewolf* defender);
  // virtual FightInfo visit(Robber* atacker, Orc* defender);

  virtual FightInfo visit(std::shared_ptr<Orc> atacker, std::shared_ptr<Werewolf>  defender);
  virtual FightInfo visit(std::shared_ptr<Orc> atacker, std::shared_ptr<Robber>  defender);

  virtual FightInfo visit(std::shared_ptr<Robber> atacker, std::shared_ptr<Werewolf>  defender);
  virtual FightInfo visit(std::shared_ptr<Robber> atacker, std::shared_ptr<Orc>  defender);

  virtual FightInfo visit(std::shared_ptr<Werewolf> atacker, std::shared_ptr<Robber>  defender);
  virtual FightInfo visit(std::shared_ptr<Werewolf> atacker, std::shared_ptr<Orc>  defender);


  // virtual FightInfo visit(Robber element);
  // virtual FightInfo visit(Fighters element);
};

#endif // VISITOR_H_INCLUDED