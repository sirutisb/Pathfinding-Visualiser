#pragma once

class Cell {
public:
	Cell() : solid(false) {}
	bool isSolid() { return solid; }
	void setSolid(bool value) { solid = value; }
private:
	bool solid;
};