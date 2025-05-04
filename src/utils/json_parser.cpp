#include "json_parser.h"
#include "reg_window.h"
#include "auth_window.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json create_registration_json(const reg_window &regWin) {
    json registrationData;

    registrationData["login"] = regWin.get_new_login().toStdString();
    registrationData["password"] = regWin.get_new_password().toStdString();
    registrationData["confirmation"] = regWin.get_confirmation().toStdString();

    return registrationData;
}

json create_auth_json(const auth_window &authWin) {
    json authData;

    authData["login"] = authWin.get_login().toStdString();
    authData["password"] = authWin.get_password().toStdString();

    return authData;
}

