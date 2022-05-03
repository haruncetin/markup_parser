#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> tokens;
    string token;
    istringstream ts(s);

    while (getline(ts, token, delim))
    {
        tokens.push_back(token);
    }
    return tokens;
}

string lrtrim(string s, const string &ldelim, const string &rdelim)
{
    s.erase(0, s.find_first_not_of(ldelim));
    s.erase(s.find_last_not_of(rdelim) + 1);
    return s;
}

string trim(string s, const string &delim)
{
    s.erase(0, s.find_first_not_of(delim));
    s.erase(s.find_last_not_of(delim) + 1);
    return s;
}

map<string, map<string, string>>::iterator rsearch(string val, map<string, map<string, string>>::iterator it)
{
    if (val != it->first)
    {
        it = rsearch(val, ++it);
    }
    return it;
}

int main()
{
    map<string, map<string, string>> maps;

    int N, Q;

    scanf_s("%d %d", &N, &Q);

    for (int i = 0; i < N; i++)
    {
        string line;
        getline(cin >> ws, line);

        if (line[0] == '<' && line[1] != '/' && line[line.size() - 1] == '>')
        {
            line = lrtrim(line, "<", ">");
            vector<string> tokens = split(line, ' ');

            string tag = tokens[0];

            regex word_regex("(\\w+)\\s?=\\s?\\\"(.*?)\\\"");

            auto rbegin = sregex_iterator(line.begin(), line.end(), word_regex);

            for (auto i = rbegin; i != sregex_iterator(); ++i)
            {
                smatch m = *i;
                string attr = m[1].str(), val = m[2].str();
                maps[tag].insert({attr, val});
            }
        }
        else if (line[0] == '<' && line[1] == '/' && line[line.size() - 1] == '>')
        {
            lrtrim(line, "</", ">");
            maps.insert({line, {}});
        }
    }

    for (int i = 0; i < Q; i++)
    {
        string line;

        getline(cin >> ws, line);

        vector<string> sp = split(line, '.'), vals;

        for (auto v : sp)
        {
            auto x = split(v, '~');
            if (x.size() > 1)
            {
                vals.push_back(x[0]);
                vals.push_back(x[1]);
            }
            else
            {
                vals.push_back(v);
            }
        }

        map<string, map<string, string>>::iterator it = maps.begin();

        for (int i = 0; i < vals.size(); i++)
        {
            string val = vals[i], next_val = i < vals.size() ? vals[i + 1] : string();

            if (!next_val.empty())
            {
                it = rsearch(val, it);
                if (it->first.empty())
                {
                    std::cout << "Not Found!" << endl;
                    continue;
                }
            }
            else
            {
                string r = it->second[val];

                if (!r.empty())
                {
                    cout << r << endl;
                }
                else
                {
                    std::cout << "Not Found!" << endl;
                }
            }
        }
    }

    return 0;
}
