#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <nlohmann/json.hpp>

class reg_window;
class auth_window;

using json = nlohmann::json;

json create_registration_json(const reg_window &regWin);  
json create_auth_json(const auth_window &authWin);  

#endif // JSON_PARSER_H
