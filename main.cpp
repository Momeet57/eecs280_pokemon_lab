#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;

class League {
 private:
  vector<Trainer *> gym_leaders;
  int num_gym_leaders;
  Trainer *player;
  vector<Trainer *> defeated;

 public:
  League(int num_gym_leads, istream &is) {
    num_gym_leaders = num_gym_leads;
    string gym;
    is >> gym;
    for (int i = 0; i < num_gym_leaders; i++) {
      gym_leaders[i] = Trainer_factory(is);
    }
  }

  void print_pokemon_battles(Trainer *current_gym_leader) {
    int num_wins = 0;
    for (int i = 0; i < 5; ++i) {
      // Each individual pokemon battle
      Pokemon enemy = current_gym_leader->choose_pokemon();
      cout << *current_gym_leader << " chooses " << enemy << endl;
      Pokemon p = player->choose_pokemon(enemy.get_type());
      cout << *player << " chooses " << p << endl;
      if (Pokemon_battle(p, enemy)) {
        cout << p << " defeats " << enemy << endl << endl;
        ++num_wins;
      } else {
        cout << enemy << " defeats " << p << endl << endl;
      }
    }
    cout << "Result: " << *player << "=" << num_wins << ", "
         << *current_gym_leader << "=" << 5 - num_wins << endl;
  }

  void gym_battles() {
    for (int i = 0; i < gym_leaders.size(); ++i) {
      player->reset();
      cout << "-----" << *player << " vs. " << *gym_leaders[i] << "-----"
           << endl;
      print_pokemon_battles(gym_leaders[i]);
    }
  }
  void print_final_results() {
    cout << *player << " won " << defeated.size()
         << " matches by defeating:" << endl;
    for (int i = 0; i < defeated.size(); ++i) {
      cout << *defeated[i] << endl;
    }
  }
  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }

  std::string player_in_name = argv[1];
  std::string gym_leaders_in_name = argv[2];

  std::ifstream player_in(player_in_name);
  if (!player_in.is_open()) {
    cout << "Unable to open " << player_in_name << endl;
    return 1;
  }
  std::ifstream gym_in(gym_leaders_in_name);
  if (!gym_in.is_open()) {
    cout << "Unable to open " << gym_leaders_in_name << endl;
    return 1;
  }
  int numGymLeads;
  gym_in >> numGymLeads;
  League league(numGymLeads, gym_in);
  Trainer_factory(player_in);
  league.gym_battles();
  league.print_final_results();

  return 0;
}