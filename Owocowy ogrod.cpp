#include <iostream>


class TREE_CLASS;
class FRUIT_CLASS;
class GARDEN_CLASS;
class BRANCH_CLASS;
class FRUIT_CLASS;



class FRUIT_CLASS
{
private:
    unsigned int length;
    unsigned int weight;
    BRANCH_CLASS* branch;

    FRUIT_CLASS* next;
    FRUIT_CLASS* prev;

    

public:

    FRUIT_CLASS()
    {
        branch = NULL;
        weight = 0;
        length = 0;
    }
  

    FRUIT_CLASS(unsigned int length, BRANCH_CLASS* branch)
    {
        this->weight = 0;
        this->length = length;
        this->branch = branch;
        this->next = NULL;
        this->prev = NULL;

    }

    FRUIT_CLASS(const FRUIT_CLASS& obj)
    {
        this->length = obj.length;
        this->weight = obj.weight;
        this->branch = obj.branch;
        this->next = NULL;
        this->prev = NULL;
    }

    ~FRUIT_CLASS()
    {
        weight = 0;
        length = 0;
        branch = NULL;
    }

    FRUIT_CLASS* getNext()
    {
        return this->next;
    }

    FRUIT_CLASS* getPrev()
    {
        return this->prev;
    }

    void setBranch(BRANCH_CLASS* branch)
    {
        this->branch = branch;
    }

    void setNext(FRUIT_CLASS* fruit)
    {
        this->next = fruit;
    }

    void setPrev(FRUIT_CLASS* fruit)
    {
        this->prev = fruit;
    }

    unsigned int getLength()
    {
        return this->length;
    }

    unsigned int getWeight()
    {
        return this->weight;
    }

    void growthFruit()
    {
        weight += 1;
    }

    void fadeFruit()
    {
        if(weight > 0) weight -= 1;
    }

    void pluckFruit()
    {
        weight = 0;
    }

    BRANCH_CLASS* getBranchPointer()
    {
        return this->branch;
    }
};


class BRANCH_CLASS
{
private:
    unsigned int fruitCount;
    unsigned int length;
    unsigned int height;
    TREE_CLASS* treePtr;

    FRUIT_CLASS* first;
    FRUIT_CLASS* last;

    BRANCH_CLASS* next;
    BRANCH_CLASS* prev;


public:

    BRANCH_CLASS()
    {
        this->fruitCount = 0;
        this->length = 0;
        this->height = 0;
        this->treePtr = NULL;
        this->first = NULL;
        this->last = NULL;
        this->next = NULL;
        this->prev = NULL;
    }

    BRANCH_CLASS(unsigned int height, TREE_CLASS* tree)
    {
        this->height = height;
        this->treePtr = tree;
        this->length = 0;
        this->fruitCount = 0;
        this->treePtr = tree;
        this->first = NULL;
        this->last = NULL;
        this->prev = NULL;
        this->next = NULL;

    }

    BRANCH_CLASS(const BRANCH_CLASS& obj)
    {

        this->length = obj.length;
        this->fruitCount = 0;
        this->height = obj.height;
        treePtr = obj.treePtr;
        this->first = NULL;
        this->last = NULL;
        this->next = NULL;
        this->prev = NULL;


        FRUIT_CLASS* tmp = obj.first;

        while (tmp != NULL)
        {
            FRUIT_CLASS* newFruit = new FRUIT_CLASS(*tmp);
            newFruit->setBranch(this);
            addFruit(newFruit);
            tmp = tmp->getNext();
        }
    }

    ~BRANCH_CLASS()
    {
        height = 0;
        length = 0;
        fruitCount = 0;

        FRUIT_CLASS* tmp = first;
        while (tmp != NULL)
        {
            FRUIT_CLASS* tmp2 = tmp->getNext();
            delete tmp;
            tmp = tmp2;
        }
        
    }

    BRANCH_CLASS* getNext()
    {
        return this->next;
    }

    BRANCH_CLASS* getPrev()
    {
        return this->prev;
    }

    void setTreePtr(TREE_CLASS* tree)
    {
        this->treePtr = tree;
    }
    void setNext(BRANCH_CLASS* branch)
    {
        this->next = branch;
    }

    void setPrev(BRANCH_CLASS* branch)
    {
        this->prev = branch;
    }

    void setHeight(unsigned int height)
    {
        this->height = height;
    }

    unsigned int getFruitsTotal(void)
    {
        return this->fruitCount;
    }

