/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ELEMENT_TYPE_HPP
#define BOOST_ALIGN_DETAIL_ELEMENT_TYPE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <cstddef>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::remove_reference;
using std::remove_all_extents;
using std::remove_cv;
#else
template<class T>
struct remove_reference {
    typedef T type;
};

template<class T>
struct remove_reference<T&> {
    typedef T type;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T>
struct remove_reference<T&&> {
    typedef T type;
};
#endif

template<class T>
struct remove_all_extents {
    typedef T type;
};

template<class T>
struct remove_all_extents<T[]> {
    typedef typename remove_all_extents<T>::type type;
};

template<class T, std::size_t N>
struct remove_all_extents<T[N]> {
    typedef typename remove_all_extents<T>::type type;
};

template<class T>
struct remove_cv {
    typedef T type;
};

template<class T>
struct remove_cv<const T> {
    typedef T type;
};

template<class T>
struct remove_cv<volatile T> {
    typedef T type;
};

template<class T>
struct remove_cv<const volatile T> {
    typedef T type;
};
#endif

template<class T>
struct element_type {
    typedef typename remove_cv<typename remove_all_extents<typename
        remove_reference<T>::type>::type>::type type;
};

} /* detail */
} /* alignment */
} /* boost */

#endif

/* element_type.hpp
GsMlEFFFebTrfp6zA/q1nMEMDdnXEF7QNPxHVehV65Dy6oD2X1NfYvYXM2K1/Jj0OxaWrwpz5pR1u1ORkPAAGLIPzG6ishLnE4anr4qSMxluAX+Y+koLfMm4MCAvXDuFwdBgPtR7ifyARpVTfbUzZDo294nC52vFIXpaGhvynOtYs5+9Mp0+Oz63gQNfTL43F2TcYlVRcmu/G5OjOVnlMY9HSZjJKRWa7UWUA7fZWI0mrDxaTEBeQ7VNb8M7z4fbN69k/oVHwfZjRNhTz35oSp38JqmcVhN0sc2gz+m2LHu7Z6YCef6NjblC4VM49cKTzfOIsjt7m67RIGegbdkLpXXrOyvJCmoyJDnS0caCC0wAjJelT5FiYnZmWKCSOBsqTuyxgA3R6PBRlnpo4VjLdeMnbL7BpiVRzSJfhkOrcjejRPJo8CgZkAwCazf0fh4ZdjXJawKzA9I7g8TL7kYlBf7WtaNMtVC7hCJW17loL9WDpcAxJo7+EjesqsgulOKnH6Tsu3xAF/0xfd0QF3fTRlovOn5YFOx9ab0TlPdS4BCO/wm5BAhxVNoW9LMm5RrugM6cipLydhKJaOQ0e/0FxJ22nWMQSbQqGcOlI5WKb5vJH6tGBPwBknzJzr/TlSq8PPGiIvCyfKxN6F/IuRLxofPMCB9tljIRVKm0eCzLd66pgU/ejeUXT9ct4WkfFXEqjHHdTStK/H2kPlUn
*/