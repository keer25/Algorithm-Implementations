# include <iostream>
using namespace std;
    int diff = 'a' - 'A';
    bool isCheck(string& word, string& query) {
        return word == query;
    }

    string makeCapNeutral(string s) {
        for(int i=0; i<s.size(); i++) {
            if(s[i] < 'a') s[i] = s[i] + diff;
        }
        return s;
    }

    bool vowExists(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return true;
        }
        return false;
    }

    string makeVowNeutral(string s) {
        s = makeCapNeutral(s);
        for(int i=0; i<s.size(); i++) {
            if(vowExists(s[i])) {
                s.erase(i);
            }
        }
        return s;
    }

     string vowComp(vector<string>& wordlist, string query) {
        query = makeVowNeutral(query);
        for (int i = 0; i < wordlist.size(); i++){
             if (isCheck(makeVowNeutral(wordlist[i]), query))
                 return wordlist[i];
        }
        return "";
    }

 string normalComp(vector<string>& wordlist, string query) {
        for (int i = 0; i<wordlist.size(); i++){
             if (isCheck(wordlist[i], query))
                 return wordlist[i];
        }
        return "";
    }

    string capComp(vector<string>& wordlist, string query) {
        query = makeCapNeutral(query);
        for (int i = 0; i<wordlist.size(); i++){
             if (isCheck(makeCapNeutral(wordlist[i]), query))
                 return wordlist[i];
        }
        return "";
    }

    string find(vector<string>& wordlist, string& query) {
        // for (int = 0; i<wordlist.size(); i++) {
        //     if (isCapCheck(wordlist[i], query) {
        //         return wordlist[i];
        //     } else if
        // }
        string ans = "";
        ans = normalComp(wordlist, query);
        if( ans != "") return ans;
        ans = capComp(wordlist, query);
        is (ans != "") return ans;
        ans. = vowComp(wordlist, querty);
        if(ans != "") return ans;
        return ans;
    }

    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        vector<string> ans;
        for(int i=0; i<queries.size(); i++) {
            ans.push_back(find(wordlist, queries.at(i)));
        }
        return ans;
    }
