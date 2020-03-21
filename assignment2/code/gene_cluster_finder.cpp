#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct Gene{ //struct Gene hold info for each gene
public:
    string chr;
    int start;
    int end;
    int mid; //middle position of gene
    int c_id{}; //the cluster gene belongs to
    Gene(string& chromosome, int& start_pos, int& end_pos);
};

Gene::Gene(string &chromosome, int &start_pos, int &end_pos): chr(chromosome), start(start_pos), end(end_pos), mid((end_pos + start_pos)/2) {}

void sort(std::vector<int>& v);
void sort(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
}

static int get_min_mid_gene(vector<Gene>& v) { //find the smallest middle_position out of all genes in a cluster
    vector<int> vmid;
    vmid.reserve(v.size());
    for (Gene& i:v) vmid.push_back(i.mid);
    sort(vmid);
    return(vmid[0]);
}

static int get_max_mid_gene(vector<Gene>& v) { //find the largest middle_position out of all genes in a cluster
    vector<int> vmid;
    vmid.reserve(v.size());
    for (Gene& i:v) vmid.push_back(i.mid);
    sort(vmid);
    return(vmid[vmid.size()-1]);
}


int main(int argc, const char* argv[]) {
    ifstream reader(argv[1]); ofstream writer(argv[3]); int allowed_distant = atoi(argv[2]); //read input file and allow distance from argument
    string last_chromosome = "chr0"; int last_start = 0; int last_end = 0; //coordinates of the last gene are stored here
    string chromosome; int pos_start, pos_end; //coordinates of the currently examined gene
    int cluster_id = 0;

    vector<Gene> cluster; vector<vector<Gene>> all_cluster;

    while (reader >> chromosome >> pos_start >> pos_end){ //cin input into coordinates
        if ((chromosome < last_chromosome) || (chromosome == last_chromosome && pos_start < last_start) || ((chromosome == last_chromosome) && (pos_start == last_start) && (pos_end < last_end))){
            //If the coordinate of current gene is smaller than last gene, exit
            cerr << "Input file is not sorted in coordinate order."<< endl;
            exit (1);
        }

        Gene new_gene(chromosome, pos_start, pos_end);
        if (new_gene.chr != last_chromosome){
            //If new gene has different chromosome -> new cluster
            all_cluster.push_back(cluster); //Store old cluster in all_cluster
            cluster.clear(); //Clear old cluster to store genes of new cluster

            ++cluster_id;
            new_gene.c_id = cluster_id; //assign updated cluster_id to Gene struct

            last_chromosome = new_gene.chr; //store info of current gene to compare to next gene
        }
        else {
            if (abs(get_min_mid_gene(cluster) - new_gene.mid) > allowed_distant && abs(get_max_mid_gene(cluster) - new_gene.mid) > allowed_distant) {
                //If the mid_pos of current gene is larger than the largest mid_pos in cluster/ smaller than the smallest mid_pos in cluster by a distant
                //of allowed_distant -> new cluster
                all_cluster.push_back(cluster);
                cluster.clear();

                ++cluster_id;
                new_gene.c_id = cluster_id;
            }
            else{
                //Last scenario -> same cluster
                new_gene.c_id = cluster_id;
            }

        }
        last_start = new_gene.start; //store info of current gene to compare to next gene
        last_end = new_gene.end; //store info of current gene to compare to next gene
        cluster.push_back(new_gene); //assign current gene into a cluster
    }
    all_cluster.push_back(cluster); //store the last cluster

    for (auto & clust : all_cluster){ //write result
        for (auto & g:clust){
            writer << g.chr << "\t" << g.start << "\t" << g.end << "\tcluster=" <<  g.c_id << endl;
        }
    }

    return 0;
}
