#include <thread>

class NetSpeed
{
public:
    void start();
    void stop();
    void get_speed(int& in, int& out);
private:
    int in_speed;
    int out_speed;
    std::unique_ptr<std::thread> t;
    bool reqStop = false;
	void calc();
};
