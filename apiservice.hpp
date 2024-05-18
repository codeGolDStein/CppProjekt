#ifndef APISERVICE_HPP
#define APISERVICE_HPP

#include <curl/curl.h>
#include <nlohmann/json.hpp>
using nlohmann::json;


#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using std::string;
using std::vector;

// Beide Funktionen müssen static oder freie Funktionen sein:
size_t WriteCallback(void*, size_t, size_t, string*);

// Sendet Anfrage an ChatGPT und gibt die Antwort zurück
string getCompletion(const string&, string api_token);

#endif