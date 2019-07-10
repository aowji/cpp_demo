#include <iostream>
#include <boost/filesystem.hpp>

#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

namespace bf = boost::filesystem;

int main(int argc, char**argv)
{
	bf::path path(std::getenv("USERPROFILE"));
	path = path / "Desktop" / "test---.txt";

	std::string filecontent;
	std::ifstream file(path.c_str());
	std::stringstream buffer;
	buffer << file.rdbuf();
	filecontent = buffer.str();
	buffer.clear();

	std::cout << filecontent << std::endl;
}