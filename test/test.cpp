#include"../card.hpp"
#include<iostream>
#include<vector>

int main(int argc, char const *argv[])
{
    // vector<vector<int>> a;
    // for(int  i = 0; i < 5; i ++) {
    //     a.push_back({2});
    // }
    // for(vector<int> x:a) {
    //     cout << x[0] << endl;
    // }

    // int cardData[15] = {};
    // cardData[11] = 3;
    // cardData[10] = 2;
    // cardData[9] = 1;

    // int one_hot[15] = {0};
    // vector<int> cardData = {15, 3, 8, 7, 7, 7};
    // get_one_hot_respresentation(one_hot, cardData, false);
    // for(int i = 0; i < 15; i++) {
    //     cout << one_hot[i] << endl;
    // }

    int cardData[15] = {};
    cardData[11] = 3;
    cardData[10] = 2;
    cardData[9] = 1;
    auto all_actions = get_all_actions(cardData);
    for(CardGroup one_action:all_actions) {
        vector<int> cvt = one_card_group2vector(one_action);
        for(int c:cvt) cout << c << " ";
        float value = get_card_group_value(one_action);
        cout << ": " << value << endl;
    }
    // CardGroup one_action = all_actions[4];
    // vector<int> cvt = one_card_group2vector(one_action);
    // for(int c:cvt) cout << c << endl;

    // int count = 0;
    // auto all_actions = get_all_actions(cardData);
    // vector<vector<int>> a = CardGroup2matrix(all_actions);
    // for(vector<int> b:a) {
    //     for(int c:b) {
    //         cout << c << endl;
    //     }
    //     cout << endl;
    // }

    // for(int i = 0; i < 15; i++) {
    //     cout << cardData[i] << endl;
    // }
    return 0;
}

float get_card_group_value(CardGroup card_group) {
    vector<int> cards = one_card_group2vector(card_group);
    Category category = card_group._category;
    float value = 0.0f;
    // empty
    if(category == Category(0)) value = 0;
    // single
    else if(category == Category(1)) {
        assert(cards.size() == 1);
        value = cards[0] * 0.1;
    } 
    // double 
    else if(category == Category(2)) {
        assert(cards.size() == 2);
        value = cards[0] * 0.2;
    } 
    // triple
    else if(category == Category(3)) {
        assert(cards.size() == 3);
        value = cards[0] * 0.3;
    } 
    // quatric
    else if(category == Category(4)) {
        assert(cards.size() == 4);
        value = cards[0] * 3;
    } 
    // three one
    else if(category == Category(5)) {
        assert(cards.size() == 4);
        int main_card, kicker;
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n == 1) kicker = card;
            else main_card = card;
        }
        value = main_card * 1 - kicker * 0.1;
    }
    // three two
    else if(category == Category(6)) {
        assert(cards.size() == 5);
        int main_card, kicker;
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n == 2) kicker = card;
            else main_card = card;
        }
        value = main_card * 1 - kicker * 0.1;
    }
    // single line
    else if(category == Category(7)) {
        assert(cards.size() >= 5);
        for(int card:cards) value += card * 0.2;
    }
    // double line
    else if(category == Category(8)) {
        assert(cards.size() >= 6);
        for(int card:cards) value += card * 0.2;
    }
    // triple line
    else if(category == Category(9)) {
        assert(cards.size() == 6);
        for(int card:cards) value += card * 0.2;
    }
    // three one line
    else if(category == Category(10)) {
        assert(cards.size() == 8);
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n <= 2) value += -0.1 * card;
            else value += 0.3 * card;
        }
    }
    // three two line 
    else if(category == Category(11)) {
        assert(cards.size() == 10);
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n <= 2) value += -0.1 * card;
            else value += 0.3 * card;
        }
    }
    // big band
    else if(category == Category(12)) value = 5;
    // four take one
    else if(category == Category(13)) {
        assert(cards.size() == 5);
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n == 1) value += -0.1 * card;
            else value += 0.1 * card;
        }
    }
    // take take two
    else if(category == Category(14)) {
        assert(cards.size() == 6);
        for(int card:cards) {
            int count_n = count(cards.begin(), cards.end(), card);
            if(count_n == 1) value += -0.1 * card;
            else value += 0.1 * card;
        }
    }
    return value;
} 

