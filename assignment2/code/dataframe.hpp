#ifndef ASSIGNMENT2_DATAFRAME_HPP
#define ASSIGNMENT2_DATAFRAME_HPP

#include <list>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

#include "col_type.hpp"

// This is needed to be able to deduce the first type of a passed lambda object
template<typename Ret, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...) const);

template <typename F>
decltype(first_argument_helper(&F::operator())) first_argument_helper(F); //first_argument_helper(F) will have type of first_argument_helper(&F::operator())

template <typename T>
using first_argument_t = decltype(first_argument_helper(std::declval<T>())); //first_argument_helper(F) will have type std::declval<T>()


class Dataframe {
public:
    class Invalid{
    public:
        struct NameNotFound : public std::exception {
            const char * what () const noexcept {
                return "Error: Row or Column name not found!";
            }
        };

        struct NoColRowName : public std::exception {
            const char * what () const noexcept {
                return "Error: Dataframe has no column name and/or row name.";
            }
        };
    };
    Dataframe(): data(), colnames(), rownames() {}

    Dataframe(const Dataframe& other): data(other.data), colnames(other.colnames), rownames(other.rownames) {}

    ~Dataframe(){
        colnames.clear();
        rownames.clear();
        data.clear();
    }

    //4a
    size_t nrows() const {
        auto it = data.begin();
        std::advance(it, 0);
        std::vector<ColType> vct = *it;
        return vct.size();
    }
    //4b
    size_t ncols() const {
        return data.size();
    }

    //5
    template <typename T>
    T& get(size_t i, size_t j){
        if (i > nrows() || j > ncols()) throw std::out_of_range("Index out of range.");

        auto it = data.begin();
        std::advance(it, j);
        std::vector<ColType> &v_coltype = *it; //access column j
        ColType coltype = v_coltype[i]; //access item i of column j
        T &ct = get_orig_type_<T>(coltype);
        return ct;
    }
    //6
    template <typename T>
    T get(const std::string& r, const std::string& c){
        if (!has_rownames() || !has_colnames()) throw Invalid::NoColRowName();
        if (find(colnames.begin(), colnames.end(), c) == colnames.end() || find(rownames.begin(), rownames.end(), r) == rownames.end()) throw Invalid::NameNotFound();

        int j = find(colnames.begin(), colnames.end(), c) - colnames.begin(); //get index of column by name
        int i = find(rownames.begin(), rownames.end(), r) - rownames.begin();

        auto it = data.begin();
        std::advance(it, j);
        std::vector<ColType> &v_coltype = *it;//access column j
        ColType coltype = v_coltype[i]; //access item i of column j
        T &ct = get_orig_type_<T>(coltype);
        return ct;
    }

    //7a TODO: name vector has to be of the same size as nrow and ncol
    void set_colnames(const std::vector<std::string>& v_colnames){
        for (const auto & v_colname : v_colnames){
            colnames.push_back(v_colname);
        }
    }
    //7b
    void set_rownames(const std::vector<std::string>& v_rownames){
        for (const auto & v_rowname : v_rownames){
            rownames.push_back(v_rowname);
        }
    }

    //8a
    void clear_colnames(){
        colnames.clear();
    }
    //8b
    void clear_rownames(){
        rownames.clear();
    }

    //9a
    bool has_colnames() const {
        return !colnames.empty();
    }
    //9b
    bool has_rownames() const {
        return !rownames.empty();
    }

    //10
    template <typename T>
    void add_column(std::vector<T> col) {
        std::vector<ColType> v_coltype;
        for (int i = 0; i < col.size(); ++i){
            ColType p = ColType(col[i]);
            v_coltype.push_back(p);
        }
        data.push_back(v_coltype);
    }

    //11a
    void remove_column(const size_t i){
        if (i > ncols()) throw std::out_of_range("Index out of range.");

        auto it = data.begin();
        std::advance(it, i);
        data.erase(it);
        colnames.erase(colnames.begin() + i);
    }
    //11b
    void remove_column(const std::string& col_name){
        if (find(colnames.begin(), colnames.end(), col_name) == colnames.end()) throw Invalid::NameNotFound();
        int index = find(colnames.begin(), colnames.end(), col_name) - colnames.begin(); //get index of column by name

        auto it = data.begin();
        std::advance(it, index);
        data.erase(it);
        colnames.erase(colnames.begin() + index);
    }

