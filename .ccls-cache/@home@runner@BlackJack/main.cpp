#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

void shuffleDeck(std::array<std::string, 312> &deck) {
  // TODO: Rewrite to create my own shuffling method
  std::random_device randomizer;
  std::mt19937 g(randomizer());

  std::shuffle(deck.begin(), deck.end(), g);
}

int main() {
  std::array<std::string, 52> cards = {
      "2H",     "3H",     "4H",     "5H",     "6H",    "7H",   "8H",
      "9H",     "10H",    "JackH",  "QueenH", "KingH", "AceH", "2D",
      "3D",     "4D",     "5D",     "6D",     "7D",    "8D",   "9D",
      "10D",    "JackD",  "QueenD", "KingD",  "AceD",  "2C",   "3C",
      "4C",     "5C",     "6C",     "7C",     "8C",    "9C",   "10C",
      "JackC",  "QueenC", "KingC",  "AceC",   "2S",    "3S",   "4S",
      "5S",     "6S",     "7S",     "8S",     "9S",    "10S",  "JackS",
      "QueenS", "KingS",  "AceS"};
  std::array<std::string, 312> currentDeck = {};
  std::vector<std::string> playerHand = {};
  std::vector<std::string> dealerHand = {};
  
  int deckLength = sizeof(cards) / sizeof(cards[0]);
  int numOfDecks = 6;
  int counter = 0;

  int money = 100;
  int bet = 0;

  // Create BlackJack deck of 6 individual card decks. Copy each deck into
  // currentDeck list 6 times
  for (int i = 0; i < numOfDecks; i++) {
    std::copy(cards.begin(), cards.end(), currentDeck.begin() + i * deckLength);
  }

  shuffleDeck(currentDeck);

  // Remove Later, testing only
  for (std::string card : currentDeck) {
    std::cout << card << " ";
  }

  std::cout << "\nWelcome to the Black Jack table, gambler!\n" << std::endl;

  while (money > 0 && counter < 312) {
    std::cout << "\nYou have $" << std::to_string(money) << std::endl;
    std::cout << "Enter your bet: " << std::endl;
    std::cin >> bet;
    money -= bet;
    std::cout << "Your bet is $" << bet << std::endl;
    
    for (int i = 0; i < 2; i++) {//Give cards to player and dealer
      playerHand.push_back(currentDeck[counter]);
      dealerHand.push_back(currentDeck[counter+1]);
      counter += 2;
    }

    std::cout << "\nPlayer Hand: " << std::endl;
    for(std::string value : playerHand) {
      std::cout << value << "\t";
    }
    
    std::cout << "\n\nDealer Hand: " << std::endl;
    for(std::string value : dealerHand) {
      std::cout << value << "\t";
    }
    
  }
}