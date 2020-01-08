#include "cxxopts.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::regex_constants;

static vector<string> all_result; //all_result stores all printed line -> no duplicates

static void match_regex(const string& s, const regex& r, bool non_matching, bool line_number, size_t n_line){
    if (non_matching){ //Display non-matches
        if (!regex_search(s, r) && find(all_result.begin(), all_result.end(), s) == all_result.end()) {
            if (line_number) cout << n_line + 1 << ":"; //Display matches with line number
            cout << s << endl;
            all_result.push_back(s);
        }
    }
    else { //Display matches
        if (regex_search(s, r) && find(all_result.begin(), all_result.end(), s) == all_result.end()) {
            if (line_number) cout << n_line + 1 << ":"; //Display matches with line number
            cout << s << endl;
            all_result.push_back(s);
        }
    }
}

static string read_raw_string(string& p){ //preprocess pattern
    regex special_chars1 (R"([-[\]{}()*+?.,\^$|#\t])"); //read common special characters
    regex special_chars2 (R"(\\+[abfnrtv])"); //read \_t \_n \_r etc...
    p = regex_replace(p, special_chars1, R"(\$&)");
    p = regex_replace(p, special_chars2, R"(\$&)");
    return p;
}

static regex make_regex(string& p, bool fixed_string, bool whole_word, bool i_case){
    if (fixed_string){ //Read raw string literal
        p = read_raw_string(p);
    }

    if (whole_word){ //Match only whole word
        p = "\\b" + p + "\\b";
    }

    if (i_case) { //Case insensitive
        regex pattern(p, icase);
        return pattern;
    }
    else {
        regex pattern(p);
        return pattern;
    }
}

int main(int argc, char* argv[]) {
    vector<string> args; //args stores all arguments (files containing string to match)
    string pattern;
    string pattern_filename;
    bool pattern_from_file = false;
    bool i_case = false;
    bool fixed_string = false;
    bool whole_word = false;
    bool non_matching = false;
    bool line_number = false;

    try {
        cxxopts::Options options("Lightweight grep", "Pattern matching program");
        options.add_options()
                ("positional", "Arguments entered without options",cxxopts::value<vector<string>>())
                ("i", "Case insensitive", cxxopts::value<bool>()->default_value("false"))
                ("f", "Pattern from file", cxxopts::value<string>())
                ("F", "Fixed string", cxxopts::value<bool>()->default_value("false"))
                ("w", "Whole word", cxxopts::value<bool>()->default_value("false"))
                ("v", "Non-matching line", cxxopts::value<bool>()->default_value("false"))
                ("n", "Line number", cxxopts::value<bool>()->default_value("false")); //TODO add not n when v

        options.parse_positional({"positional"});
        auto result = options.parse(argc, argv);

        //Parse pattern and filenames
        if (result.count("positional")) {
            vector<string> pos_args = result["positional"].as<vector<string>>();
            if (result.count("f")){
                pattern_filename = result["f"].as<string>();
                pattern_from_file = true;
                for (const auto & pos_arg : pos_args) args.push_back(pos_arg);
            }
            else {
                pattern = pos_args[0];
                for (size_t i = 1; i < pos_args.size(); ++i) args.push_back(pos_args[i]);
            }
        }

        //Case b: Case insensitive
        if (result.count("i")) {
            i_case = true;
        }

        //Case c: Fix string
        if (result.count("F")) {
            fixed_string = true;
        }

        //Case d: Whole word
        if (result.count("w")) {
            whole_word = true;
        }

        //Case f: Non matching line
        if (result.count("v")) {
            non_matching = true;
        }

        //Case g: Line number
        if (result.count("n")) {
            line_number = true;
        }

    }
    catch (const cxxopts::OptionException& e){
        cout << "Error parsing options: " << e.what() << endl;
        exit(1);
    }

    try {
        if (pattern_from_file) { //Read pattern from file
            ifstream pattern_reader(pattern_filename);
            while (getline(pattern_reader, pattern)){ //Each line is a pattern
                regex p = make_regex(pattern, fixed_string, whole_word, i_case);
                for (const auto & arg : args) {
                    ifstream reader(arg); string line; size_t n_line = 0;
                    while(getline(reader, line)) {
                        match_regex(line, p, non_matching, line_number, n_line);
                        n_line += 1;
                    }
                }
            }
        }
        else { //Read pattern from input
            regex p = make_regex(pattern, fixed_string, whole_word, i_case);
            for (const auto & arg : args) {
                ifstream reader(arg); string line; size_t n_line = 0;
                while(getline(reader, line)) {
                    match_regex(line, p, non_matching, line_number, n_line);
                    n_line += 1;
                }
            }
        }
    }
    catch (const exception& e)
    {
        cout << "An error occured: " << e.what() << endl;
        exit(1);
    }

    return 0;
}
