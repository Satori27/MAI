// #ifndef FABRIC_H_INCLUDED
// #define FABRIC_H_INCLUDED
#pragma once

#include "Observer.h"

class Factory {
public:
  std::shared_ptr<NPC> factory(std::istream &is) {
	std::shared_ptr<NPC> result;
	int type{0};
	if (is >> type) {
	  switch (type) {
	  case OrcType:
		result = std::make_shared<Orc>(is);
		break;
	  case RobberType:
		result = std::make_shared<Robber>(is);
		break;
	  case WerewolfType:
		result = std::make_shared<Werewolf>(is);
		break;
	  }
	} else
	  std::cerr << "unexpected NPC type:" << type << std::endl;

	if (result)
	  result->subscribe(TextObserver::get());

	return result;
  }

  std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
	std::shared_ptr<NPC> result;
	switch (type) {
	case OrcType:
	  result = std::make_shared<Orc>(x, y);
	  break;
	case RobberType:
	  result = std::make_shared<Robber>(x, y);
	  break;
	case WerewolfType:
	  result = std::make_shared<Werewolf>(x, y);
	  break;
	default:
	  break;
	}
	if (result)
	  result->subscribe(TextObserver::get());

	return result;
  }
};
