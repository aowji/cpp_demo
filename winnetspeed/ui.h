#include <thread>

class UI
{
private:
	std::unique_ptr<std::thread> uithread;
	void uithreadfunc();
	int in_speed = 0;
	int out_speed = 0;
public:
    UI();
	void set_speed(int& in, int& out);
    ~UI();
};
