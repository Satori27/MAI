#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <random>
#include <set>
#include <shared_mutex>
#include <string>

struct NPC;
struct Orc;
struct Robber;
struct Werewolf;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType { Unknown = 0, OrcType = 1, RobberType = 2, WerewolfType = 3 };

struct IFightObserver {
  virtual void on_fight(const std::shared_ptr<NPC> attacker,
						const std::shared_ptr<NPC> defender, bool win) = 0;
};

class NPC {
private:
  std::mutex mtx;

  NpcType type;
  int x{0};
  int y{0};
  bool alive{true};

  std::vector<std::shared_ptr<IFightObserver>> observers;

protected:
  int dist{0};

public:
  NPC(NpcType t, int _x, int _y, int _dist);
  NPC(NpcType t, std::istream &is);

  void subscribe(std::shared_ptr<IFightObserver> observer);
  void fight_notify(const std::shared_ptr<NPC> defender, bool win);
  virtual bool is_close(const std::shared_ptr<NPC> &other);

  virtual bool accept(std::shared_ptr<NPC> visitor) = 0;

  virtual bool fight(std::shared_ptr<Orc> other) = 0;
  virtual bool fight(std::shared_ptr<Robber> other) = 0;
  virtual bool fight(std::shared_ptr<Werewolf> other) = 0;

  virtual void print() = 0;
  std::pair<int, int> position();
  NpcType get_type();

  virtual void save(std::ostream &os);

  friend std::ostream &operator<<(std::ostream &os, NPC &npc);

  void move(int shift_x, int shift_y, int max_x, int max_y);

  bool is_alive();
  void must_die();
};