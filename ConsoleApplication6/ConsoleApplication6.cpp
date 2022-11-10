#include <iostream>
#define CURL_STATICLIB
#pragma comment(lib,"Ws2_32.lib") 
#pragma comment(lib,"Crypt32.lib") 
#pragma comment(lib,"Wldap32.lib") 
#pragma comment(lib,"Normaliz.lib") 
#pragma comment(lib,"advapi32.lib") 
#include "curl/curl.h"
#pragma comment(lib,"curl/libcurl_a_debug.lib") 


static size_t __cdecl WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
int  main()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    char* dasd;
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    curl = curl_easy_init();
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_URL, "https://localhost:443/check");
        curl_easy_setopt(curl, CURLOPT_URL, "https://127.0.0.1:443/check");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        std::string sParam = "{\"key1\", \"val1\"},{\"key2\",\"val2\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sParam.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        std::cout << readBuffer + '\n';
        curl_global_cleanup();
    }
}