vector<int> one_card_group2vector(CardGroup card_group) {
    vector<int> vct;
    vector<Card> cg_cards = card_group._cards;
    for(Card cd:cg_cards) {
            vct.push_back((int) cd);
        }
    return vct;
}

void get_one_hot_respresentation(int one_hot[], vector<int> hand_card_data, bool zero_start) {
    for(int idx = 0; idx < 15; idx ++) {
        int new_idx = idx;
        if(!zero_start) new_idx = idx + 3;
        for(int card:hand_card_data) {
            if(new_idx == card) one_hot[idx] += 1;
        }
    }
    return;
}

// here cardData is a one hot representation of current hand data
vector<CardGroup> get_all_actions(int cardData[]) {
	vector<CardGroup> actions;
	actions.push_back(CardGroup({}, Category::EMPTY, 0));
	for (int i = 0; i < 15; i++)
	{
        if(cardData[i] >= 1) actions.push_back(CardGroup({ Card(i) }, Category::SINGLE, i));
	}
	for (int i = 0; i < 13; i++)
	{
		if(cardData[i] >= 2) actions.push_back(CardGroup({ Card(i), Card(i) }, Category::DOUBLE, i));
	}
	for (int i = 0; i < 13; i++)
	{
		if(cardData[i] >= 3) actions.push_back(CardGroup({ Card(i), Card(i), Card(i) }, Category::TRIPLE, i));
	}
	for (int i = 0; i < 13; i++)
	{
        if(cardData[i] == 4) {
            vector<Card> main_cards = { Card(i), Card(i), Card(i), Card(i) };
            actions.push_back(CardGroup(main_cards, Category::QUADRIC, i));
            vector<vector<Card>> kickers = { {} };
            get_kickers(main_cards, true, 2, kickers, cardData);
            for (const auto &kicker : kickers)
            {
                auto cards_kickers = main_cards;
                cards_kickers.insert(cards_kickers.end(), kicker.begin(), kicker.end());
                actions.push_back(CardGroup(cards_kickers, Category::FOUR_TAKE_ONE, i));
            }
            kickers.clear();
            kickers.push_back({});
            get_kickers(main_cards, false, 2, kickers, cardData);
            for (const auto &kicker : kickers)
            {
                auto cards_kickers = main_cards;
                cards_kickers.insert(cards_kickers.end(), kicker.begin(), kicker.end());
                actions.push_back(CardGroup(cards_kickers, Category::FOUR_TAKE_TWO, i));
            }
        }
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i != j && cardData[i] >= 3 && cardData[j] >= 1) {
				actions.push_back(CardGroup({ Card(i), Card(i), Card(i), Card(j) }, Category::THREE_ONE, i));
				if (j < 13 && cardData[j] >= 2)
				{
					actions.push_back(CardGroup({ Card(i), Card(i), Card(i), Card(j), Card(j) }, Category::THREE_TWO, i));
				}
			}
		}
	}
	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = i + 5; j < 13; j++)
		{
            bool stop_flag = false;
            for(size_t l = i; l < j; l++) {
                if(cardData[l] == 0) stop_flag = true;
            }
            if(stop_flag) break;
			vector<Card> cards;
			for (size_t k = i; k < j; k++)
			{
				cards.push_back(Card(k));
			}
			assert(cards.size() >= 5);
			actions.push_back(CardGroup(cards, Category::SINGLE_LINE, i, cards.size()));
		}
		for (size_t j = i + 3; j < 13; j++)
		{
            bool stop_flag = false;
            for(size_t l = i; l < j; l++) {
                if(cardData[l] <= 1) stop_flag = true;
            }
            if(stop_flag) break;
			vector<Card> cards;
			for (size_t k = i; k < j; k++)
			{
				cards.push_back(Card(k));
				cards.push_back(Card(k));
			}
			assert(cards.size() >= 6);
			if (cards.size() <= 20)
			{
				actions.push_back(CardGroup(cards, Category::DOUBLE_LINE, i, cards.size() / 2));
			}
		}
		for (size_t j = i + 2; j < 13; j++)
		{
            bool stop_flag = false;
            for(size_t l = i; l < j; l++) {
                if(cardData[l] <= 2) stop_flag = true;
            }
            if(stop_flag) break;
			vector<Card> cards;
			for (size_t k = i; k < j; k++)
			{
				cards.push_back(Card(k));
				cards.push_back(Card(k));
				cards.push_back(Card(k));
			}
			assert(cards.size() >= 6);
			if (cards.size() <= 20)
			{
				actions.push_back(CardGroup(cards, Category::TRIPLE_LINE, i, cards.size() / 3));
			}
			size_t len = cards.size() / 3;
			vector<vector<Card>> kickers = { {} };
			get_kickers(cards, true, len, kickers, cardData);
			for (const auto &kicker : kickers)
			{
				/*std::copy(kicker.begin(), kicker.end(), std::ostream_iterator<Card>(cout));
				cout << endl;*/
				auto cards_kickers = cards;
				cards_kickers.insert(cards_kickers.end(), kicker.begin(), kicker.end());
				if (cards_kickers.size() <= 20)
				{
					actions.push_back(CardGroup(cards_kickers, Category::THREE_ONE_LINE, i, len));
				}
			}
			if (len < 5)
			{
				kickers.clear();
				kickers.push_back({});
				get_kickers(cards, false, len, kickers, cardData);
				for (const auto &kicker : kickers)
				{
					auto cards_kickers = cards;
					cards_kickers.insert(cards_kickers.end(), kicker.begin(), kicker.end());
					if (cards_kickers.size() <= 20)
					{
						actions.push_back(CardGroup(cards_kickers, Category::THREE_TWO_LINE, i, len));
					}
				}
			}
		}
	}
	if(cardData[13] != 0 && cardData[14] != 0) actions.push_back(CardGroup({ Card(13), Card(14) }, Category::BIGBANG, 100));
	return actions;
}

