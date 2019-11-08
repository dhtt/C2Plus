#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <string.h>
using namespace std;

class Sequence{
private:
    static int base_count[4];
public:
    string id, seq;
    Sequence(string seq_id, string sequence){
        id = std::move(seq_id);
        seq = std::move(sequence);
    }

    bool check_valid_seq(){
        istringstream stream_seq(seq); char c; bool check = true;
        if ((find(seq.begin(), seq.end(), 'U') != seq.end()) && (find(seq.begin(), seq.end(), 'T') != seq.end())){
            check = false;
        }
        else {
            while (stream_seq>>c){
                if (c != 'A' && c != 'C' && c != 'G' && c != 'U' && c != 'T') {
                    check = false;
                    break;
                }
            }
        }
        return check;
    }

    bool check_if_DNA(){
        if (find(seq.begin(), seq.end(), 'T') != seq.end()) return true;
        else return false;
    }
    void convert_to_RNA(){
        replace(seq.begin(), seq.end(), 'T', 'U');
    }

    bool check_palindrome(){
        return equal(seq.begin(), seq.begin() + seq.size() / 2, seq.rbegin());
    }

    static int totalbase(){
        return base_count[4];
    }
};

int Sequence::base_count[4]={0};


int base_counter(const string& RNA_seq, const char base[4], int base_count[4]);
int base_counter(const string& RNA_seq, const char base[4], int base_count[4]){
    for (char i : RNA_seq){
        if (i == base[0]) ++base_count[0];
        else if (i == base[1]) ++base_count[1];
        else if (i == base[2]) ++base_count[2];
        else if (i == base[3]) ++base_count[3];
    }
    return base_count[4];
}


int main(int argc, char* argv[]) {
    if (argc!=3){
        printf("Please give 1 FASTA input file and 1 output file.\n");
        return EXIT_FAILURE;
    }

    ifstream reader(argv[1]); ofstream writer(argv[2]);
    string line;
    int n_line = 0; int n_seq = 0;
    char base[4] = {'A', 'C', 'G', 'U'}; int base_count[4]={0};
    string id; string seq;

    while (getline(reader,line)) {
        ++n_line; //Increment lines count
        if (line.empty()) continue; //Skip empty lines to avoid segmentation error
        if (line[0] == '>') { //Line starts with > is Sequence ID
            ++n_seq; //Increment sequences count

            if (!id.empty()) { //If there is no ID: examine the concatenated New squence
                Sequence new_seq(id, seq);
                if (new_seq.check_valid_seq()){ //If New sequence is valid, then if 1> DNA -> RNA; 2> Count bases; 3> Check and write palindrome
                    if (new_seq.check_if_DNA()) new_seq.convert_to_RNA(); //1> DNA -> RNA;
                    base_counter(new_seq.seq, base, base_count); //2> Count bases;
                    if (new_seq.check_palindrome()) writer << new_seq.seq << endl; //3> Check and write palindrome
                    }
                else cout << new_seq.id <<endl; //If New sequence is invalid: output its corresponding FASTA header on the standard error stream
            }

            id = line.substr(1);
            seq.clear(); //Delete current sequence

        } else seq += line; //If Line does not start with > and there is no ID: concatenate lines into current sequence
    }

    //Read and rocess the last sequence
    Sequence last_seq(id, seq);
    if (last_seq.check_valid_seq()){
        if (last_seq.check_if_DNA()) last_seq.convert_to_RNA();
        base_counter(last_seq.seq, base, base_count);
        if (last_seq.check_palindrome()) writer << last_seq.seq << endl;
    }
    else cout << last_seq.id <<endl;

    //Print result
    cout << "Lines: " << n_line << endl;
    cout << "Sequences: " << n_seq << endl;

    double n_base = base_count[0] + base_count[1] + base_count[2] + base_count[3];
    cout << "AU ratio: " << (base_count[0]/n_base + base_count[3]/n_base) << endl;
    for (int i = 0; i < 4; ++i){
        cout << base[i] << ": " << base_count[i]/n_base << endl;
    }

    reader.close();
    writer.close();
    return 0;
}

