/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
ohBxZFUsDAoWC5VItW4OaAR0kigMthjubzhuKm0cD5ng/oU3mdrdHZHZBAQaqwt2RvjyuZaOblglFSwpumHbR+PHL61m4mNMLq0XTzfxK7uRFEn4XWWZZJhPkYSfo7eShGNdAb1dDogbX3QFtjuPQJOaO4QLzhopxzUKq4rJmpP/h1D3r47KtKjR19Y1rNLYJA3XxYJfr+PDSC5egtXs1Jtj+BGtauPM4ZHeTuUBJgAGIdwr/V3kgyeY5pSIdVk=
*/