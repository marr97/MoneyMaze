#include "json_parser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json create_registration_json(const reg_window &regWin) {
    json registrationData;

    registrationData["login"] = regWin.get_new_login();
    registrationData["password"] = regWin.get_new_password();
    registrationData["confirmation"] = regWin.get_confirmation();

    return registrationData;
}

json create_auth_json(const auth_window &authWin) {
    json authData;

    authData["login"] = authWin.get_login();
    authData["password"] = authWin.get_password();

    return authData;
}

