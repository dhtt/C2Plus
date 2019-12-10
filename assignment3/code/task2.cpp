#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <iomanip>
using namespace std;

static double get_mean(vector<double> V){
    return accumulate(V.begin(), V.end(), 0.0)/V.size();
}
static double get_sd(vector<double> V){
    vector<double> mean_diff(V.size());
    double mean = get_mean(V);
    transform(V.begin(), V.end(), mean_diff.begin(), [mean](double d){ return d - mean;});
    double square_sum = std::inner_product(mean_diff.begin(), mean_diff.end(), mean_diff.begin(), 0.0); //TODO check
    return sqrt(square_sum / V.size());
}
static vector<double> scale_vector(vector<double> V){
    vector<double> V1_scaled(V.size());
    transform(V.begin(), V.end(), V1_scaled.begin(), [](double d){ return log2(abs(d) + 1);});
    return V1_scaled;
}
void print_vector(vector<double> V, const string& V_name, int print_type){ //print 2 first vectors
    string separator = "";
    if (print_type == 1) {
        sort(V.rbegin(), V.rend());
        size_t elem = 10;
        if (V.size() < 10) elem = V.size();

        cout << V_name << " Top " << elem << " elements: " ;
        for (auto it = V.begin(); it != V.begin() + elem; ++it){
            cout << separator << setprecision(3) << *it;
            separator = ", ";
        }
        cout << endl;
    }
    else if (print_type == 2) { //print last vector
        cout << "Sorted vector: ";
        for (auto it = V.begin(); it != V.end(); ++it){
            cout << separator << setprecision(3) << *it;
            separator = ", ";
        }
        cout << endl;
    }
}
static double t_test(const vector<double>& V1_, const vector<double>& V2_){
    double mean1 = get_mean(V1_); double mean2 = get_mean(V2_);
    double sd1 = get_sd(V1_); double sd2 = get_sd(V2_);
    double n1 = V1_.size(); double n2 = V2_.size();

    double sd_pooled = sqrt(((n1-1)*sd1*sd1 + (n2-1)*sd2*sd2)/(n1+n2-2));//TODO: check calculation
    double t_score = (mean1 - mean2)/(sd_pooled*sqrt(1/n1 + 1/n2));
    return t_score;
}
static vector<double> generate_seqvector(unsigned vec_size, unsigned seed){
    mt19937_64 mt_generator(seed);
    vector<double> V(vec_size);
    iota(V.begin(), V.end(), 1);
    shuffle(V.begin(), V.end(), mt_generator);
    return V;
}

static void sort_special(vector<double>& V){
    sort(V.begin(), V.end(), [](double d1, double d2) -> bool { //sort rounded number: even goes to beginning part, odd goes to end part
        int a = (int)round(d1); int b = (int)round(d2);
        return ((a % 2) < (b % 2));
    });

    auto it = find_if(V.begin(), V.end(), [](double d){ return ((int)round(d)%2 == 1);}); //find position where first (rounded) odd number is
    sort(it, V.end()); //sort odd part in ascending order
    sort(V.begin(), it, [](double d1, double d2){ return d1> d2; }); //sort even part in descending order
}

int main(int argc, char* argv[]) {//TODO add exit error
    if (argc != 6) {
        printf("Please give 5 argument: n, m, s (unsigned int), p (double) and k (unsigned int).\n");
        exit(1);
    }

    unsigned n = static_cast<unsigned int>(atoi(argv[1]));
    unsigned m = static_cast<unsigned int>(atoi(argv[2]));
    unsigned s = static_cast<unsigned int>(atoi(argv[3]));

    double p = strtod(argv[4], nullptr);

    unsigned k = static_cast<unsigned int>(atoi(argv[5]));
    negative_binomial_distribution<int> distribution(k, p);
    mt19937_64 mt_generator1 (s); mt19937_64 mt_generator2 (s*2);
    auto gen1 = [&distribution, &mt_generator1](){return distribution(mt_generator1);};
    auto gen2 = [&distribution, &mt_generator2](){return distribution(mt_generator2);};

    vector<double> V1(n);
    generate(V1.begin(), V1.end(), gen1);
    for (auto& i:V1){cout << i<< "\t";}
    cout <<endl;

    vector<double> V2(m);
    generate(V2.begin(), V2.end(), gen2);
    for (auto& i:V2){cout << i<< "\t";}
    cout <<endl;

    cout << "V1 Mean: " << setprecision(3) << get_mean(V1) << endl;
    cout << "V1 Sample standard deviation: " << setprecision(3) << get_sd(V1) << endl;
    vector<double> V1_scaled = scale_vector(V1);
    print_vector(V1_scaled, "V1", 1);
    cout << "V2 Mean: " << setprecision(3) << get_mean(V2) << endl;
    cout << "V2 Sample standard deviation: " << setprecision(3) << get_sd(V2) << endl;
    vector<double> V2_scaled = scale_vector(V2);
    print_vector(V2_scaled, "V2", 1);
    cout << endl;

    cout << "Comparing V1 and V2..." << endl;
    cout << "Unscaled t-statistic: " << t_test(V1, V2) << endl;
    cout << "Comparing log2 scaled V1 and V2..." << endl;
    cout << "Scaled t-statistic: " << t_test(V1_scaled, V2_scaled) << endl;
    cout << "Total degrees of freedom: " << V1.size() + V2.size() - 2  << endl;
    cout << endl;

    vector<double> V3 = generate_seqvector(n, s*7);
    transform(V1_scaled.begin(), V1_scaled.end(), V3.begin(),  V3.begin(),multiplies<>() );
    sort_special(V3);
    print_vector(V3, "V3", 2);

    return 0;
}
