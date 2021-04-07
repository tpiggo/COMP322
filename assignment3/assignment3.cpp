#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

/**
 * Name: Timothy Piggott
 * Date: March 13th 2021
 * Student ID: 260855765
 * 
 **/ 
enum Rank{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum Type{CLUBS, DIAMONDS, HEARTS, SPADES};

class Card 
{
    public:
        Card(Rank r, Type t)
        {
            this->rank = r;
            this->type = t;
        };

        int getValue(bool isOne)
        {
            switch(rank)
            {
                case JACK:
                    return 10;
                case QUEEN:
                    return 10;
                case KING:
                    return 10;
                case ACE:
                    if (isOne)
                    {
                        return 1;
                    }
                    return 11;
                default:
                    return this->rank;
            }
        };

        void displayCard()
        {
            string aString = "";
            switch(rank)
            {
                case JACK:
                    aString.append("J");
                    break;
                case QUEEN:
                    aString.append("Q");
                    break;
                case KING:
                    aString.append("K");
                    break;
                default:
                    aString.append(to_string(rank));
                    break;
            }
            switch(type)
            {
                case CLUBS:
                    aString.append("C");
                    break;
                case DIAMONDS:
                    aString.append("D");
                    break;
                case HEARTS:
                    aString.append("H");
                    break;
                case SPADES:
                    aString.append("S");
                    break;
            }
            cout << aString;
        };

    private:
        Rank rank;
        Type type;
};

class Hand
{
    public:
        Hand(){};

        ~Hand()
        {
            this->hand.clear();
        };

        void add(Card *pCard)
        {
            this->hand.push_back(pCard);
        };
        
        void clear()
        {
            this->hand.clear();
        };

        int getTotal();

        void printHand()
        {
            for (Card *aCard: hand)
            {
                aCard->displayCard();
                cout << " ";
            }
            cout << "[" << getTotal() << "]" << endl;
        }

    private:
        vector<Card*> hand;
};

int Hand::getTotal()
{
    int tot = 0;
    bool hasAce = false;
    int firstAcePos = -1;
    for (int i = 0; i < hand.size(); i++)
    {
        if (firstAcePos < 0 && hand.at(i)->getValue(false) == 11)
        {
            firstAcePos = i;
        }
        else 
        {
            tot += hand.at(i)->getValue(firstAcePos < 0);
        }
    }

    // Enforcing the rules here.
    if (tot + 11 > 21 && firstAcePos >= 0)
    {
        tot += hand.at(firstAcePos)->getValue(true);
    }

    return tot;
}

class Deck 
{
    public:
        Deck()
        {
            auto seed = chrono::system_clock::now().time_since_epoch().count();
            generator = std::default_random_engine{seed};
        }

        ~Deck()
        {
            for (Card *c: aDeck)
            {
                delete c;
            }
            aDeck.clear();
        }

        void printDeck()
        {
            int i = 0;
            for (Card *aCard: aDeck)
            {
                aCard->displayCard();
                if (aCard != aDeck.back())
                {
                    cout << ", ";
                }
                i++;
            }
            cout << endl;
            cout << "Size is " << aDeck.size() << endl;    
        }

        void populate()
        {
            for (int i  = 0; i < 4; i++)
            {
                for (int j = 1; j < 14; j++)
                {
                    Card *aCard = new Card((Rank)j, (Type)i);
                    aDeck.push_back(aCard);
                }
            }
        }

        void shuffle()
        {
            std::shuffle(aDeck.begin(), aDeck.end(), generator);
        }

        void deal(Hand &hand)
        {
            // assign it to the given hand, 
            hand.add(aDeck[0]);
            auto top = aDeck.begin();
            // take the card off the top and push it into the back.
            aDeck.erase(top);
            aDeck.push_back(*top);
        }
    private:
        vector<Card *> aDeck;
        std::default_random_engine generator;
};

/**
 * NOTE: Players do not INHERIT from hand as a player is NOT a hand. They have a hand.
 */ 
class AbstractPlayer
{   
    public:
        virtual bool isDrawing() const = 0;
        bool isBusted()
        {
            return this->aHand.getTotal() > 21;
        }
    protected:
        Hand aHand;
};

class ComputerPlayer: public AbstractPlayer
{
    public:
        bool isDrawing() const
        {
            if(constHand().getTotal() <= 16)
            {
                return true;
            }
            return false;
        }
        
        void handInfo()
        {
            cout << "Casino: "; 
            aHand.printHand();
        }

        Hand& getHand()
        {
            return aHand;
        }
    private:
        Hand constHand() const
        {
            return aHand;
        }
};

class HumanPlayer: public AbstractPlayer
{
    public:
        bool isDrawing() const
        {
            char answer = 'y';
            cout << "Do you want to draw? (y/n):";
            cin >> answer;
            return answer == 'y';
        }
        void announce(ComputerPlayer casino)
        {
            if (casino.isBusted() && !this->isBusted())
                cout << "Player wins!" << endl;
            else if (!casino.isBusted() && this->isBusted())
                cout << "Casino wins!" << endl;
            else 
            {
                if (casino.getHand().getTotal() > this->getHand().getTotal())
                {
                    cout << "Casino wins!" << endl;
                } 
                else if (casino.getHand().getTotal() < this->getHand().getTotal()) 
                {
                    cout << "Player wins!" << endl;
                } 
                else
                {
                    cout << "Push: it was a draw" << endl;
                }
            }

        }

        void handInfo()
        {
            cout << "Player: "; 
            aHand.printHand();
        }

        Hand& getHand()
        {
            return aHand;
        }
    private:
        char answer = 'y';
};

class BlackJackGame
{
    public:
        BlackJackGame()
        {
            aDeck.populate();
        }

        void play();
    private:
        Deck aDeck;
        HumanPlayer human;
        ComputerPlayer m_casino;
};

void BlackJackGame::play()
{
    aDeck.shuffle();
    // Deal a card to the casino
    aDeck.deal(m_casino.getHand());
    // Deal 2 cards to the player
    aDeck.deal(human.getHand());
    aDeck.deal(human.getHand());
    m_casino.handInfo();
    human.handInfo();
    bool done[2] = {false, false};
    while (!done[0] || !done[1])
    {
        if (!done[0] && human.isDrawing())
        {
            aDeck.deal(human.getHand());
            human.handInfo();
            if (human.isBusted())
            {
                break;
            }
        }
        else if (!done[0])
        {
            done[0] = true;
        }

        // Next is the casinos turn.
        if (!done[1] && m_casino.isDrawing())
        {
            aDeck.deal(m_casino.getHand());
            m_casino.handInfo();
            if (m_casino.isBusted())
            {
                break;
            }
        }
        else if (!done[1])
        {
            done[1] = true;
        }
    }

    human.announce(m_casino);
    // Otherwise done! Clear the hands
    m_casino.getHand().clear();
    human.getHand().clear();
}

int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;
    BlackJackGame game;
    // The main loop of the game
    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        game.play();
        // Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
    }
    cout <<"Game over!";
    return 0;
}