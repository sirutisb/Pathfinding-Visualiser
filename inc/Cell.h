#pragma once

class Cell {
public:
	Cell() : solid(false) {}
	bool isSolid() { return solid; }
	void setSolid(bool value) { solid = value; }
	bool solid; // temporary make this public, will cleanup this class later
private:
};