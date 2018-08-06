#pragma once
#include <string>
#include <iostream>
#include <vector>

class Base64
{
public:
	std::string encode(unsigned char const*, unsigned int len);
	static std::vector<std::uint8_t> decode(std::string s);
};
