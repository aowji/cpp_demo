#include <string>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <fstream>



int main(int argc, char**argv)
{
    std::string host = "www.baidu.com";
    std::string port = "80";

    boost::asio::io_context ioc;

    boost::asio::ip::tcp::resolver resolver(ioc);
    auto endpoints = resolver.resolve(host, port);

    boost::beast::tcp_stream stream(ioc);
    stream.connect(endpoints);

    boost::beast::http::request<boost::beast::http::string_body> req{
        boost::beast::http::verb::get, "/", 10
    };
    req.set(boost::beast::http::field::host, host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    boost::beast::http::write(stream, req);
    
	boost::beast::flat_buffer buffer;
	boost::beast::http::response<boost::beast::http::dynamic_body> res;
	boost::beast::http::read(stream, buffer, res);

	std::ofstream out("baidu_index.html");
	out << res << std::endl;
	out.close();

    

	stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);

    return 0;

}