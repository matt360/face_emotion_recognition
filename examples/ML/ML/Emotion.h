#pragma once
class Emotion
{
public:
	Emotion();
    // virtual destructor ensures that both destructors will be called; of the base and the derived class
	virtual ~Emotion();
};

