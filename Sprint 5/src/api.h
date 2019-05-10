#ifndef API_H
#define API_H

#include <stdio.h>
#include <string>
#include <jsoncpp/json/json.h>
using namespace std;

#define MAX_SCORE               25000000
#define DEFAULT_CURL_TIMEOUT    15
#define CURL_GET_APPEND         "/getscores"
#define CURL_POST_APPEND        "/uploadscore"

/* Struct used in the uploadScore() method. */
typedef struct
{
    string username;
    string id;
    string token;
    int score;
} Score;

/**
 * \brief The API class provides functionality to POST and GET SCORES from a
 * server.
 */
class API
{
private:

    /**
     * \brief disabled - if true, then the whole API service is disabled.
     */
    bool disabled;

    /**
     * \brief serverUrlStorage stores the URL where the server URL is tores.
     */
    string serverUrlStorage;

    /**
     * \brief serverUrl the URL of the server.
     */
    string serverUrl;

    /**
     * \brief curlGet makes a GET request using CURL.
     * \param url is the URL from which we GET the CURL.
     * \return a raw string.
     */
    string curlGet(const string& url);

    /**
     * \brief curlPost makes a POST request using CURL.
     * \ref https://stackoverflow.com/questions/51776246/curl-post-request-in-c/51776289
     * \param url is the URL to which it's POSTing.
     * \param data is the data which is POSTed.
     * \return true if successful, false otherwise.
     */
    bool curlPost(const string& url, char *data);

public:

    /**
     * \brief Default constructor
     */
    API();

    /**
     * \brief acquireServerUrl tries to acquire the serverUrl from the serverUrlStorage.
     * \ref https://curl.haxx.se/libcurl/c/simple.html
     * \return true if successful, false otherwise.
     */
    bool acquireServerUrl();

    /**
     * \brief disable is an inline method which disables the usage of the API completely.
     */
    void disable();

    /**
     * \brief enable is an inline method which enables the usage of the API.
     */
    void enable();

    /**
     * \brief getTopScores gets top 10 scores from the live scoreboard using CURL
     * \return Json::Value JSON format of the top 10 scores.
     */
    Json::Value getTopScores();

    /**
     * \brief uploadScore uploads the new score on the server everytime the game
     * is saved.
     * \param score - see typedef struct Score.
     * \return true if the request is successful, false otherwise.
     */
    bool uploadScore(Score *score);

    /**
     * \brief setNewURLStorage sets a new URL so that testing could be done
     * \param newURL is the new URL set
     * \return void
    */ 
    void setNewURLStorage(std::string newURL);
};

/**
 * \brief getCurlCallback used as a WRITEFUNCTION callback
 * \see API::acquireServerUrl()
 * \ref https://gist.github.com/connormanning/41efa6075515019e499c
 *
 * \param in const char* - the result from the curl.
 * \param size size_t
 * \param num size_t
 * \param out string - the output from the curl.
 * \return Length of the string which is returned.
 */
size_t getCurlCallback(const char* in, size_t size, size_t num, string* out);

#endif // API_H
