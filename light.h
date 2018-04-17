#ifndef LIGHT_H_
#define LIGHT_H_

typedef enum 
{
	GREEN,
	ORANGE,
	RED,
}COLOURS;

class light
{
public:
	static light* create(int green_pin, int orange_pin, int red_pin);
	light(int green_pin, int orange_pin, int red_pin);
	void go(void);
	void slow(void);
	void stop(void);
	void turnOn(COLOURS colour);
	void turnOff(COLOURS colour);

private:
	int _green;
	int _orange;
	int _red;
};

#endif