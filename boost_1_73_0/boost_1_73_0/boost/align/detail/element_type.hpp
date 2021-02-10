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
UuC4PMbarwFLof5oUYNBDNBFcC3D8yGELZNAFFETec/czPPq8OT03dvj8/N355qVFVpBwJ671zM8kRKEdKVbH9gNIuj8QHb9n//0s/sACHyvxZtQ/K8z64hmlPRPOLY3tHSdmGmrj8lano3C+k4gw9BCgUSUkzZSrxt4n4ZI7wwdbUhNrNRl6G56E/tecAF+TTSNkGV0LXOAaXBDHZjk2asxjvrWPIVNmD5EbIW2HmDUOFh+i9gquRlbWU9XxOlBvB2lucwhJU5lQ7b5jbY9kxV4fCFjT9eR1qs07YAybKgEbsX96bDDqrp1v10v7VG+R14P+kJHXv7YGotjLderEmSgKjzTIR0UwZ5F3mg54R/rJTId28rlveDwfWb9CzVj0RvwQZKgyOJdrBHZLpdhgayB6c2q0j6Cf4m9kwz3WHd5LLSzrPTp0TTTRIzsb47w2uhXw5LcReLtSGRixgyFXriRFlsofmGWddanCYGNXKytfpbGHSfpdZHpWJduygc2IW1fofCBEyJ9JS3TBo0jlIsNE6p4V1tkd+ja1NbzVa8ovFP/adLGyTI8WSPAnHkI6FlNu4ChtKK2oVvEPShZXykzVPhIaf8hJ0rfnp9cHr88vDxMii+5yO7vuaKJKVXKTCfdytIrl2evTk6P
*/