void get_kickers(const vector<Card> main_cards, bool single, int len, vector<vector<Card>> &kickers, int cardData[]) {
	if (len == 0)
	{
		return;
	}
	vector<vector<Card>> result;
	for (auto &kicker : kickers) {
		for (size_t i = (kicker.empty() ? 0 : static_cast<int>(kicker.back()) + 1); i < (single ? 15 : 13); i++)
		{
			vector<Card> tmp = kicker;
			if (find(main_cards.begin(), main_cards.end(), Card(i)) == main_cards.end() && cardData[i] >= 1)
			{
                tmp.push_back(Card(i));
                if (!single && cardData[i] >= 2)
                {
                    tmp.push_back(Card(i));
                }
                if (!(tmp.size() == 2 && static_cast<int>(tmp[0]) + static_cast<int>(tmp[1]) == 13 + 14))
                {
                    result.push_back(tmp);
                }           	
			}
		}
	}
	kickers = result;
	get_kickers(main_cards, single, len - 1, kickers, cardData);
}

vector<vector<int>> CardGroup2matrix(vector<CardGroup> card_group) {
    vector<vector<int>> card_group_matrix;
    vector<int> one_row; 
    for(CardGroup cg:card_group) {
        vector<Card> cg_cards = cg._cards;
        for(Card cd:cg_cards) {
            one_row.push_back((int) cd);
        }
        card_group_matrix.push_back(one_row);
        one_row.clear();
    }
    return card_group_matrix;
}