    unsigned int getWeightsTotal(void)
    {
        FRUIT_CLASS* tmp = first;
        unsigned int sum = 0;

        while (tmp != NULL)
        {
            sum += tmp->getWeight();
            tmp = tmp->getNext();
        }

        return sum;

    }

    unsigned int getHeight(void)
    {
        return this->height;
    }

    unsigned int getLength(void)
    {
        return this->length;
    }

    void addFruit(FRUIT_CLASS* newFruit)
    {
        newFruit->setNext(NULL);

        if (first == NULL && last == NULL)
        {     
            first = newFruit;
            last = newFruit;
        }
        else
        {
            last->setNext(newFruit);
            newFruit->setPrev(last);
            last = newFruit;
        }
        fruitCount++;
       
    }

    void delFruit(FRUIT_CLASS* fruit)
    {
        if (first == NULL || fruit == NULL) return;
       
        if (first == last)
        {
            first = NULL;
            last = NULL;
            delete(fruit);
            fruitCount = 0;
            return;

        }

        if (fruit == first)
        {
            first = first->getNext();
            first->setPrev(NULL);
            delete(fruit);
            fruitCount--;
            return;
        }

        if (fruit == last)
        {
            last = last->getPrev();
            last->setNext(NULL);
            delete(fruit);
            fruitCount--;
            return;
        }

        FRUIT_CLASS* tmp1 = fruit->getPrev();
        FRUIT_CLASS* tmp2 = fruit->getNext();

        tmp1->setNext(tmp2);
        tmp2->setPrev(tmp1);
        delete(fruit);
        fruitCount--;
        return;


    }

    void growthBranch(void)
    {
        length += 1;

        FRUIT_CLASS* tmp = first;
 
        while (tmp != NULL)
        {
            tmp->growthFruit();
            tmp = tmp->getNext();
        }

        if (length != 0 && length % 2 == 0)
        {
            FRUIT_CLASS* newFruit = new FRUIT_CLASS(length, this);
            addFruit(newFruit);

        }
    }

    void fadeBranch(void)
    {
        if (length > 0)
        {
            length -= 1;

            FRUIT_CLASS* tmp = first;

            while (tmp != NULL)
            {
                tmp->fadeFruit();
                FRUIT_CLASS* tmp2 = tmp->getNext();
                if (tmp->getLength() > length) delFruit(tmp);
                tmp = tmp2;
            }
        }
    }

    void harvestBranch(unsigned int weight)
    {
        FRUIT_CLASS* tmp = first;

        while (tmp != NULL)
        {
            if (tmp->getWeight() >= weight) tmp->pluckFruit();
            
             tmp = tmp->getNext();
        }

    }

    void cutBranch(unsigned int cut)
    {
        length = cut;
     

        FRUIT_CLASS* tmp = last;

        while (tmp != NULL)
        {
            if (tmp->getLength() < length) break;
            FRUIT_CLASS* tmp2 = tmp->getPrev();
            if (tmp->getLength() > length) delFruit(tmp);
            
            tmp = tmp2;
        }

    }

    FRUIT_CLASS* getFruitPointer(unsigned int length)
    {
        FRUIT_CLASS* tmp = first;

        while (tmp != NULL)
        {
            if (tmp->getLength() == length) return tmp;

            tmp = tmp->getNext();
        }

        return NULL;
    }

    TREE_CLASS* getTreePointer()
    {
        return this->treePtr;

    }


};

class TREE_CLASS
{
private:
    unsigned int id;
    unsigned int countBranch;
    unsigned int height;
    TREE_CLASS* next;
    TREE_CLASS* prev;
    TREE_CLASS* treePtr;
    GARDEN_CLASS* gardenPtr;
    BRANCH_CLASS* first;
    BRANCH_CLASS* last;



public:

    TREE_CLASS(unsigned int id, GARDEN_CLASS* garden)
    {
        this->next = NULL;
        this->prev = NULL;
        this->first = NULL;
        this->last = NULL;
        this->id = id;
        this->countBranch = 0;
        this->height = 0;
        this->gardenPtr = garden;
    }


    TREE_CLASS(const TREE_CLASS& obj)
    {

      

        this->treePtr = this;
        this->next = NULL;
        this->prev = NULL;
        this->first = NULL;
        this->last = NULL;
        this->height = obj.height;
        this->gardenPtr = obj.gardenPtr;
        this->id = obj.id;
        this->countBranch = 0;

        BRANCH_CLASS* tmp = obj.first;

        while (tmp != NULL)
        {
            BRANCH_CLASS* newBranch = new BRANCH_CLASS(*tmp);
            newBranch->setTreePtr(this);
            addBranch(newBranch);
            tmp = tmp->getNext();
        }


    }

