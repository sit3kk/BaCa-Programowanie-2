//Konrad Sitek

#include <iostream>
#include <string>


class PLAYER_CLASS
{
protected:

    unsigned int maxhp;
    unsigned int hp;
    unsigned int attack;
    unsigned int agility;

    friend class SQUAD_CLASS;
    friend class CAESAR_CLASS;

public:


    PLAYER_CLASS(unsigned int maxhp_, unsigned int hp_, unsigned int attack_, unsigned int agility_) : maxhp(maxhp_),hp(hp_),attack(attack_),agility(agility_) {}
    PLAYER_CLASS(){}


	virtual unsigned int getRemainingHealth() { return hp * 100 / maxhp; }

    virtual unsigned int getHP(){return hp;}

    virtual unsigned int getMaxHP(){return maxhp;}

	virtual unsigned int getDamage() { return attack; }


	virtual unsigned int getAgility() { return agility; }

    virtual std::string getId() {return "\0";}

    virtual unsigned int getDefense(){return 0;}

	virtual void takeDamage(unsigned int dmg)
	{
        if(dmg > hp) die();
        else
        {
            hp = hp - dmg;
            if(getRemainingHealth() == 0) die();
        }

	}

	virtual void applyWinnerReward()
	{
		agility += 2;
		attack += 2;
	}

	virtual void printParams()
	{
		std::cout << maxhp << ":" << getHP() << ":" <<getRemainingHealth()<<"%:"<< getDamage() << ":" << getAgility();
	}

	virtual void cure() { hp = maxhp; }

private:
	void die()
    {
        hp = 0;
    }

};

class CAESAR_CLASS
{

public:

    unsigned int judgeCounter;
    unsigned int attackCounter;

    CAESAR_CLASS() : judgeCounter(0),attackCounter(0) {}

    void judgeDeathOfLife(PLAYER_CLASS* player)
    {
        judgeCounter++;
        if (judgeCounter % 3 == 0  && attackCounter % 2 == 0) player->die();
    }

};

class ARENA_CLASS
{
    CAESAR_CLASS* caesar;


public:
    ARENA_CLASS(CAESAR_CLASS* c) : caesar(c) {}



    void fight(PLAYER_CLASS* player1, PLAYER_CLASS* player2)
    {


        if (player1->getRemainingHealth() == 0 || player2->getRemainingHealth() == 0) return;
        caesar->attackCounter = 0;

        if (player1->getAgility() < player2->getAgility())
        {
            PLAYER_CLASS* tmp = player1;
            player1 = player2;
            player2 = tmp;
        }

        player1->printParams();
        player2->printParams();


        for (int i = 0; i < 40; i++)
        {

            if (player1->getRemainingHealth() >= 10 && player2->getRemainingHealth() >= 10)
            {
                player2->takeDamage(player1->getDamage());
                player2->printParams();
                caesar->attackCounter++;

            }
            else break;

            if (player2->getRemainingHealth() >= 10)
            {
                player1->takeDamage(player2->getDamage());
                player1->printParams();
                caesar->attackCounter++;
            }
            else break;
        }


        if (player1->getRemainingHealth() > 0)
        {
            caesar->judgeDeathOfLife(player1);
            player1->printParams();
        }

        if (player2->getRemainingHealth() > 0)
        {
            caesar->judgeDeathOfLife(player2);
            player2->printParams();
        }

        if (player1->getRemainingHealth() > 0)
        {
            player1->applyWinnerReward();
            player1->cure();
        }

        if (player2->getRemainingHealth() > 0)
        {
            player2->applyWinnerReward();
            player2->cure();
        }


        player1->printParams();
        player2->printParams();

    }


};

class HUMAN_CLASS : public virtual PLAYER_CLASS
{
    std::string id;

protected:
    unsigned int defense;

public:
    HUMAN_CLASS(std::string id_) : PLAYER_CLASS(200, 200, 30, 10) , id(id_), defense(10) {}


    virtual void takeDamage(unsigned int damage)
    {
        unsigned int bonus = getAgility() + defense;


        if (damage > bonus) damage = damage - bonus;
        else damage = 0;

        PLAYER_CLASS::takeDamage(damage);
    }

    virtual std::string getId() {return id;}

    virtual unsigned int getDefense(){return defense;}


