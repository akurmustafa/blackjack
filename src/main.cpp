
#include "src/blackjack.h"

#include <array>
#include <iostream>

int main() {
	//// test functions
	//blackjack::test_print_card();
	//blackjack::test_print_deck();
	//blackjack::test_swap_cards();
	//blackjack::test_shuffle_deck();
	//blackjack::test_get_card_value();
	//// end of test functions

	std::string new_play{ "" };
	do {
		int cur_play_end{ 0 };

		// initialize deck with order
		std::vector<blackjack::Card> deck;
		for (int i = 2; i < static_cast<int>(blackjack::CardRanks::max_ranks); ++i) {
			for (int j = 0; j < static_cast<int>(blackjack::CardSuits::max_suits); ++j) {
				deck.push_back(blackjack::Card{ static_cast<blackjack::CardRanks>(i),\
													static_cast<blackjack::CardSuits>(j) });
			}
		}

		blackjack::shuffle_deck(deck);  // at the start of the game make sure to shuffle
		blackjack::Dealer dealer(deck);
		blackjack::Client client(deck);
		std::string user_decision;

		if (client.get_total_point() == 21) {
			std::cout << "\nCards you have chosen\n";
			blackjack::print_deck(client.get_cards());
			std::cout << "Your point is 21! You have won.\n";
			cur_play_end = 1;
			std::cout << "\n\n-----------------------\nTo play a new game, press \"new\"!. To end game ";
			std::cout << "press any other key\n";
			std::cin >> new_play;
			continue;
		}
		std::cout << "Cards you have chosen\n";
		blackjack::print_deck(client.get_cards());
		std::cout << "Your current point is " << client.get_total_point() << '\n';
		std::cout << "Please press \"hit\" to continue playing, to end current turn, press any other key!\n";
		std::cin >> user_decision;
		while (user_decision == "hit") {
			client.choose_card(deck);
			if (client.get_total_point() == 21) {
				std::cout << "\nCards you have chosen\n";
				blackjack::print_deck(client.get_cards());
				std::cout << "Your point is 21! You have won.\n";
				cur_play_end = 1;
				break;
			}
			else if (client.get_total_point() > 21 && client.get_number_of_aces() != 0) {
				client.change_total_point();
				std::cout << "\nCards you have chosen\n";
				blackjack::print_deck(client.get_cards());
				std::cout << "Your current point is " << client.get_total_point() << '\n';
			}
			else if(client.get_total_point() > 21 && client.get_number_of_aces() == 0) {
				std::cout << "\nCards you have chosen\n";
				blackjack::print_deck(client.get_cards());
				std::cout << "Your point is " << client.get_total_point() << " You have lost.\n";
				cur_play_end = 1;
				break;
			}
			std::cout << "\nCards you have chosen\n";
			blackjack::print_deck(client.get_cards());
			std::cout << "Your current point is " << client.get_total_point() << '\n';
			std::cout << "Please press \"hit\" to continue playing, to end current turn press any other key!\n";
			std::cin >> user_decision;
		}
		while (!cur_play_end) {
			std::cout << "\nCards I have chosen\n";
			blackjack::print_deck(dealer.get_cards());
			std::cout << "My current point is " << dealer.get_total_point() << '\n';

			dealer.choose_card(deck);
			if (dealer.get_total_point() > 21) {
				if (dealer.get_number_of_aces() != 0) {
					dealer.change_total_point();
					std::cout << "\nCards you have chosen\n";
					blackjack::print_deck(client.get_cards());
					std::cout << "Your current point is " << client.get_total_point() << '\n';
					continue;
				}
				std::cout << "\nCards I have chosen\n";
				blackjack::print_deck(dealer.get_cards());
				std::cout << "My point is " << dealer.get_total_point() << ". You have won.\n";
				cur_play_end = 1;
				break;
			}
			else if (dealer.get_total_point() > client.get_total_point()) {
				std::cout << "\nCards I have chosen\n";
				blackjack::print_deck(dealer.get_cards());
				std::cout << "My point is " << dealer.get_total_point() << ". I have won.\n";
				cur_play_end = 1;
				break;
			}
		}
		// std::cout << deck.size() << '\n';
		std::cout << "\n\n-----------------------\nTo play a new game, press \"new\"!. To end game ";
		std::cout<<"press any other key\n";
		std::cin >> new_play;
	} while (new_play == "new");
	return 0;
}
