#ifndef BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP
#define BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP

// (C) Copyright 2005  Matthias Troyer
// (C) Copyright 2020  Robert Ramey

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cstddef> // size_t
#include <boost/assert.hpp>
#include <boost/operators.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>

namespace boost {
namespace serialization {

template<typename T> // T is the basic type holding the integer
struct cardinal_number : private
    boost::totally_ordered<cardinal_number<T> >,
    boost::additive<cardinal_number<T> >,
    boost::unit_steppable<cardinal_number<T> >
{
private:
    template<typename CharType, typename Traits>
    friend std::basic_ostream<CharType, Traits> & operator<<(
        const std::basic_ostream<CharType, Traits> & bos,
        const cardinal_number & rhs
    );
    template<typename CharType, typename Traits>
    friend std::basic_istream<CharType, Traits> & operator>>(
        std::basic_istream<CharType, Traits> & bis,
        const cardinal_number & rhs
    );
public:
    T m_t;
    cardinal_number(T t = 0) :
        m_t(t)
    {}
    cardinal_number(unsigned int t) :
        m_t(t)
    {}
    cardinal_number(int t) :
        m_t(t)
    {
        BOOST_ASSERT(t >= 0);
    }
    operator const T (){
        return m_t;
    }
    // assignment operator
    cardinal_number & operator=(const cardinal_number & rhs){
        m_t = rhs.m_t;
        return *this;
    }
    // basic operations upon which others depend
    // totally ordered / less_than_comparable
    bool operator<(const cardinal_number & rhs) const {
        return m_t < rhs.m_t;
    }
    bool operator==(const cardinal_number & rhs) const {
        return m_t == rhs.m_t;
    }
    // additive
    cardinal_number & operator+=(const cardinal_number & rhs){
        m_t += rhs.m_t;
        return *this;
    }
    // subtractive
    cardinal_number & operator-=(const cardinal_number & rhs){
        BOOST_ASSERT(m_t >= rhs.m_t);
        m_t -= rhs.m_t;
        return *this;
    }
    // increment
    cardinal_number operator++(){
        ++m_t;
        return *this;
     }
     // decrement
    cardinal_number operator--(){
        BOOST_ASSERT(m_t > T(0));
        --m_t;
        return *this;
     }
};

typedef cardinal_number<std::size_t> collection_size_type;

} } // end namespace boost::serialization

#include <ostream>
#include <istream>

namespace std {

template<typename CharType, typename Traits>
basic_ostream<CharType, Traits> & operator<<(
    std::basic_ostream<CharType, Traits> & bos,
    const boost::serialization::collection_size_type & rhs
){
    bos << rhs.m_t;
    return bos;
}

template<typename CharType, typename Traits>
basic_istream<CharType, Traits> & operator>>(
    std::basic_istream<CharType, Traits> & bis,
    boost::serialization::collection_size_type & rhs
){
    bis >> rhs.m_t;
    return bis;
}

} // std

BOOST_CLASS_IMPLEMENTATION(                     \
    boost::serialization::collection_size_type, \
    primitive_type                              \
)
BOOST_IS_BITWISE_SERIALIZABLE(boost::serialization::collection_size_type)

#endif //BOOST_SERIALIZATION_COLLECTION_SIZE_TYPE_HPP

/* collection_size_type copy.hpp
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
*/