    virtual void printParams()
    {
        if (getRemainingHealth() > 0)
        {
            std::cout << id << ":";
            PLAYER_CLASS::printParams();
            std::cout << ":" << defense<<'\n';
        }
        else std::cout <<id<< ":R.I.P." << "\n";

    }

};

class BEAST_CLASS : public virtual PLAYER_CLASS
{
	std::string id;
public:
	BEAST_CLASS(std::string id_) : PLAYER_CLASS(150, 150, 40, 20), id(id_) {}

	virtual unsigned int getDamage()
	{
		if (getRemainingHealth() < 25) return attack * 2;

		return attack;
	}

    virtual std::string getId(){return id;}

    virtual void takeDamage(unsigned int damage)
    {
        unsigned int bonus = getAgility() / 2;

        if (damage > bonus) damage = damage - bonus;
        else damage = 0;

        PLAYER_CLASS::takeDamage(damage);

    }


	virtual void printParams()
	{
		if (getRemainingHealth() > 0)
		{
			std::cout << id << ":";
             PLAYER_CLASS::printParams();
			std::cout <<'\n';
		}
		else std::cout <<id<< ":R.I.P." << "\n";

	}

};

class BERSERKER_CLASS : virtual public HUMAN_CLASS, virtual public BEAST_CLASS
{
	std::string idHuman;
	std::string idBeast;

public:
    BERSERKER_CLASS(std::string idHuman, std::string idBeast) : PLAYER_CLASS(200, 200, 35, 5),HUMAN_CLASS(idHuman),BEAST_CLASS(idBeast) {defense = 15;}

	void takeDamage(unsigned int damage)
	{
        if(getRemainingHealth() >= 25 || getRemainingHealth() == 0) HUMAN_CLASS::takeDamage(damage);
        else BEAST_CLASS::takeDamage(damage);

	}

    std::string getId()
    {
        if(getRemainingHealth() >= 25 || getRemainingHealth() == 0) return HUMAN_CLASS::getId();

        return BEAST_CLASS::getId();
    }

	unsigned int getDamage()
	{
        if(getRemainingHealth() >= 25 || getRemainingHealth() == 0) return HUMAN_CLASS::getDamage();

        return BEAST_CLASS::getDamage();

	}

	unsigned int getAgility()
	{
        if(getRemainingHealth() >= 25 || getRemainingHealth() == 0) return HUMAN_CLASS::getAgility();

        return BEAST_CLASS::getAgility();
	}

	void printParams()
	{

        if(getRemainingHealth() >= 25 || getRemainingHealth() == 0) HUMAN_CLASS::printParams();
        else BEAST_CLASS::printParams();
	}
};

class Node
{
public:
    Node* next;
    PLAYER_CLASS* player;
    Node(PLAYER_CLASS* player_)
    {
        this->player = player_;
        next = NULL;

    }
};

void swap(Node* a, Node* b)
{
    PLAYER_CLASS* tmp = a->player;
    a->player = b->player;
    b->player = tmp;

}


class SLL
{
public:
    unsigned int size;
    Node* first;
    SLL()
    {
        first = NULL;
        size = 0;

    }

    ~SLL()
    {
        Node* tmp = first;
        while(tmp!=NULL)
        {
            Node* tmp2 = tmp->next;
            delete(tmp);
            tmp = tmp2;

        }
    }

    void push(PLAYER_CLASS* player)
    {
        Node* newNode = new Node(player);

        if(first == NULL) first = newNode;
        else
        {
            Node* tmp = first;
            while(tmp->next != NULL) tmp = tmp->next;
            tmp->next = newNode;
        }

        size++;


    }

    void clearTeam()
    {
        Node* tmp = first;

        if(size == 1 && tmp->player->getRemainingHealth() == 0)
        {
            delete(first);
            first = NULL;
            size = 0;
            return;
        }

        while(tmp != NULL)
        {
            if(tmp != NULL && tmp->player->getRemainingHealth() == 0 && tmp == first)
            {
                Node* tmp2 = first->next;
                delete(first);
                first = tmp2;
                size--;
                tmp = first;
            }

            if(tmp != NULL && tmp->next != NULL && tmp->next->player->getRemainingHealth() == 0)
            {
                Node*tmp2 = tmp->next->next;
                delete(tmp->next);
                tmp->next = tmp2;
                size--;
                tmp = first;
            }

            tmp = tmp->next;
        }

    }

