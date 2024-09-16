#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>

void shuffleDeck(std::array<std::string, 312> &deck) {
  // TODO: Rewrite to create my own shuffling method
  std::random_device randomizer;
  std::mt19937 g(randomizer());

  std::shuffle(deck.begin(), deck.end(), g);
}

std::pair <int, int> calculateScore(std::string card){
  size_t cardLength = card.length();
  std::string cardFirstPart = card.substr(0, 1);
  int num = 0;
  int score = 0;
  int potentialScore = 0;
  
  if (cardFirstPart == "A") {
    score += 11;
    potentialScore += 1;
    std::cout << "Ace" << std::endl;
  } else if (cardLength > 2) {
    score += 10;
  } else {
    num = std::stoi(cardFirstPart);
    score += num;
  }

  return std::make_pair(score, potentialScore);
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
  int cardCounter = 0;   // Count cards left in the deck
  int dealerCounter = 0; // Count dealer cards shown to player

  int money = 100;
  int bet = 0;
  std::string move = "";
  int playerScore = 0;
  int potentialPlayerScore = 0;
  int dealerScore = 0;
  int potentialDealerScore = 0;

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

  std::cout << "\n\nWelcome to the Black Jack table, gambler!\n" << std::endl;
  std::cout << "Rules:\n## - card is hidden\ns - stand\nh - hit\ndd - double "
               "down\nsplit - split"
            << std::endl;

  while (money > 0 && cardCounter < 312) {
    move = "";
    playerScore = 0;
    dealerScore = 0;

    std::cout << "\nYou have $" << std::to_string(money) << std::endl;
    std::cout << "Enter your bet: " << std::endl;
    std::cin >> bet;
    money -= bet;
    std::cout << "Your bet is $" << bet << std::endl;

    // Give cards to player and dealer. First player then dealer, then player,
    // then dealer. Count scores as well
    for (int i = 0; i < 2; i++) {
      playerHand.push_back(currentDeck[cardCounter]);
      dealerHand.push_back(currentDeck[cardCounter + 1]);

      //Calculate Player Score
      std::pair<int, int> playerResult = calculateScore(currentDeck[cardCounter]);
      playerScore += playerResult.first;
      potentialPlayerScore += playerResult.second;

      //Calculate Computer Score
      std::pair<int, int> dealerResult = calculateScore(currentDeck[cardCounter+1]);
      dealerScore += dealerResult.first;
      potentialDealerScore += dealerResult.second;

      cardCounter += 2;
    }
    
    // Show player cards
    std::cout << "\nPlayer Hand: " << std::endl;
    for (std::string value : playerHand) {
      std::cout << value << "\t";
    }
    //DEBUG
    std::cout << "\n" << playerScore << std::endl;
    std::cout << potentialPlayerScore << std::endl;

    // Show dealer cards
    std::cout << "\n\nDealer Hand: " << std::endl;
    for (std::string value : dealerHand) {
      if (dealerCounter == 0) {
        std::cout << value << "\t";
      } else {
        std::cout << "##"
                  << "\t";
      }
      dealerCounter++;
    }
    //DEBUG
    std::cout <<"\n" <<  dealerScore << std::endl;
    std::cout << potentialDealerScore << std::endl;

    // Player move
    while (move != "s") {
      std::cout << "\nHit, Stand or Double Down ?" << std::endl;
      std::cin >> move;
    }
  }
}