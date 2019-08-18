#include <thread>
#include <iostream>
#include "netspeed.h"
#include "ui.h"



int main()
{
    NetSpeed n;
    n.start();
	UI ui;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int in,out;
        n.get_speed(in, out);
        ui.set_speed(in, out);
    }
    
    n.stop();
}

int WinMain() {
	return main();
}