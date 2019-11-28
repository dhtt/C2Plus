#ifndef ASSIGNMENT2_COLTYPE_HPP
#define ASSIGNMENT2_COLTYPE_HPP

#include <memory>
#include <ostream>

class GenericDataType {
public:
    virtual ~GenericDataType() = default;
    virtual std::unique_ptr<GenericDataType> clone() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const GenericDataType& v);
    virtual bool operator==(const GenericDataType& other) const = 0;
    virtual bool operator<(const GenericDataType& other) const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
};

inline std::ostream &operator<<(std::ostream &os, const GenericDataType& v) {
    v.print(os);
    return os;
}

// implement a class DataType<T> that is derived from GenericDataType and holds the actual value
template <typename T>
class DataType: public GenericDataType{
public:
    T value_;
    DataType():value_(0) {}
    ~DataType() override = default;
    explicit DataType(T const& value): value_(value){}
    std::unique_ptr<GenericDataType> clone() const override {
        return std::make_unique<DataType>(*this);
    }
    bool operator==(const GenericDataType& other ) const override {
        const auto *o = dynamic_cast<const DataType*>(&other);
        return (value_ == o->value_);
    }

    bool operator<(const GenericDataType& other) const override {
        const auto *o = dynamic_cast<const DataType*>(&other);
        return (value_ < o->value_);
    }

    T& get_value(){
        return value_;
    }
protected:
    void print(std::ostream& os) const override {
        os << value_;
    }
};


class ColType {
public:
    template <typename ValueType>
    explicit ColType(const ValueType& value): container(std::make_unique<DataType<ValueType>>(value)){}
    ColType(const ColType& other): container(other.container -> clone()){}
    ColType& operator=(const ColType& other);
    GenericDataType& get();
    const GenericDataType& get() const;
    bool operator==(const ColType& other) const;
    bool operator<(const ColType& other) const;
    ~ColType() {container = nullptr;}

private:
    std::unique_ptr<GenericDataType> container;
};

ColType &ColType::operator=(const ColType &other) {
    container = other.container -> clone();
    return *this;
}

bool ColType::operator==(const ColType &other) const {
    return (container == other.container);
}

bool ColType::operator<(const ColType &other) const {
    return (container < other.container);
}

GenericDataType &ColType::get() {
    return *container;
}

const GenericDataType &ColType::get() const {
    return *container;
}


#endif //ASSIGNMENT2_COLTYPE_HPP