    //12a
    void swap_columns(const size_t i, const size_t j) {
        if (i > ncols() || j > ncols()) throw std::out_of_range("Index out of range.");

        auto it1 = data.begin();
        std::advance(it1, i);
        std::vector<ColType> &v_coltype1 = *it1; //first column

        auto it2 = data.begin();
        std::advance(it2, j);
        std::vector<ColType> &v_coltype2 = *it2;//second column

        v_coltype1.swap(v_coltype2);
        colnames[i].swap(colnames[j]);
    }
    //12b
    void swap_columns(const std::string& column1, const std::string& column2) {
        if (!has_colnames()) throw Invalid::NoColRowName();
        if (find(colnames.begin(), colnames.end(), column1) == colnames.end() || find(colnames.begin(), colnames.end(), column2) == colnames.end()) throw Invalid::NameNotFound();

        int i = find(colnames.begin(), colnames.end(), column1) - colnames.begin(); //get index of column by name
        int j = find(colnames.begin(), colnames.end(), column2) - colnames.begin();

        auto it1 = data.begin();
        std::advance(it1, i);
        std::vector<ColType> &v_coltype1 = *it1; //first column

        auto it2 = data.begin();
        std::advance(it2, j);
        std::vector<ColType> &v_coltype2 = *it2; //second column

        v_coltype1.swap(v_coltype2);
        colnames[i].swap(colnames[j]);
    }

    //13a
    template<typename Fun>
    void apply(const size_t i, Fun l) {
        if (i > ncols()) throw std::out_of_range("Index out of range.");

        auto it = data.begin();
        std::advance(it, i);
        std::vector<ColType> &v_coltype = *it;

        for (auto &coltype:v_coltype){
            l(get_orig_type_<first_argument_t<Fun>>(coltype));
        }
    }
    //13b
    template<typename Fun>
    void apply(const std::string& c, Fun l){
        if (!has_colnames()) throw Invalid::NoColRowName();
        if (find(colnames.begin(), colnames.end(), c) == colnames.end()) throw Invalid::NameNotFound();

        int i = find(colnames.begin(), colnames.end(), c) - colnames.begin();
        auto it = data.begin();
        std::advance(it, i);
        std::vector<ColType> &v_coltype = *it;

        for (auto &coltype:v_coltype){
            l(get_orig_type_<first_argument_t<Fun>>(coltype));
        }
    }

    //14
    void order_by(const size_t i) {}
    void order_by(const std::string c) {}

    //15
    friend std::ostream& operator<<(std::ostream& os, const Dataframe& df){
        std::vector<std::vector<ColType>> vv_coltype;
        for (size_t j = 0; j < df.ncols(); ++j){
            std::vector<ColType> v_coltype;
            for (size_t i = 0; i < df.nrows(); ++i){
                const ColType &coltype = df.at(i,j);
                v_coltype.push_back(coltype);
            }
            vv_coltype.push_back(v_coltype);
        }

        if (df.has_colnames() && df.has_rownames()){ //print col name and row name
            for (const auto& c:df.colnames) os << "\t" << c;
            os << std::endl;
        }
        else if (df.has_colnames() && !df.has_rownames()){ //print col name only
            for (const auto& c:df.colnames) os << c;
            os << std::endl;
        }

        if (df.has_rownames()){ //print row name
            for (size_t j = 0; j < df.nrows(); ++j){
                os << df.rownames[j] << "\t";
                for (size_t i = 0; i < vv_coltype.size(); ++i){
                    ColType &ct = vv_coltype[i][j];
                    os << ct.get() << "\t" ;
                }
                os << std::endl;
            }
        }
        else { //else print just the data
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
    bool operator==(const Dataframe& other) const{
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
    bool operator!=(const Dataframe& other) const{
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
    ColType at(size_t i, size_t j) const { //get access to ColType object in dataframe
        auto it = data.begin();
        std::advance(it, j);
        std::vector<ColType> v_coltype = *it;
        ColType coltype = v_coltype[i];
        return coltype;
    }


private:

    std::list<std::vector<ColType>> data;
    std::vector<std::string> colnames;
    std::vector<std::string> rownames;

    template<typename T>
    T& get_orig_type_(ColType& ct){
        auto& val = dynamic_cast<DataType<typename std::remove_reference_t<T>>&>(ct.get());
        return val.get_value();
    }

    template<typename T>
    const T& get_orig_type_(const ColType& ct) const {
        const auto& val = dynamic_cast<const DataType<typename std::remove_reference_t<T>>&>(ct.get());
        return val.get_value();
    }
};


#endif //ASSIGNMENT2_DATAFRAME_HPP
