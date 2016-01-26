struct Node{
	int x, y, f, g, h;
	Node* parent;
	Node(int x, int y, Node* parent){
		this->x = x;
		this->y = y;
		this->parent = parent;
	}
	~Node(){
	}
	void setF(){
		f = g + h;
	}
};

bool findNode(std::list<Node*> list, Node* node){
	for (auto it : list){
		if (it->x == node->x && it->y == node->y)
			return true;
	}
	return false;
}

Node* findBest(std::list<Node*> list){
	Node* best = list.front();
	for (auto it : list){
		if (best->f > it->f || (best->f == it->f && best->h > it->h))
			best = it;
	}
	return best;
}

int setH(int currentX, int currentY, int targetX, int targetY){
	int xDistance = abs(currentX - targetX);
	int yDistance = abs(currentY - targetY);
	if (xDistance > yDistance)
		return 14 * yDistance + 10 * (xDistance - yDistance);
	else
		return 14 * xDistance + 10 * (yDistance - xDistance);
}

struct aStar{
	std::list<Node*> open, closed;
	Node* runner;
	bool cUp, cDown, cLeft, cRight;
	aStar(Node* start){
		runner = start;
		runner->f = 0;
		runner->g = 0;
		runner->h = 0;
		open.push_back(runner);
		cUp = false;
		cDown = false;
		cLeft = false;
		cRight = false;
	}
	~aStar(){
		while (open.size() > 0){
			open.clear();
		}
		while (closed.size() > 0){
			closed.clear();
		}
	}
	// faire le check d'impossibilité (open vide avant d'être à la fin) + rectification des parents
	std::stack<Node*> findPath(int x, int y){
		while (runner->x != x || runner->y != y){
			//close actual square
			runner = findBest(open);
			closed.push_back(runner);
			open.remove(runner);
			//reject corners
			cUp = false;
			cDown = false;
			cLeft = false;
			cRight = false;
			//find adjacent square
			if (runner->y < WINDOW_HEIGHT * 0.75 - square.y && map[MAP_WIDTH * (runner->y + 1) + runner->x]){
				cDown = true;
				Node* path = new Node(runner->x, runner->y + 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 10;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (runner->y > 0 && map[MAP_WIDTH * (runner->y - 1) + runner->x]){
				cUp = true;
				Node* path = new Node(runner->x, runner->y - 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 10;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (runner->y < WINDOW_WIDTH - square.x && map[MAP_WIDTH * runner->y + runner->x + 1]){
				cRight = true;
				Node* path = new Node(runner->x + 1, runner->y, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 10;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (runner->y > 0 && map[MAP_WIDTH * runner->y + runner->x - 1]){
				cLeft = true;
				Node* path = new Node(runner->x - 1, runner->y, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 10;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (cUp && cLeft && map[MAP_WIDTH * (runner->y - 1) + runner->x - 1]){
				Node* path = new Node(runner->x - 1, runner->y - 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 14;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (cUp && cRight && map[MAP_WIDTH * (runner->y - 1) + runner->x + 1]){
				Node* path = new Node(runner->x + 1, runner->y - 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 14;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (cDown && cLeft && map[MAP_WIDTH * (runner->y + 1) + runner->x - 1]){
				Node* path = new Node(runner->x - 1, runner->y + 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 14;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
			if (cDown && cRight && map[MAP_WIDTH * (runner->y + 1) + runner->x + 1]){
				Node* path = new Node(runner->x + 1, runner->y + 1, runner);
				if (findNode(open, path) || findNode(closed, path))
					delete path;
				else{
					path->g = runner->g + 14;
					path->h = setH(path->x, path->y, x, y);
					path->setF();
					open.push_back(path);
				}
			}
		}
		runner = closed.back();
		std::stack<Node*> pathStack;
		while (runner){
			pathStack.push(runner);
			runner = runner->parent;
		}
		return pathStack;
	}
};