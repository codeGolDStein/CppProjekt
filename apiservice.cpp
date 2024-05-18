
#include "apiservice.hpp"

// Funktion berechnet die gesamte Größe der empfangenen Daten (totalSize) 
// und fügt den Inhalt des Puffers zu der Zeichenkette response hinzu, indem sie 
// response->append((char*)contents, totalSize) aufruft. Dadurch wird der Inhalt des 
// Buffers in response angehängt. 
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}


string getCompletion(const string& prompt, string api_token) {
    string apiKey = api_token; 
    string baseUrl = "https://api.openai.com/v1/chat/completions";
    string response;
    CURL* curl = curl_easy_init();

    if (curl) {
        // Hier werden die ganzen Parameter für die 
        // API Anfrage gespeichert:
        json requestData;
        requestData["model"] = "gpt-3.5-turbo";
        requestData["messages"][0]["role"] = "user";
        requestData["messages"][0]["content"] = prompt;
        requestData["temperature"] = 0;

        string requestDataStr = requestData.dump().c_str();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());

        // Curl wird eingerichtet:
        curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestDataStr.length()); // ?? 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // empfängt Daten
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // Empfangenen Daten werden an response gesendet

        // Anfrage wird gesendet:
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "request fehlgeschlagen: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    string content;
    std::istringstream iss(response);
    while (std::getline(iss, content)) {
        //response wird durch einen Stream gelesen
        size_t startPos = content.find("\"content\": \""); // ist in der aktuellen line " "content:" " enthalten?  
        if (startPos != string::npos) { // npos wird von find zurück gegeben wenn der Substring nicht gefunden wurde
            startPos += 12; // Länge von "\"content\": \""
            size_t endPos = content.find("\"", startPos); // sucht nach " ab startpos um das Ende des Inhalts bereiches zu markieren
            if (endPos != string::npos) {
                return content.substr(startPos, endPos - startPos);
            } 
        }
    }

    return "";

    // json jresponse = json::parse(response);
    // return jresponse["choices"][0]["message"]["content"].get<string>();
}