//Konrad Sitek
#include <iostream>
#include "memory_check.h"

struct Cord;
struct List;
struct Node;
struct IdCord;
typedef short IdBead;
struct Bead;


struct IdCord
{
	IdCord()
	{
		data1 = '0';
		data2 = '0';
		data3 = '0';
	}

	IdCord(const char* data_)
	{
		data1 = *(data_ + 0);
		data2 = *(data_ + 1);
		data3 = *(data_ + 2);
	}

	char data1;
	char data2;
	char data3;





	bool operator <(const IdCord& obj)
	{
		if (data1 != obj.data1) {
			return data1 < obj.data1;
		}
		else if (data2 != obj.data2) {
			return data2 < obj.data2;
		}
		else {
			return data3 < obj.data3;
		}
	}

	bool operator >(const IdCord& obj)
	{
		if (data1 != obj.data1) {
			return data1 > obj.data1;
		}
		else if (data2 != obj.data2) {
			return data2 > obj.data2;
		}
		else {
			return data3 > obj.data3;
		}
	}

	bool operator == (const IdCord& obj)
	{
		return
			data1 == obj.data1 &&
			data2 == obj.data2 &&
			data3 == obj.data3;
	}

	friend std::istream& operator >>(std::istream& in, IdCord& id)
	{
		in >> id.data1;
		in >> id.data2;
		in >> id.data3;
		return in;
	}

	friend std::ostream& operator <<(std::ostream& out, const IdCord& id)
	{
		return out << id.data1 << id.data2 << id.data3;
	}

};



struct Node
{
	Node()
	{

	}

	Node* prev;
	Bead* bead;
	Node* next;

};




struct Bead
{
	Bead()
	{
		size = 0;
		idBead = 000;
	}

	Bead(IdBead idBead_)
	{
		idBead = idBead_;
		size = 0;
	}

	~Bead()
	{
		Node* node;

		while (firstNode)
		{
			node = firstNode->next;
			if (firstNode != NULL) delete firstNode;
			firstNode = node;
		}
	}

	Bead* prev;
	IdBead idBead;
	IdCord idCord;
	Bead* next;


	bool exist;
	short size = 0;
	Node* firstNode = NULL;
	Node* node;
	Node* lastNode = NULL;



	void sort()
	{
		Node* current = NULL;
		Node* index = NULL;
		Bead* tmp;

		if (size == 0) return;
		else
		{
			for (current = firstNode; current->next != NULL; current = current->next)
			{
				for (index = current->next; index != NULL; index = index->next)
				{
					if (current->bead->idCord > index->bead->idCord || current->bead->idCord == index->bead->idCord)
					{
						if (current->bead->idBead > index->bead->idBead)
						{
							tmp = current->bead;
							current->bead = index->bead;
							index->bead = tmp;
						}
						
					}
				}
			}
		}
	}




	void link(Bead* linkBead)
	{
		if (linkBead != NULL)
		{
			node = new Node;
			node->bead = linkBead;
			if (lastNode) lastNode->next = node;
			node->next = NULL;
			node->prev = lastNode;
			lastNode = node;
			if (!firstNode) firstNode = lastNode;
			size++;

		}



	}



	Node* getNodeId(IdBead idBead_)
	{
		Node* walkNode = firstNode;
		while (walkNode != NULL)
		{
			if (walkNode->bead->idBead == idBead_) return walkNode;
			walkNode = walkNode->next;
		}
		return NULL;

	}

	


	Node* getNodeObj(IdCord idCord_)
	{
		Node* walkNode = firstNode;
		while (walkNode != NULL)
		{
			if (walkNode->bead->idCord == idCord_) return walkNode;
			walkNode = walkNode->next;
		}
		return NULL;
	}



	Node* unlink(Bead* unlinkBead)
	{
		Node* delNode = getNodeObj(unlinkBead->idCord);

		if (delNode->prev) delNode->prev->next = delNode->next;
		else firstNode = delNode->next;
		if (delNode->next) delNode->next->prev = delNode->prev;
		else lastNode = delNode->prev;

		if (delNode != NULL) delete delNode;
		size--;
	
		return NULL;

	}

	short lenght()
	{
		return size;
	}

	Node* delNodeFront()
	{
		Node* node;
		if (firstNode)
		{
			node = firstNode;
			firstNode = firstNode->next;
			if (!firstNode) lastNode = NULL;
			if(node!=NULL) delete node;
			size--;
			return node;
		}
		else return NULL;
	}


