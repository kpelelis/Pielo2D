#pragma once

#include "conf.h"
#include <fstream>

class ScriptResource
{
public:
	ScriptResource() {};
	~ScriptResource() { delete content_; };
	
	std::string get_content() { return *content_; }

	bool loadFromFile(const std::string& filename) {
		try{
			std::ifstream ifs(filename);
  			content_ = new std::string((std::istreambuf_iterator<char>(ifs)),
                       		  	   (std::istreambuf_iterator<char>()));			
  			return true;
		} catch (...) {
			return false;
		}
	}

private:
	std::string *content_;
};