    TREE_CLASS()
    {
        this->first = NULL;
        this->last = NULL;
        this->next = NULL;
        this->prev = NULL;
        this->id = 0;
        this->countBranch = 0;
        this->height = 0;
        this->gardenPtr = NULL;
    }
   
    
      ~TREE_CLASS()
      {
          BRANCH_CLASS* tmp = first;
          while (tmp != NULL)
          {
              BRANCH_CLASS* tmp2 = tmp->getNext();
              delete tmp;
              tmp = tmp2;
          }
      }


    void setNext(TREE_CLASS* tree)
    {
        this->next = tree;
    }

    void setPrev(TREE_CLASS* tree)
    {
        this->prev = tree;
    }

    TREE_CLASS* getPrev()
    {
        return prev;
    }

    TREE_CLASS* getNext()
    {
        return next;
    }

    void setTreePtr(TREE_CLASS* tree)
    {
        this->treePtr = tree;
    }

    void setId(unsigned int id)
    {
        this->id = id;
    }

    void setGarden(GARDEN_CLASS* garden)
    {
        this->gardenPtr = garden;
    }

    unsigned int getBranchesTotal(void)
    {
        return this->countBranch;
    }

    unsigned int getFruitsTotal(void)
    {
        BRANCH_CLASS* tmp = first;
        unsigned int sum = 0;
        while (tmp != NULL)
        {
            sum += tmp->getFruitsTotal();
            tmp = tmp->getNext();
        }

        return sum;
    }

    unsigned int getWeightsTotal(void)
    {
        BRANCH_CLASS* tmp = first;
        unsigned int sum = 0;
        while (tmp != NULL)
        {
            sum += tmp->getWeightsTotal();
            tmp = tmp->getNext();
        }

        return sum;

    }

    unsigned int getNumber(void)
    {
        return this->id;
    }

    unsigned int getHeight(void)
    {
        return this->height;
    }

    void addBranch(BRANCH_CLASS* newBranch)
    {
        newBranch->setNext(NULL);

        if (first == NULL && last == NULL)
        {
            first = newBranch;
            last = newBranch;
        }
        else
        {
            last->setNext(newBranch);
            newBranch->setPrev(last);
            last = newBranch;
        }
        countBranch++;
    }

    void growthTree(void)
    {
        this->height += 1;

        BRANCH_CLASS* tmp = first;
        while (tmp != NULL)
        {
            tmp->growthBranch();
            tmp = tmp->getNext();
        }

        if (height != 0 && height % 3 == 0)
        {
            BRANCH_CLASS* newBranch = new BRANCH_CLASS(height, this);
            addBranch(newBranch);

        }

    }

    void deleteBranch(BRANCH_CLASS* branch)
    {

        if (countBranch > 0)
        {
            if (branch == NULL) return;


            if (branch == first && branch == last)
            {
                first = NULL;
                last = NULL;
                delete(branch);
                countBranch = 0;
                return;
            }

            if (branch == first)
            {
                first = first->getNext();
                first->setPrev(NULL);
                delete(branch);
                countBranch--;
                return;
            }

            if (branch == last)
            {
                last = last->getPrev();
                last->setNext(NULL);
                delete(branch);
                countBranch--;
                return;
            }


            BRANCH_CLASS* tmp1 = branch->getPrev();
            BRANCH_CLASS* tmp2 = branch->getNext();

            tmp1->setNext(tmp2);
            tmp2->setPrev(tmp1);
            delete(branch);
            countBranch--;
            return;
        }


        countBranch--;
        delete branch;
    }

    void fadeTree(void)
    {
        if (height > 0)
        {
            height -= 1;


            BRANCH_CLASS* tmp = first;
            while (tmp != NULL)
            {
                tmp->fadeBranch();


                BRANCH_CLASS* tmp2 = tmp->getNext();

                if (tmp->getHeight() > height)
                {
                    deleteBranch(tmp);
                }
                tmp = tmp2;
            }
        }
    }

    void harvestTree(unsigned int weight)
    {
        BRANCH_CLASS* tmp = first;
        while (tmp != NULL)
        {
            tmp->harvestBranch(weight);
            tmp = tmp->getNext();
        }
    }

