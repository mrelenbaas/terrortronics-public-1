/**
 * @file game.h
 * 
 * Game manager.
 * 
 * @section author Author
 * - Created by Bradley Elenbaas on 12/30/2020.
 * - Modified by Bradley Elenbaas on 12/30/2020.
 *
 * Copyright (c) 2020 Bradley Elenbaas. All rights reserved.
 */

// 2nd-party libraries.
#include "inputer.h"
#include "outputer.h"

class Game {
public:
  void starter();
  void updater();
  void updater_other(int, int, int, int);
private:
  Inputer inputer;   ///< Input manager.
  Outputer outputer; ///< Output manager.
};

/**
 * Pseudo-constructor.
 */
void Game::starter() {
  outputer.starter();
}

/**
 * Update input and output.
 * 
 * @param result Passed to outputer.
 */
void Game::updater() {
  //profile_set(ID_INPUTER);
  int count = inputer.updater();
  //profile_set(ID_OUTPUTER);
  outputer.updater(count, inputer.get_analog_counter());
  //profile_set(ID_OTHER);
}

void Game::updater_other(int bin_one, int bin_two, int bin_three, int bin_four) {
  outputer.updater_other(bin_one, bin_two, bin_three, bin_four);
}
