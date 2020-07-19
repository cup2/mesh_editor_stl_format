#ifndef PARSER_H
#define PARSER_H

class Parser {
public:
	static std::map<std::string, std::string> parseArgv(int argc, char* argv[]) {
		std::vector<std::string> pairs = splitBySubstr(convertToString(argc, argv));
		std::map<std::string, std::string> parsedtext= splitByPairs(pairs);
		parsedtext["Command"] = argv[1];
		return parsedtext;
	}
private:
	enum class  ModeParse { Normal, BracketOpen, QuoteOpen};
	static std::vector<std::string> splitBySubstr(const std::string &inputarg) {
		std::vector<std::string> parameters;
		std::string parametr;
		ModeParse mode = ModeParse::Normal;
		for (const auto &character : inputarg) {
			switch (mode) {
				case ModeParse::Normal:
					if (character == '(') {
						mode = ModeParse::BracketOpen;
					}
					else if (character == '\"') {
						mode = ModeParse::QuoteOpen;
					}
					else if (character == ',') {
						parameters.push_back(parametr);
						parametr.clear();
					}
					else {
						parametr.push_back(character);
					}
					break;
				case ModeParse::BracketOpen:
					if (character == ')') {
						mode = ModeParse::Normal;
					}
					else if (character == ',') {
						parametr.push_back(' ');
					}
					else{
						parametr.push_back(character);
					}
					break;
				case ModeParse::QuoteOpen:
					if (character == '\"') {
						mode = ModeParse::Normal;
					}					
					else {
						parametr.push_back(character);
					}
					break;

				default:
					break;
			}
		}
		parameters.push_back(parametr);
		return parameters;
	}

	static std::map<std::string, std::string> splitByPairs(const std::vector<std::string> &parameters) {
		std::map<std::string, std::string> parsedtext;
		std::string key, value;
		bool valueWrite = false;
		for (const auto &str : parameters) {
			for (const auto &character : str) {
				if (valueWrite) {
					value.push_back(character);
				}
				else if (character == '=') {
					valueWrite = true;
				}
				else {
					key.push_back(character);
				}
			}
			if (valueWrite) {
				parsedtext.insert(std::make_pair(key, value));
				key.clear();
				value.clear();
			}
			valueWrite = false;
			key.clear();
			value.clear();
		}
		return parsedtext;
	};

	static std::string convertToString(int n, char* arraychar[]) {
		std::string strtext;
		for (int i = 2; i < n; i++) {
			if (arraychar[i]) {
				strtext += arraychar[i];
			}
		}
		return strtext;
	}
};

#endif // PARSER_H