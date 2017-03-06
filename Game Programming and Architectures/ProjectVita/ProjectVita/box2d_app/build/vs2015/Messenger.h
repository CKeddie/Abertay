#pragma once

class EventArgs
{
public:
	virtual ~EventArgs();
};

class Messenger
{
public:
	Messenger();
	~Messenger();
};

class Event
{
public:
	virtual ~Event() = 0;
	virtual void Handle(const EventArgs& args) = 0;
};