	void printNodeASC()
	{
		Node* node = firstNode;
		sort();
	

		if (size > 0)
		{

			if (!firstNode) {}
			else
			{
				node = firstNode;
				while (node)
				{
					if (node->bead->idBead >= 0 && node->bead->idBead <= 999 && (node->bead->idCord > "AAA" || node->bead->idCord == "AAA") && (node->bead->idCord < "ZZZ" || node->bead->idCord == "ZZZ"))
						std::cout << node->bead->idCord << " " << node->bead->idBead << " ";
					node = node->next;
				}
			}

		}
	
	}


	
};


struct Cord
{
	Cord()
	{
		size = 0;
		firstBead = NULL;
		lastBead = NULL;
		exist = true;
	}

	Cord(IdCord idCord_)
	{
		firstBead = NULL;
		lastBead = NULL;
		idCord = idCord_;
		size = 0;
		exist = true;
	}

	~Cord()
	{
		Bead* bead;

		while (firstBead)
		{
			bead = firstBead->next;
			if (firstBead != NULL) delete firstBead;
			firstBead = bead;
		}
	}


	Cord* prev;
	IdCord idCord;
	Cord* next;

	bool exist;
	short size;
	Bead* firstBead = NULL;
	Bead* bead;
	Bead* lastBead = NULL;

	void addBead(IdBead idBead_)
	{

		bead = new Bead(idBead_);
		bead->idCord = idCord;
		if (lastBead) lastBead->next = bead;
		bead->next = NULL;
		bead->prev = lastBead;
		lastBead = bead;
		if (!firstBead) firstBead = lastBead;
		size++;

	}

	void moveBead(Bead* bead)
	{
		bead->next = firstBead;
		bead->prev = NULL;
		if (firstBead) firstBead->prev = bead;
		firstBead = bead;
		if (!lastBead) lastBead = firstBead;
		size++;
	}


	void clearAfterMoveBead(Bead* moveBead)
	{
		Bead* bead;

		if (moveBead->prev) moveBead->prev->next = moveBead->next;
		else firstBead = moveBead->next;
		if (moveBead->next) moveBead->next->prev = moveBead->prev;
		else lastBead = moveBead->prev;
		size--;
	}




	short lenght()
	{
		return size;
	}


	void printASC()
	{

		Bead* bead;
		IdBead min;
		IdBead printed = 0;
		bool find;


		for (int i = 0; i < size; i++)
		{
			min = 1000;

			if (!firstBead) {}
			else
			{
				find = false;
				bead = firstBead;
				while (bead)
				{
					if (bead->idBead != NULL)
					{
						if (bead->idBead > printed)
						{
							if (bead->idBead < min)
							{
								min = bead->idBead;
								find = true;
							}
						}

					}

					bead = bead->next;
				}
			}

			if (find)
			{
				std::cout << min << " ";
				getBeadObj(min)->printNodeASC();

				std::cout << std::endl;
				printed = min;
			}

		}


	}

	Bead* getBeadObj(IdBead idBead_)
	{

		Bead* walkBead = firstBead;
		while (walkBead != NULL)
		{
			if (walkBead->idBead == idBead_) return walkBead;
			walkBead = walkBead->next;
		}
		return NULL;



	}




	Bead* delBeadFront()
	{
		Bead* bead;

		if (firstBead)
		{
			while (firstBead->lenght() != 0) firstBead->delNodeFront();
			bead = firstBead;
			firstBead = firstBead->next;
			if (!firstBead) lastBead = NULL;
			size--;
			if(bead!=NULL) delete bead;
			return NULL;

		}
		else return NULL;
	}


	Bead* delBead(Bead* delBead)
	{
		Bead* bead;

		while (delBead->lenght() != 0) delBead->delNodeFront();

		if (delBead->prev) delBead->prev->next = delBead->next;
		else firstBead = delBead->next;
		if (delBead->next) delBead->next->prev = delBead->prev;
		else lastBead = delBead->prev;
		if(delBead!=NULL) delete delBead;
		size--;
		return NULL;
	}


};




struct List
{
	List()
	{
		size = 0;
		firstCord = NULL;
		lastCord = NULL;
	}

	~List()
	{

		Cord* delCord = firstCord;

		while (size != 0)
		{
			Cord* saveCord = delCord->next;
			if(delCord!=NULL) delete delCord;
			size--;
			delCord = saveCord;
		}

	}

	Cord* firstCord = NULL;
	Cord* lastCord = NULL;
	short size;


