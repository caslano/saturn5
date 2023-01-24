#ifndef BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP
#define BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert_linebreaks.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ using ::memcpy; }
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert line break every N characters
template<
    class Base,
    int N,
    class CharType = typename boost::iterator_value<Base>::type
>
class insert_linebreaks :
    public iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    >
{
private:
    friend class boost::iterator_core_access;
    typedef iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    > super_t;

    bool equal(const insert_linebreaks<Base, N, CharType> & rhs) const {
        return
//            m_count == rhs.m_count
//            && base_reference() == rhs.base_reference()
            this->base_reference() == rhs.base_reference()
        ;
    }

    void increment() {
        if(m_count == N){
            m_count = 0;
            return;
        }
        ++m_count;
        ++(this->base_reference());
    }
    CharType dereference() const {
        if(m_count == N)
            return '\n';
        return * (this->base_reference());
    }
    unsigned int m_count;
public:
    // make composible buy using templated constructor
    template<class T>
    insert_linebreaks(T  start) :
        super_t(Base(static_cast< T >(start))),
        m_count(0)
    {}
    // intel 7.1 doesn't like default copy constructor
    insert_linebreaks(const insert_linebreaks & rhs) :
        super_t(rhs.base_reference()),
        m_count(rhs.m_count)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

/* insert_linebreaks.hpp
NQabTDcVniPxGbcbIVZSBpyFXhqBW5wOrD/MgCpwEZtsxiVuOCrplbZ5xmUeK7LeWuKs5N+qxe7eu8wOHMZyDtzcuIDDZWO5ErlRsdXgT+mVahhaAg6X3vQRUVkHjt5quYmzFLdKQXiKnMWVzzh9O8qzTBEQu7DUZZ7JfALH2Uhwg31jAk6Wjp55kkuo7ilWLOHW0Mt0TpZuzqOGc8SF7wiFUbEfz2Q8hS9IgImAzAM0CteqbWRMNy6Xx0OGPzcpHKKkWNtp189MASHB5Yn41pLJXWssl8fZxmkhL643L4oL8focStdyFTvA0In7EIACigzrfQ1jJpQKg1K2DV7GSLfYrMAl+GKCkje+gWc3AmOGOvfoWIEyiBF8rzUQNIAebtbU271z9C+c33MU+7W4VL79Fi5KogHr2/kHO4j1Vv18B4Z+GIy4jXQkG8GzEW3sRpr7wX/BZrBpYhNRKs/vURxglhoezRIGCZ8mC4muQ2n/BeBQowGyrmwUzUa5V0e5YaceG22M4LEv//wHcSXQ0QNTF1wV/t2bUHs9Pxs4knaaBYmEeNkJZUocV660DDdG8RzDJ+JKu01/Y2q5EuexsK3yZGGbesAbTCOxz7IyeMSq7Db5wa+aYNug4G++dJs4Axa4x/JXXiKOApACUwGUh2wbsvhmgpLLN5K7gjeRu5LfT4p8Qoq4JWEJzH1LzH3lJVy6B0/phWfu3c8p
*/