
#ifndef SRC_BLACKJACK_H
#define SRC_BLACKJACK_H
// header content

#include <array>
#include <vector>

namespace blackjack {
	enum class CardRanks {
		rank_2 = 2,
		rank_3,
		rank_4,
		rank_5,
		rand_6,
		rank_7,
		rank_8,
		rank_9,
		rank_10,
		rank_jack,
		rank_queen,
		rank_king,
		rank_ace,
		max_ranks
	};

	enum class CardSuits {
		suit_clubs,
		suit_diamonds,
		suit_hearts,
		suit_spades,
		max_suits
	};

	struct Card {
		blackjack::CardRanks rank;
		blackjack::CardSuits suit;
	};

	void print_card(const Card & card);
	void test_print_card();

	void print_deck(const std::vector<Card> &deck);
	void test_print_deck();

	void swap_cards(Card& card_1, Card& card_2);
	void test_swap_cards();

	void shuffle_deck(std::vector<Card> &deck);
	void test_shuffle_deck();

	int get_card_value(const Card card);
	void test_get_card_value();

	class Player {
	protected:
		std::vector<Card> cards;
		int total_point{ 0 };
		int number_of_aces{ 0 };
	public:
		Player();
		const std::vector<Card>& get_cards() const;
		const int get_number_of_aces() const;
		const int get_total_point() const;
		void change_total_point();
		void choose_card(std::vector<Card> &deck);
	};
	
	class Dealer : public Player {
	public:
		Dealer(std::vector<Card>& deck);
	};

	class Client : public Player {
	public:
		Client(std::vector<Card>& deck);
	};

}  // namespace blackjack

#endif  // SRC_BLACKJACK_H
