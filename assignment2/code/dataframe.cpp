#include "dataframe.hpp"
#include <set>

//4a
size_t Dataframe::nrows() const {
    auto it = data.begin();
    std::advance(it, 0);
    std::vector<ColType> vct = *it;
    return vct.size();
}

//4b
size_t Dataframe::ncols() const {
    return data.size();
}


//7a TODO: name vector has to be of the same size as nrow and ncol
void Dataframe::set_colnames(const std::vector<std::string>& v_colnames){
    std::set<std::string> s(v_colnames.begin(), v_colnames.end());
    if (s.size() != v_colnames.size()) throw std::exception();

    for (const auto & v_colname : v_colnames){
        colnames.push_back(v_colname);
    }
}
//7b
void Dataframe::set_rownames(const std::vector<std::string>& v_rownames){
    std::set<std::string> s(v_rownames.begin(), v_rownames.end());
    if (s.size() != v_rownames.size()) throw std::exception();

    for (const auto & v_rowname : v_rownames){
        rownames.push_back(v_rowname);
    }
}

//8a
void Dataframe::clear_colnames(){
    colnames.clear();
}
//8b
void Dataframe::clear_rownames(){
    rownames.clear();
}

//9a
bool Dataframe::has_colnames() const {
    return !colnames.empty();
}
//9b
bool Dataframe::has_rownames() const {
    return !rownames.empty();
}



//11a
void Dataframe::remove_column(const size_t i){
    if (i >= ncols()) throw std::out_of_range("Index out of range.");

    auto it = data.begin();
    std::advance(it, i);
    data.erase(it);
    colnames.erase(colnames.begin() + i);
}
//11b
void Dataframe::remove_column(const std::string& col_name){
    if (find(colnames.begin(), colnames.end(), col_name) == colnames.end()) throw Invalid::NameNotFound();
    if (!has_colnames()) throw Invalid::NoColRowName();

    int index = find(colnames.begin(), colnames.end(), col_name) - colnames.begin();

    auto it = data.begin();
    std::advance(it, index);
    data.erase(it);
    colnames.erase(colnames.begin() + index);
}

//12a
void Dataframe::swap_columns(const size_t i, const size_t j) {
    if (i > ncols() || j > ncols()) throw std::out_of_range("Index out of range.");

    auto it1 = data.begin();
    std::advance(it1, i);
    std::vector<ColType> &v_coltype1 = *it1;

    auto it2 = data.begin();
    std::advance(it2, j);
    std::vector<ColType> &v_coltype2 = *it2;

    v_coltype1.swap(v_coltype2);
    colnames[i].swap(colnames[j]);
}
//12b
void Dataframe::swap_columns(const std::string& column1, const std::string& column2) {
    if (!has_colnames()) throw Invalid::NoColRowName();
    if (find(colnames.begin(), colnames.end(), column1) == colnames.end() || find(colnames.begin(), colnames.end(), column2) == colnames.end()) throw Invalid::NameNotFound();

    int i = find(colnames.begin(), colnames.end(), column1) - colnames.begin();
    int j = find(colnames.begin(), colnames.end(), column2) - colnames.begin();

    auto it1 = data.begin();
    std::advance(it1, i);
    std::vector<ColType> &v_coltype1 = *it1;

    auto it2 = data.begin();
    std::advance(it2, j);
    std::vector<ColType> &v_coltype2 = *it2;

    v_coltype1.swap(v_coltype2);
    colnames[i].swap(colnames[j]);
}



//14
void order_by(const size_t i) {}
void order_by(const std::string c) {}

//15
std::ostream& operator<<(std::ostream& os, const Dataframe& df){
    std::vector<std::vector<ColType>> vv_coltype;
    for (size_t j = 0; j < df.ncols(); ++j){ //iterate through column
        std::vector<ColType> v_coltype;
        for (size_t i = 0; i < df.nrows(); ++i){ //iterate through row
            const ColType &coltype = df.at(i,j);
            v_coltype.push_back(coltype);
        }
        vv_coltype.push_back(v_coltype);
    }

    if (df.has_colnames() && df.has_rownames()){
        for (const auto& c:df.colnames) os << "\t" << c;
        os << std::endl;
    }
    else if (df.has_colnames() && !df.has_rownames()){
        for (const auto& c:df.colnames) os << c;
        os << std::endl;
    }

    if (df.has_rownames()){
        for (size_t j = 0; j < df.nrows(); ++j){
            os << df.rownames[j] << "\t";
            for (size_t i = 0; i < vv_coltype.size(); ++i){
                ColType &ct = vv_coltype[i][j];
                os << ct.get() << "\t" ;
            }
            os << std::endl;
        }
    }
    else {
        for (size_t j = 0; j < df.nrows(); ++j){
            for (size_t i = 0; i < vv_coltype.size(); ++i){
                ColType &ct = vv_coltype[i][j];
                os << ct.get() << "\t" ;
            }
            os << std::endl;
        }
    }
    return os;
}

//16a
bool Dataframe::operator==(const Dataframe& other) const{
    if (nrows()!=other.nrows() && ncols()!=other.ncols()) return false;
    bool b = true;
    for (size_t j = 0; j < ncols(); ++j){
        for (size_t i = 0; i < nrows(); ++i){
            if (!(this->at(i,j).get() == other.at(i,j).get())){
                b = false;
                break;
            }
        }
    }
    return b;
}
//16b
bool Dataframe::operator!=(const Dataframe& other) const{
    bool b = true;
    for (size_t j = 0; j < ncols(); ++j){
        for (size_t i = 0; i < nrows(); ++i){
            if (this->at(i,j).get() == other.at(i,j).get()){
                b = false;
                break;
            }
        }
    }
    return b;
}


//Other
ColType Dataframe::at(size_t i, size_t j) const {
    auto it = data.begin();
    std::advance(it, j);
    std::vector<ColType> v_coltype = *it;
    ColType coltype = v_coltype[i];
    return coltype;
}
