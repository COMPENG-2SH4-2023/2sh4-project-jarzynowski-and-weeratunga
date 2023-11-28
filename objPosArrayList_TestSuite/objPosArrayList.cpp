#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];      //256 elements on the heap
    listSize = 0;                           //no valid elements in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;          //array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;                         //delete[] to call the destructor of all instances in the array
}                                           //otherwise only first element will be deleted, leading to leak

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //check if listSize is equal to arrayCapacity. If yes, at capacity, don't insert
    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);     //this will shuffle all the elements towards the tail
    }
    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{

}

void objPosArrayList::removeHead()
{
    
}

void objPosArrayList::removeTail()
{

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < listSize) 
    {
        returnPos = aList[index]; // Assign the objPos element at the specified index to returnPos
    }
    else
    {
        returnPos.setObjPos(-1, -1, ' '); // Default x-y coordinate (-1, -1) and symbol ' '
    }
}