    void sort()
    {
        Node* tmp = NULL;
        Node* index = NULL;


        if(first == NULL) return;
        else
        {

            for(tmp = first; tmp->next != NULL; tmp = tmp->next)
            {
                for(index = tmp->next; index != NULL ; index = index->next)
                {
                    if(tmp->player->getId().compare(index->player->getId()) > 0)
                    {
                        swap(tmp,index);
                    }
                    else if(tmp->player->getId() == index->player->getId())
                    {
                        if(tmp->player->getMaxHP() > index->player->getMaxHP())
                        {
                            swap(tmp,index);
                        }
                        else if(tmp->player->getMaxHP() == index->player->getMaxHP())
                        {
                            if(tmp->player->getHP() > index->player->getHP())
                            {
                                swap(tmp,index);
                            }
                            else if(tmp->player->getHP() == index->player->getHP())
                            {
                                if(tmp->player->getRemainingHealth() > index->player->getRemainingHealth())
                                {
                                    swap(tmp,index);
                                }
                                else if(tmp->player->getRemainingHealth() == index->player->getRemainingHealth())
                                {
                                    if(tmp->player->getDamage() > index->player->getDamage())
                                    {
                                        swap(tmp,index);
                                    }
                                    else if(tmp->player->getDamage() == index->player->getDamage())
                                    {
                                        if(tmp->player->getAgility() > index->player->getAgility())
                                        {
                                           swap(tmp,index);
                                        }
                                        else if(tmp->player->getAgility() == index->player->getAgility())
                                        {
                                            if(tmp->player->getDefense() > index->player->getDefense())
                                            {
                                                swap(tmp,index);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};



class SQUAD_CLASS : public PLAYER_CLASS
{
    std::string id;
    SLL list;


public:
SQUAD_CLASS(std::string id_)
{
    id = id_;
}


void addPlayer(PLAYER_CLASS* player)
{

    if(player->getRemainingHealth() > 0)
    {
        Node* tmp = list.first;

        while(tmp != NULL)
        {
            if(tmp->player == player) return;
            tmp = tmp->next;
        }
        list.push(player);
    }
}

    unsigned int getAgility()
    {
        Node* tmp = list.first;
        unsigned int min = tmp->player->getAgility();

        while(tmp != NULL)
        {
            if(tmp->player->getRemainingHealth() > 0 && tmp->player->getAgility() < min) min = tmp->player->getAgility();
            tmp = tmp->next;
        }

        return min;
    }

    unsigned int getRemainingHealth()
    {
        Node* tmp = list.first;
        unsigned int max = 0;
        while(tmp != NULL)
        {
            if(tmp->player->getRemainingHealth() > max) max = tmp->player->getRemainingHealth();
            tmp = tmp->next;
        }

        return max;
    }

    unsigned int getDamage()
    {
        Node* tmp = list.first;
        unsigned int sum = 0;
        while(tmp != NULL)
        {
            if(tmp->player->getRemainingHealth() > 0) sum += tmp->player->getDamage();
            tmp = tmp->next;
        }
        return sum;
    }


    void applyWinnerReward()
    {
        Node* tmp = list.first;
        while(tmp != NULL)
        {
            tmp->player->applyWinnerReward();
            tmp = tmp->next;
        }
    }

    void takeDamage(unsigned int damage)
    {
        if(list.size == 0) return;
        damage = damage / list.size;

        Node* prev = list.first;
        Node* tmp = list.first;
        while(tmp != NULL)
        {
            tmp->player->takeDamage(damage);
            tmp = tmp->next;
        }

        list.clearTeam();
    }



    void printParams()
    {

         list.clearTeam();
        if(getRemainingHealth() > 0)
        {
            std::cout<<id<<":"<<list.size<<":"<<getRemainingHealth()<<"%:"<<getDamage()<<":"<<getAgility()<<"\n";
            list.sort();
            Node* tmp = list.first;
            while(tmp != NULL)
            {
                tmp->player->printParams();
                tmp = tmp->next;
            }
        }
        else std::cout<<id<<":nemo"<<"\n";

    }

    void cure()
    {
        Node* tmp = list.first;
        while(tmp != NULL)
        {
            tmp->player->cure();
            tmp = tmp->next;
        }
    }

    void die()
    {
        Node* tmp = list.first;
        while(tmp != NULL)
        {
            tmp->player->die();
            tmp = tmp->next;
        }
        list.clearTeam();

    }
};