	void moveBead(IdBead k, IdCord sS, IdCord dS)
	{
		getCordObj(dS)->moveBead(getCordObj(sS)->getBeadObj(k));
		getCordObj(sS)->clearAfterMoveBead(getCordObj(sS)->getBeadObj(k));

	}



	short lenght()
	{
		return size;
	}

	void delCordById(IdCord idCord_)
	{

		Cord* delCord = getCordObj(idCord_);

		while (getCordObj(idCord_)->lenght() != 0) getCordObj(idCord_)->delBeadFront();

		Cord* current = firstCord;
		Cord* tmp;

		while (current->next != NULL)
		{
			if (current->idCord == idCord_) break;
			current = current->next;
		}
		tmp = current->next;
		current->next = tmp->next;
		current->next->prev = current;
		delete tmp;
	}


	Cord* getCordObj(IdCord idCord_)
	{
		Cord* walkCord = firstCord;
		while (walkCord != NULL)
		{
			if (walkCord->idCord == idCord_) return walkCord;
			walkCord = walkCord->next;
		}
		return NULL;
	}


	void addCordBack(IdCord idCord_)
	{
		Cord* newCord = new Cord(idCord_);

		if (lastCord) lastCord->next = newCord;
		newCord->next = NULL;
		newCord->prev = lastCord;
		lastCord = newCord;
		if (!firstCord) firstCord = lastCord;
		size++;
	}


	void printASC()
	{

		Cord* cord;
		Cord* tmp = NULL;
		IdCord printed = "000";
		IdCord min;

		for (int i = 0; i < size; i++)
		{
			min = "}}}";

			if (!firstCord) {}
			else
			{
				cord = firstCord;
				while (cord)
				{
					if (cord->idCord > printed)
					{
						if (cord->idCord < min)
						{
							min = cord->idCord;
							tmp = cord;
						}
					}
					cord = cord->next;
				}
			}

			if (tmp->exist) std::cout << min << std::endl;
			getCordObj(min)->printASC();
			printed = min;


		}

	}




	Cord* delFront()
	{
		Cord* cord;

		if (firstCord)
		{
			cord = firstCord;
			firstCord = firstCord->next;
			if (!firstCord) lastCord = NULL;
			else firstCord->prev = NULL;
			if(cord!=NULL) delete cord;
			size--;
			return NULL;
		}

	}


};




void loop()
{
	char commandCode;
	char id1, id2, id3;

	IdCord dS, s, sn, sS;
	IdBead dK, k, kr, sK;
	List list;




	while (std::cin >> commandCode)
	{


		if (commandCode == 'S')
		{
			std::cin >> sn;
			list.addCordBack(sn);

		}
		else if (commandCode == 'B')
		{
			std::cin >> kr >> sn;
			list.getCordObj(sn)->addBead(kr);

		}
		else if (commandCode == 'L')
		{
			std::cin >> sK >> sS >> dK >> dS;

			if (list.getCordObj(dS) != NULL)
			{
				if (list.getCordObj(dS)->getBeadObj(dK) != NULL)
				{
					Bead* tmp = list.getCordObj(dS)->getBeadObj(dK);
					if (tmp != NULL) list.getCordObj(sS)->getBeadObj(sK)->link(tmp);
				}
			}

		}
		else if (commandCode == 'U')
		{
			std::cin >> sK >> sS >> dK >> dS;
			Bead* tmp = list.getCordObj(dS)->getBeadObj(dK);
			if (tmp != NULL) list.getCordObj(sS)->getBeadObj(sK)->unlink(tmp);

		}
		else if (commandCode == 'D')
		{
			std::cin >> k >> s;
			Bead* tmp = list.getCordObj(s)->getBeadObj(k);
			list.getCordObj(s)->delBead(tmp);
		}
		else if (commandCode == 'M')
		{
			std::cin >> k >> sS >> dS;

			Bead* tmp = list.getCordObj(sS)->getBeadObj(k);
			list.moveBead(k, sS, dS);
			list.getCordObj(sS)->clearAfterMoveBead(tmp);
		}
		else if (commandCode == 'R')
		{
			std::cin >> s;
			list.delCordById(s);
		}
		else if (commandCode == 'P')
		{
			list.printASC();

		}
		else if (commandCode == 'F')
		{
			while (list.lenght() != 0) list.delFront();

			break;
		}
	}

}



int main()
{

	loop();
	_MemoryCheck();
	return 0;

}
