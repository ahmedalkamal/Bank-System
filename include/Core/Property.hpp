/*
 this class `property` was made by ai it's not good btw
*/

#ifndef CLASS_PROPERTY_HPP
#define CLASS_PROPERTY_HPP

#include <functional>
#include <iostream>
#include <ostream>

template <typename T>
class Property {
   private:
    std::function<T()> getter;
    std::function<void(const T&)> setter;

   public:
    Property(std::function<T()> get = nullptr,
             std::function<void(const T&)> set = nullptr)
        : getter(std::move(get)), setter(std::move(set)) {}

    operator T() const { return getter ? getter() : T(); }
    Property<T>& operator=(const T& value) {
        if (setter) setter(value);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Property<T>& property) {
        if (property.getter) out << property.getter();
        return out;
    }
};

#endif  // CLASS_PROPERTY_HPP