#include "api.h"
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <stdio.h>
using namespace std;

size_t getCurlCallback(const char* in, size_t size, size_t num, string* out)
{
    const size_t totalBytes(size*num);
    out->append(in, totalBytes);
    return totalBytes;
}

bool API::acquireServerUrl()
{
    string rawJSON = this->curlGet(this->serverUrlStorage);

    Json::Value jsonData;
    Json::Reader jsonReader;

    string res;

    if(rawJSON.empty())
    {
        fprintf(stderr, "CURL failed\n");
        return false;
    }

    if(jsonReader.parse(rawJSON, jsonData))
    {
        this->serverUrl = jsonData["link"].asString();
    }
    else
    {
        fprintf(stderr, "JSON parsing failed\n");
        return false;
    }

    if(this->serverUrl.empty())
    {
        fprintf(stderr, "Wrong JSON format\n");
        return false;
    }

    return true;
}

string API::curlGet(const string &url)
{
    CURL *curl;
    CURLcode res;

    string ret;

    curl = curl_easy_init();
    if(!curl)
    {
        fprintf(stderr, "Curl could not init\n");
        return ret;  // Return empty
    }

    /* Set options for the request */
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // URL
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_CURL_TIMEOUT);  // Timeout
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // If follow redirections

    /* Write back the data into a string */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getCurlCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);

    // fprintf(stderr, "Performing CURL GET...");

    /* Perform the request */
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "\ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return "";  // Return empty
    }

    // fprintf(stderr, "\nDone\n");

    curl_easy_cleanup(curl);
    return ret;
}

API::API()
{
    this->serverUrlStorage = "https://matiusulung.com/se.json";
    this->enable();
    bool ret = this->acquireServerUrl();
    if(!ret)
    {
        fprintf(stderr, "Connection error: please check your internet connection "
                        "and restart the game\n");
    }
}

void API::disable()
{
    this->disabled = true;
}

void API::enable()
{
    this->disabled = false;
}

Json::Value API::getTopScores()
{
    Json::Reader jsonReader;
    Json::Value jsonData;
    string rawJSON, url;

    if(this->disabled)
    {
        return jsonData;
    }

    if(this->serverUrl.empty())
    {
        /* Return empty */
        return jsonData;
    }

    /* CURL GET */
    url = this->serverUrl + "/getscores";
    rawJSON = this->curlGet(url);

    if(rawJSON.empty())
    {
        fprintf(stderr, "CURL GET failed\n");
        return jsonData;  // Return empty
    }

    if(!jsonReader.parse(rawJSON, jsonData))
    {
        fprintf(stderr, "JSON could not be parsed\n");
        Json::Value emptyVal;
        return emptyVal;  // Return empty
    }

    return jsonData;
}

bool API::curlPost(const string& url, char *data)
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(!curl)
    {
        fprintf(stderr, "ERROR: Could not start CURL\n");
        curl_global_cleanup();
        return false;
    }

    /* Setup URL and data */
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_CURL_TIMEOUT);

    /* Append some headers */
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

//    fprintf(stderr, "Performing CURL POST...");

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "\ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

//    fprintf(stderr, "\nDone\n");

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return true;
}

bool API::uploadScore(Score *score)
{
    if(this->disabled)
    {
        fprintf(stderr, "ERROR: API is disabled\n");
        return false;
    }

    if(score->score < 0 || score->score > MAX_SCORE || score->id.empty()
            || score->token.empty() || score->username.empty())
    {
        fprintf(stderr, "ERROR: Invalid structure of Score\n");
        return false;
    }

    char *data = new char[1024];

    sprintf(data, "{\"jacobs-id\":\"%s\", \"se-token\":\"%s\", \"game-username\":\"%s\", \"score\":%d}",
             score->id.c_str(), score->token.c_str(), score->username.c_str(), score->score);

    return this->curlPost(this->serverUrl + CURL_POST_APPEND, data);
}

void API::setNewURLStorage(std::string newURL)
{
    this->serverUrlStorage = newURL;
}