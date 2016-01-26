#pragma once
#include <list>
#include "Map.h"
#include "Hand.h"

struct Deck{
	std::list<int> deck;
	Deck(std::list<int> id){
		//use id...
		deck.push_front(0x00);
		deck.push_front(0x01);
		deck.push_front(0x02);
		deck.push_front(0x10);
		deck.push_front(0x11);
		deck.push_front(0x12);
		deck.push_front(0x20);
		deck.push_front(0x21);
		deck.push_front(0x22);
		deck.push_front(0x30);
	}
	static void affect(int id){
		
	}
};