    void cutTree(unsigned int cut)
    {
        height = cut;

        BRANCH_CLASS* tmp = last;
        while (tmp != NULL)
        {

            if (tmp->getHeight() < height) break;
            BRANCH_CLASS* tmp2 = tmp->getPrev();
            if (tmp->getHeight() > height) deleteBranch(tmp);
            tmp = tmp2;
        }
          

        
    }

    void cloneBranch(BRANCH_CLASS* obj)
    {
       
       
        BRANCH_CLASS* tmp = first;

        while (tmp != NULL)
        {
          
            if (tmp->getLength() == 0)
            {
                BRANCH_CLASS* branch = new BRANCH_CLASS(*obj);
                branch->setTreePtr(this);
               
                if (tmp == first && tmp == last)
                {
                    branch->setHeight(first->getHeight());
                    delete(tmp);
                    first = branch;
                    last = branch;
                    return;
                }

                if (tmp == first)
                {
                    branch->setHeight(first->getHeight());
        
                     branch->setNext(first->getNext());
                     first->getNext()->setPrev(branch);
                     delete(tmp);
                     first = branch;
                    return;
                }

                if (tmp == last)
                {
                    branch->setHeight(last->getHeight());
                    last->getPrev()->setNext(branch);
                    branch->setPrev(last->getPrev());
                    delete(tmp);
                    last = branch;
                    return;
                }

                branch->setHeight(tmp->getHeight());
                tmp->getPrev()->setNext(branch);
                tmp->getNext()->setPrev(branch);
                branch->setNext(tmp->getNext());
                branch->setPrev(tmp->getPrev());
                delete(tmp);
                tmp = branch;
                return;
            }

            tmp = tmp->getNext();
        }
        
    }

    GARDEN_CLASS* getGardenPointer(void)
    {
        return this->gardenPtr;
    }

    BRANCH_CLASS* getBranchPointer(unsigned int height)
    {
        BRANCH_CLASS* tmp = first;
        while (tmp != NULL)
        {
            if (tmp->getHeight() == height) return tmp;
            tmp = tmp->getNext();
        }
        return NULL;

    }

};


class GARDEN_CLASS
{
private:
    unsigned int size;
    unsigned int gaps;
    TREE_CLASS* first;
    TREE_CLASS* last;


public:

    GARDEN_CLASS()
    {
        size = 0;
        gaps = 0;
        first = NULL;
        last = NULL;
    }

    ~GARDEN_CLASS()
    {
        TREE_CLASS* tmp = first;
        while (tmp != NULL)
        {
            TREE_CLASS* tmp2 = tmp->getNext();
            delete tmp;
            tmp = tmp2;
        }
    }


    unsigned int getTreesTotal(void)
    {
        return this->size;
    }

    unsigned int getBranchesTotal(void)
    {
        TREE_CLASS* tmp = first;
        unsigned int sum = 0;

        while (tmp != NULL)
        {
            sum += tmp->getBranchesTotal();
            tmp = tmp->getNext();
        }

        return sum;
    }

    unsigned int getFruitsTotal(void)
    {
        TREE_CLASS* tmp = first;
        unsigned int sum = 0;

        while (tmp != NULL)
        {
            sum += tmp->getFruitsTotal();
            tmp = tmp->getNext();
        }

        return sum;
    }

    unsigned int getWeightsTotal(void)
    {
        TREE_CLASS* tmp = first;
        unsigned int sum = 0;

        while (tmp != NULL)
        {
            sum += tmp->getWeightsTotal();
            tmp = tmp->getNext();
        }

        return sum;

    }


