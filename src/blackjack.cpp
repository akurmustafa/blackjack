
#include  "blackjack.h"


#include <array>
#include <iostream>
#include <random>
#include <vector>

namespace blackjack {
	std::random_device rd;
	void print_card(const Card &card) {
		switch(card.rank) {
		case CardRanks::rank_jack:
			std::cout << 'J';
			break;
		case CardRanks::rank_queen:
			std::cout << 'Q';
			break;
		case CardRanks::rank_king:
			std::cout << 'K';
			break;
		case CardRanks::rank_ace:
			std::cout << 'A';
			break;
		default:
			std::cout << static_cast<int>(card.rank);
			break;
		}

		switch (card.suit) {
		case CardSuits::suit_clubs:
			std::cout << "C";
			break;
		case CardSuits::suit_diamonds:
			std::cout << "D";
			break;
		case CardSuits::suit_hearts:
			std::cout << "H";
			break;
		case CardSuits::suit_spades:
			std::cout << "S";
			break;
		}
		std::cout << ' ';
	}

	void test_print_card() {
		std::cout << "print_card() function test code\n";
		std::cout << "Function should print:\n2H JH JD 9D\n";
		Card card_2H{ CardRanks::rank_2, CardSuits::suit_hearts };
		print_card(card_2H);
		Card card_JH{ CardRanks::rank_jack, CardSuits::suit_hearts };
		print_card(card_JH);
		Card card_JD{ CardRanks::rank_jack, CardSuits::suit_diamonds };
		print_card(card_JD);
		Card card_9D{ CardRanks::rank_9, CardSuits::suit_diamonds };
		print_card(card_9D);
		std::cout << '\n';
	}

	void print_deck(const std::vector<Card> &deck) {
		for (const auto cur_card : deck) {
			print_card(cur_card);
		}
		std::cout << '\n';
	}
	
	void test_print_deck() {
		std::cout << "print_deck() function test code\n";
		std::cout << "Function should print: \n";
		std::vector<Card> deck;
		for (int i = 2; i < static_cast<int>(CardRanks::max_ranks); ++i) {
			for (int j = 0; j < static_cast<int>(CardSuits::max_suits); ++j) {
				deck.push_back(Card{ static_cast<CardRanks>(i),\
									static_cast<CardSuits>(j) });
				print_card(Card{ static_cast<CardRanks>(i),\
					static_cast<CardSuits>(j) });
			}
		}
		std::cout << '\n';
		print_deck(deck);
	}

	void swap_cards(Card &card_1, Card &card_2){
		Card temp{ card_1.rank, card_1.suit };
		card_1 = card_2;
		card_2 = temp;
	}

	void test_swap_cards() {
		std::cout << "swap_cards() function test code\n";
		Card card_1{ CardRanks::rank_10, CardSuits::suit_hearts };
		Card card_2{ CardRanks::rank_jack, CardSuits::suit_spades };
		std::cout << "Function should swap following values:\n";
		print_card(card_1);
		print_card(card_2);
		std::cout<<'\n';
		swap_cards(card_1, card_2);
		std::cout << "Function result:\n";
		print_card(card_1);
		print_card(card_2);
		std::cout << '\n';
	}

	void shuffle_deck(std::vector<Card> &deck) {
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0.0, 51.0);
		for (auto &cur_card : deck) {
			swap_cards(cur_card, deck[std::ceil(dist(mt))]);
		}
	}

	void test_shuffle_deck() {
		std::cout << "shuffle_deck() function test code\n";
		std::cout << "Function should print shuffled version of below values: \n";
		std::vector<Card> deck;
		for (int i = 2; i < static_cast<int>(CardRanks::max_ranks); ++i) {
			for (int j = 0; j < static_cast<int>(CardSuits::max_suits); ++j) {
				deck.push_back(Card{ static_cast<CardRanks>(i),\
									static_cast<CardSuits>(j) });
				print_card(Card{ static_cast<CardRanks>(i),\
					static_cast<CardSuits>(j) });
			}
		}
		std::cout << '\n';
		shuffle_deck(deck);
		std::cout << "Shuffled Version:\n";
		print_deck(deck);
	}

	int get_card_value(const Card card) {
		switch (card.rank) {
		case CardRanks::rank_jack:
			return 10;
		case CardRanks::rank_queen:
			return 10;
		case CardRanks::rank_king:
			return 10;
		case CardRanks::rank_ace:
			return 11;
		default:
			return static_cast<int>(card.rank);
		}
	}

	void test_get_card_value() {
		std::cout << "get_card_value() function test code\n";
		std::cout << "Function should print below values: \n";
		std::cout << 4 << ", " << 10 << ", " << 11 << '\n';
		Card card_1{ CardRanks::rank_4, CardSuits::suit_clubs };
		Card card_2{ CardRanks::rank_jack, CardSuits::suit_clubs };
		Card card_3{ CardRanks::rank_ace, CardSuits::suit_clubs };
		std::cout << get_card_value(card_1) << ", ";
		std::cout << get_card_value(card_2) << ", ";
		std::cout << get_card_value(card_3) << '\n';
	}

	Player::Player() : total_point{ 0 }, cards{}, number_of_aces{0} {}
	
	const std::vector<Card>& Player::get_cards() const {
		return cards;
	}
	const int Player::get_number_of_aces() const { return number_of_aces; }
	const int Player::get_total_point() const { return total_point; }

	void Player::change_total_point() {
		total_point = total_point - 10;
		--number_of_aces;
	}

	void Player::choose_card(std::vector<Card> &deck) {
		Card cur_card = deck.back();
		cards.push_back(cur_card);
		deck.erase(deck.end() - 1);
		total_point += get_card_value(cur_card);
		if (cur_card.rank == CardRanks::rank_ace) {
			++number_of_aces;
		}
	}

	Dealer::Dealer(std::vector<Card>& deck) {
		choose_card(deck);
	}

	Client::Client(std::vector<Card>& deck) {
		choose_card(deck);
		choose_card(deck);
	}

}  // namespace blackjack
