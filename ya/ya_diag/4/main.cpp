#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <unordered_map>

#include <curl/curl.h>

using namespace std;

static size_t writeToString(void* data, size_t size, size_t nmemb, void* userp)
{
    const size_t realsize = size * nmemb;
    string *storage = (string*)userp;
    storage->append(string((char*)data, realsize));
    return realsize;
}

bool compareChars(const char c1, const char c2)
{
    if (c1 == c2)
        return true;
    else if (tolower(c1) == tolower(c2))
        return true;
    return false;
}

bool compareStrings(const string& s1, const string& s2)
{
    if (s1.size() != s2.size())
        return false;
    return equal(begin(s1), end(s1), begin(s2), &compareChars);
}

inline vector<string> getValues(const string& s)
{
    if (s.empty())
        return {};

    vector<string> out;
    for (int i = 1, j = 0; i < s.size(); ++i) {
        if (s[i] == '\n') {
            string line = s.substr(j, i-j-1);
            j = i+1;
            while (line.back() == '\r' || line.back() == '\n') {
                line.resize(line.size()-1);
            }

            static const string header = "x-cat-value: ";
            if (line.size() < header.size()+1)
                continue;

            if (compareStrings(line.substr(0,header.size()), header))
                out.push_back(line.substr(header.size()));
        }
    }
    return out;
}

string getDataFromHttpService(const vector<string>& in)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
        return string();

    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:7777/");

    struct curl_slist *headers = NULL;
    unordered_set<string> hist;
    for (const string &v : in) {
        if (hist.find(v) != hist.end())
            continue;

        hist.insert(v);
        const string &&s = "X-Cat-Variable: " + v;
        headers = curl_slist_append(headers, s.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "MEW");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    string out;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeToString);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void*)&out);

    // HTTP request
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return out;
}

string findAnswer(const vector<string>& in)
{
    const auto &&values = getValues(getDataFromHttpService(in));
    if (values.empty())
        return string();

    string out;
    int idx = -1;
    unordered_map<string,string> hist;
    for (const string &s : in) {
        if (hist.find(s) != hist.end()) {
            out.append(hist[s] + "\n");
            continue;
        }
        if (++idx < values.size()) {
            out.append(values[idx] + "\n");
            hist[s] = values[idx];
        }
    }
    return out;
}


int main()
{
    vector<string> in;
    string s;

    for (int k = 0; k < 4; ++k) {
        cin >> s;
        in.push_back(s);
    }

    cout << findAnswer(in) << endl;

    return 0;
}
