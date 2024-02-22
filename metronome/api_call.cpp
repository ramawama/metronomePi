#include <iostream>
#include <curl/curl.h>
#include <string>
#include <jsoncpp/json/json.h>

// Callback function to handle the response data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getAndParseJson(const std::string& url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::size_t ret;
    curl = curl_easy_init();

     if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // Set the URL
        // get is default so no need to specify

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return false;
        }

        // Parse the JSON response
        Json::Value jsonData;
        Json::Reader reader;
        if (reader.parse(readBuffer, jsonData) && jsonData.isMember(key) && jsonData[key].isString()) {
            std::string valueString = jsonData[key].asString();
            try {
                // Convert string to unsigned long long first
                unsigned long long tempValue = std::stoull(valueString);
                // Then, if needed, static_cast to size_t
                numericValue = static_cast<size_t>(tempValue);
            } 
            catch (const std::exception& e) {
                std::cerr << "Conversion error: " << e.what() << std::endl;
            }
        }
        else {
                std::cerr << "Failed to parse JSON or key not found" << std::endl;
        }

        return ret;

    }

    return 0;
}

// Function to send a PUT request to an API
bool sendPutRequest(const std::string& url, const std::string& jsonData) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();

    if(curl) {
        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Specify the PUT request method
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        // Set the header
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Provide the data for the PUT request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Set the callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the PUT request
        res = curl_easy_perform(curl);

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return false;
        }

        // Optionally print the response
        std::cout << "Response: " << readBuffer << std::endl;
        
        return true;
    }

    return false;
}

// int main() {
//     // Example usage
//     std::string url = "http://127.0.0.1:5000/bpm/";
//     Json::Value root;
//     root["BPM"] = "60";
//     Json::StyledWriter writer; 
//     std::string jsonData = writer.write(root);
//     //std::string jsonData = "{\"BPM\": \"60\"}";

//     if(sendPutRequest(url, jsonData)) {
//         std::cout << "PUT request sent successfully." << std::endl;
//     } else {
//         std::cout << "Failed to send PUT request." << std::endl;
//     }

//     return 0;
// }