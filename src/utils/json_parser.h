#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <nlohmann/json.hpp>
#include "reg_window.h"
#include "auth_window.h"

using json = nlohmann::json;

json create_registration_json(const reg_window &regWin);  
json create_auth_json(const auth_window &authWin);  

#endif // JSON_PARSER_H