    void plantTree(void)
    {

        if (gaps == 0 && last != NULL)
        {
            size++;
            TREE_CLASS* newTree = new TREE_CLASS(last->getNumber() + 1, this);
            last->setNext(newTree);
            newTree->setPrev(last);
            last = newTree;
            return;
        }



        size++;

        TREE_CLASS* tmp = first;
        TREE_CLASS* tmp2 = NULL;
        unsigned int i = 0;
        while (tmp != NULL)
        {
            if (tmp->getNumber() != i)
            {
                gaps--;
                break;
            }
            i++;
            tmp = tmp->getNext();
        }




        TREE_CLASS* newTree = new TREE_CLASS(i, this);



        if (first == NULL && last == NULL)
        {
            first = newTree;
            last = newTree;
            return;
        }

        if (i < first->getNumber())
        {
            newTree->setNext(first);
            first->setPrev(newTree);
            first = newTree;
            return;
        }
        if (first == last && i > last->getNumber())
        {
            last = newTree;
            first->setNext(newTree);
            newTree->setPrev(first);

            // newTree->setNext(last);
          //   last->setPrev(newTree);
            return;
        }
        /*
        if (first == last)
        {
            first = newTree;
            newTree->setNext(last);
            last->setPrev(newTree);
            return;
        }
        */

        if (tmp == NULL)
        {
            last->setNext(newTree);
            newTree->setPrev(last);
            last = newTree;
            return;
        }



        tmp2 = tmp->getPrev();

        tmp2->setNext(newTree);
        newTree->setPrev(tmp2);

        tmp->setPrev(newTree);
        newTree->setNext(tmp);


    }

    void extractTree(unsigned int id)
    {

        if (size > 0)
        {
            TREE_CLASS* tree = getTreePointer(id);


            if (first == NULL || tree == NULL) return;

            if (first == last)
            {
                gaps = 0;
                delete(tree);
                first = NULL;
                last = NULL;
                size = 0;
                return;
            }



            if (tree == first)
            {

                gaps++;
                first = tree->getNext();
                first->setPrev(NULL);
                delete(tree);
                size--;
                return;

            }


            if (tree == last)
            {
                last = tree->getPrev();
                last->setNext(NULL);
                delete(tree);
                size--;
                return;
            }


            gaps++;


            TREE_CLASS* tmp1 = tree->getPrev();
            TREE_CLASS* tmp2 = tree->getNext();


            tmp1->setNext(tmp2);
            tmp2->setPrev(tmp1);
            delete(tree);
            size--;

        }

    }

    void growthGarden(void)
    {
        TREE_CLASS* tmp = first;

        while (tmp != NULL)
        {

            tmp->growthTree();
            tmp = tmp->getNext();
        }

    }

    void fadeGarden(void)
    {
        if (size > 0)
        {
            TREE_CLASS* tmp = first;
            while (tmp != NULL)
            {
                tmp->fadeTree();
                tmp = tmp->getNext();
            }

        }


    }

    void harvestGarden(unsigned int weight)
    {
        TREE_CLASS* tmp = first;
        while (tmp != NULL)
        {
            tmp->harvestTree(weight);
            tmp = tmp->getNext();
        }

    }

    TREE_CLASS* getTreePointer(unsigned int id)
    {
        if (last != NULL && id > last->getNumber()) return NULL;

     

        if (last->getNumber() == id) return last;



        TREE_CLASS* tmp = first;
        while (tmp != NULL)
        {
            if (tmp->getNumber() == id) return tmp;
            tmp = tmp->getNext();
        }


        return NULL;
    }

    void cloneTree(unsigned int id)
    {

        TREE_CLASS* tree2Copy = getTreePointer(id);

        if (tree2Copy == NULL) return;

        if (gaps == 0 && last != NULL)
        {
            size++;
            TREE_CLASS* newTree = new TREE_CLASS(*tree2Copy);
            newTree->setId(last->getNumber() + 1);
            last->setNext(newTree);
            newTree->setPrev(last);
            last = newTree;
            return;
        }
        
        size++;
        TREE_CLASS* tmp = first;
        TREE_CLASS* tmp2 = NULL;
        unsigned int i = 0;
        while (tmp != NULL)
        {
            if (tmp->getNumber() != i)
            {
                gaps--;
                break;
            }
            i++;
            tmp = tmp->getNext();
        }

        TREE_CLASS* newTree = new TREE_CLASS(*tree2Copy);
        newTree->setId(i);
        newTree->setGarden(this);

        if (first == NULL && last == NULL)
        {
            first = newTree;
            last = newTree;
            return;
        }
        if (i < first->getNumber())
        {
            newTree->setNext(first);
            first->setPrev(newTree);
            first = newTree;
            return;
        }
        if (first == last && i > last->getNumber())
        {
            last = newTree;
            first->setNext(newTree);
            newTree->setPrev(first);

           
            return;
        }
     
        if (tmp == NULL)
        {
            last->setNext(newTree);
            newTree->setPrev(last);
            last = newTree;
            return;
        }



        tmp2 = tmp->getPrev();

        tmp2->setNext(newTree);
        newTree->setPrev(tmp2);

        tmp->setPrev(newTree);
        newTree->setNext(tmp);
        

    }


};
