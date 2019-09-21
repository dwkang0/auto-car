///*
// * input.cpp
// *
// *  Created on: 2019. 9. 21.
// *      Author: dwkang
// */
//
//#include <stdio.h>
//#include <iostream>
//#include "json/json.h"
//#include "input.h"
//
//
//input * inputMapFromJson(char * str){
//	Json::Reader reader;
//		Json::Value root;
//		bool parsingRet = reader.parse(str, root);
//
//		if (!parsingRet)
//		{
//			std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
//			return NULL;
//		}
//
//		std::cout << root["hasCar"] << " : " << root["age"] << std::endl << std::endl;
//
//		const Json::Value items = root["items"];
//		for (int i = 0; i < items.size(); i++)
//		{
//			std::cout << items[i].asString() << std::endl;
//		}
//		std::cout << std::endl;
//
//		auto member = root.getMemberNames();
//
//		for (std::string s : member)
//		{
//			std::cout << s << std::endl;
//		}
//		std::cout << std::endl;
//
//		for (std::string s : member)
//		{
//			if (root[s].isString())
//			{
//				std::cout << root[s] << std::endl;
//			}
//		}
//		std::cout << std::endl;
//
//		Json::Value friends = root["friends"];
//		for (auto it = friends.begin(); it != friends.end(); it++)
//		{
//			if (it->isObject())
//			{
//				std::cout << (*it)["name"] << " : " << (*it)["age"] << std::endl;
//			}
//		}
//		std::cout << std::endl;
//
//		return NULL;
//}
